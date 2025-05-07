﻿/**
 * @file ComponentFactory.h
 * @brief 组件工厂
 * @author YanZhiHui(chanyuantiandao@126.com)
 * @date 2024-04-19
 */
#ifndef __COMPONENTFACTORY__
#define __COMPONENTFACTORY__

#include "FITK_Kernel/FITKAppFramework/FITKComponentFactory.h"
 /**
  * @brief 组件工厂类
  * @author YanZhiHui (chanyuantiandao@126.com)
  * @date 2024-04-19
  */
class ComponentFactory : public AppFrame::FITKComponentFactory
{
public:
    /**
     * @brief 构造函数（默认实现）
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date 2024-04-19
     */
    ComponentFactory() = default;
    /**
     * @brief 析构函数（默认实现）
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date 2024-04-19
     */
    ~ComponentFactory() = default;
    /**
     * @brief 虚函数重写，创建自己的component
     * @return QList<AppFrame::FITKComponentInterface*>
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-04
     */
    QList<AppFrame::FITKComponentInterface *> createComponents() override;
};

#endif // !__COMPONENTFACTORY__
