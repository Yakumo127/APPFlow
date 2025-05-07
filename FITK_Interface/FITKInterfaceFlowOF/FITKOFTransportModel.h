/**********************************************************************
 * @file   FITKOFTransportModel.h
 * @brief  TransportModel数据接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-23
 *********************************************************************/
#ifndef _FITK_OF_TRANSPORT_MODEL__H___
#define _FITK_OF_TRANSPORT_MODEL__H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"

namespace Core
{
    class FITKParameter;
}

namespace Interface
{
    class FITKInterfaceFlowOFAPI FITKAbsOFTransportModel : public Core::FITKAbstractNDataObject
    {
    public:
        explicit FITKAbsOFTransportModel();
        virtual ~FITKAbsOFTransportModel();

        

        /**
         * @brief    获取参数
         * @return   Core::FITKParameter *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-23
         */
        Core::FITKParameter* getTransportModelPara();

    protected:
        virtual void initTransportModelParam() = 0;

    protected:
        Core::FITKParameter* _transModelPara{};
    };

    class FITKInterfaceFlowOFAPI FITKOFTransModelNewtonian : public FITKAbsOFTransportModel
    {
    public:
        explicit FITKOFTransModelNewtonian();
        virtual ~FITKOFTransModelNewtonian();

    protected:
        virtual void initTransportModelParam() override;
    };
}


#endif
