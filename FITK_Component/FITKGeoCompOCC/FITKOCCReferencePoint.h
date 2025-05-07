﻿/**
 * @file   FITKOCCReferencePoint.h
 * @brief  基准点.
 * @author YanZhiHui (chanyuantiandao@126.com)
 * @date   2024-09-04
 */
#ifndef FITKOCCREFERENCEPOINT_H
#define FITKOCCREFERENCEPOINT_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoDatum.h"

namespace OCC
{
    /**
     * @brief  坐标点.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-27
     */
    class FITKGeoCompOCCAPI FITKOCCReferencePoint :public Interface::FITKAbsGeoDatumPoint, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferencePoint();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferencePoint() override = default;
        /**
         * @brief  更新数据对象.
         * @return 是否更新成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        virtual bool update() override;
        /**
         * @brief  获取基准元素类型.
         * @return 基准元素类型
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        Interface::FITKGeoEnum::FITKDatumType getDatumType() override;
    };
}

#endif // FITKOCCREFERENCEPOINT_H
