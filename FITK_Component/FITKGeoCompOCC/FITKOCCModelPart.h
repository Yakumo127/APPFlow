﻿/*****************************************************************//**
 * @file    FITKOCCModelPart.h
 * @brief   OCC几何部件。
 *
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2025-03-27
 *********************************************************************/

#ifndef  __FITKOCCMODELPART_H__
#define  __FITKOCCMODELPART_H__

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoPart.h"

#include "FITKGeoCompOCCAPI.h"

// 前置声明
class TopoDS_Shape;

namespace OCC
{
    /**
     * @brief   OCC几何部件。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-03-27
     */
    class FITKGeoCompOCCAPI FITKOCCModelPart : public Interface::FITKAbsGeoPart, public OCCShapeAgent
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        explicit FITKOCCModelPart();
        
        /**
         * @brief   析构函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        virtual ~FITKOCCModelPart() = default;

        /**
         * @brief   获取部件当前形状。
         * @return  部件形状
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        TopoDS_Shape* getPartShape();

        /**
         * @brief   获取部件当前形状的备份。
         * @return  部件形状
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        TopoDS_Shape getCopiedPartShape();

        /**
         * @brief   更新部件形状。
         * @param   shape：子命令形状
         * @param   unite：是否与原模型求和[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        void updatePartShape(TopoDS_Shape & shape, bool unite = false);

        /**
         * @brief   几何形状回退：同步部件几何形状。
         * @return  是否执行成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-28
         */
        bool backtrackingShape() override;

        /**
         * @brief   更新命令。
         * @return  是否更新成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        virtual bool update() override;

        /**
         * @brief   重写添加数据对象功能。（添加命令并更新部件几何）[重写]
         * @param   obj：数据对象
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        void appendDataObj(Core::FITKAbstractDataObject* obj) override;

    };
}

#endif // !__FITKOCCMODELPART_H__
