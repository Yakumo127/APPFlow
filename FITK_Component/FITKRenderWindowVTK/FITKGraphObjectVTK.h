﻿/**
 * 
 * @file FITKGraphObject.h
 * @brief 渲染对象接口声明 
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-03-12
 * 
 */
#ifndef _FITKGraphObject_H_VTK_
#define _FITKGraphObject_H_VTK_

#include "FITKRenderWindowVTKAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractGraphObject.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include <QObject>

class vtkProp;
class vtkPlane;
class vtkInteractorObserver;
class vtkDataSetMapper;
class vtkAlgorithmOutput;

namespace Core 
{
    class FITKAbstractDataObject;
}

namespace Comp
{
    /**
     * @brief 渲染对象接口声明
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-03-12
     */
    class FITKRenderWindowVTKAPI FITKGraphObjectVTK :
        public Core::FITKAbstractGraphObject
    {
        FITKCLASS(Comp, FITKGraphObjectVTK);
        Q_OBJECT

    public:
        /**
         * @brief   The clip type of the graph object.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-10
         */
        enum GraphClipType
        {
            NoneType = -1,
            Clip = 0,
            Cut,
            ExtractGeometry
        };

        /**
         * @brief Construct a new FITKGraphObject object
         * @param[i]  dataObject     数据对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-25
         */
        explicit FITKGraphObjectVTK(Core::FITKAbstractDataObject* dataObject);
        explicit FITKGraphObjectVTK();
        /**
         * @brief Destroy the FITKActor object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        virtual ~FITKGraphObjectVTK();

        /**
         * @brief   Enable or disable global clip mode.[virtual]
         * @param   type: The clip type
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-10
         */
        virtual void setClipType(GraphClipType type);

        /**
         * @brief   Set the custom clip plane.[virtual]
         * @param   org: The origin of the plane
         * @param   nor: The normal of the plane
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-10
         */
        virtual void setCustomClipPlane(double* org, double* nor);

        /**
         * @brief 添加VTK渲染对象
         * @param[i]  actor          vtkProp对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        virtual void addActor(vtkProp* actor);
        /**
         * @brief 获取VTK渲染对象
         * @param[i]  index          索引值
         * @return vtkProp* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        vtkProp* getActor(int index);
 
        /**
         * @brief 获取VTK渲染对象数量
         * @return int 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-14
         */
        int getActorCount();

        /**
         * @brief   添加控件。
         * @param   widget：控件
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-05
         */
        virtual void addWidget(vtkInteractorObserver* widget);

        /**
         * @brief   根据索引获取当前可视化对象控件。
         * @param   index：索引
         * @return  控件
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-05
         */
        vtkInteractorObserver* getWidget(int index);

        /**
         * @brief   获取当前可视化对象所有控件数量。
         * @return  数量
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-05
         */
        int getWidgetCount();

        /**
         * @brief   外边界是否为固定值，不会随相机变化发生变化。
         * @return  是或否
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-17
         */
        bool hasFixedBounds();

        /**
         * @brief   获取当前可视化对象内固定尺寸包围盒尺寸。[虚函数]
         * @param   包围盒尺寸
         * @return  包围盒是否为空
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-17
         */
        virtual bool getFixedBounds(double* bounds);

        /**
         * @brief   获取演员包围盒。
         * @param   prop：演员
         * @param   bounds：包围盒
         * @param   ignoreVisibility：是否无视隐藏
         * @return  是否存在包围盒
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-17
         */
        bool getActorBounds(vtkProp* prop, double* bounds, bool ignoreVisibility = false);

        /**
         * @brief   获取一组演员包围盒。
         * @param   props：演员列表
         * @param   bounds：包围盒
         * @return  是否存在包围盒
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-17
         */
        bool getActorsBounds(QList<vtkProp*> props, double* bounds);

        /**
         * @brief 获取数据对象
         * @return Core::FITKAbstractDataObject* 
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-22
         */
//         Core::FITKAbstractDataObject* getDataObject();
//     signals:
//         /**
//          * @brief 移除渲染对象
//          * @param[i]  object         渲染对象
//          * @author BaGuijun (baguijun@163.com)
//          * @date 2024-03-14
//          */
//         void removeObjectSig(FITKGraphObject* object);
//         /**
//          * @brief 刷新渲染对象
//          * @param[i]  object         渲染对象
//          * @author BaGuijun (baguijun@163.com)
//          * @date 2024-03-14
//          */
//         void reRenderObjectSig(FITKGraphObject* object);
//         /**
//          * @brief 强制刷新
//          * @author BaGuijun (baguijun@163.com)
//          * @date 2024-03-14
//          */
//         void reRenderSig();
 
         
    protected:
        /**
         * @brief VTK渲染对象组
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-03-12
         */
        QList<vtkProp*> m_actorList;

        /**
         * @brief   VTK抽象控件组。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-05
         */
        QList<vtkInteractorObserver*> m_widgetList;
        
        /**
         * @brief   是否存在固定外边界大小。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-05-17
         */
        bool m_hasFixedBounds = true;

        /**
         * @brief   模型（面）偏移系数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-11-11
         */
        double m_polygonOffset = 0.;
        /**
         * @brief  平面函数
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-10
         */
        vtkPlane* m_planeFunction = nullptr;
        /**
         * @brief  是否开启裁切
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-10
         */
        bool m_isOpenClip = false;
        /**
         * @brief   裁切平面。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-10
         */
        vtkPlane* m_clipPlane{ nullptr };

    };
}
#endif
