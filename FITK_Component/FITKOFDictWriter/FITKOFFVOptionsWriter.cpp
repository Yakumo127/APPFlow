#include "FITKOFFVOptionsWriter.h"
#include "FITKDictObject.h"
#include "FITKDictArray.h"
#include "FITKDictGroup.h"
#include "FITKDictVector.h"
#include "FITKDictValue.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFSolution.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamBoolGroup.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamCombox.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDouble.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFSolver.h"
#include <QFileInfo>
#include <QtMath>
//命名空间
namespace IO
{
    FITKOFFVOptionsWriter::FITKOFFVOptionsWriter()
    {
    }
    FITKOFFVOptionsWriter::~FITKOFFVOptionsWriter()
    {
    }

    void FITKOFFVOptionsWriter::setFilePath(const QString& filePath)
    {
        FITKOFAbstractDictWriter::setFilePath(filePath);
        QFileInfo fileInfo(filePath);
        //判断是否是路径
        if (!fileInfo.isDir())return;
        m_fileName = QString("%1/system/fvOptions").arg(filePath);
    }

    bool FITKOFFVOptionsWriter::run()
    {
        //判断文件是否存在
        if (m_fileName.isEmpty())return false;
        //获取字典工程
        this->openDictObject();
        if (!m_objectDict)return false;
        //写出FoamFile
        this->dictObjectFoamFile();
        //设置写出的网格区域数据
        bool Ok = this->fvOptionsWrite();
        //写出字典文件
        if (Ok)
            Ok = this->writeDictFile();

        //关闭字典工程
        this->closeDictObject();
        return Ok;
    }

    QString FITKOFFVOptionsWriter::getFileName()
    {
        return m_fileName;
    }

    void FITKOFFVOptionsWriter::dictObjectFoamFile()
    {
        if (!m_objectDict)return;
        //FoamFile
        DICT::FITKDictGroup* group = new DICT::FITKDictGroup;
        group->append("version", 2.0);
        group->append("format", "ascii");
        group->append("class", "dictionary");
        group->append("location", "\"system\"");
        group->append("object", "fvOptions");
        m_objectDict->append("FoamFile", group);
    }

    bool FITKOFFVOptionsWriter::fvOptionsWrite()
    {
        if (!m_objectDict) return false;
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取离散数据
        Interface::FITKOFSolution* solutionData = physicsData->getSolution();
        if (!solutionData)return false;
        Core::FITKParameter* limits = solutionData->getLimits();
        if (!limits)return false;
        Core::FITKParamBoolGroup* velocityLimit = dynamic_cast<Core::FITKParamBoolGroup*>(limits->getDataByName("Velocity Damping"));
        if (velocityLimit && velocityLimit->getValue())
        {
            DICT::FITKDictGroup* vL = new DICT::FITKDictGroup;
            m_objectDict->append("velocityLimit", vL);
            vL->append("active", true);
            vL->append("type", "limitVelocity");
            DICT::FITKDictGroup* limitVelocityCoeffs = new DICT::FITKDictGroup;
            vL->append("limitVelocityCoeffs", limitVelocityCoeffs);
            Core::FITKParameter* vaGroup = velocityLimit->getValueGroup();
            if (!vaGroup)return false;
            bool ok = false;
            double v = vaGroup->getDoubleParaByName("Umax", ok);
            if (!ok)return false;
            limitVelocityCoeffs->append("max", v);
            limitVelocityCoeffs->append("selectionMode", "all");
            limitVelocityCoeffs->append("U", "U");
        }
        return true;
    }
}



