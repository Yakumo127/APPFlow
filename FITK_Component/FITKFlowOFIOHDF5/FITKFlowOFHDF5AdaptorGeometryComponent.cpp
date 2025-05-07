#include "FITKFlowOFHDF5AdaptorGeometryComponent.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorCommand.h"
#include "FITK_Component/FITKGeoOCCIOHDF5/FITKOCCHDF5AdaptorCommand.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoShapeAgent.h"
#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"

//数据层
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"



#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorGeometryComponent::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorGeometryComponent";
    }

    bool FITKFlowOFHDF5AdaptorGeometryComponent::adaptR()
    {
        Interface::FITKAbsGeoCommand* geoCommand = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !geoCommand) return false;
        Interface::FITKAbsGeoShapeAgent* geoModel = geoCommand->getShapeAgent();
        if (!geoModel)return false;
        //获取组件管理器
        _geoComponentMgr = geoModel->getGeoComponentManager();
        bool isR = true;

        int count = readIntAttribute(*_h5Group, "componentCount");
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!_h5Group->attrExists(name))continue;
            if (!_h5Group->nameExists(name))continue;
            int type = readIntAttribute(*_h5Group, name);
            H5::Group h5Group = _h5Group->openGroup(name);
            Interface::FITKGeoComponent* component = new Interface::FITKGeoComponent(Interface::FITKModelEnum::FITKModelSetType(type));
            isR &= this->geoComponentR(component, h5Group);
            _geoComponentMgr->appendDataObj(component);
        }

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorGeometryComponent::adaptW()
    {
        Interface::FITKAbsGeoCommand* geoCommand = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !geoCommand) return false;
        Interface::FITKAbsGeoShapeAgent* geoModel = geoCommand->getShapeAgent();
        if (!geoModel)return false;
        //获取组件管理器
        _geoComponentMgr = geoModel->getGeoComponentManager();
        bool isW = true;
        int count = _geoComponentMgr->getDataCount();
        writeIntAttribute(*_h5Group, "componentCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKGeoComponent* component = _geoComponentMgr->getDataByIndex(i);
            if (!component)continue;
            int type = component->getGeoType();
            std::string name = std::to_string(i);
            writeIntAttribute(*_h5Group, name, &type);
            H5::Group h5Group = _h5Group->createGroup(name);
            isW &= this->geoComponentW(component, h5Group);
        }
        return isW;
    }

    bool FITKFlowOFHDF5AdaptorGeometryComponent::geoComponentW(Interface::FITKGeoComponent* component, H5::Group& h5Group)
    {
        if (!component)return false;
        if (!writeNDataObject(component, h5Group))return false;
        int absModelId = component->getAbsModelID();
        writeIntAttribute(h5Group, "absModelID", &absModelId);
        QList<int> allMember = component->getMember();
        writeIntDataSet(h5Group, "member", allMember);
        return true;
    }
    bool FITKFlowOFHDF5AdaptorGeometryComponent::geoComponentR(Interface::FITKGeoComponent* component, H5::Group& h5Group)
    {
        if (!component)return false;
        if (!readNDataObject(component, h5Group))return false;
        int absModelId = readIntAttribute(h5Group, "absModelID");
        component->setModel(absModelId);
        QList<int> allMember;
        readIntDataSet(h5Group, "member", allMember);
        component->setMember(allMember);
        return true;
    }
}
