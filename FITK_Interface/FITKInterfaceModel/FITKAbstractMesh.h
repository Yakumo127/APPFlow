﻿/**
 *
 * @file FITKAbstractMesh.h
 * @brief 抽象网格模型定义
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-03-29
 *
 */
#ifndef _FITKABSTRACT_MESH_H__
#define _FITKABSTRACT_MESH_H__

#include "FITKAbstractModel.h"
#include "FITKInterfaceModelAPI.h"

namespace Interface
{
    struct FITKElemntQuality 
    {
        double _minEdgeLength{ 0 }; //最短边长
        double _maxEdgeLength{ 0 }; //最长边长
        double _aspectRatio{ 0 };   //长宽比
    };

    /**
     * @brief 定义抽象网格模型
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-29
     */
    class FITKInerfaceModelAPI FITKAbstractMesh: public FITKAbstractModel
    {
     //   FITKSafeDownCastA(FITKAbstractMesh, Core::FITKAbstractDataObject);

    public:
        /**
         * @brief Construct a new FITKAbstractMesh object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-29
         */
        explicit FITKAbstractMesh() = default;
        /**
         * @brief Destroy the FITKAbstractMesh object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-29
         */
        virtual ~FITKAbstractMesh() = 0;

        /**
         * @brief 获取模型类型
         * @return AbsModelType
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual FITKModelEnum::AbsModelType getAbsModelType() override;
        /**
         * @brief 更新数据
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual void update() = 0;
        /**
         * @brief 获取网格维度
         * @return FITKModelEnum::FITKMeshDim
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        virtual FITKModelEnum::FITKMeshDim getMeshDim();
        
        /**
         * @brief 通过位运算获取网格维度
         * @return unsigned int 返回网格维度的位表示，参考 FITKModelEnum::FITKMeshDim 
         * @author LiBaojun
         * @date 2025-04-11
         */
        virtual unsigned int getMeshDimBit() ;

    };
}



#endif
