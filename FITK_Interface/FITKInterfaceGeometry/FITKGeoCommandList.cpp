#include "FITKGeoCommandList.h"

#include "FITKAbsGeoShapeAgent.h"

namespace Interface
{
    FITKGeoCommandList::FITKGeoCommandList()
    {
        // 创建基准元素管理器。
        m_datumMgr = new FITKDatumList;

        // 初始化重做列表。
        m_redoList = new FITKGeoCommandManager;

        m_globalGeoCompMgr = new FITKGlobalGeoComponentManager;
    }

    FITKGeoCommandList::~FITKGeoCommandList()
    {
        // 析构基准元素管理器。
        if (m_datumMgr)
        {
            delete m_datumMgr;
            m_datumMgr = nullptr;
        }

        // 析构全局几何分组管理器。
        if (m_globalGeoCompMgr)
        {
            delete m_globalGeoCompMgr;
            m_globalGeoCompMgr = nullptr;
        }

        // 析构重做列表。
        if (m_redoList)
        {
            delete m_redoList;
            m_redoList = nullptr;
        }
    }

    QString FITKGeoCommandList::checkName(const QString & name)
    {
        // 检查现存命令列表名称。
        QString newName = this->FITKGeoCommandManager::checkName(name);

        // 检查重做命令列表名称。
        if (m_redoList)
        {
            newName = m_redoList->checkName(newName);
        }

        return newName;
    }

    FITKDatumList* FITKGeoCommandList::getDatumManager()
    {
        return m_datumMgr;
    }

    void FITKGeoCommandList::setCurrentSketchID(int sketchDataId)
    {
        m_currentSketchID = sketchDataId;
    }

    FITKAbsGeoSketch2D* FITKGeoCommandList::getCurrentSketchData()
    {
        // 尝试获取草图数据。
        FITKAbsGeoSketch2D* sData = dynamic_cast<FITKAbsGeoSketch2D*>(this->getDataByID(m_currentSketchID));
        if (!sData)
        {
            m_currentSketchID = -1;
        }

        return sData;
    }

    FITKGlobalGeoComponentManager* FITKGeoCommandList::getGlobalGeoCompManager()
    {
        return m_globalGeoCompMgr;
    }

    bool FITKGeoCommandList::canUndo()
    {
        bool flag = false;

        // 检查是否为草绘模式。
        FITKAbsGeoSketch2D* currSketch = getCurrentSketchData();
        if (currSketch)
        {
            flag = currSketch->canUndo();
        }
        else
        {
            FITKGeoCommandManager* list = this->getUndoList();
            if (!list)
            {
                return false;
            }

            flag = list->getDataCount() != 0;
        }

        return flag;
    }

    bool FITKGeoCommandList::canRedo()
    {
        bool flag = false;

        // 检查是否为草绘模式。
        FITKAbsGeoSketch2D* currSketch = getCurrentSketchData();
        if (currSketch)
        {
            flag = currSketch->canRedo();
        }
        else
        {
            FITKGeoCommandManager* list = this->getRedoList();
            if (!list)
            {
                return false;
            }

            flag = list->getDataCount() != 0;
        }

        return flag;
    }

    bool FITKGeoCommandList::undo()
    {
        bool flag = false;

        // 检查是否为草绘模式。
        FITKAbsGeoSketch2D* currSketch = getCurrentSketchData();
        if (currSketch)
        {
            flag = currSketch->undoInternal();
        }
        else
        {
            int nCmd = this->getDataCount();
            if (nCmd == 0)
            {
                return false;
            }

            // 移动命令。
            FITKAbsGeoCommand* cmd = this->getDataByIndex(nCmd - 1);
            if (!cmd)
            {
                return false;
            }

            cmd->undo();
            this->removeDataObjWithoutRelease(cmd);
            m_redoList->appendDataObj(cmd);

            flag = true;
        }

        return flag;
    }

    bool FITKGeoCommandList::redo()
    {
        bool flag = false;

        // 检查是否为草绘模式。
        FITKAbsGeoSketch2D* currSketch = getCurrentSketchData();
        if (currSketch)
        {
            flag = currSketch->redoInternal();
        }
        else
        {
            if (!m_redoList)
            {
                return false;
            }

            int nCmd = m_redoList->getDataCount();
            if (nCmd == 0)
            {
                return false;
            }

            // 移动命令。
            FITKAbsGeoCommand* cmd = m_redoList->getDataByIndex(nCmd - 1);
            if (!cmd)
            {
                return false;
            }

            cmd->redo();
            m_redoList->removeDataObjWithoutRelease(cmd);

            // 需要跳过清空Redo列表逻辑进行添加。
            FITKGeoCommandManager::appendDataObj(cmd);

            flag = true;
        }

        return flag;
    }

    void FITKGeoCommandList::appendDataObj(Core::FITKAbstractDataObject* obj)
    {
        // 清空重做列表。
        if (m_redoList)
        {
            m_redoList->clear();
        }

        //如果包含则跳出
        if (this->isContains(obj)) return;

        // 执行插入数据。
        FITKGeoCommandManager::appendDataObj(obj);
    }

    void FITKGeoCommandList::getBoundaryBox(double* minPt, double* maxPt)
    {
        //遍历
        const int n = this->getDataCount();
        for (int i = 0; i < n; ++i)
        {
            //h获取模型
            FITKAbsGeoCommand* c = this->getDataByIndex(i);
            if (c == nullptr) continue;
            FITKAbstractGeoModel* m = c->getShapeAgent();
            //最值计算
            double min[3] = { 9e66,9e66,9e66 }, max[3] = { -9e66, -9e66, -9e66 };
            bool hasBds = m->getBoundaryBox(min, max);
            if (!hasBds)
            {
                continue;
            }

            //与现有参数对比判断
            for (int j = 0; j < 3; ++j)
            {
                minPt[j] = minPt[j] < min[j] ? minPt[j] : min[j];
                maxPt[j] = maxPt[j] > max[j] ? maxPt[j] : max[j];
            }
        }
    }

    FITKGeoCommandManager* FITKGeoCommandList::getUndoList()
    {
        // 当前命令列表即为撤销列表。
        return this;
    }

    FITKGeoCommandManager* FITKGeoCommandList::getRedoList()
    {
        return m_redoList;
    }

    QList<FITKAbsGeoCommand*> FITKGeoCommandList::getRootCommandList()
    {
        QList <FITKAbsGeoCommand*> cmdList;

        // 查找所有引用次数为0的命令。
        for (int i = 0; i < this->getDataCount(); i++)
        {
            FITKAbsGeoCommand* cmd = this->getDataByIndex(i);
            if (!cmd)
            {
                continue;
            }

            if (!cmd->getDataValidInGUI())
            {
                continue;
            }

            if (cmd->getReferencedCmdCount() == 0)
            {
                cmdList.push_back(cmd);
            }
        }

        return cmdList;
    }
    QList<int> FITKGeoCommandList::getGlobalDataIDList()
    {
        QList<int> ids;
        ids << this->getDataObjectID();
        //基准
        if (m_datumMgr)
        {
            ids << m_datumMgr->getPrincipalAxis(FITKDatumList::PAT_X)->getDataObjectID();
            ids << m_datumMgr->getPrincipalAxis(FITKDatumList::PAT_Y)->getDataObjectID();
            ids << m_datumMgr->getPrincipalAxis(FITKDatumList::PAT_Z)->getDataObjectID();
            ids << m_datumMgr->getPrincipalPlane(FITKDatumList::PPT_XOY)->getDataObjectID();
            ids << m_datumMgr->getPrincipalPlane(FITKDatumList::PPT_YOZ)->getDataObjectID();
            ids << m_datumMgr->getPrincipalPlane(FITKDatumList::PPT_ZOX)->getDataObjectID();
        }
        return ids;

    }
}
