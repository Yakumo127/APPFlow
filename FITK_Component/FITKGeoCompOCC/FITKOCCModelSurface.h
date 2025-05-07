#ifndef  FITKOCCMODELSURFACE_H
#define  FITKOCCMODELSURFACE_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSurface.h"

namespace OCC
{
    /**
     * @brief  封闭曲线形成的面.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelClosedWireSurface :
        public Interface::FITKAbsGeoModelClosedWireSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelClosedWireSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelClosedWireSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;
    };
    /**
     * @brief  偏移曲面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelOffsetSurface :
        public Interface::FITKAbsGeoModelOffsetSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelOffsetSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelOffsetSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;

    };

    /**
     * @brief  拉伸曲面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelExtrudeSurface :
        public Interface::FITKAbsGeoModelExtrudeSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelExtrudeSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelExtrudeSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;

    };

    /**
     * @brief  旋转曲面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelRevolSurface :
        public Interface::FITKAbsGeoModelRevolSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelRevolSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelRevolSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;

    };

    /**
     * @brief  修剪曲面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelRectangularTrimmedSurface :
        public Interface::FITKAbsGeoModelRectangularTrimmedSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelRectangularTrimmedSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelRectangularTrimmedSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;

    };

    /**
     * @brief  扫略曲面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelSweepSurface :
        public Interface::FITKAbsGeoModelSweepSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelSweepSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelSweepSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;

    };

    /**
     * @brief  多截面扫略抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKGeoCompOCCAPI FITKOCCModelMultiSectionSurface :
        public Interface::FITKAbsGeoModelMultiSectionSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelMultiSectionSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelMultiSectionSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;
    };

    /**
     * @brief  桥接曲面.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-27
     */
    class FITKGeoCompOCCAPI FITKOCCModelBridgeSurface :
        public Interface::FITKAbsGeoModelBridgeSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelBridgeSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelBridgeSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;
    };

    /**
     * @brief  体的面.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-27
     */
    class FITKGeoCompOCCAPI FITKOCCModelSolidSurface :
        public Interface::FITKAbsGeoModelSolidSurface, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKOCCModelSolidSurface();
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKOCCModelSolidSurface() = default;
        /**
         * @brief  更新模型.
         * @return 是否成功
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual bool update() override;
    };

}

#endif // !FITKOCCMODELSURFACE_H
