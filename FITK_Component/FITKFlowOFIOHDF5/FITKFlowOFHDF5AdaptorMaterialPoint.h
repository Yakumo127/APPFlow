﻿/**********************************************************************
 * @file   FITKFlowOFHDF5AdaptorMaterialPoint.h
 * @brief  HDF5文件材料点读写接口适配器 
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-09
 *********************************************************************/
#ifndef __FITKFLOWOFHDF5ADAPTORCMATERIALPOINT_R_H__
#define __FITKFLOWOFHDF5ADAPTORCMATERIALPOINT_R_H__

#include "FITKFlowOFIOHDF5API.h"
#include "FITKFlowOFHDF5AbstractAdaptor.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

 //前置声明
ForwardDeclarNS(Interface, FITKZonePoint)

namespace IO
{
    /**
     * @brief HDF5 Geometry 读写适配器
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-05-30
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFHDF5AdaptorMaterialPoint : public FITKFlowOFHDF5AbstractAdaptor
    {
    public:
        explicit FITKFlowOFHDF5AdaptorMaterialPoint() = default;
        ~FITKFlowOFHDF5AdaptorMaterialPoint() = default;

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
        /**
         * @brief  几何数据对象
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-09
         */
        Interface::FITKZonePoint* _pointData{};
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKZonePoint, FITKFlowOFHDF5AdaptorMaterialPoint)
}


#endif // !1

