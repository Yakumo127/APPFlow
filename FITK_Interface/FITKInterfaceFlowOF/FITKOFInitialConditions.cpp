#include "FITKOFInitialConditions.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

namespace Interface
{
    FITKOFGeometryPatch::FITKOFGeometryPatch(int geoId, FITKOFSolverInitialEnum::FITKPatchApplyObjectType type)
    {
        _fieldPara = new Core::FITKParameter;
        //设置组件
        _geometryId = geoId;
        _applyType = type;
    }

    FITKOFGeometryPatch::~FITKOFGeometryPatch()
    {
        if (_fieldPara) delete _fieldPara;
    }

    int FITKOFGeometryPatch::getGeometryId()
    {
        //获取组件Id
        return _geometryId;
    }

    Interface::FITKAbsGeoCommand* FITKOFGeometryPatch::getGeometryModel()
    {
        //获取几何数据对象
        return FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(_geometryId);
    }

    Core::FITKParameter* FITKOFGeometryPatch::getFieldPara()
    {
        return _fieldPara;
    }

    FITKOFSolverInitialEnum::FITKPatchApplyObjectType FITKOFGeometryPatch::getAppltTo()
    {
        return _applyType;
    }

    FITKOFInitialConditions::FITKOFInitialConditions()
    {
        _basic = new Core::FITKParameter;
    }

    FITKOFInitialConditions::~FITKOFInitialConditions()
    {
        if (_basic) delete _basic;
        for (FITKOFGeometryPatch* pat : _patchs)
        {
            if (pat) delete pat;
        }
    }

    Core::FITKParameter* FITKOFInitialConditions::getBasicData()
    {
        return _basic;
    }

    int FITKOFInitialConditions::getPatchCount()
    {
        return _patchs.size();
    }

    FITKOFGeometryPatch* FITKOFInitialConditions::getPatch(int index)
    {
        if (index < 0 || index >= _patchs.size())return nullptr;
        return _patchs.at(index);
    }

    void FITKOFInitialConditions::appendPatch(FITKOFGeometryPatch* patch)
    {
        if (!patch)return;
        _patchs.append(patch);
    }

    void FITKOFInitialConditions::removePatch(int index)
    {
        FITKOFGeometryPatch* patch = this->getPatch(index);
        if (patch)
        {
            _patchs.removeAt(index);
            delete patch;
        }
    }
}
