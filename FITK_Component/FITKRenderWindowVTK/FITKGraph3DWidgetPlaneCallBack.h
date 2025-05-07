﻿/**********************************************************************
 * @file   FITKGraph3DWidgetPlaneCallBack.h
 * @brief  VTK平面界面回调类
 * @author BaGuijun (baguijun@163.com)
 * @date   2024-10-09
 *********************************************************************/
#ifndef _PostGraphWidgetPlaneCallBack_H_
#define _PostGraphWidgetPlaneCallBack_H_

#include <QObject>
#include <vtkCommand.h>

namespace Comp
{
    /**
     * @brief  VTK平面界面回调类
     * @author BaGuijun (baguijun@163.com)
     * @date   2024-10-09
     */
    class FITKGraph3DWidgetPlaneCallBack : public QObject, public vtkCommand
    {
        Q_OBJECT;
    public:
        /**
         * @brief    构造函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-09
         */
        FITKGraph3DWidgetPlaneCallBack() = default;
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-09
         */
        ~FITKGraph3DWidgetPlaneCallBack() = default;
        /**
         * @brief    回调函数重写
         * @param[i] caller         对象
         * @param[i] eventId        
         * @param[i] callData 
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-18
         */
        virtual void Execute(vtkObject *caller, unsigned long eventId, void* callData) override;
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
    };
}

#endif