/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorOperGeometryFace.h
 * @brief  HDF5 Adaptor OperGeometryFace。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-13
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTOROPERGEOMETRYFACE_H__
#define __FITKINTERFACEHDF5ADAPTOROPERGEOMETRYFACE_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometryFace.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoModelSurface);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoModelOperFace);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Face
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-13
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorOperGeometryFace : public FITKInterfaceHDF5AdaptorBasicGeometryFace
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorOperGeometryFace object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        explicit FITKInterfaceHDF5AdaptorOperGeometryFace() = default;
        virtual ~FITKInterfaceHDF5AdaptorOperGeometryFace() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool adaptW() override;

    protected:

        /**
         * @brief 读取基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readOperGeometryFace(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeOperGeometryFace(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readOperGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何面
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeOperGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何面 抽象面操作类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readOperGeometryOperFaceBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何面 抽象面操作类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeOperGeometryOperFaceBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何面 填补缝隙
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readOperGeometryOperFaceFillGaps(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何面 填补缝隙
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeOperGeometryOperFaceFillGaps(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何面 填补孔洞
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readOperGeometryOperFaceFillHoles(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何面 填补孔洞
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeOperGeometryOperFaceFillHoles(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何面 删除悬浮边
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool readOperGeometryOperFaceDeleteFloatingEdge(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何面 删除悬浮边
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-12
         */
        bool writeOperGeometryOperFaceDeleteFloatingEdge(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSurface,                      FITKInterfaceHDF5AdaptorOperGeometryFace, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelClosedWireSurface,            FITKInterfaceHDF5AdaptorOperGeometryFace, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOffsetSurface,                FITKInterfaceHDF5AdaptorOperGeometryFace, 3)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelExtrudeSurface,               FITKInterfaceHDF5AdaptorOperGeometryFace, 4)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRevolSurface,                 FITKInterfaceHDF5AdaptorOperGeometryFace, 5)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRectangularTrimmedSurface,    FITKInterfaceHDF5AdaptorOperGeometryFace, 6)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSweepSurface,                 FITKInterfaceHDF5AdaptorOperGeometryFace, 7)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelMultiSectionSurface,          FITKInterfaceHDF5AdaptorOperGeometryFace, 8)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelBridgeSurface,                FITKInterfaceHDF5AdaptorOperGeometryFace, 9)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSolidSurface,                 FITKInterfaceHDF5AdaptorOperGeometryFace, 10)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFace,                     FITKInterfaceHDF5AdaptorOperGeometryFace, 11)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFaceRemoveFace,           FITKInterfaceHDF5AdaptorOperGeometryFace, 12)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFaceExtendFace,           FITKInterfaceHDF5AdaptorOperGeometryFace, 13)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFaceRepairFaces,          FITKInterfaceHDF5AdaptorOperGeometryFace, 14)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFaceFillGaps,             FITKInterfaceHDF5AdaptorOperGeometryFace, 15)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFaceFillHoles,            FITKInterfaceHDF5AdaptorOperGeometryFace, 16)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperFaceDeleteFloatingEdge,   FITKInterfaceHDF5AdaptorOperGeometryFace, 17)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTBridgeSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 3)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTSurfaceFromSolid, FITKInterfaceHDF5AdaptorOperGeometryFace, 4)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTMultiSectionSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 5)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTSweepSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 6)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTRevolSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 7)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTExtrudeSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 8)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTOffsetSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 9)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTClosedWireSurface, FITKInterfaceHDF5AdaptorOperGeometryFace, 10)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTFillGapsFace, FITKInterfaceHDF5AdaptorOperGeometryFace, 11)


}


#endif
