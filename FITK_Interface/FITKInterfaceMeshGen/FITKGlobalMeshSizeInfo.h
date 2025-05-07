﻿/**
 *
 * @file FITKGlobalMeshSizeInfo.h
 * @brief 全局网格尺寸类声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-07-17
 *
 */
#ifndef __FITK_ABSTRACT_GLOBALINFO_H__
#define __FITK_ABSTRACT_GLOBALINFO_H__

#include "FITKInterfaceMeshGenAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITK_Kernel/FITKCore/FITKVarientParams.h"

namespace Interface
{
    /**
     * @brief 全局网格尺寸
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-07-17
     */
    class FITKInterfaceMeshGenAPI FITKGlobalMeshSizeInfo :
        public Core::FITKAbstractNDataObject, public Core::FITKVarientParams
    {
        Q_OBJECT
    public:
        /**
         * @brief Construct a new FITKGlobalMeshSizeInfo object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        explicit FITKGlobalMeshSizeInfo();
        /**
         * @brief Destroy the FITKGlobalMeshSizeInfo object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        virtual ~FITKGlobalMeshSizeInfo() = default;
        /**
         * @brief 设置全局尺寸
         * @param[i]  s              全局尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        void setGlobalSize(const double s);
        /**
         * @brief 获取全局尺寸
         * @return double 全局尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double getGlobalSize() const;
        /**
         * @brief 设置最小尺寸
         * @param[i]  s              最小尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        void setMinSize(const double s);
        /**
         * @brief 获取最小尺寸
         * @return double 最小尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double getMinSize() const;
        /**
         * @brief 设置最大尺寸
         * @param[i]  s              最大尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        void setMaxSize(const double s);
        /**
         * @brief 获取最大尺寸
         * @return double 最大尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double getMaxSize() const;
        /**
         * @brief 设置尺寸因子
         * @param[i]  f              尺寸因子
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        void setSizeFactor(const double f);
        /**
         * @brief 获取尺寸因子
         * @return double 尺寸因子
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double getSizeFactor() const;

    protected:
        /**
         * @brief 全局尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double _globalSize{ 0 };
        /**
         * @brief 最小尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double _minSize{ 0 };
        /**
         * @brief 最大尺寸
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double _maxSize{ 0 };
        /**
         * @brief 尺寸因子
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-17
         */
        double _sizeFactor{ 1.0 };

    };
}


#endif
