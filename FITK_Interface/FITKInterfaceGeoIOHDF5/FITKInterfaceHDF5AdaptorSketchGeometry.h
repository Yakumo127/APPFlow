/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorSketchGeometry.h
 * @brief  HDF5 Adaptor OperGeometry。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-19
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5AdaptorSketchGeometry_H__
#define __FITKINTERFACEHDF5AdaptorSketchGeometry_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoSketch2D);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Basic Geometry Solid
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-19
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorSketchGeometry : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorSketchGeometry object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-19
         */
        explicit FITKInterfaceHDF5AdaptorSketchGeometry() = default;
        virtual ~FITKInterfaceHDF5AdaptorSketchGeometry() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-19
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-19
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-19
         */
        bool adaptW() override;

    protected:

        /**
         * @brief 读取草绘
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-19
         */
        bool readSketchGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 写出草绘
         * @param comm 几何命令
         * @param h5Group 数据块
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-19
         */
        bool writeSketchGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief 根据枚举名称实例化该类 GeoModel
         * @param enumName 枚举转换的字符串名称
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        Core::FITKAbstractNDataObject* getGeoCommand(QString enumName);

    };
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoSketch2D, FITKInterfaceHDF5AdaptorSketchGeometry, 1)
}


#endif
