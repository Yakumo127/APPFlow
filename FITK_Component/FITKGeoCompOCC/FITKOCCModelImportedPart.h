﻿/*****************************************************************//**
 * @file    FITKOCCModelImportedPart.h
 * @brief   导入的几何部件形状。
 *
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2025-03-27
 *********************************************************************/

#ifndef __FITKOCCMODELIMPORTEDPART_H__
#define __FITKOCCMODELIMPORTEDPART_H__

#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoImportedPart.h"
#include "FITKAbstractOCCModel.h"
#include "FITKGeoCompOCCAPI.h"

// 前置声明
class TopoDS_Shape;

namespace OCC
{
    /**
     * @brief   导入的几何部件形状。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-03-27
     */
    class FITKGeoCompOCCAPI FITKOCCModelImportedPart : public Interface::FITKAbsGeoImportedPart, public OCCShapeAgent
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        explicit FITKOCCModelImportedPart();

        /**
         * @brief   析构函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        virtual ~FITKOCCModelImportedPart() = default;

        /**
         * @brief   更新命令。[重写]
         * @return  是否更新成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool update() override;

        /**
         * @brief   保存几何形状。
         * @param   shape：几何形状[引用]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        void setShape(TopoDS_Shape & shape);

    };
}

#endif //!__FITKOCCMODELIMPORTEDPART_H__
