#include "FITKAbsGeoCommand.h"
#include "FITKAbsGeoShapeAgent.h"
#include "FITKGeoCommandProp.h"
// Global data
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

namespace Interface
{
    FITKAbsGeoCommand::FITKAbsGeoCommand()
    {
        // 创建引用命令管理器。
        m_referenceCmdList = new FITKGeoCommandManager;

        // 创建引用命令管理器。
        m_referencedCmdList = new FITKGeoCommandManager;
        //几何属性
        m_prop = new FITKGeoCommandProp;
    }

    FITKAbsGeoCommand::~FITKAbsGeoCommand()
    {
        // 删除几何属性
        if (m_prop != nullptr) delete m_prop;
        m_prop = nullptr;
        // 删除几何形状代理器
        if (_shapeAgent != nullptr) delete _shapeAgent;
        _shapeAgent = nullptr;

        // 析构引用数据管理器。（不析构管理数据对象）
        if (m_referenceCmdList)
        {
            // 遍历所有引用移除。
            int nRef = m_referenceCmdList->getDataCount();
            for (int i = nRef - 1; i >= 0; i--)
            {
                FITKAbsGeoCommand* cmd = m_referenceCmdList->getDataByIndex(i);
                if (!cmd)
                {
                    continue;
                }

                // 不减少引用对象引用计数并移出列表。
                m_referenceCmdList->removeDataObjWithoutRelease(cmd);
            }

            delete m_referenceCmdList;
            m_referenceCmdList = nullptr;
        }

        // 析构被引用数据管理器。（不析构管理数据对象）
        if (m_referencedCmdList)
        {
            // 遍历所有引用移除。
            int nRef = m_referencedCmdList->getDataCount();
            for (int i = nRef - 1; i >= 0; i--)
            {
                FITKAbsGeoCommand* cmd = m_referencedCmdList->getDataByIndex(i);
                if (!cmd)
                {
                    continue;
                }

                // 不减少引用对象引用计数并移出列表。
                m_referencedCmdList->removeDataObjWithoutRelease(cmd);
            }

            delete m_referencedCmdList;
            m_referencedCmdList = nullptr;
        }
    }

    FITKGeoEnum::FITKGeometryComType FITKAbsGeoCommand::getGeometryCommandType()
    {
        //抽象类，错误值
        return FITKGeoEnum::FGTNone;
    }

    bool FITKAbsGeoCommand::update()
    {
        //错误值
        return false;
    }

    bool FITKAbsGeoCommand::undo()
    {
        // 执行撤销逻辑，将引用数据计数暂时屏蔽。
        if (!m_referenceCmdList)
        {
            return false;
        }

        // 遍历所有引用。
        enableReferenceList(false);

        // 撤销编辑。
        FITKAbsGeoCommand* cmdMod = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_modifiedCmdId);
        if (cmdMod)
        {
            cmdMod->setCommandStatus(FITKGeoEnum::FITKGeoStatus::FGSNormal);
        }

        return true;
    }

    bool FITKAbsGeoCommand::redo()
    {
        // 执行重做逻辑，将引用数据计数恢复。
        if (!m_referenceCmdList)
        {
            return false;
        }

        // 遍历所有引用。
        enableReferenceList(true);

        // 重做编辑。
        FITKAbsGeoCommand* cmdMod = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_modifiedCmdId);
        if (cmdMod)
        {
            cmdMod->setCommandStatus(FITKGeoEnum::FITKGeoStatus::FGSModified);
        }

        return true;
    }

    void FITKAbsGeoCommand::triangleShanpe()
    {
        if (_shapeAgent)
            _shapeAgent->triangulation();
    }

    void FITKAbsGeoCommand::setCommandStatus(FITKGeoEnum::FITKGeoStatus status)
    {
        // 获取命令状态。
        m_status = status;
    }

    FITKGeoEnum::FITKGeoStatus FITKAbsGeoCommand::getCommandStatus()
    {
        return m_status;
    }

    Interface::FITKAbsGeoShapeAgent* FITKAbsGeoCommand::getShapeAgent()
    {
        return _shapeAgent;
    }

    FITKShapeVirtualTopoManager* FITKAbsGeoCommand::getShapeVirtualTopoManager(FITKGeoEnum::VTopoShapeType type)
    {
        if (!_shapeAgent)
        {
            return nullptr;
        }

        // 获取管理器。
        FITKVirtualTopoManager* vTopoMgr = _shapeAgent->getVirtualTopoManager();
        if (!vTopoMgr)
        {
            return nullptr;
        }

        // 获取指定形状虚拓扑管理器。
        return vTopoMgr->getShapeVirtualTopoManager(type);
    }

    Interface::FITKVirtualTopoManager* FITKAbsGeoCommand::getVirtualTopoManager()
    {
        if (!_shapeAgent)
        {
            return nullptr;
        }

        return _shapeAgent->getVirtualTopoManager();
    }

    FITKAbsVirtualTopo* FITKAbsGeoCommand::getVirtualTopoByIndex(FITKGeoEnum::VTopoShapeType type, int index)
    {
        FITKVirtualTopoManager* tMgr = getVirtualTopoManager();
        if (!tMgr)
        {
            return nullptr;
        }

        // 获取形状虚拓扑管理器。
        FITKShapeVirtualTopoManager* vsMgr = tMgr->getShapeVirtualTopoManager(type);
        if (!vsMgr)
        {
            return nullptr;
        }

        return vsMgr->getDataByIndex(index);
    }

    QList<FITKAbsVirtualTopo*> FITKAbsGeoCommand::getVirtualToposByIndice(FITKGeoEnum::VTopoShapeType type, QList<int> indice)
    {
        QList<FITKAbsVirtualTopo*> topos;
        FITKVirtualTopoManager* tMgr = getVirtualTopoManager();
        if (!tMgr)
        {
            return topos;
        }

        // 获取形状虚拓扑管理器。
        FITKShapeVirtualTopoManager* vsMgr = tMgr->getShapeVirtualTopoManager(type);
        if (!vsMgr)
        {
            return topos;
        }

        for (const int & index : indice)
        {
            FITKAbsVirtualTopo* topo = vsMgr->getDataByIndex(index);
            if (topo)
            {
                topos.push_back(topo);
            }
        }

        return topos;
    }

    void FITKAbsGeoCommand::enableReferenceList(bool flag)
    {
        if (flag && !m_enableRefer)
        {
            int nRef = m_referenceCmdList->getDataCount();
            for (int i = nRef - 1; i >= 0; i--)
            {
                FITKAbsGeoCommand* cmd = m_referenceCmdList->getDataByIndex(i);
                if (!cmd)
                {
                    continue;
                }

                // 增加引用对象引用计数。
                cmd->addReferencedCmdObj(this);
            }
        }
        else if (!flag && m_enableRefer)
        {
            int nRef = m_referenceCmdList->getDataCount();
            for (int i = nRef - 1; i >= 0; i--)
            {
                FITKAbsGeoCommand* cmd = m_referenceCmdList->getDataByIndex(i);
                if (!cmd)
                {
                    continue;
                }

                // 移除引用对象引用计数。
                cmd->removeReferencedCmdObj(this);
            }
        }

        // 保存状态。
        m_enableRefer = flag;
    }

    bool FITKAbsGeoCommand::getEnableReferenceList()
    {
        return m_enableRefer;
    }

    void FITKAbsGeoCommand::addReferenceCmdID(int id)
    {
        // 获取需要添加引用的命令数据对象。
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(id);
        addReferenceCmdObj(cmd);
    }

    void FITKAbsGeoCommand::addReferenceCmdObj(FITKAbsGeoCommand* cmd, bool isSet)
    {
        if (!cmd || !m_referenceCmdList)
        {
            return;
        }

        // 为目标对象添加引用关系。
        cmd->addReferencedCmdObj(this);

        // 判断数据是否已被引用。
        bool contains = m_referenceCmdList->isContains(cmd);
        if (contains)
        {
            return;
        }

        // 存储引用对象。
        m_referenceCmdList->appendDataObj(cmd);
    }

    void FITKAbsGeoCommand::removeReferenceCmdID(int id)
    {
        // 获取需要移除引用的命令数据对象。
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(id);
        removeReferenceCmdObj(cmd);
    }

    void FITKAbsGeoCommand::removeReferenceCmdObj(FITKAbsGeoCommand* cmd)
    {
        if (!cmd || !m_referenceCmdList)
        {
            return;
        }

        // 判断数据是否被引用。
        bool contains = m_referenceCmdList->isContains(cmd);
        if (!contains)
        {
            return;
        }

        // 从目标对象移除引用关系。
        cmd->removeReferencedCmdObj(this);

        // 移除引用对象。
        m_referenceCmdList->removeDataObjWithoutRelease(cmd);
    }

    void FITKAbsGeoCommand::clearReference()
    {
        if (!m_referenceCmdList)
        {
            return;
        }

        // 遍历所有引用移除。
        int nRef = m_referenceCmdList->getDataCount();
        for (int i = nRef - 1; i >= 0; i--)
        {
            FITKAbsGeoCommand* cmd = m_referenceCmdList->getDataByIndex(i);
            if (!cmd)
            {
                continue;
            }

            // 减少引用对象引用计数并移出列表。
            m_referenceCmdList->removeDataObjWithoutRelease(cmd);
            cmd->removeReferencedCmdObj(this);
        }
    }

    int FITKAbsGeoCommand::getReferenceCmdCount()
    {
        if (!m_referenceCmdList)
        {
            return 0;
        }

        // 获取引用命令列表长度。
        return m_referenceCmdList->getDataCount();
    }

    FITKAbsGeoCommand* FITKAbsGeoCommand::getReferenceCmdByIndex(int index)
    {
        if (!m_referenceCmdList)
        {
            return nullptr;
        }

        // 返回第i条命令。
        return m_referenceCmdList->getDataByIndex(index);
    }

    int FITKAbsGeoCommand::getReferencedCmdCount()
    {
        if (!m_referencedCmdList)
        {
            return 0;
        }

        // 获取被引用命令列表长度。
        return m_referencedCmdList->getDataCount();
    }

    FITKAbsGeoCommand* FITKAbsGeoCommand::getReferencedCmdByIndex(int index)
    {
        if (!m_referencedCmdList)
        {
            return nullptr;
        }

        // 返回第i条命令。
        return m_referencedCmdList->getDataByIndex(index);
    }

    void FITKAbsGeoCommand::addReferencedCmdID(int id)
    {
        // 获取需要添加引用的命令数据对象。
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(id);
        addReferencedCmdObj(cmd);
    }

    void FITKAbsGeoCommand::addReferencedCmdObj(FITKAbsGeoCommand* cmd)
    {
        if (!cmd || !m_referencedCmdList)
        {
            return;
        }

        // 判断数据是否已被引用。
        bool contains = m_referencedCmdList->isContains(cmd);
        if (contains)
        {
            return;
        }

        // 存储引用对象。
        m_referencedCmdList->appendDataObj(cmd);
    }

    void FITKAbsGeoCommand::removeReferencedCmdID(int id)
    {
        // 获取需要移除的被引用命令数据对象。
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(id);
        removeReferencedCmdObj(cmd);
    }

    void FITKAbsGeoCommand::removeReferencedCmdObj(FITKAbsGeoCommand* cmd)
    {
        if (!cmd || !m_referencedCmdList)
        {
            return;
        }

        // 判断数据是否被引用。
        bool contains = m_referencedCmdList->isContains(cmd);
        if (!contains)
        {
            return;
        }

        // 移除引用对象。
        m_referencedCmdList->removeDataObjWithoutRelease(cmd);
    }

    bool FITKAbsGeoCommand::getDataValidInGUI()
    {
        // 被移除、被修改或者删除命令无需显示。
        if (this->getCommandStatus() == Interface::FITKGeoEnum::FITKGeoStatus::FGSDeleted ||
            this->getCommandStatus() == Interface::FITKGeoEnum::FITKGeoStatus::FGSModified ||
            this->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTDelete ||
            this->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTMultiDelete)
        {
            return false;
        }

        return true;
    }

    void FITKAbsGeoCommand::setModifiedCmdID(int id)
    {
        // 检查数据ID并保存。
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(id);
        if (cmd)
        {
            m_modifiedCmdId = id;
        }
    }

    int FITKAbsGeoCommand::getModifiedCmdID()
    {
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_modifiedCmdId);
        if (!cmd)
        {
            m_modifiedCmdId = -1;
        }

        return m_modifiedCmdId;
    }

    bool FITKAbsGeoCommand::hasModifiedCommand()
    {
        // 被编辑命令不为空则为编辑命令。
        FITKAbsGeoCommand* cmd = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_modifiedCmdId);
        return cmd != nullptr;
    }

    QList<FITKAbsGeoCommand*> FITKAbsGeoCommand::getDownStreamCommands()
    {
        // 递归向上查询。
        QList<FITKAbsGeoCommand*> cmdList;
        getRefCmdRecursively(this, cmdList, true);
        return cmdList;
    }

    QList<FITKAbsGeoCommand*> FITKAbsGeoCommand::getUpStreamCommands()
    {
        // 递归向下查询。
        QList<FITKAbsGeoCommand*> cmdList;
        getRefCmdRecursively(this, cmdList, false);
        return cmdList;
    }

    QList<int> FITKAbsGeoCommand::getCreatedCommandIds()
    {
        // 默认仅返回自身数据ID。
        QList<int> ids;
        ids.push_back(this->getDataObjectID());
        return ids;
    }

    void FITKAbsGeoCommand::getRefCmdRecursively(FITKAbsGeoCommand* cmd, QList<FITKAbsGeoCommand*> & cmdList, bool downStream)
    {
        if (!cmd)
        {
            return;
        }

        cmdList.push_back(cmd);

        // 获取引用对象数据。
        if (downStream)
        {
            int nRefed = cmd->getReferencedCmdCount();
            for (int i = 0; i < nRefed; i++)
            {
                Interface::FITKAbsGeoCommand* subCmd = cmd->getReferencedCmdByIndex(i);
                if (!subCmd)
                {
                    continue;
                }

                // 递归查询。
                getRefCmdRecursively(subCmd, cmdList, downStream);
            }
        }
        else
        {
            int nRef = cmd->getReferenceCmdCount();
            for (int i = 0; i < nRef; i++)
            {
                Interface::FITKAbsGeoCommand* subCmd = cmd->getReferenceCmdByIndex(i);
                if (!subCmd)
                {
                    continue;
                }

                // 递归查询。
                getRefCmdRecursively(subCmd, cmdList, downStream);
            }
        }
    }

    QList<FITKAbsGeoCommand*> FITKGeoCommandManager::getRootCommands()
    {
        QList<FITKAbsGeoCommand*> cmdList;
        for (int i = 0; i < this->getDataCount(); i++)
        {
            FITKAbsGeoCommand* subCmd = this->getDataByIndex(i);
            if (subCmd->getReferencedCmdCount() != 0)
            {
                continue;
            }

            FITKAbsGeoShapeAgent* shapeAgent = subCmd->getShapeAgent();
            if (!shapeAgent)
            {
                continue;
            }

            if (shapeAgent->isValid())
            {
                cmdList.push_back(subCmd);
            }
        }

        return cmdList;
    }

    bool FITKGeoCommandManager::addAndUpdate(Interface::FITKAbsGeoCommand* subCmd)
    {
        if (!subCmd)
        {
            return false;
        }

        // 先添加至子命令列表。
        this->appendDataObj(subCmd);

        // 尝试刷新数据。
        bool flag = subCmd->update();
        if (!flag)
        {
            // 刷新失败则将命令从列表中移除。
            this->removeDataObjWithoutRelease(subCmd);
        }

        return flag;
    }
}
