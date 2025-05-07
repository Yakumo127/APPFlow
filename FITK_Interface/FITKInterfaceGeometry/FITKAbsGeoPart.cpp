#include "FITKAbsGeoPart.h" 

// Global data
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

namespace Interface
{
    // 获取数据类型。
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoPart::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTPart;
    }

    bool FITKAbsGeoPart::backtrackingShape()
    {
        return false;
    }

    bool FITKAbsGeoPart::update()
    {
        return true;
    }
}