#ifndef  FITKABSGEOREFERENCELINE_H
#define  FITKABSGEOREFERENCELINE_H

#include "FITKInterfaceGeometryAPI.h"
#include "FITKAbsGeoDatum.h"
#include <array>

namespace Interface
{
    /**
     * @brief  曲线抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-13
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferenceLine :
        public FITKAbsGeoDatumLine
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        FITKAbsGeoReferenceLine() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        virtual ~FITKAbsGeoReferenceLine() = default;

    };
    /**
     * @brief  有限线段抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-13
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferenceSegment : public FITKAbsGeoReferenceLine {
        FITKCLASS(Interface, FITKAbsGeoReferenceSegment);
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        FITKAbsGeoReferenceSegment() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        ~FITKAbsGeoReferenceSegment() override = default;
        /**
         * @brief  获取起点.
         * @return 起点坐标数组
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        std::array<double, 3> startPoint() const { return { m_pos[0] ,m_pos[1] ,m_pos[2] }; };
        /**
         * @brief  设置起点.
         * @param  x 起点的x坐标值
         * @param  y 起点的y坐标值
         * @param  z 起点的z坐标值
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        void setStartPoint(double x, double y, double z) { m_pos[0] = x; m_pos[1] = y; m_pos[2] = z; };
        void setStartPoint(std::array<double, 3> xyz) { m_pos[0] = xyz[0]; m_pos[1] = xyz[1]; m_pos[2] = xyz[2]; };
        /**
         * @brief  获取终点.
         * @return 终点坐标数组
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        std::array<double, 3> endPoint() const { return { m_pos2[0] ,m_pos2[1] ,m_pos2[2] }; };
        /**
         * @brief  设置终点.
         * @param  x 终点的x坐标值
         * @param  y 终点的y坐标值
         * @param  z 终点的z坐标值
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        void setEndPoint(double x, double y, double z) { m_pos2[0] = x; m_pos2[1] = y; m_pos2[2] = z; };
        void setEndPoint(std::array<double, 3> xyz) { m_pos2[0] = xyz[0]; m_pos2[1] = xyz[1]; m_pos2[2] = xyz[2]; };
        /**
         * @brief   获取基准元素类型。[重写]
         * @return  基准元素类型
         * @author  @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-13
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

    };

}

#endif // !FITKABSGEOREFERENCELINE_H
