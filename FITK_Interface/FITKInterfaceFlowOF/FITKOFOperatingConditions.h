/**********************************************************************
 * @file   FITKOFOperatingConditions.h
 * @brief  算例工作条件 接口声明
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-04
 *********************************************************************/
#ifndef _FITK_OF_OPERATINGCONDITIONS__H___
#define _FITK_OF_OPERATINGCONDITIONS__H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"

namespace Core
{
    class FITKParameter;
}

namespace Interface
{

    class FITKInterfaceFlowOFAPI FITKOFOperatingConditions : public Core::FITKAbstractNDataObject
    {
        Q_OBJECT
            FITKCLASS(Interface, FITKOFOperatingConditions);
    public:
        explicit FITKOFOperatingConditions();
        virtual ~FITKOFOperatingConditions();
        /**
         * @brief    获取引力与加速度条件参数
         * @return   Core::FITKParameter *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-04
         */
        Core::FITKParameter* getGravitationalAcceleration();

        Core::FITKParameter* getReferencePressure();

        void initGravitationalAcceleration();

        void initReferencePressure();

    private:
        /**
         * @brief  引力与加速度条件
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-04
         */
        Core::FITKParameter* _gravitationalAcceleration{};
        /**
         * @brief  参考压力配置
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-04
         */
        Core::FITKParameter* _referencePressure{};
    };
}


#endif
