/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorCommand.h
 * @brief  HDF5 Adaptor Command。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-11
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTORCOMMAND_H__
#define __FITKINTERFACEHDF5ADAPTORCOMMAND_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
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
    * @date 2024-09-11
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorCommand : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorCommand object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-11
         */
        explicit FITKInterfaceHDF5AdaptorCommand() = default;
        virtual ~FITKInterfaceHDF5AdaptorCommand() = default;

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
         * @brief 读取
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool read(Interface::FITKAbsGeoCommand* comm, H5::Group & h5Group);
        /**
         * @brief 写出
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool write(Interface::FITKAbsGeoCommand* comm, H5::Group & h5Group);

        /**
         * @brief 读取命令
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool readCommand(Interface::FITKAbsGeoCommand* comm, H5::Group & h5Group);

        /**
         * @brief 写出命令
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool writeCommand(Interface::FITKAbsGeoCommand* comm, H5::Group & h5Group);

        /**
         * @brief 读取子对象虚拓扑
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool readChildVirtualShape(Interface::FITKAbsGeoCommand* comm, H5::Group & h5Group, bool isSaveShape = false);

        /**
         * @brief 写出子对象虚拓扑
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool writeChildVirtualShape(Interface::FITKAbsGeoCommand* comm, H5::Group & h5Group, bool isSaveShape = false);

        /**
         * @brief 读取虚拓扑形状
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool readVShape(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group) = 0;

        /**
         * @brief 写出虚拓扑形状
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-10
         */
        virtual bool writeVShape(Interface::FITKAbsGeoShapeAgent* agent, H5::Group & h5Group) = 0;

    };
}

#endif
