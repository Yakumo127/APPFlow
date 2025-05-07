/**********************************************************************
 * @file   FITKFlowOFHDF5AdaptorRegionMesh.h
 * @brief  hdf5区域网格读写接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-10
 *********************************************************************/
#ifndef __FITKFLOWOFHDF5ADAPTORREGIONMESH_R_H__
#define __FITKFLOWOFHDF5ADAPTORREGIONMESH_R_H__

#include "FITKFlowOFIOHDF5API.h"
#include "FITKFlowOFHDF5AbstractAdaptor.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

 //前置声明
ForwardDeclarNS(Interface, FITKAbstractRegionMeshSize)

namespace IO
{
    /**
     * @brief HDF5 Geometry 读写适配器
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-05-30
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFHDF5AdaptorRegionMesh : public FITKFlowOFHDF5AbstractAdaptor
    {
    public:
        explicit FITKFlowOFHDF5AdaptorRegionMesh() = default;
        ~FITKFlowOFHDF5AdaptorRegionMesh() = default;

        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-30
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-30
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-30
         */
        bool adaptW() override;

    private:
        bool regionGeometryW(H5::Group& h5Group);
        bool regionGeometryR(H5::Group& h5Group);
        bool regionBoxW(H5::Group& h5Group);
        bool regionBoxR(H5::Group& h5Group);
        bool regionCylinderW(H5::Group& h5Group);
        bool regionCylinderR(H5::Group& h5Group);
        bool regionSphereW(H5::Group& h5Group);
        bool regionSphereR(H5::Group& h5Group);


    private:
        /**
         * @brief  几何数据对象
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-09
         */
        Interface::FITKAbstractRegionMeshSize* _regionMeshData{};
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbstractRegionMeshSize, FITKFlowOFHDF5AdaptorRegionMesh)
}


#endif // !1

