#include "FITKOFGeometryData.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

namespace Interface
{
    FITKOFGeometryData* FITKOFGeometryData::getGeometryDataFromFrame()
    {
        if (FITKAPP == nullptr) return nullptr;
        return FITKAPP->getGlobalData()->getGeometryData<FITKOFGeometryData>();
    }
}


