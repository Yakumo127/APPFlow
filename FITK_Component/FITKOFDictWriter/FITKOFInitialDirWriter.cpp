#include "FITKOFInitialDirWriter.h"
#include "FITKDictObject.h"
#include "FITKDictArray.h"
#include "FITKDictGroup.h"
#include "FITKDictVector.h"
#include "FITKDictValue.h"
#include "FITKOFChangeDictionaryDictW.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundary.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundaryType.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFInitialConditions.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamRadioGroup.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamBool.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamCombox.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDouble.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDoubleList.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFSolver.h"
#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredFluidMeshVTK.h"
#include <QFileInfo>
#include <QtMath>
//命名空间
namespace IO
{
    FITKOFInitialDirWriter::FITKOFInitialDirWriter()
    {
        m_boundaryTool = new FITKOFChangeDictionaryDictW;
    }
    FITKOFInitialDirWriter::~FITKOFInitialDirWriter()
    {
        if (!m_boundaryTool) delete m_boundaryTool;
    }

    void FITKOFInitialDirWriter::setFilePath(const QString& filePath)
    {
        FITKOFAbstractDictWriter::setFilePath(filePath);
        QFileInfo fileInfo(filePath);
        //判断是否是路径
        if (!fileInfo.isDir())return;
        m_fileName = m_filePath;
    }

    bool FITKOFInitialDirWriter::run()
    {
        //判断文件是否存在
        if (m_fileName.isEmpty())return false;
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取initial
        Interface::FITKOFInitialConditions* initialCond = physicsData->getInitialConditions();
        if (!initialCond)return false;
        Core::FITKParameter* vPara = initialCond->getBasicData();
        for (int i = 0; i < vPara->getDataCount(); ++i)
        {
            Core::FITKAbstractEasyParam* d = vPara->getDataByIndex(i);
            if (!d)continue;
            QString vName = d->getDataObjectName();
            m_fileName = QString("%1/0/%2").arg(m_filePath).arg(vName);
            //打开字典工程
            this->openDictObject();
            if (!m_objectDict)return false;
            //设置写出的网格区域数据
            bool Ok = this->initialFileWrite(vName, d);
            //写出字典文件
            if (Ok)
                Ok = this->writeDictFile();
            //关闭字典工程
            this->closeDictObject();
        }
        return true;
    }

    QString FITKOFInitialDirWriter::getFileName()
    {
        return m_fileName;
    }

    void FITKOFInitialDirWriter::dictObjectFoamFile(QString vName)
    {
        if (!m_objectDict)return;
        //FoamFile
        DICT::FITKDictGroup* group = new DICT::FITKDictGroup;
        group->append("version", 2.0);
        group->append("format", "ascii");
        if (vName == "U")
            group->append("class", "volVectorField");
        else
            group->append("class", "volScalarField");
        group->append("location", "\"0\"");
        group->append("object", vName);
        group->append("arch", "\"LSB;label=32;scalar=64\"");
        m_objectDict->append("FoamFile", group);
    }

    bool FITKOFInitialDirWriter::initialFileWrite(QString vName, Core::FITKAbstractEasyParam* vPara)
    {
        if (!m_objectDict) return false;
        //写出FoamFile
        this->dictObjectFoamFile(vName);
        bool ok = this->dimensionsW(vName);
        if (!ok)return false;
        QString value;
        Core::FITKAbstractEasyParam::FITKEasyParamType type = vPara->getParamType();
        if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDouble)
        {
            Core::FITKParamDouble * p = dynamic_cast<Core::FITKParamDouble*>(vPara);
            if (p) value = QString("uniform %1").arg(p->getValue());
        }
        else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDoubleList)
        {
            Core::FITKParamDoubleList * p = dynamic_cast<Core::FITKParamDoubleList*>(vPara);
            if (p)
            {
                QStringList vlist;
                for (int i = 0; i < p->getCount(); ++i)
                    vlist.append(QString::number(p->getValue(i)));
                value = QString("uniform (%1)").arg(vlist.join(' '));
            }
        }
        if (value.isEmpty())return false;
        m_objectDict->append("internalField", value);
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取离散数据
        Interface::FITKOFBoundaryManager* boundaryMgr = physicsData->getBoundaryManager();
        if (!boundaryMgr)return false;
        int count = boundaryMgr->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFBoundary* boundary = boundaryMgr->getDataByIndex(i);
            if (!boundary)continue;
            //获取boundaryField
            DICT::FITKDictGroup* boundaryField = nullptr;
            DICT::FITKDictValue* boundF = m_objectDict->value("boundaryField");
            if (!boundF)
            {
                boundaryField = new DICT::FITKDictGroup;
                m_objectDict->append("boundaryField", boundaryField);
            }
            else
                boundaryField = boundF->toGroup(ok);
            if (!boundaryField)continue;
            Interface::FITKBoundaryMeshVTK* boundaryMesh = boundary->getMeshBoundary();
            if (!boundaryMesh)return false;
            DICT::FITKDictGroup* boundaryG = new DICT::FITKDictGroup;
            boundaryField->append(boundaryMesh->getDataObjectName(), boundaryG);
            Interface::FITKOFAbsBoundaryType* para = boundary->getBoundary(vName);
            if (!para)
            {
                boundaryG->append("type", "calculated");
                boundaryG->append("value", value);
            }
            if (m_boundaryTool)
                m_boundaryTool->paraBTyW(para, boundaryG, vName);
            if (vName.contains("alpha"))
            {
                DICT::FITKDictValue* v = boundaryG->value("phi");
                if (v)
                {
                    boundaryG->removeKey("phi");
                    boundaryG->append("value", value);
                }
            }
        }
        return true;
    }

    bool FITKOFInitialDirWriter::dimensionsW(QString vName)
    {
        if (!m_objectDict) return false;
        if (vName == "p")
            m_objectDict->append("dimensions", "[0 2 -2 0 0 0 0]");
        else if (vName == "U")
            m_objectDict->append("dimensions", "[0 1 -1 0 0 0 0]");
        else if (vName == "omega")
            m_objectDict->append("dimensions", "[0 0 -1 0 0 0 0]");
        else if (vName == "k")
            m_objectDict->append("dimensions", "[0 2 -2 0 0 0 0]");
        else if (vName == "nut")
            m_objectDict->append("dimensions", "[0 2 -1 0 0 0 0]");
        else if (vName.contains("alpha"))
            m_objectDict->append("dimensions", "[0 0 0 0 0 0 0]");
        else if (vName == "p_rgh")
            m_objectDict->append("dimensions", "[1 -1 -2 0 0 0 0]");
        return true;
    }
}



