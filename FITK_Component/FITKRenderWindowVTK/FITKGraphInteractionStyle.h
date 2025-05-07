﻿/**
 * 
 * @file FITKGraphInteractionStyle.h
 * @brief 渲染窗口交互器类接口声明
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-18
 * 
 */
#ifndef _FITKGraphInteractionStyle_H_
#define _FITKGraphInteractionStyle_H_

#include "FITKRenderWindowVTKAPI.h"
#include <QObject>
#include <vtkInteractorStyleRubberBandPick.h>

namespace Comp
{
    class FITKGraphOperator;
    class FITKGraph3DWindowVTK;
    class FITKGraphAreaPicker;
    /**
     * @brief 渲染窗口交互器类接口声明
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-18
     */
    class FITKRenderWindowVTKAPI FITKGraphInteractionStyle :public QObject, public vtkInteractorStyleRubberBandPick
    {
        Q_OBJECT
    public:
        /**
         * @brief 创建函数
         * @return FITKGraphInteractionStyle* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        static FITKGraphInteractionStyle* New();
        vtkTypeMacro(FITKGraphInteractionStyle, vtkInteractorStyleRubberBandPick);
        /**
         * @brief 设置交互器对应的窗口
         * @param[i]  graphWin       窗口对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void setGraph3DWin(FITKGraph3DWindowVTK* graphWin);
        /**
         * @brief 设置窗口的交互器对象
         * @param[i]  interactor     My Param doc
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        void setInteractor(vtkRenderWindowInteractor* interactor);
        
        /**
         * @brief 设置框选器框选的渲染图层对象
         * @param[i]  renderer       渲染图层对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void setAreaPickRenderer(vtkRenderer* renderer);
        /**
         * @brief 获取VTK交互器对象
         * @return vtkRenderWindowInteractor* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkRenderWindowInteractor* getInteractor();
        /**
         * @brief 设置框选器的状态
         * @param[i]  state          状态（true为开启）
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void setAredPickerState(bool state);
        /**
         * @brief 区域拾取
         * @param[i]  startPos   起始点
         * @param[i]  endPos   终止点
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-17
         */
        virtual void areaPick(int* startPos, int* endPos);
        /**
         * @brief    实施相机缩放
         * @param[i] factor              缩放倍率
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-02
         */
        virtual void applyDolly(double factor);
    protected:
        /**
         * @brief Construct a new FITKGraphInteractionStyle object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FITKGraphInteractionStyle();
        /**
         * @brief Destroy the FITKGraphInteractionStyle object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual ~FITKGraphInteractionStyle();
        /**
         * @brief 鼠标左键按下事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnLeftButtonDown() override;
        /**
         * @brief 鼠标左键抬起事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnLeftButtonUp() override;
        /**
         * @brief 鼠标中键按下事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnMiddleButtonDown() override;
        /**
         * @brief 鼠标中键抬起事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnMiddleButtonUp() override;
        /**
         * @brief 鼠标移动事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnMouseMove() override;
        /**
         * @brief 鼠标滑轮向前事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnMouseWheelForward() override;
        /**
         * @brief 鼠标滑轮向后事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnMouseWheelBackward() override;
        /**
         * @brief 鼠标中键按下事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnRightButtonDown() override;
        /**
         * @brief 鼠标中键抬起事件
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        virtual void OnRightButtonUp() override;
        /**
         * @brief    键盘事件重写
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-03-28
         */
        virtual void OnChar() override;
        /**
         * @brief 鼠标移动判断
         * @return true
         * @return false
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        bool isMouseMoved();

    protected:
        /**
         * @brief 渲染窗口对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FITKGraph3DWindowVTK* m_graph3dWin = nullptr;
        /**
         * @brief 绘图操作器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        FITKGraphOperator* m_operactor = nullptr;
        /**
         * @brief 鼠标按下位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        int m_leftButtonDowmPos[2] = { 0,0 };
        /**
         * @brief 鼠标抬起位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-18
         */
        int m_leftButtonUpPos[2] = { 0,0 };
        /**
         * @brief 框选功能对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        FITKGraphAreaPicker* m_areaPick = nullptr;
        /**
         * @brief 框选器状态
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
//        bool m_pickerState = true;
    };
}
#endif
