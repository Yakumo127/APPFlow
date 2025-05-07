/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorBasicGeometryFace.h
 * @brief  HDF5 Adaptor BasicGeometryFace。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYFACE_H__
#define __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYFACE_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoModelSurface);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Face
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-09
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorBasicGeometryFace : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorBasicGeometryFace object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        explicit FITKInterfaceHDF5AdaptorBasicGeometryFace() = default;
        virtual ~FITKInterfaceHDF5AdaptorBasicGeometryFace() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        QString getAdaptorClass() override;

    protected:

        /**
         * @brief 读取基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryFace(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryFace(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryFaceBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryFaceBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryClosedWireSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryClosedWireSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 偏移曲面抽象类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryOffsetSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 偏移曲面抽象类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryOffsetSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 拉伸曲面抽象类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryExtrudeSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 拉伸曲面抽象类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryExtrudeSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 旋转曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryRevolSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 旋转曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryRevolSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 修剪曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 修剪曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 扫略曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometrySweepSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 扫略曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometrySweepSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 多截面扫略
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryMultiSectionSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 多截面扫略
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryMultiSectionSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 桥接曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryBridgeSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 桥接曲面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometryBridgeSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何面 体的面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometrySolidSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面 体的面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeBasicGeometrySolidSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);
    };
}


#endif
