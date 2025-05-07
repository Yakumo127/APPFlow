/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorOperGeometryCurve.h
 * @brief  HDF5 Adaptor OperGeometryCurve。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-11
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTOROPERGEOMETRYCURVE_H__
#define __FITKINTERFACEHDF5ADAPTOROPERGEOMETRYCURVE_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometryCurve.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoModelCurve);
ForwardDeclarNS(Interface, FITKAbsGeoModelOperLine);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Oper Geometry Curve
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-11
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorOperGeometryCurve : public FITKInterfaceHDF5AdaptorBasicGeometryCurve
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorOperGeometryCurve object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        explicit FITKInterfaceHDF5AdaptorOperGeometryCurve() = default;
        virtual ~FITKInterfaceHDF5AdaptorOperGeometryCurve() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool adaptW() override;

    protected:

        /**
         * @brief 读取操作几何曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 裁剪曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryTrimmedCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 裁剪曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryTrimmedCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 偏移曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readOperGeometryOffsetCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 偏移曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeOperGeometryOffsetCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 线在面上的投影
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryCurveProjectionOnSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 线在面上的投影
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryCurveProjectionOnSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 面和面的交线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometrySurfaceIntersectionSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 面和面的交线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometrySurfaceIntersectionSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 桥接曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryBridgeCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 桥接曲线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryBridgeCurve(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 面的边线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometrySurfaceEdge(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 面的边线
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometrySurfaceEdge(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryOperLineBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 基类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryOperLineBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 合并线数据结构
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryMergeOperLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 合并线数据结构
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryMergeOperLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 线中点分割操作数据结构
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryMiddleOperLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 线中点分割操作数据结构
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryMiddleOperLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 合并线数据结构
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryAngleOperLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 合并线数据结构
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryAngleOperLine(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCurve,                        FITKInterfaceHDF5AdaptorOperGeometryCurve, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelLine,                         FITKInterfaceHDF5AdaptorOperGeometryCurve, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSegment,                      FITKInterfaceHDF5AdaptorOperGeometryCurve, 3)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelWire,                         FITKInterfaceHDF5AdaptorOperGeometryCurve, 4)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelConic,                        FITKInterfaceHDF5AdaptorOperGeometryCurve, 5)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCircle,                       FITKInterfaceHDF5AdaptorOperGeometryCurve, 6)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCircleArc,                    FITKInterfaceHDF5AdaptorOperGeometryCurve, 7)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelThreePointsCircle,            FITKInterfaceHDF5AdaptorOperGeometryCurve, 8)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelEllipse,                      FITKInterfaceHDF5AdaptorOperGeometryCurve, 9)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelEllipseArc,                   FITKInterfaceHDF5AdaptorOperGeometryCurve, 10)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelThreePointsEllipse,           FITKInterfaceHDF5AdaptorOperGeometryCurve, 11)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelHyperbola,                    FITKInterfaceHDF5AdaptorOperGeometryCurve, 12)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelThreePointsHyperbola,         FITKInterfaceHDF5AdaptorOperGeometryCurve, 13)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelHyperbolaArc,                 FITKInterfaceHDF5AdaptorOperGeometryCurve, 14)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelParabola,                     FITKInterfaceHDF5AdaptorOperGeometryCurve, 15)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelThreePointsParabola,          FITKInterfaceHDF5AdaptorOperGeometryCurve, 16)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelParabolaArc,                  FITKInterfaceHDF5AdaptorOperGeometryCurve, 17)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelBeizeByControlPoints,         FITKInterfaceHDF5AdaptorOperGeometryCurve, 18)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelBsplineByThroughPoints,       FITKInterfaceHDF5AdaptorOperGeometryCurve, 19)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelTrimmedCurve,                 FITKInterfaceHDF5AdaptorOperGeometryCurve, 20)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOffsetCurve,                  FITKInterfaceHDF5AdaptorOperGeometryCurve, 21)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCurveProjectionOnSurface,     FITKInterfaceHDF5AdaptorOperGeometryCurve, 22)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSurfaceIntersectionSurface,   FITKInterfaceHDF5AdaptorOperGeometryCurve, 23)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelBridgeCurve,                  FITKInterfaceHDF5AdaptorOperGeometryCurve, 24)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSurfaceEdge,                  FITKInterfaceHDF5AdaptorOperGeometryCurve, 25)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperLine,                     FITKInterfaceHDF5AdaptorOperGeometryCurve, 26)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelMergeOperLine,                FITKInterfaceHDF5AdaptorOperGeometryCurve, 27)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelMiddleOperLine,               FITKInterfaceHDF5AdaptorOperGeometryCurve, 28)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelAngleOperLine,                FITKInterfaceHDF5AdaptorOperGeometryCurve, 29)
}


#endif
