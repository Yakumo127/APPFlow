#ifndef _FITKABSTRACT_PAEAM_WIDGET_H___
#define _FITKABSTRACT_PAEAM_WIDGET_H___
 
#include "FITKEasyParamAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractGUI.h"

namespace Core
{
    class FITKEasyParamAPI FITKAbstractEasyParamWidget
    {
    public:
        explicit FITKAbstractEasyParamWidget();
        virtual ~FITKAbstractEasyParamWidget() = default;
    };
}
#endif
