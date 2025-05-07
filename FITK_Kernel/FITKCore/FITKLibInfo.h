﻿/**
 *
 * @file FITKLibInfo.h
 * @brief FITK库信息类声明,提供库版本号等基本信息
 * @author libaojun (libaojunqd@foxmail.com)
 * @date 2025-04-09
 *
 */
#ifndef __FITK_LIB_INFO_H__
#define __FITK_LIB_INFO_H__

#include "FITKCoreAPI.h"
#include "FITKCoreMacros.h"
#include <QString>
#include <QHash>
#include <QMutex>
#include <QMutexLocker>

namespace Core
{
    class FITKLibInfoDeleator;

    /**
     * @brief 库信息结构体
     */
    struct LibraryInfo {
        QString name;        ///< 库名称
        QString version;     ///< 版本号
        QString buildDate;   ///< 构建日期

        LibraryInfo() = default;
        LibraryInfo(const QString& n, const QString& v, const QString& d)
            : name(n), version(v), buildDate(d) {}
    };

    /**
     * @brief FITK库信息管理类,提供多个库的版本号等基本信息管理
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2025-04-09
     */
    class FITKCoreAPI FITKLibInfo
    {
        DeclSingleton(FITKLibInfo);
        friend FITKLibInfoDeleator;

    public:
        /**
         * @brief 注册一个库的信息
         * @param name 库名称
         * @param version 版本号
         * @param buildDate 构建日期
         */
        void registerLibrary(const QString& name, const QString& version, const QString& buildDate);

        /**
         * @brief 获取指定库的信息
         * @param name 库名称
         * @return LibraryInfo 库信息，如果不存在返回空的LibraryInfo
         */
        LibraryInfo getLibraryInfo(const QString& name) const;

        /**
         * @brief 获取所有已注册的库名称
         * @return QStringList 库名称列表
         */
        QStringList getRegisteredLibraries() const;

        /**
         * @brief 获取指定库的版本号
         * @param name 库名称
         * @return QString 版本号
         */
        QString getVersion(const QString& name = "FITKCore") const;

        /**
         * @brief 获取指定库的构建日期
         * @param name 库名称
         * @return QString 构建日期
         */
        QString getBuildDate(const QString& name = "FITKCore") const;

        /**
         * @brief 打印所有已注册库的信息到控制台
         */
        void printAllLibraryInfo() const;

        /**
         * @brief 将所有库信息转换为字符串列表
         * @return QStringList 每个元素包含一个库的完整信息
         */
        QStringList toStringList() const;

    private:
        /**
         * @brief 初始化
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2025-04-09
         */
        void initialize();

        /**
         * @brief 结束,析构函数调用
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2025-04-09
         */
        void finalize();

    private:
       
        /**
         * @brief 库信息哈希表
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2025-04-09
         */
        QHash<QString, LibraryInfo> m_libraries;
    };

    class FITKLibInfoDeleator
    {
    public:
        explicit FITKLibInfoDeleator() = default;
        virtual ~FITKLibInfoDeleator();
    };
}

#ifndef FITKLIBINFO
#define FITKLIBINFO   (Core::FITKLibInfo::getInstance())
#endif

#endif
