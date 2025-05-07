/**********************************************************************
 * @file   FITKOFRunControl.h
 * @brief  求解器运行配置
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-31
 *********************************************************************/
#ifndef _FITK_OF_RUN_CONTROL__H___
#define _FITK_OF_RUN_CONTROL__H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"

namespace Core
{
    class FITKParameter;
}

namespace Interface
{

    class FITKInterfaceFlowOFAPI FITKOFRunControl : public Core::FITKAbstractNDataObject
    {
        Q_OBJECT
            FITKCLASS(Interface, FITKOFRunControl);
    public:
        explicit FITKOFRunControl();
        virtual ~FITKOFRunControl();

        Core::FITKParameter* getTimeControl();
        Core::FITKParameter* getOutputControl();

    private:
        Core::FITKParameter* _timeControl{};
        Core::FITKParameter* _outputControl{};
    };
}


#endif
