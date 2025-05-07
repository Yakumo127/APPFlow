/**
 *
 * @file FITKOFMeshSizeGenerator.h
 * @brief 网格尺寸生成器声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-07-18
 *
 */
#ifndef _FITK_MESH_SIZE_GEN_OF_H___
#define _FITK_MESH_SIZE_GEN_OF_H___


#include "FITK_Interface/FITKInterfaceMeshGen/FITKAbstractMeshSizeInfoGenerator.h"

namespace OF
{
    /**
     * @brief 网格尺寸生成器
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-07-18
     */
    class FITKOFMeshSizeGenerator :
        public Interface::FITKAbstractMeshSizeInfoGenerator
    {
    public:
        /**
         * @brief Construct a new FITKOFMeshSizeGenerator object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-18
         */
        explicit FITKOFMeshSizeGenerator() = default;
        /**
         * @brief Destroy the FITKOFMeshSizeGenerator object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-18
         */
        virtual ~FITKOFMeshSizeGenerator() = default;
        /**
        * @brief 生成全局尺寸信息
        * @return FITKGlobalMeshSizeInfo*
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-07-17
        */
        virtual Interface::FITKGlobalMeshSizeInfo* generateGlobalMeshSizeInfo() override;
        /**
         * @brief 生成局部区域网格尺寸
         * @param[i]  t              区域类型
         * @return FITKAbstractRegionMeshSize*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        virtual Interface::FITKAbstractRegionMeshSize* createRegionMeshSize(Interface::FITKAbstractRegionMeshSize::RegionType t) override;
    };
}


#endif
