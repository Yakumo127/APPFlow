﻿/**
 * 
 * @file FITKAbstractSysChecker.h
 * @brief 抽象系统检查声明
 * @author libaojun (libaojunqd@foxmail.com)
 * @date 2024-09-18
 * 
 */
#ifndef _FITKABSTRACT_SYSTEM_CHHECKER_H___
#define _FITKABSTRACT_SYSTEM_CHHECKER_H___
 
#include "FITKAppFrameworkAPI.h"
#include <QStringList>

namespace AppFrame
{
    /**
     * @brief 抽象系统检查器
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-09-18
     */
    class FITKAppFrameworkAPI FITKAbstractSysChecker
    {
    public:
        /**
         * @brief Construct a new FITKAbstractSysChecker object
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-09-18
         */
        explicit FITKAbstractSysChecker() = default;
        /**
         * @brief Destroy the FITKAbstractSysChecker object
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-09-18
         */
        virtual ~FITKAbstractSysChecker() = 0;
        /**
         * @brief 进行检查，返回错误信息
         * @return QStringList 错误信息
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-09-18
         */
        virtual QStringList check() = 0;

    protected:
        /**
          * @brief 将错误信息添加到错误列表中
          * @param errors 错误列表
          * @param error 错误信息
          * @author libaojun (libaojunqd@foxmail.com)
          * @date 2024-09-18
          */
        void appendError(QStringList& errors, const QString& error) ;

         /**
         * @brief 检查系统硬盘容量是否满足最小要求
         * @param minDiskSpaceMB 最小硬盘容量，单位MB
         * @return QString 若不满足最小资源则返回当前资源信息，若满足则返回空
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-09-18
         */
        QString checkDiskSpace(qint64 minDiskSpaceMB);

        /**
         * @brief 检查系统内存容量是否满足最小要求
         * @param minMemoryMB 最小内存容量，单位MB
         * @return QString 若不满足最小资源则返回当前资源信息，若满足则返回空
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-09-18
         */
        QString checkMemory(qint64 minMemoryMB);
        /**
         * @brief 检查系统线程数是否满足最小要求
         * @param minThreadCount 最小线程数
         * @return QString 若不满足最小资源则返回当前资源信息，若满足则返回空
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-09-18
         */
        QString checkThreadCount(int minThreadCount);
    };
}


#endif
