﻿#include "FITKGraphInteractionStyle.h"
#include "FITKGraphAreaPicker.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKKeyMouseStates.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include <vtkRenderWindowInteractor.h>

namespace Comp
{
    FITKGraphInteractionStyle* FITKGraphInteractionStyle::New()
    {
        return new FITKGraphInteractionStyle();
    }

    void FITKGraphInteractionStyle::setGraph3DWin(FITKGraph3DWindowVTK * graphWin)
    {
        m_graph3dWin = graphWin;
    }

    void FITKGraphInteractionStyle::setInteractor(vtkRenderWindowInteractor * interactor)
    {
        if (interactor == nullptr)return;

        //将渲染窗口的交互器设置为该类
        interactor->SetInteractorStyle(this);
    }

    void FITKGraphInteractionStyle::setAreaPickRenderer(vtkRenderer * renderer)
    {
        if (renderer == nullptr || m_areaPick == nullptr)return;
        m_areaPick->setPickerRender(renderer);
    }

    vtkRenderWindowInteractor * FITKGraphInteractionStyle::getInteractor()
    {
        return this->Interactor;
    }

    void FITKGraphInteractionStyle::setAredPickerState(bool state)
    {
        m_areaPick->enable(state);
    }

    void FITKGraphInteractionStyle::areaPick(int* startPos, int* endPos)
    {

    }

    void FITKGraphInteractionStyle::applyDolly(double factor)
    {
        Dolly(factor);
    }

    FITKGraphInteractionStyle::FITKGraphInteractionStyle()
    {
        m_areaPick = new FITKGraphAreaPicker(this);
    }

    FITKGraphInteractionStyle::~FITKGraphInteractionStyle()
    {
        if (m_areaPick != nullptr) delete m_areaPick; m_areaPick = nullptr;
    }

    void FITKGraphInteractionStyle::OnLeftButtonDown()
    {
        //使用VTK自身的鼠标左键按下事件
        this->Interactor->GetEventPosition(m_leftButtonDowmPos);
        vtkInteractorStyleRubberBandPick::OnLeftButtonDown();
        if (m_areaPick != nullptr && m_areaPick->isEnable())
        {
            m_areaPick->setLeftButtonDownPos(m_leftButtonDowmPos);
        }
    }

    void FITKGraphInteractionStyle::OnLeftButtonUp()
    {
        //使用VTK自身的鼠标左键抬起事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnLeftButtonUp();

        if (m_areaPick != nullptr /*&& isMouseMoved()*/)
        {
            m_areaPick->enable(false);
        }
    }

    void FITKGraphInteractionStyle::OnMiddleButtonDown()
    {
        //使用VTK自身的鼠标中键按下事件
        this->Interactor->GetEventPosition(m_leftButtonDowmPos);
        vtkInteractorStyleRubberBandPick::OnMiddleButtonDown();
    }

    void FITKGraphInteractionStyle::OnMiddleButtonUp()
    {
        //使用VTK自身的鼠标中键抬起事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnMiddleButtonUp();
    }

    void FITKGraphInteractionStyle::OnMouseMove()
    {
        //使用VTK自身的鼠标移动事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnMouseMove();

        //判断是否移动
        bool isMove = this->isMouseMoved();

        //判断鼠标左键是否按下
        bool isMouseState = FITKAPP->getGlobalData()->getKeyMouseStates()->mousePressed(Qt::LeftButton);

        if (m_areaPick != nullptr && isMove  && isMouseState)
        {
            //重新绘制框选选框
            m_areaPick->drawRectangle();
        }
    }

    void FITKGraphInteractionStyle::OnMouseWheelForward()
    {
        //调用VTK自身的鼠标滑轮向前事件
        vtkInteractorStyleRubberBandPick::OnMouseWheelForward();
    }

    void FITKGraphInteractionStyle::OnMouseWheelBackward()
    {
        //调用VTK自身的鼠标滑轮向后事件
        vtkInteractorStyleRubberBandPick::OnMouseWheelBackward();
    }

    void FITKGraphInteractionStyle::OnRightButtonDown()
    {
        //调用VTK自身的鼠标右键按下事件
        this->Interactor->GetEventPosition(m_leftButtonDowmPos);
        vtkInteractorStyleRubberBandPick::OnRightButtonDown();
    }

    void FITKGraphInteractionStyle::OnRightButtonUp()
    {
        //调用VTK自身的鼠标右键抬起事件
        this->Interactor->GetEventPosition(m_leftButtonUpPos);
        vtkInteractorStyleRubberBandPick::OnRightButtonUp();
    }

    void FITKGraphInteractionStyle::OnChar()
    {
        vtkRenderWindowInteractor* interactor = this->Interactor;
        if (interactor == nullptr) {
            return;
        }

        //当前按钮
        std::string curKey = interactor->GetKeySym();

        //禁用按钮
        QList<std::string> keys = {};
        keys << "KP_3";
        keys << "3";
        keys << "r";

        //判断是否是禁用按钮
        if (keys.contains(curKey)) {
            //直接返回，不处理
            return; 
        }

        vtkInteractorStyleRubberBandPick::OnChar();
    }

    bool FITKGraphInteractionStyle::isMouseMoved()
    {
        int dx = m_leftButtonUpPos[0] - m_leftButtonDowmPos[0];
        int dy = m_leftButtonUpPos[1] - m_leftButtonDowmPos[1];
        return dx * dx + dy * dy > 50;
    }
}