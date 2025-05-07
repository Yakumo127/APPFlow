﻿/**
 * @file   FITKOCCReferencePlane.h
 * @brief  基准面.
 * @author YanZhiHui (chanyuantiandao@126.com)
 * @date   2024-09-04
 */
#ifndef FITKOCCREFERENCEPLANE_H
#define FITKOCCREFERENCEPLANE_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoReferencePlane.h"
#include <array>

namespace OCC
{
    /**
     * @brief  基准面.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-27
     */
    class FITKGeoCompOCCAPI FITKOCCReferencePlane :
        public Interface::FITKAbsGeoReferencePlane, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferencePlane();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferencePlane() override = default;
        /**
         * @brief  更新数据对象.
         * @return 是否更新成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        virtual bool update() override;
    };

    /**
     * @brief  偏移方式创建基准面.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-27
     */
    class FITKGeoCompOCCAPI FITKOCCReferenceOffsetPlane :
        public Interface::FITKAbsGeoReferenceOffsetPlane, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferenceOffsetPlane();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferenceOffsetPlane() override = default;
        /**
         * @brief  更新数据对象.
         * @return 是否更新成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        virtual bool update() override;
    };
    /**
     * @brief  三点创建参考面类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCReferenceThreePointsPlane :
        public Interface::FITKAbsGeoReferenceThreePointsPlane, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferenceThreePointsPlane();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferenceThreePointsPlane() override = default;
        /**
         * @brief  更新数据对象.
         * @return 是否更新成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        virtual bool update() override;
    };

    /**
     * @brief  方程（Ax+By+Cz+D=0）创建参考面类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCReferenceEquationPlane :
        public Interface::FITKAbsGeoReferenceEquationPlane, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferenceEquationPlane();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferenceEquationPlane() override = default;
        /**
         * @brief  更新数据对象.
         * @return 是否更新成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        virtual bool update() override;
    };

    /**
     * @brief  点和法线创建参考面类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCReferencePointAndDirectionPlane :
        public Interface::FITKAbsGeoReferencePointAndDirectionPlane, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferencePointAndDirectionPlane();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferencePointAndDirectionPlane() override = default;
        /**
         * @brief  更新数据对象.
         * @return 是否更新成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        virtual bool update() override;
    };
}
#endif // FITKOCCREFERENCEPLANE_H
