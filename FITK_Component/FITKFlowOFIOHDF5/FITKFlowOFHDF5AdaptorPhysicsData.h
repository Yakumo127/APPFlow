/**********************************************************************
 * @file   FITKFlowOFHDF5AdaptorPhysicsData.h
 * @brief  hdf5求解物理数据
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-11
 *********************************************************************/
#ifndef __FITKFLOWOFHDF5ADAPTORPHYSICSDATA_R_H__
#define __FITKFLOWOFHDF5ADAPTORPHYSICSDATA_R_H__

#include "FITKFlowOFIOHDF5API.h"
#include "FITKFlowOFHDF5AbstractAdaptor.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

 //前置声明
ForwardDeclarNS(Interface, FITKOFPhysicsData)

namespace IO
{
    /**
     * @brief HDF5 Geometry 读写适配器
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-05-30
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFHDF5AdaptorPhysicsData : public FITKFlowOFHDF5AbstractAdaptor
    {
    public:
        explicit FITKFlowOFHDF5AdaptorPhysicsData() = default;
        ~FITKFlowOFHDF5AdaptorPhysicsData() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-30
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-30
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-30
         */
        bool adaptW() override;

    protected:
        bool physicsSolverW();
        bool physicsSolverR();
        bool physicsTurbulenceW();
        bool physicsTurbulenceR();
        bool physicsTransportPropW();
        bool physicsTransportPropR();
        bool physicsDiscretizationW();
        bool physicsDiscretizationR();
        bool physicsSolutionW();
        bool physicsSolutionR();
        bool physicsInitialConditionsW();
        bool physicsInitialConditionsR();
        bool physicsBoundaryW();
        bool physicsBoundaryR();
        bool physicsRunControlW();
        bool physicsRunControlR();
        bool physicsOperatingConditionsW();
        bool physicsOperatingConditionsR();

    private:
        /**
         * @brief  物理数据对象
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-09
         */
        Interface::FITKOFPhysicsData* _physicsData{};
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKOFPhysicsData, FITKFlowOFHDF5AdaptorPhysicsData)
}


#endif // !1

