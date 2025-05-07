﻿/**********************************************************************
 * @file   FITKGraph3DClipDialog.h
 * @brief  三维渲染窗口裁切对话框
 * @author BaGuijun (baguijun@163.com)
 * @date   2025-04-09
 *********************************************************************/
#ifndef _FITKGraph3DClipDialog_H
#define _FITKGraph3DClipDialog_H

#include "FITK_Kernel/FITKCore/FITKAbstractGUIDialog.h"

namespace Ui {
    class FITKGraph3DClipDialog;
}

class vtkActor;

namespace Comp
{
    class FITKGraph3DWindowVTK;
    class FITKGraph3DWidgetPlane;
    class FITKGraphObjectVTK;
    /**
     * @brief  三维渲染窗口裁切对话框
     * @author BaGuijun (baguijun@163.com)
     * @date   2025-04-09
     */
    class FITKGraph3DClipDialog : public Core::FITKDialog
    {
        Q_OBJECT;
    public:
        /**
         * @brief    构造函数
         * @param[i] graph3DWindow                三维渲染窗口
         * @param[i] clipCreateNewModel           裁切是否产生新模型
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-09
         */
        FITKGraph3DClipDialog(FITKGraph3DWindowVTK* graph3DWindow, bool clipCreateNewModel);
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-09
         */
        virtual ~FITKGraph3DClipDialog();
        /**
         * @brief    初始化
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        void init();
    protected:
        /**
         * @brief    显示事件重写
         * @param[i] event                 事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        void showEvent(QShowEvent *event) override;
        /**
         * @brief    获取边界
         * @param[i] boundValue                边界(Xmin,Xmax,Ymin,Ymax,Zmin,Zmax)
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void getBound(double* boundValue);
        /**
         * @brief    更新方向与中心点位置
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void updateValue();
        /**
         * @brief    启动裁切(裁切在原模型上进行裁切，不会产生新的模型，原来模型的属性保留)
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void startClipInOldModel();
        /**
         * @brief    启动裁切(裁切会产生新的模型，原来模型的属性不保留)
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void startClipCreateNewModel();
        /**
         * @brief    终止裁切
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void stopClipInOldModel();
        /**
         * @brief    终止裁切
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void stopClipCreateNewModel();
    protected slots:
        ;
        /**
         * @brief    中心点X轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_OriginX_editingFinished();
        /**
         * @brief    中心点Y轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_OriginY_editingFinished();
        /**
         * @brief    中心点Z轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_OriginZ_editingFinished();
        /**
         * @brief    方向X轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_NormalX_editingFinished();
        /**
         * @brief    方向Y轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_NormalY_editingFinished();
        /**
         * @brief    方向Z轴修改事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_lineEdit_NormalZ_editingFinished();
        /**
         * @brief    应用按钮点击事件
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_pushButton_Apply_clicked();
        /**
         * @brief    裁切界面是否显示事件
         * @param[i] checked                       是否显示
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void on_checkBox_PlaneWidget_clicked(bool checked);
        /**
         * @brief    VTKWidget回调槽函数
         * @param[i] origin                  中心点
         * @param[i] normal                  方向
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-10
         */
        virtual void slot_ValueChange(double* origin, double* normal);
    protected:
        /**
         * @brief  ui对象
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-09
         */
        Ui::FITKGraph3DClipDialog* _ui = nullptr;
        /**
         * @brief  三维渲染窗口
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-09
         */
        FITKGraph3DWindowVTK* _graph3DWindow = nullptr;
        /**
         * @brief  三维渲染平面界面
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-09
         */
        FITKGraph3DWidgetPlane* _graph3DWidgetPlane = nullptr;
        /**
         * @brief  裁切演员对象
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-10
         */
        FITKGraphObjectVTK* _clipObj = nullptr;
        /**
         * @brief  演员可见性映射表（仅限在模式为产生新模型下有用）
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-18
         */
        QHash<vtkActor*, bool> _actionPro = {};
        /**
         * @brief  裁切是否产生新模型
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-18
         */
        bool _clipCreateNewModel = true;
    };
}

#endif
