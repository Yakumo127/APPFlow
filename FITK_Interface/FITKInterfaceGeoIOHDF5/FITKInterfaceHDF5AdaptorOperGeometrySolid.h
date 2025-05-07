/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorOperGeometrySolid.h
 * @brief  HDF5 Adaptor OperGeometrySolid。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef __FITKINTERFACEHDF5ADAPTOROPERGEOMETRYSOLID_H__
#define __FITKINTERFACEHDF5ADAPTOROPERGEOMETRYSOLID_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometrySolid.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoModelOperImprintSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelChamferSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelFilletSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelDefeatureSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelRemoveChamferSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelRemoveFilletSolid);
ForwardDeclarNS(Interface, FITKAbsGeoModelFillHoleSolid);
ForwardDeclarNS(Interface, FITKAbsGeoStiffener);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Oper Geometry Solid
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-10
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorOperGeometrySolid : public FITKInterfaceHDF5AdaptorBasicGeometrySolid
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorOperGeometrySolid object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        explicit FITKInterfaceHDF5AdaptorOperGeometrySolid() = default;
        virtual ~FITKInterfaceHDF5AdaptorOperGeometrySolid() = default;

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
         * @brief   读取基础几何体
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolid(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolid(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 倒角抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidChamfer(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 倒角抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidChamfer(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 倒圆抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidFillet(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 倒圆抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidFillet(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 删除倒角抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidRemoveChamfer(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 删除倒角抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidRemoveChamfer(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 删除倒圆抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidRemoveFillet(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 删除倒圆抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidRemoveFillet(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 特征移除抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidDefeature(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 特征移除抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidDefeature(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 填补孔洞抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidFillHole(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 填补孔洞抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidFillHole(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 基类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 基类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 封闭曲面形成的体
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidClosedSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 封闭曲面形成的体
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidClosedSurface(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 拉伸实体抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidExtrude(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 拉伸实体抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidExtrude(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 旋转实体抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidRevol(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 旋转实体抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidRevol(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 扫略体抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidSweep(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 扫略体抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidSweep(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 多截面扫略抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool readOperGeometrySolidMultiSection(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 多截面扫略抽象类
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        bool writeOperGeometrySolidMultiSection(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   读取基础几何体 肋板
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-10-16
         */
        bool readOperGeometrySolidStiffener(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief   写出基础几何体 肋板
         * @param   comm 几何命令
         * @param   h5Group 数据块
         * @return  状态 true成功， false失败
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-10-16
         */
        bool writeOperGeometrySolidStiffener(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelBox, FITKInterfaceHDF5AdaptorOperGeometrySolid, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSphere, FITKInterfaceHDF5AdaptorOperGeometrySolid, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCylinder, FITKInterfaceHDF5AdaptorOperGeometrySolid, 3)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelChamferSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 4)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelFilletSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 5)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelDefeatureSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 6)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRemoveChamferSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 7)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRemoveFilletSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 8)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelFillHoleSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 9)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelClosedSurfaceSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 10)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelExtrudeSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 11)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRevolSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 12)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelSweepSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 13)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelMultiSectionSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 14)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoStiffener, FITKInterfaceHDF5AdaptorOperGeometrySolid, 15)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTBox, FITKInterfaceHDF5AdaptorOperGeometrySolid, 16)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTSphere, FITKInterfaceHDF5AdaptorOperGeometrySolid, 17)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTCylinder, FITKInterfaceHDF5AdaptorOperGeometrySolid, 18)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTChamferSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 19)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTRemoveChamfer, FITKInterfaceHDF5AdaptorOperGeometrySolid, 20)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTFilletSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 21)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTRemoveFillet, FITKInterfaceHDF5AdaptorOperGeometrySolid, 22)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTDefeature, FITKInterfaceHDF5AdaptorOperGeometrySolid, 23)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTFillHole, FITKInterfaceHDF5AdaptorOperGeometrySolid, 24)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTClosedSurfaceSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 25)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTExtrudeSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 26)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTRevolSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 27)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTSweepSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 28)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTMultiSectionSolid, FITKInterfaceHDF5AdaptorOperGeometrySolid, 29)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTStiffener, FITKInterfaceHDF5AdaptorOperGeometrySolid, 30)


}


#endif
