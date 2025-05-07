﻿/**********************************************************************
 * @file   FITKFlowOFHDF5AdaptorRunControl.h
 * @brief  hdf5 物理场运行配置读写接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-13
 *********************************************************************/
#ifndef __FITKFLOWOFHDF5ADAPTORRUNCONTROL_R_H__
#define __FITKFLOWOFHDF5ADAPTORRUNCONTROL_R_H__

#include "FITKFlowOFIOHDF5API.h"
#include "FITKFlowOFHDF5AbstractAdaptor.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

 //前置声明
ForwardDeclarNS(Interface, FITKOFRunControl)

namespace IO
{
    /**
     * @brief HDF5 Geometry 读写适配器
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-05-30
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFHDF5AdaptorRunControl : public FITKFlowOFHDF5AbstractAdaptor
    {
    public:
        explicit FITKFlowOFHDF5AdaptorRunControl() = default;
        ~FITKFlowOFHDF5AdaptorRunControl() = default;

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
        bool timeControlW();
        bool timeControlR();
        bool outputControlW();
        bool outputControlR();

    private:
        /**
         * @brief  物理场材料数据
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-09
         */
        Interface::FITKOFRunControl* _runControl{};
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKOFRunControl, FITKFlowOFHDF5AdaptorRunControl)
}


#endif // !1

