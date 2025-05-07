/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorBasicGeometryCurve.h
 * @brief  HDF5 Adaptor BasicGeometryCurve。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-11
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYCURVE_H__
#define __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYCURVE_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Curve
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-11
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorBasicGeometryCurve : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorBasicGeometryCurve object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        explicit FITKInterfaceHDF5AdaptorBasicGeometryCurve() = default;
        virtual ~FITKInterfaceHDF5AdaptorBasicGeometryCurve() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        QString getAdaptorClass() override;

    protected:

        /**
         * @brief 读取基础几何线基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readBasicGeometryCurveBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何线基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryCurveBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何圆锥基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryCurveConicBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何圆锥基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryCurveConicBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometrySegment(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometrySegment(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryWire(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryWire(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何圆锥曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryConic(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何圆锥曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryConic(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryCircle(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryCircle(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 圆弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryCircleArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 圆弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryCircleArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 三点圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryThreePointsCircle(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 三点圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryThreePointsCircle(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 椭圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryEllipse(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 椭圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryEllipse(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 椭圆弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryEllipseArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 椭圆弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryEllipseArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 三点椭圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryThreePointsEllipse(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 三点椭圆
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryThreePointsEllipse(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 双曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryHyperbola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 双曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryHyperbola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 三点双曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryThreePointsHyperbola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 三点双曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryThreePointsHyperbola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 双曲线弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryHyperbolaArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 双曲线弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryHyperbolaArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 抛物线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryParabola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 抛物线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryParabola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 三点双曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryThreePointsParabola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 三点双曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryThreePointsParabola(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 抛物线弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryParabolaArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 抛物线弧
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryParabolaArc(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 贝塞尔曲线(控制点)
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryBeizeByControlPoints(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 贝塞尔曲线(控制点)
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryBeizeByControlPoints(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何 B样条(通过线上的点)
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readBasicGeometryBsplineByThroughPoints(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何 B样条(通过线上的点)
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeBasicGeometryBsplineByThroughPoints(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

    };
}


#endif
