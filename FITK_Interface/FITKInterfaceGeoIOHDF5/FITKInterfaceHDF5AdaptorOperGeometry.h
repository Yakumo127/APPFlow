/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorOperGeometry.h
 * @brief  HDF5 Adaptor OperGeometry。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-11
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTOROPERGEOMETRY_H__
#define __FITKINTERFACEHDF5ADAPTOROPERGEOMETRY_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoDelete);
ForwardDeclarNS(Interface, FITKAbsGeoMultiDelete);
ForwardDeclarNS(Interface, FITKAbsGeoOperBool);
ForwardDeclarNS(Interface, FITKAbsGeoModelOperImprintSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelImport);
ForwardDeclarNS(Interface, FITKAbsGeoModelExport);
ForwardDeclarNS(Interface, FITKAbsGeoModelOperCompound);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Solid
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-11
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorOperGeometry : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorOperGeometry object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        explicit FITKInterfaceHDF5AdaptorOperGeometry() = default;
        virtual ~FITKInterfaceHDF5AdaptorOperGeometry() = default;

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
         * @brief 读取操作几何
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 删除
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryDelete(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 删除
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryDelete(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 多选删除
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-10-30
         */
        bool readOperGeometryMultiDelete(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 多选删除
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-10-30
         */
        bool writeOperGeometryMultiDelete(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 布尔
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool readOperGeometryBool(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 布尔
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        bool writeOperGeometryBool(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 抽象压印体操作类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool readOperGeometryOperImprintSolid(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 抽象压印体操作类
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool writeOperGeometryOperImprintSolid(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 导入
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool readOperGeometryOperImport(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 导入
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool writeOperGeometryOperImport(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 导出
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool readOperGeometryOperExport(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 导出
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool writeOperGeometryOperExport(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 读取操作几何 复合体操作抽象类 添加或删除
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool readOperGeometryOperCompoundBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出操作几何 复合体操作抽象类 添加或删除
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-13
         */
        bool writeOperGeometryOperCompoundBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

    };
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoDelete,                FITKInterfaceHDF5AdaptorOperGeometry, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoMultiDelete,           FITKInterfaceHDF5AdaptorOperGeometry, 7)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoOperBool,              FITKInterfaceHDF5AdaptorOperGeometry, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperImprintSolid, FITKInterfaceHDF5AdaptorOperGeometry, 3)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelImport,           FITKInterfaceHDF5AdaptorOperGeometry, 4)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelExport,           FITKInterfaceHDF5AdaptorOperGeometry, 5)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelOperCompound,     FITKInterfaceHDF5AdaptorOperGeometry, 6)
}


#endif
