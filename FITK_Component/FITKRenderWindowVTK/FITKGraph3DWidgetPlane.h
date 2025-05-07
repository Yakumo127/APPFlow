﻿/**********************************************************************
 * @file   FITKGraph3DWidgetPlane.h
 * @brief  VTK平面界面
 * @author BaGuijun (baguijun@163.com)
 * @date   2024-10-09
 *********************************************************************/
#ifndef _PostGraphWidgetPlane_H_
#define _PostGraphWidgetPlane_H_

#include <QObject>
#include "FITKRenderWindowVTKAPI.h"

class vtkImplicitPlaneWidget2;

namespace Comp
{
    class FITKGraph3DWidgetPlaneCallBack;
    class FITKGraph3DWindowVTK;
    /**
     * @brief  VTK平面界面
     * @author BaGuijun (baguijun@163.com)
     * @date   2024-10-09
     */
    class FITKRenderWindowVTKAPI FITKGraph3DWidgetPlane : public QObject
    {
        Q_OBJECT;
    public:
        /**
         * @brief    构造函数
         * @param[i] graph3DWidget              三维渲染界面
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-09
         */
        FITKGraph3DWidgetPlane(FITKGraph3DWindowVTK* graph3DWidget);
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-09
         */
        ~FITKGraph3DWidgetPlane();
        /**
         * @brief    设置边界
         * @param[i] bounds           边界[6]
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-18
         */
        void setBounds(double* bounds);
        /**
         * @brief    设置数据
         * @param[i] origin           原点[3]
         * @param[i] normal           方向[3]
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-26
         */
        void setValue(double* origin, double* normal);
        /**
         * @brief    设置是否显示
         * @param[i] isShow           是否显示
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-18
         */
        void setIsShow(bool isShow);
    signals:
        ;
        /**
         * @brief    数据更改
         * @param[i] origin        原点
         * @param[i] normal        轴向
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-18
         */
        void sigValueChange(double* origin, double* normal);
    private:
        /**
         * @brief  裁切界面
         * @author BaGuijun (baguijun@163.com)
         * @date   2024-09-18
         */
        vtkImplicitPlaneWidget2* _widget = nullptr;
        /**
         * @brief  回调
         * @author BaGuijun (baguijun@163.com)
         * @date   2024-09-18
         */
        FITKGraph3DWidgetPlaneCallBack* _callBack = nullptr;
    };
}

#endif