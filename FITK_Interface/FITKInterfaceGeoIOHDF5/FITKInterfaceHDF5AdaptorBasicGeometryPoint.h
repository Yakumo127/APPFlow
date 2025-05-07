/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorBasicGeometryPoint.h
 * @brief  HDF5 Adaptor BasicGeometryPoint。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYPOINT_H__
#define __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYPOINT_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoModelPoint);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Point
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-09
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorBasicGeometryPoint : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorBasicGeometryPoint object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        explicit FITKInterfaceHDF5AdaptorBasicGeometryPoint() = default;
        virtual ~FITKInterfaceHDF5AdaptorBasicGeometryPoint() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool adaptW() override;

    protected:

        /**
         * @brief 读取基础几何点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryPointBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryPointBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 曲线的端点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryCurveEnd(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 曲线的端点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryCurveEnd(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 距离曲线的端点指定距离
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryCurveEndDistance(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 距离曲线的端点指定距离
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryCurveEndDistance(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 指定曲线比例创建点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryCurveRadio(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 指定曲线比例创建点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryCurveRadio(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 点在线上的投影
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryProjectionOnCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 点在线上的投影
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryProjectionOnCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 两条线的交点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryTwoCurveIntersection(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 两条线的交点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryTwoCurveIntersection(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 点在面上的投影
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryPointProjectionOnSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 点在面上的投影
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryPointProjectionOnSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何点 线和面的交点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readBasicGeometryCurveIntersectionSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何点 线和面的交点
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeBasicGeometryCurveIntersectionSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelPoint, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCurveEndDistance, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCurveEnd, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 3)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCurveRadio, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 4)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelPointProjectionOnCurve, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 5)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelTwoCurveIntersection, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 6)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelPointProjectionOnSurface, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 7)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCurveIntersectionSurface, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 8)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelInteractionPoint, FITKInterfaceHDF5AdaptorBasicGeometryPoint, 9)
}


#endif
