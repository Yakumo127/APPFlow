﻿/**
 *
 * @file FITKAPPSettings.h
 * @brief 软件设置基类
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-04-06
 *
 */
#ifndef __FITKAPP_SETTINGS_H__
#define __FITKAPP_SETTINGS_H__

#include "FITKAppFrameworkAPI.h"
#include <QVariant>
#include <QString>

class QSettings;

namespace AppFrame
{
    /**
     * @brief 软件设置
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-06
     */
    class FITKAppFrameworkAPI FITKAppSettings
    {
    public:
        /**
         * @brief Construct a new FITKAppSettings object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        explicit FITKAppSettings();
        /**
         * @brief Destroy the FITKAppSettings object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        virtual ~FITKAppSettings();
        /**
         * @brief 设置值
         * @param[i]  key            关键字
         * @param[i]  varient        变量值
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        void setValue(const QString& key, const QVariant& varient);

        template<typename T>
        /**
         * @brief 按照类型获取值
         * @param[i]  key           关键字
         * @return T
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        T getValue(const QString& key)
        {
            QVariant v = this->getVarient(key);
            return v.value<T>();
        }
        /**
         * @brief 读取文件
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        virtual void read() = 0;
        /**
         * @brief 写出文件
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        virtual void write();
        /**
         * @brief 获取值
         * @param[i]  k             关键字
         * @return QVariant
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        QVariant getVarient(const QString& k);
        /**
         * @brief 获取工作目录
         * @return QString
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        virtual QString getWorkingDir();
        /**
         * @brief 设置工作目录
         * @param[i]  wd             工作目录
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        void setWorkingDir(const QString& wd);

        /**
         * @brief 设置插件路径
         * @param[i]  pathList       插件路径
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        void setPlugins(const QStringList& pathList);
        /**
         * @brief 获取插件路径
         * @return QStringList
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        QStringList getPlugins();
        /**
         * @brief 获取软件设置
         * @return QSettings*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        QSettings* getSettings();

    protected:
        /**
         * @brief 软件路径
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        QString _appDir{};
        /**
         * @brief 软件设置
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-06
         */
        QSettings* _settings{};

    };



}

#endif
