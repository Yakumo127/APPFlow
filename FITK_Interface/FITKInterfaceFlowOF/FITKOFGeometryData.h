#ifndef _FITKOFGEOMETRYDATA__H__
#define _FITKOFGEOMETRYDATA__H__

#include "FITKInterfaceFlowOFAPI.h" 
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"

namespace Interface
{
    class FITKInterfaceFlowOFAPI FITKOFGeometryData :  
         public FITKGeoCommandList
    {
    public:
        explicit FITKOFGeometryData() = default;
        virtual ~FITKOFGeometryData() = default;

        static FITKOFGeometryData* getGeometryDataFromFrame();
    
    };
}


#endif
