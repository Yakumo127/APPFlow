#ifndef _FITK_EASY_PARAM_FACTORY_H___
#define _FITK_EASY_PARAM_FACTORY_H___

#include "FITKEasyParamAPI.h" 
#include "FITKAbstractEasyParam.h"

namespace Core
{
    class FITKAbstractEasyParam;

    class FITKEasyParamAPI FITKEasyParamFactory

    {
    public:
        static FITKAbstractEasyParam* createParam(FITKAbstractEasyParam::FITKEasyParamType type);
   
    private:
        explicit FITKEasyParamFactory() = default;
        virtual ~FITKEasyParamFactory() = default;
    };
 
}


#endif
