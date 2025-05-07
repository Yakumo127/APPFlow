﻿/**
 * 
 * @file FITKPluginManager.h
 * @brief  插件与插件管理器声明
 * @author libaojun (libaojunqd@foxmail.com)
 * @date 2024-12-04
 * 
 */
#ifndef _FITK_PLUGINS_MANAGER_H___
#define _FITK_PLUGINS_MANAGER_H___

#include "FITK_Kernel/FITKCore/FITKAbstractObject.hpp" 
#include "FITKAppFrameworkAPI.h"
#include <QString>
#include <QList>


namespace AppFrame
{
    class FITKAbstractPlugin;
   
    /**
     * @brief 插件管理器
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-12-04
     */
    class FITKAppFrameworkAPI FITKPluginsManager : public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief Construct a new FITKPluginsManager object
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        explicit FITKPluginsManager() = default;
        /**
         * @brief Destroy the FITKPluginsManager object
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        virtual ~FITKPluginsManager();
        /**
         * @brief 将当前加载的插件路径写到配置文件
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        void write2Setting();
        /**
         * @brief 根据配置文件加载插件
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        void loadFromSetting();
        /**
         * @brief 加载动态库
         * @param[i]  libPath        动态库路径
         * @return true   加载成功
         * @return false  加载失败
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        bool installLibrary(const QString& libPath);
        /**
         * @brief 卸载动态库
         * @param[i]  p             插件指针
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        void uninstallLib(FITKAbstractPlugin* p);
        /**
         * @brief 卸载动态库
         * @param[i]  index          动态库索引
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        void uninstallLib(const int & index);
        /**
         * @brief 卸载动态库
         * @param[i]  path          动态库路径
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-19
         */ 
        void uninstallLibByPath(const QString& path);
        /**
         * @brief 卸载动态库
         * @param[i]  name          插件名称
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-19
         */
        void uninstallLibByName(const QString& name);
        /**
         * @brief 获取动态库数量
         * @return int 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        int getLibraryCount();
        /**
         * @brief 获取插件
         * @param[i]  index         插件索引
         * @return FITKAbstractPlugin* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        FITKAbstractPlugin* getPlugin(const int & index);
        /**
         * @brief 获取插件
         * @param[i]  name          插件名称
         * @return FITKAbstractPlugin* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        FITKAbstractPlugin* getPluginByName(const QString& name);
        /**
         * @brief 获取插件
         * @param[i]  path          插件路径
         * @return FITKAbstractPlugin* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        FITKAbstractPlugin* getPluginByPath(const QString& path);
        /**
         * @brief 设置插件键值，用于插件识别的密钥
         * @param[i]  k             插件键值
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        void setPluginKey(const QString& k);

    private:
        /**
         * @brief 插件对象
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-12-04
         */
        QList<FITKAbstractPlugin*> _pluginList{};
        /**
         * @brief 用于插件识别的密钥
         * @author libaojun (libaojunqd@@foxmail.com)
         * @date 2024-12-19
         */
        QString _pluginKey{};
        
    };

}


#endif
