/**********************************************************************
 * @file   FITKFlowOFHDF5AdaptorTurbulence.h
 * @brief  hdf5 物理场湍流模型接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-18
 *********************************************************************/
#ifndef __FITKFLOWOFHDF5ADAPTORTURBULENCE_R_H__
#define __FITKFLOWOFHDF5ADAPTORTURBULENCE_R_H__

#include "FITKFlowOFIOHDF5API.h"
#include "FITKFlowOFHDF5AbstractAdaptor.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

 //前置声明
ForwardDeclarNS(Interface, FITKAbstractOFTurbulence)

namespace IO
{
    /**
     * @brief  物理场湍流读写接口 hdf5
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-09-18
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFHDF5AdaptorTurbulence : public FITKFlowOFHDF5AbstractAdaptor
    {
    public:
        explicit FITKFlowOFHDF5AdaptorTurbulence() = default;
        ~FITKFlowOFHDF5AdaptorTurbulence() = default;

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

    private:
        bool turbulenceParaW();
        bool turbulenceParaR();
        bool deltaW();
        bool deltaR();

    private:
        /**
         * @brief  物理场材料数据
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-09
         */
        Interface::FITKAbstractOFTurbulence* _turbulence{};
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbstractOFTurbulence, FITKFlowOFHDF5AdaptorTurbulence)
}


#endif // !1

