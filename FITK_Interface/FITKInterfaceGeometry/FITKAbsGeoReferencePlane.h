#ifndef  FITKABSGEOREFERENCEPLANE_H
#define  FITKABSGEOREFERENCEPLANE_H

#include "FITKInterfaceGeometryAPI.h"
#include "FITKAbsGeoDatum.h"
#include <array>

namespace Interface
{
    /**
     * @brief  参考面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferencePlane :
        public FITKAbsGeoDatumPlane
    {
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKAbsGeoReferencePlane() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKAbsGeoReferencePlane() = default;

        void setPosition(double x, double y, double z) {
            m_pos[0] = x; m_pos[1] = y; m_pos[2] = z;
        }
        void setNormal(double x, double y, double z) {
            m_nor[0] = x; m_nor[1] = y; m_nor[2] = z;
        }
        void setUp(double x, double y, double z) {
            m_up[0] = x; m_up[1] = y; m_up[2] = z;
        }
    };


    /**
     * @brief  偏移参考面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferenceOffsetPlane :
        public FITKAbsGeoReferencePlane
    {
        FITKCLASS(Interface, FITKAbsGeoReferenceOffsetPlane);
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKAbsGeoReferenceOffsetPlane() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKAbsGeoReferenceOffsetPlane() = default;
        /**
         * @brief  获取基准面类型.
         * @return 命令类型
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

        VirtualShape sourceSurface() const { return m_SourceSurface; }
        void setSourceSurface(VirtualShape obj) { m_SourceSurface = obj; }
        std::array<double, 3> direction() const { return m_Direction; };
        void setDirection(std::array<double, 3> dir) { m_Direction = dir; };
        void setDirection(double x, double y, double z) { m_Direction = { x,y,z }; };
        double offset() const { return m_Offset; };
        void setOffset(double offset) { m_Offset = offset; };
    protected:
        /**
         * @brief  源面.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-23
         */
        VirtualShape m_SourceSurface{};
        /**
         * @brief  偏移方向.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-23
         */
        std::array<double, 3> m_Direction{};
        /**
         * @brief  偏移距离.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        double m_Offset{};
    };

    /**
     * @brief  三点创建参考面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferenceThreePointsPlane :
        public FITKAbsGeoReferencePlane
    {
        FITKCLASS(Interface, FITKAbsGeoReferenceThreePointsPlane);
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKAbsGeoReferenceThreePointsPlane() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKAbsGeoReferenceThreePointsPlane() = default;
        /**
         * @brief  获取基准面类型.
         * @return 命令类型
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

        std::array<double, 3> point(int index) {
            assert(index >= 0 && index < 3);
            return m_Points[index];
        }
        void setPoint(int index, std::array<double, 3> xyz) {
            assert(index >= 0 && index < 3);
            m_Points[index] = xyz;
        }
        void setPoint(int index, double x, double y, double z) {
            assert(index >= 0 && index < 3);
            m_Points[index] = { x,y,z };
        }
    protected:
        /**
         * @brief  面上的三点.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-09-04
         */
        std::array<std::array<double, 3>, 3> m_Points{};
    };

    /**
     * @brief  方程（Ax+By+Cz+D=0）创建参考面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferenceEquationPlane :
        public FITKAbsGeoReferencePlane
    {
        FITKCLASS(Interface, FITKAbsGeoReferenceEquationPlane);
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKAbsGeoReferenceEquationPlane() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKAbsGeoReferenceEquationPlane() = default;
        /**
         * @brief  获取基准面类型.
         * @return 命令类型
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

        double a() const { return m_A; }
        void setA(double val) { m_A = val; }
        double b() const { return m_B; }
        void setB(double val) { m_B = val; }
        double c() const { return m_C; }
        void setC(double val) { m_C = val; }
        double d() const { return m_D; }
        void setD(double val) { m_D = val; }
    protected:
        /* 平面方程（Ax+By+Cz+D=0）系数 */
        /* @{ */
        double m_A{ 0 };
        double m_B{ 0 };
        double m_C{ 0 };
        double m_D{ 0 };
        /* @} */
    };
    /**
     * @brief  点和法线创建参考面抽象类.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2024-08-16
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoReferencePointAndDirectionPlane :
        public FITKAbsGeoReferencePlane
    {
        FITKCLASS(Interface, FITKAbsGeoReferencePointAndDirectionPlane);
    public:
        /**
         * @brief  构造函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKAbsGeoReferencePointAndDirectionPlane() = default;
        /**
         * @brief  析构函数.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        virtual ~FITKAbsGeoReferencePointAndDirectionPlane() = default;
        /**
         * @brief  获取基准面类型.
         * @return 命令类型
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

        std::array<double, 3> point() {
            return m_Point;
        }
        void setPoint(std::array<double, 3> xyz) {
            m_Point = xyz;
        }
        void setPoint(double x, double y, double z) {
            m_Point = { x,y,z };
        }

        std::array<double, 3> direction() {
            return m_Direction;
        }
        void setDirection(std::array<double, 3> xyz) {
            m_Direction = xyz;
        }
        void setDirection(double x, double y, double z) {
            m_Direction = { x,y,z };
        }

    protected:
        /**
         * @brief  平面上的一点.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        std::array<double, 3> m_Point{};
        /**
         * @brief  平面的法线法向.
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-16
         */
        std::array<double, 3> m_Direction{};
    };
}

#endif // !FITKABSGEOREFERENCEPLANE_H
