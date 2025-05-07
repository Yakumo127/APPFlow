#include "FITKAbsGeoModelCurve.h" 
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractModel.h"
#include "FITKAbsGeoReferenceLine.h"

namespace Interface
{
    FITKGeoEnum::FITKDatumType FITKAbsGeoReferenceSegment::getDatumType()
    {
        return FITKGeoEnum::FITKDatumType::FDTLine;
    }
}
