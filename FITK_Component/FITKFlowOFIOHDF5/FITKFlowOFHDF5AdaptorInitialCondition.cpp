#include "FITKFlowOFHDF5AdaptorInitialCondition.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFInitialConditions.h"

#include "FITK_Interface/FITKInterfaceFlowOF/FITKFlowPhysicsHandlerFactory.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"

//数据层
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"



#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorInitialCondition::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorInitialCondition";
    }

    bool FITKFlowOFHDF5AdaptorInitialCondition::adaptR()
    {
        _initialCond = dynamic_cast<Interface::FITKOFInitialConditions*>(_dataObj);
        if (!_reader || !_initialCond) return false;
        if (!readNDataObject(_initialCond, *_h5Group)) return false;
        bool isR = true;

        isR &= basicDataR();
        isR &= patchDataR();

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorInitialCondition::adaptW()
    {
        _initialCond = dynamic_cast<Interface::FITKOFInitialConditions*>(_dataObj);
        if (!_writer || !_initialCond) return false;
        if (!writeNDataObject(_initialCond, *_h5Group)) return false;
        bool isW = true;

        isW &= basicDataW();
        isW &= patchDataW();

        return isW;
    }

    bool FITKFlowOFHDF5AdaptorInitialCondition::basicDataW()
    {
        if (!_writer || !_initialCond) return false;
        H5::Group h5Group = _h5Group->createGroup("Basic");
        if (_initialCond->getBasicData())
            parameterToolW(h5Group, _initialCond->getBasicData());
        return true;
    }

    bool FITKFlowOFHDF5AdaptorInitialCondition::basicDataR()
    {
        if (!_reader || !_initialCond)return false;
        if (!_h5Group->nameExists("Basic"))return false;
        H5::Group h5Group = _h5Group->openGroup("Basic");
        if (h5Group.getNumAttrs() > 0)
        {
            Core::FITKParameter* limits = _initialCond->getBasicData();
            if (!limits) return false;
            limits->clear();
            parameterToolR(h5Group, limits);
        }
        return true;
    }

    bool FITKFlowOFHDF5AdaptorInitialCondition::patchDataW()
    {
        if (!_writer || !_initialCond)return false;
        H5::Group h5Group = _h5Group->createGroup("Patchs");
        int count = _initialCond->getPatchCount();
        writeIntAttribute(h5Group, "PatchCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFGeometryPatch* patchData = _initialCond->getPatch(i);
            if (!patchData) continue;
            std::string name = std::to_string(i);
            H5::Group patchH5Group = h5Group.createGroup(name);
            //几何id
            int geometryId = patchData->getGeometryId();
            writeIntAttribute(patchH5Group, "geometryId", &geometryId);
            //类型
            int applyType = patchData->getAppltTo();
            writeIntAttribute(patchH5Group, "ApplyToType", &applyType);
            //场数据
            Core::FITKParameter* fieldPara = patchData->getFieldPara();
            if (fieldPara) parameterToolW(patchH5Group, fieldPara);
        }
        return true;
    }

    bool FITKFlowOFHDF5AdaptorInitialCondition::patchDataR()
    {
        if (!_reader || !_initialCond)return false;
        if (!_h5Group->nameExists("Patchs"))return false;
        H5::Group h5Group = _h5Group->openGroup("Patchs");
        int count = readIntAttribute(h5Group, "PatchCount");
        //清空数据
        for (int i = 0; i < count; ++i)
            _initialCond->removePatch(i);
        //读取数据并设置
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.nameExists(name))continue;
            H5::Group patchH5Group = h5Group.openGroup(name);
            //几何id
            int geometryId = readIntAttribute(patchH5Group, "geometryId");
            //类型
            int applyType = readIntAttribute(patchH5Group, "ApplyToType");
            //场数据
            Interface::FITKOFGeometryPatch* patchData = new Interface::FITKOFGeometryPatch(geometryId, Interface::FITKOFSolverInitialEnum::FITKPatchApplyObjectType(applyType));
            parameterToolR(patchH5Group, patchData->getFieldPara());
            _initialCond->appendPatch(patchData);
        }
        return true;
    }

}
