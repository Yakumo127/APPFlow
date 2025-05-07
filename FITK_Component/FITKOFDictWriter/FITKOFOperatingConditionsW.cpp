#include "FITKOFOperatingConditionsW.h"
#include "FITKDictObject.h"
#include "FITKDictArray.h"
#include "FITKDictGroup.h"
#include "FITKDictVector.h"
#include "FITKDictValue.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFOperatingConditions.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFRunControl.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDouble.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDoubleList.h"
#include <QFileInfo>
#include <QtMath>
//命名空间
namespace IO
{
    FITKOFOperatingConditionsW::FITKOFOperatingConditionsW()
    {
    }
    FITKOFOperatingConditionsW::~FITKOFOperatingConditionsW()
    {
    }

    void FITKOFOperatingConditionsW::setFilePath(const QString& filePath)
    {
        FITKOFAbstractDictWriter::setFilePath(filePath);
        QFileInfo fileInfo(filePath);
        //判断是否是路径
        if (!fileInfo.isDir())return;
        m_fileName = filePath;
    }

    bool FITKOFOperatingConditionsW::run()
    {
        //判断文件是否存在
        if (m_fileName.isEmpty())return false;
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        m_physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!m_physicsData)return false;
        this->gravitationalFileW();
        this->accelerationFileW();
        return true;
    }

    QString FITKOFOperatingConditionsW::getFileName()
    {
        return m_fileName;
    }

    bool FITKOFOperatingConditionsW::gravitationalFileW()
    {
        if (!m_physicsData)return false;
        //获取initial
        Interface::FITKOFOperatingConditions* operatingCond = m_physicsData->getOperatingConditions();
        if (!operatingCond)return false;
        Core::FITKParameter* gaData = operatingCond->getGravitationalAcceleration();
        if (!gaData)return false;
        Core::FITKParamDoubleList* gPara = dynamic_cast<Core::FITKParamDoubleList*>(gaData->getDataByName("g [m/s2]"));
        if (!gPara)return false;
        m_fileName = QString("%1/constant/g").arg(m_filePath);
        //获取重力数据
        int count = gPara->getCount();
        QStringList valueList;
        for (int i = 0; i < count; ++i)
            valueList.append(QString::number(gPara->getValue(i)));
        if (valueList.size() != 3)return false;
        //获取字典工程
        this->openDictObject();
        if (!m_objectDict)return false;
        //写出FoamFile
        DICT::FITKDictGroup* group = new DICT::FITKDictGroup;
        group->append("version", 2.0);
        group->append("format", "ascii");
        group->append("class", "uniformDimensionedVectorField");
        group->append("location", "\"constant\"");
        group->append("object", "g");
        m_objectDict->append("FoamFile", group);
        //设置重力数据
        m_objectDict->append("dimensions", "[0 1 -2 0 0 0 0]");
        m_objectDict->append("value", QString("(%1)").arg(valueList.join(' ')));
        //写出字典文件
        this->writeDictFile();

        //关闭字典工程
        this->closeDictObject();
        return true;
    }

    bool FITKOFOperatingConditionsW::accelerationFileW()
    {
        if (!m_physicsData)return false;
        //获取initial
        Interface::FITKOFOperatingConditions* operatingCond = m_physicsData->getOperatingConditions();
        if (!operatingCond)return false;
        Core::FITKParameter* gaData = operatingCond->getGravitationalAcceleration();
        if (!gaData)return false;
        Core::FITKParamDouble* hrefPara = dynamic_cast<Core::FITKParamDouble*>(gaData->getDataByName("href [m]"));
        if (!hrefPara)return false;
        m_fileName = QString("%1/constant/hRef").arg(m_filePath);
        //获取重力数据
        double value = hrefPara->getValue();
        //获取字典工程
        this->openDictObject();
        if (!m_objectDict)return false;
        //写出FoamFile
        DICT::FITKDictGroup* group = new DICT::FITKDictGroup;
        group->append("version", 2.0);
        group->append("format", "ascii");
        group->append("class", "uniformDimensionedScalarField");
        group->append("location", "\"constant\"");
        group->append("object", "hRef");
        m_objectDict->append("FoamFile", group);
        //设置重力数据
        m_objectDict->append("dimensions", "[0 1 0 0 0 0 0]");
        m_objectDict->append("value", value);
        //写出字典文件
        this->writeDictFile();

        //关闭字典工程
        this->closeDictObject();
        return true;
    }
}



