/*****************************************************************//**
 * @file    FITKAbsGeoModelOperFace.h
 * @brief   抽象面操作类
 *
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-08-21
 *********************************************************************/

#ifndef  FITKABSGEOMODELOPERFACE_H
#define  FITKABSGEOMODELOPERFACE_H

#include "FITKInterfaceGeometryAPI.h"
#include "FITKAbsGeoCommand.h"


namespace Interface
{
    class FITKAbsGeoShapeAgent;

    /**
     * @brief  抽象面操作类
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-21
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFace : public FITKAbsGeoCommand
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFace);
    public:

        /**
         * @brief  面操作类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-21
         */
        enum GeoFaceOperType
        {
            GBTNone,
            GBTFillHoles,                ///填补孔洞
            GBTFillGaps,                 ///填补缝隙
            GBTDeleteFloatingEdge,       ///删除悬浮边
            GBTImprintMapPointToFace,    ///点映射到面
            GBTImprintMapLineToFace,     ///线映射到面
            GBTImprintMapCircleToFace,   ///圆映射到面
        };

    public:
        FITKAbsGeoModelOperFace() = default;
        virtual ~FITKAbsGeoModelOperFace() override = default;

        /**
         * @brief   添加操作对象
         * @param   geoCommandShape：操作对象结构体
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-21
         */
        void add(VirtualShape geoCommandShape);

        /**
         * @brief   添加操作对象
         * @param   geoCommandShape：操作对象结构体
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-21
         */
        void set(VirtualShape geoCommandShape);

        /**
         * @brief   添加多个操作对象
         * @param   geoCommandShapes：操作对象结构体链表
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-21
         */
        void add(QList<VirtualShape> geoCommandShapes);

        /**
         * @brief   添加多个操作对象
         * @param   geoCommandShapes：操作对象结构体链表
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-21
         */
        void set(QList<VirtualShape> geoCommandShapes);

        /**
         * @brief   移除操作对象
         * @param   index：索引
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-21
         */
        void remove(int index);

        /**
         * @brief   移除所有操作对象
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-26
         */
        void clear();

        /**
         * @brief   设置类型
         * @param   t：操作类型
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-26
         */
        void setType(GeoFaceOperType t);

        /**
         * @brief   获取类型
         * @return  返回操作类型
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-26
         */
        FITKAbsGeoModelOperFace::GeoFaceOperType getType();

        /**
         * @brief   获取虚拓扑图形
         * @return   geoCommand：操作对象
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-19
         */
        QList<VirtualShape> getVShapes();
        /**
         * @brief   获取操作对象列表
         * @return  操作对象列表
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-21
         */
        QList<int> getModelOperFacesID();

        /**
         * @brief   设置公差
         * @param   tolerance 公差
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        void setTolerance(double tolerance);

        /**
         * @brief  获取公差
         * @return 操作对象列表
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-23
         */
        double getTolerance();

    protected:

        /**
         * @brief   通过形状类型、命令ID、虚拓扑ID 获取形状
         * @param   shapeType       形状类型
         * @param   m_solidCmdId    命令ID
         * @param   virtualTopoId   虚拓扑ID
         * @return  返回虚拓扑形状
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-26
         */
        Interface::FITKAbsVirtualTopo* getRefModelVirtualTopo(Interface::FITKGeoEnum::VTopoShapeType shapeType, int m_solidCmdId, int virtualTopoId);

    protected:
        /**
         * @brief  面操作类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-21
         */
        GeoFaceOperType _faceOperType{ GBTNone };

        /**
         * @brief  操作对象列表
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-21
         */
        QList<VirtualShape> m_tempVShapes{};

        /**
         * @brief  公差
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-23
         */
        double _tolerance = 1e-2;
    };

    /**
     * @brief  抽象面操作类 移除面
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2025-03-24
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFaceRemoveFace : public FITKAbsGeoModelOperFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFaceRemoveFace);
    public:
        FITKAbsGeoModelOperFaceRemoveFace() = default;
        ~FITKAbsGeoModelOperFaceRemoveFace() = default;

        /**
         * @brief  获取几何命令类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;
    };

    /**
     * @brief  抽象面操作类 延伸面
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2025-03-26
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFaceExtendFace : public FITKAbsGeoModelOperFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFaceExtendFace);
    public:
        /**
         * @brief  Specify界面选择类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2025-04-01
         */
        enum SpecifyModel
        {
            SpecifyEdge,
            SpecifyFace,
        };
        /**
         * @brief  界面选择类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2025-04-01
         */
        enum MethodModel
        {
            MethodDistance,
            MethodFace,
        };

    public:
        FITKAbsGeoModelOperFaceExtendFace() = default;
        ~FITKAbsGeoModelOperFaceExtendFace() = default;

        /**
         * @brief  获取几何命令类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

        /**
         * @brief   设置线参数
         * @param   edges:线参数
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        void setEdges(QList<VirtualShape> edges);
        /**
         * @brief   获取线
         * @return  线参数
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        QList<VirtualShape> getEdges();

        /**
         * @brief   设置选择的面
         * @param   face 面参数
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        void setFaces(QList<VirtualShape> face);

        /**
         * @brief   获取选择的面
         * @return  面参数
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        QList<VirtualShape> getFaces();

        /**
         * @brief   设置标记面
         * @param   tagFaces 标记面
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        void setTagFaces(QList<VirtualShape> tagFaces);
        /**
         * @brief   获取标记面
         * @return  标记面
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        QList<VirtualShape> getTagFaces();

        /**
         * @brief   设置距离
         * @param   dis 距离
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        void setDistance(double dis);
        /**
         * @brief   获取距离
         * @return  距离
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        double getDistance();

        /**
         * @brief   设置是否修剪
         * @param   isTrim 是否开启修剪
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-26
         */
        void setTrim(bool isTrim);

        /**
        * @brief   是否修剪
        * @return  是否开启修剪
        * @author  fulipeng (fulipengqd@yeah.net)
        * @date    2025-03-26
        */
        bool getTrim();

        /**
         * @brief   设置延伸面选择方法
         * @param   sm
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-04-01
         */
        void setSpecifyMode(SpecifyModel sm);

        /**
         * @brief   设置延伸面方法
         * @param   mm
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-04-01
         */
        void setMethodModel(MethodModel mm);

    protected:
        /**
         * @brief   延伸长度
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-26
         */
        double _distance = 0;

        /**
         * @brief   Trim to extended underlying target surfaces
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-03-31
         */
        bool _trim = false;

        /**
         * @brief  线操作对象列表
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2025-04-01
         */
        QList<VirtualShape> _tempEdgeShapes{};

        /**
         * @brief  操作对象列表
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2025-04-01
         */
        QList<VirtualShape> _tempTagFaceShapes{};

        /**
         * @brief   key specify value Method 用于区分界面选项
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-04-01
         */
        QPair<SpecifyModel, MethodModel> _selectedMode{ SpecifyEdge,MethodDistance };

    };

    /**
     * @brief  抽象面操作类 修复面
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2025-03-26
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFaceRepairFaces : public FITKAbsGeoModelOperFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFaceRepairFaces);
    public:
        FITKAbsGeoModelOperFaceRepairFaces() = default;
        ~FITKAbsGeoModelOperFaceRepairFaces() = default;

        /**
         * @brief  获取几何命令类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;
    };

    /**
     * @brief  抽象面操作类 填补缝隙
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-21
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFaceFillGaps : public FITKAbsGeoModelOperFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFaceFillGaps);
    public:
        FITKAbsGeoModelOperFaceFillGaps() = default;
        ~FITKAbsGeoModelOperFaceFillGaps() = default;

        /**
         * @brief  获取几何命令类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

    protected:

    };

    /**
     * @brief  抽象面操作类 填补孔洞
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-21
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFaceFillHoles : public FITKAbsGeoModelOperFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFaceFillHoles);
    public:
        FITKAbsGeoModelOperFaceFillHoles() = default;
        ~FITKAbsGeoModelOperFaceFillHoles() = default;

        /**
         * @brief  获取几何命令类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

    protected:

    };

    /**
     * @brief  抽象面操作类 删除悬浮边
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-21
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelOperFaceDeleteFloatingEdge : public FITKAbsGeoModelOperFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelOperFaceDeleteFloatingEdge);
    public:
        FITKAbsGeoModelOperFaceDeleteFloatingEdge() = default;
        ~FITKAbsGeoModelOperFaceDeleteFloatingEdge() = default;

        /**
         * @brief  获取几何命令类型
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

        /**
         * @brief  设置主面
         * @param  vface：主面
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        void setMFace(VirtualShape vface);

        /**
         * @brief  获取主面
         * @return 主面
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        VirtualShape getMFace();

    protected:

        /**
         * @brief  操作主面
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-31
         */
        VirtualShape m_face{};
    };
}

#endif // !FITKAbsGeoModelOperFace_H