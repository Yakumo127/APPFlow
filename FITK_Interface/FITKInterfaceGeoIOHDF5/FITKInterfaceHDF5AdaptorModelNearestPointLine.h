/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorNearestPointLine.h
 * @brief  HDF5 Adaptor Nearest Point Line。
 * @date   2025-03-27
 * @author libaojun
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORNEARESTPOINTLINE_H__
#define __FITKINTERFACEHDF5ADAPTORNEARESTPOINTLINE_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

namespace IO
{
    /**
    * @brief HDF5 Adaptor Nearest Point Line
    * @date 2025-03-27
    * @author libaojun
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorNearestPointLine : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorNearestPointLine object
         * @date 2025-03-27
         * @author libaojun
         */
        explicit FITKInterfaceHDF5AdaptorNearestPointLine() = default;
        virtual ~FITKInterfaceHDF5AdaptorNearestPointLine() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @date 2025-03-27
         * @author libaojun
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @date 2025-03-27
         * @author libaojun
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @date 2025-03-27
         * @author libaojun
         */
        bool adaptW() override;
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelNearestPointLine, FITKInterfaceHDF5AdaptorNearestPointLine)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTNearestPointLine, FITKInterfaceHDF5AdaptorNearestPointLine, 2)
}

#endif

