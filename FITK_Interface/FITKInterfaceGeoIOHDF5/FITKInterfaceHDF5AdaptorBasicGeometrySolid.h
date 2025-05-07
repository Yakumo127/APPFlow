/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorBasicGeometrySolid.h
 * @brief  HDF5 Adaptor BasicGeometrySolid。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYSOLID_H__
#define __FITKINTERFACEHDF5ADAPTORBASICGEOMETRYSOLID_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoShapeAgent);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoModelBox);
ForwardDeclarNS(Interface, FITKAbsGeoModelSphere);
ForwardDeclarNS(Interface, FITKAbsGeoModelCylinder);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Solid
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-10
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorBasicGeometrySolid : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorBasicGeometrySolid object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        explicit FITKInterfaceHDF5AdaptorBasicGeometrySolid() = default;
        virtual ~FITKInterfaceHDF5AdaptorBasicGeometrySolid() = default;

    protected:

        /**
         * @brief 读取基础几何体 Box
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readOperGeometrySolidBox(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何体 Box
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeOperGeometrySolidBox(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何体 Box
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readOperGeometrySolidSphere(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何体 Box
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeOperGeometrySolidSphere(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取基础几何体 Box
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool readOperGeometrySolidCylinder(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出基础几何体 Box
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        bool writeOperGeometrySolidCylinder(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);
    };
}


#endif
