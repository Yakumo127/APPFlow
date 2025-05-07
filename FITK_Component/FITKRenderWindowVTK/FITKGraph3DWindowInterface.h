﻿/**
 *
 * @file FITKGraph3DWindowInterface.h
 * @brief 三维渲染窗口组件接口
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-14
 *
 */
#ifndef _FITKGraph3DWindowInterface_H_
#define _FITKGraph3DWindowInterface_H_

#include "FITKRenderWindowVTKAPI.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"
#include "FITK_Kernel/FITKCore/FITKVarientParams.h"
#include <functional>
#include <QHash>

//定义字符串
#define  VTKRENDERLAYER  "VTKRENDERLAYER"
#define  BackGroundColorTop "BackGroundColorTop"
#define  BackGroundColorButtom "BackGroundColorButtom"

namespace Comp
{

    class FITKGraphInteractionStyle;
    /**
     * @brief 渲染窗口信息
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-18
     */
    class FITKRenderWindowVTKAPI Graph3DWindowInitializer : public Core::FITKVarientParams
    {
    public:
        explicit Graph3DWindowInitializer() = default;
        virtual ~Graph3DWindowInitializer() = default;
        /**
         * @brief 获取交互器
         * @return FITKGraphInteractionStyle*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        virtual  FITKGraphInteractionStyle* getStyle();
        /**
         * @brief 设置渲染器层数
         * @param[i]  nc         渲染器层数
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        void setLayerCount(const int nc );
        /**
         * @brief 获取渲染层数
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        int getLayerCount() const;

    private:
        /**
         * @brief 渲染层数
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-08
         */
        int _layerCount{ 3 };


    };


    /**
     * @brief 三维渲染窗口组件接口
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-12
     */
    class FITKRenderWindowVTKAPI FITKGraph3DWindowInterface :public AppFrame::FITKComponentInterface
    {
    public:
        /**
         * @brief Construct a new FITKGraph3DWindowInterface object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        FITKGraph3DWindowInterface() = default;
        /**
         * @brief Destroy the FITKGraph3DWindowComp object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        virtual ~FITKGraph3DWindowInterface();
        /**
       * @brief 检查系统状态
       * @return QString 返回系统错误信息，如果为空则表示正常
       * @author libaojun
       * @date 2025-03-25
       */
        static QString CheckSystem();

        /**
         * @brief 获取三维渲染界面
         * @param[i]  indexPort      索引值（参数无效）
         * @return QWidget*
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        QWidget* getWidget(const int indexPort)override;
        /**
         * @brief 获取组件名称
         * @return QString
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        QString getComponentName();
        /**
         * @brief 添加渲染窗口相关信息
         * @param[i]  key            索引值
         * @param[i]  info           窗口信息
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void addInitializer(int key, Graph3DWindowInitializer* info);


    private:
        /**
         * @brief 三维渲染窗口信息链表
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        QHash<int, Graph3DWindowInitializer*> _initilizerList{};

    };
}

#endif
