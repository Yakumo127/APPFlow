#ifndef FITKOCCREFERENCELINE_H
#define FITKOCCREFERENCELINE_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoDatum.h"

namespace OCC
{
    /**
     * @brief  坐标点.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-27
     */
    class FITKGeoCompOCCAPI FITKOCCReferenceLine :public Interface::FITKAbsGeoDatumLine, public OCCShapeAgent
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        FITKOCCReferenceLine();
        /**
         * @brief  .
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        ~FITKOCCReferenceLine() override = default;
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
#endif // FITKOCCREFERENCELINE_H
