#include "FITKAbsGeoModelPartitionSolid.h" 
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractModel.h"

namespace Interface
{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelPartitionSolidWithDatumPlane::getGeometryCommandType()
    {
        return FITKGeoEnum::FGTPartitionSolidWithDatumPlane;
    }

}
