/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorDatum.h
 * @brief  HDF5 Adaptor Command。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-14
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORDATUM_H__
#define __FITKINTERFACEHDF5ADAPTORDATUM_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITKInterfaceHDF5AdaptorGeoCommand.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoDatum);
ForwardDeclarNS(Interface, FITKAbsGeoReferencePlane);
ForwardDeclarNS(Interface, FITKAbsGeoShapeAgent);

ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Command
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-14
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorDatum : public FITKInterfaceHDF5AdaptorGeoCommand
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorDatum object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-14
         */
        explicit FITKInterfaceHDF5AdaptorDatum() = default;
        virtual ~FITKInterfaceHDF5AdaptorDatum() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-14
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-14
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-14
         */
        bool adaptW() override;

    protected:

        /**
         * @brief 读取基准 基类
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumBase(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 基类
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumBase(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准 点
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumPoint(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 基类
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumPoint(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准 线
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumLine(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 线
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumLine(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准 面
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 线
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准 偏移线
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumOffsetPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 偏移线
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumOffsetPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准 三点面
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumThreePointsPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 三点面
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumThreePointsPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准 方程面
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatumEquationPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准 方程面
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatumEquationPlane(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 读取基准
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool readDatum(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);

        /**
         * @brief 写出基准
         * @param datum 基准面
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-18
         */
        virtual bool writeDatum(Interface::FITKAbsGeoDatum* datum, H5::Group & h5Group);
    };
}

#endif
