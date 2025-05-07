﻿#include "FITKGraphObjectVTK.h"

#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITK_Interface/FITKVTKAlgorithm/FITKActorClipTool.h"

// VTK
#include <vtkProp.h>
#include <vtkPlane.h>
#include <vtkInteractorObserver.h>
#include <vtkDataSetMapper.h>
#include <vtkAlgorithmOutput.h>

namespace Comp
{
    FITKGraphObjectVTK::FITKGraphObjectVTK(Core::FITKAbstractDataObject * dataObject):
        Core::FITKAbstractGraphObject(dataObject)
    {
        // 创建裁切平面。
        m_clipPlane = vtkPlane::New();
    }

    FITKGraphObjectVTK::FITKGraphObjectVTK() :
        Core::FITKAbstractGraphObject(nullptr)
    {
        // 创建裁切平面。
        m_clipPlane = vtkPlane::New();
    }

    FITKGraphObjectVTK::~FITKGraphObjectVTK()
    {
        //VTK相关参数释放
        this->removeFromGraphWidget();

        for (auto actor : m_actorList)
        {
            if (actor == nullptr)return;
            actor->Delete();
            actor = nullptr;
        }
        m_actorList.clear();

        // 析构控件。
        for (vtkInteractorObserver* widget : m_widgetList)
        {
            if (widget)
            {
                widget->Off();
                widget->Delete();
            }
        }

        m_widgetList.clear();

        if (m_clipPlane)
        {
            m_clipPlane->Delete();
            m_clipPlane = nullptr;
        }
    }

    void FITKGraphObjectVTK::setClipType(GraphClipType type)
    {
        if (!m_clipPlane)
        {
            return;
        }

        ClipType cType = ClipType::NoneType;

        switch (type)
        {
        case Comp::FITKGraphObjectVTK::Clip:
        {
            cType = ClipType::Clip;
            break;
        }
        case Comp::FITKGraphObjectVTK::Cut:
        {
            cType = ClipType::Cut;
            break;
        }
        case Comp::FITKGraphObjectVTK::ExtractGeometry:
        {
            cType = ClipType::ExtractGeometry;
            break;
        }
        default:
            break;
        }

        // Set the clip plane and enable the clip dataset.
        for (vtkProp* prop : m_actorList)
        {
            FITKActorClipTool* fActor = dynamic_cast<FITKActorClipTool*>(prop);
            if (!fActor)
            {
                continue;
            }

            fActor->setClipType(cType);
            fActor->setClipImplicitFunction(m_clipPlane);
        }
    }

    void FITKGraphObjectVTK::setCustomClipPlane(double* org, double* nor)
    {
        if (!m_clipPlane)
        {
            return;
        }

        m_clipPlane->SetOrigin(org);
        m_clipPlane->SetNormal(nor);
    }

    void FITKGraphObjectVTK::addActor(vtkProp * actor)
    {
        //添加渲染对象
        if (actor == nullptr || m_actorList.contains(actor))return;
        m_actorList.append(actor);
    }

    vtkProp * FITKGraphObjectVTK::getActor(int index)
    {
        //越界判断
        if (index < 0 || index >= m_actorList.size())return nullptr;

        //根据索引值获取渲染对象
        return m_actorList.at(index);
    }


    int FITKGraphObjectVTK::getActorCount()
    {
        //获取渲染对象数量
        return m_actorList.size();
    }

    void FITKGraphObjectVTK::addWidget(vtkInteractorObserver* widget)
    {
        if (!widget || m_widgetList.contains(widget))
        {
            return;
        }

        m_widgetList.push_back(widget);
    }

    vtkInteractorObserver* FITKGraphObjectVTK::getWidget(int index)
    {
        // 异常处理。
        if (index < 0 || index >= m_widgetList.count())
        {
            return nullptr;
        }

        return m_widgetList[index];
    }

    int FITKGraphObjectVTK::getWidgetCount()
    {
        return m_widgetList.count();
    }

    bool FITKGraphObjectVTK::hasFixedBounds()
    {
        return m_hasFixedBounds;
    }

    bool FITKGraphObjectVTK::getFixedBounds(double* bounds)
    {
        // 判断可视化对象外边界是否固定大小。
        if (!m_hasFixedBounds)
        {
            return false;
        }

        // 获取边界。
        double bds[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };
        bool hasBds = getActorsBounds(m_actorList, bds);
        for (int i = 0; i < 6; i++)
        {
            bounds[i] = bds[i];
        }

        return hasBds;
    }

    bool FITKGraphObjectVTK::getActorBounds(vtkProp* prop, double* bounds, bool ignoreVisibility)
    {
        // 异常处理。
        if (!prop)
        {
            return false;
        }

        if (!prop->GetVisibility() && !ignoreVisibility)
        {
            return false;
        }

        if (!prop->GetUseBounds())
        {
            return false;
        }

        // 获取使用包围盒的可视化对象尺寸。
        double* bds = prop->GetBounds();
        if (!bds)
        {
            return false;
        }

        for (int i = 0; i < 6; i++)
        {
            bounds[i] = bds[i];
        }

        return true;
    }

    bool FITKGraphObjectVTK::getActorsBounds(QList<vtkProp*> props, double* bounds)
    {
        bool hasBds = false;

        double bdsAll[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };

        for (vtkProp* prop : props)
        {
            if (!prop || !prop->GetVisibility())
            {
                continue;
            }

            double bds[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };

            // 不存在包围盒则跳过合并。
            bool flag = getActorBounds(prop, bds);
            if (!flag)
            {
                continue;
            }

            // 合并包围盒尺寸。
            if (bds[0] < bdsAll[0]) bdsAll[0] = bds[0];
            if (bds[1] > bdsAll[1]) bdsAll[1] = bds[1];

            if (bds[2] < bdsAll[2]) bdsAll[2] = bds[2];
            if (bds[3] > bdsAll[3]) bdsAll[3] = bds[3];

            if (bds[4] < bdsAll[4]) bdsAll[4] = bds[4];
            if (bds[5] > bdsAll[5]) bdsAll[5] = bds[5];

            hasBds = true;
        }

        for (int i = 0; i < 6; i++)
        {
            bounds[i] = bdsAll[i];
        }

        return hasBds;
    }
}
