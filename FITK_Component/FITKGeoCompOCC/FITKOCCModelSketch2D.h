/*****************************************************************//**
 * @file    FITKOCCModelSketch2D.h
 * @brief   OCC2D草图数据类

 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-09-05
 *********************************************************************/

#ifndef __FITKOCCMODELSKETCH_H__
#define __FITKOCCMODELSKETCH_H__
 
#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoSketch2D.h"

namespace OCC
{
    /**
     * @brief   OCC2D草图数据类。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-09-05
     */
    class FITKGeoCompOCCAPI FITKOCCModelSketch2D :public Interface::FITKAbsGeoSketch2D,
        public OCCShapeAgent
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        explicit FITKOCCModelSketch2D();

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual ~FITKOCCModelSketch2D() = default;

        /**
         * @brief   更新数据。[虚函数][重写]
         * @return  是否更新成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual bool update() override;

        /**
         * @brief   判断草图是否闭合。[虚函数][重写]
         * @return  草图是否闭合
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-01
         */
        virtual bool isClosed() override;

    };
}

#endif // __FITKOCCMODELSKETCH_H__
