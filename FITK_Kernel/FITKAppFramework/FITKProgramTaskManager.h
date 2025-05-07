﻿/**
 *
 * @file FITKProgramTaskManager.h
 * @brief 第三方程序执行任务管理器
 * @author libaojun (libaojunqd@Foxmail.com)
 * @date 2024-06-09
 *
 */
#ifndef __FITK_PROGRAMTASK_MANAGER_H___
#define __FITK_PROGRAMTASK_MANAGER_H___

#include "FITKAppFrameworkAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"

namespace AppFrame
{
    class FITKProgramInputInfo;
    /**
     * @brief 第三方程序执行任务管理器
     * @author libaojun (libaojunqd@Foxmail.com)
     * @date 2024-06-09
     */
    class FITKAppFrameworkAPI FITKProgramTaskManeger : public Core::FITKAbstractDataObject,
         public Core::FITKAbstractDataManager<FITKAbstractProgramerDriver>
    {
        Q_OBJECT
    public:
        /**
         * @brief Construct a new FITKProgramTaskManeger object
         * @author libaojun (libaojunqd@Foxmail.com)
         * @date 2024-06-09
         */
        explicit FITKProgramTaskManeger() = default;
        /**
         * @brief Destroy the FITKProgramTaskManeger object
         * @author libaojun (libaojunqd@Foxmail.com)
         * @date 2024-06-09
         */
        virtual ~FITKProgramTaskManeger() = default;

       /**
         * @brief 启动程序
         * @param type 程序类型
         * @param programName 程序名称
         * @param info 程序输入信息
         * @author libaojun (libaojunqd@Foxmail.com)
         * @date 2024-06-09
         */
        void startProgram(const int type, const QString& programName, FITKProgramInputInfo* info);

       /**
         * @brief 创建第三方程序驱动器 返回值不需要主动销毁由第三方程序执行任务管理器统一管理
         * @param type 程序类型
         * @param programName 程序名称
         * @param info 程序输入信息
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-06-29
         */
        FITKAbstractProgramerDriver* createProgram(const int type, const QString& programName, FITKProgramInputInfo* info);
     
        /**
         * @brief 强行终止程序运行
         * @author libaojun (libaojunqd@Foxmail.com)
         * @date 2024-06-09
         */
        void killAll();

        void appendDataObj(Core::FITKAbstractDataObject* item) override;

    private slots:
        void programFinishedSlot();


    };
}


#endif
