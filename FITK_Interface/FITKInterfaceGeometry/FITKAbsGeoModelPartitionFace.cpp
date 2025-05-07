#include "FITKAbsGeoModelPartitionFace.h" 
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractModel.h"

namespace Interface
{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelPartitionFaceWithSketch::getGeometryCommandType()
    {
        return FITKGeoEnum::FGTPartitionFaceWithSketch;
    }

    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelPartitionFaceWithTwoPoints::getGeometryCommandType()
    {
        return FITKGeoEnum::FGTPartitionFaceWithTwoPoints;
    }

}
