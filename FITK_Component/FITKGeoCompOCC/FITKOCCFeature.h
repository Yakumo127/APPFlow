﻿/**
 * @file   FITKOCCFeature.h
 * @brief  occ几何特征类.
 * @author YanZhiHui (chanyuantiandao@126.com)
 * @date   2024-09-25
 */
#ifndef FITKOCCFEATURE_H
#define FITKOCCFEATURE_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoFeature.h"

namespace OCC {
    /**
         * @brief  occ几何特征类.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-10
         */
    class FITKGeoCompOCCAPI FITKOCCStiffener :
        public Interface::FITKAbsGeoStiffener, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-27
         */
        FITKOCCStiffener();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-27
         */
        ~FITKOCCStiffener() override = default;
        /**
         * @brief  更新模型.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-27
         */
        virtual bool update() override;

    private:
        /**
         * @brief   根据提供的线与形状获取交点，并获取最远交点间的参数值。
         * @param   shape：形状
         * @param   edge：线
         * @param   u1：起始参数
         * @param   u2：结束参数
         * @return  是否执行成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-09
         */
        bool getUByCrossPoint(TopoDS_Shape & shape, TopoDS_Shape & edge, double & u1, double u2);

    };

}
#endif // FITKOCCFEATURE_H
