﻿/**
 * 
 * @file FITKGraphAreaPicker.h
 * @brief VTK框选功能接口声明
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-19
 * 
 */
#ifndef _FITKGraphAreaPicker_H_
#define _FITKGraphAreaPicker_H_

#include <vtkSmartPointer.h>
#include "FITKRenderWindowVTKAPI.h"
#include <vtkPolyData.h>
#include <vtkActor2D.h>

class vtkRenderer;
// class vtkActor2D;
// class vtkPolyData;

namespace Comp
{
    class FITKGraphInteractionStyle;
    /**
     * @brief VTK框选功能接口声明
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-19
     */
    class FITKRenderWindowVTKAPI  FITKGraphAreaPicker
    {
    public:
        /**
         * @brief Construct a new FITKGraphAreaPicker object
         * @param[i]  style          交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        FITKGraphAreaPicker(FITKGraphInteractionStyle* style);
        /**
         * @brief Destroy the FITKGraphAreaPicker object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        ~FITKGraphAreaPicker();
        /**
         * @brief 记录左键点击位置
         * @param[i]  pos            位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void setLeftButtonDownPos(int* pos);
        /**
         * @brief 设置框选的渲染图层
         * @param[i]  render         渲染图层对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void setPickerRender(vtkRenderer* render);
        /**
         * @brief 设置框选是否激活
         * @param[i]  state             状态
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void enable(bool state = true);
        /**
         * @brief 获取是否激活状态
         * @return bool
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-17
         */
        bool isEnable();
        /**
         * @brief 绘制框选选框
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void drawRectangle();
        /**
         * @brief 
         * @param[i]  state             状态
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void pick();

    private:
        /**  
         * @brief 初始化框选选框
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void initRectangle();
        /**
         * @brief 更新框选选框
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        void updateRectangle();
    private:
        /**
         * @brief 交互器对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        FITKGraphInteractionStyle* m_style = nullptr;
        /**
         * @brief 框选图层
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkRenderer* m_render = nullptr;
        /**
         * @brief 鼠标起始位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        int m_startPos[2] = { 0,0 };
        /**
         * @brief 鼠标终止位置
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        int m_endPos[2] = { 0,0 };
        /**
         * @brief 框选选框数据
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkSmartPointer<vtkPolyData> m_pickData = nullptr;
        /**
         * @brief 框选选框对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-19
         */
        vtkSmartPointer<vtkActor2D> m_pickActor = nullptr;
    };
}

#endif
