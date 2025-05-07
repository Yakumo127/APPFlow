﻿/**
 *
 * @file FITKOFMeshProcessor.h
 * @brief  网格处理器声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-07-18
 *
 */
#ifndef __FITK_ABSTRACTMESH_OP_PROCESSOR__H___
#define __FITK_ABSTRACTMESH_OP_PROCESSOR__H___

#include "FITK_Interface/FITKInterfaceMeshGen/FITKAbstractMeshProcessor.h"

namespace OF
{
    /**
     * @brief 网格处理器
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-07-18
     */
    class FITKOFMeshProcessor : public Interface::FITKAbstractMeshProcessor
    {
    public:
        /**
         * @brief Construct a new FITKOFMeshProcessor object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-18
         */
        explicit FITKOFMeshProcessor() = default;
        /**
         * @brief Destroy the FITKOFMeshProcessor object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-18
         */
        virtual ~FITKOFMeshProcessor() = default;
        /**
         * @brief 开始执行处理
         * @param[i]  info           附加信息
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-18
         */
        virtual void start(QStringList info = QStringList()) override;

    };
}

#endif
