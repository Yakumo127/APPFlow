/**
 *
 * @file FITKAbsGeomTools.h
 * @brief 抽象查询类声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-08-18
 *
 */
#ifndef _FITK_ABSTRACT_GEOM_TOOLS_H___
#define _FITK_ABSTRACT_GEOM_TOOLS_H___ 

#include "FITK_Kernel/FITKCore/FITKAbstractObject.hpp"
#include "FITKGeoEnum.h"
#include "FITKInterfaceGeometryAPI.h"

namespace Interface
{
    class FITKAbsVirtualTopo;

    /**
     * @brief 点查询类
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-08-18
     */
    class FITKInterfaceGeometryAPI FITKAbstractGeomPointTool :
        public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief Construct a new FITKAbstractGeomPointTool object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        explicit FITKAbstractGeomPointTool() = default;
        /**
         * @brief Destroy the FITKAbstractGeomPointTool object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        virtual ~FITKAbstractGeomPointTool() = default;
        /**
         * @brief 创建点查询类
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         * @return FITKAbstractGeomPointTool*
         */
        static FITKAbstractGeomPointTool* createTool();
        /**
         * @brief 获取点坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         * @param id 虚拓扑的id
         * @param oXyz 点的坐标
         * @return true 成功
         * @return false 失败
         */
        virtual bool getXYZByID(const int & id, double* oXyz, int modelId = -1);
        /**
         * @brief 获取点坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         * @param vtp 虚拓扑对象
         * @param oXyz 点的坐标
         * @return true 成功
         * @return false 失败
         */
        virtual bool getXYZ(FITKAbsVirtualTopo* vtp, double* oXyz, int modelId = -1)
        {
            Q_UNUSED(modelId);
            Q_UNUSED(vtp);
            Q_UNUSED(oXyz);
            return false;
        };

    };

    /**
     * @brief   线查询工具。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-12-03
     */
    class FITKInterfaceGeometryAPI FITKAbstractGeomEdgeTool :
        public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        explicit FITKAbstractGeomEdgeTool() = default;

        /**
         * @brief   析构函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        virtual ~FITKAbstractGeomEdgeTool() = default;

        /**
         * @brief   创建线信息查询工具。[静态]
         * @return  线信息查询工具
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        static FITKAbstractGeomEdgeTool* createTool();

        /**
         * @brief   获取方向。[虚函数]
         * @param   id：虚拓扑ID
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        virtual bool getStartPointDirectionByID(const int & id, double* oPos, double* oDir, int iModelId = -1);

        /**
         * @brief   获取方向。[虚函数]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-11
         */
        virtual bool getStartPointDirection(FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oPos);
            Q_UNUSED(oDir);
            Q_UNUSED(iModelId);
            return false;
        };

        /**
         * @brief   获取方向。[虚函数]
         * @param   id：虚拓扑ID
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        virtual bool getEndPointDirectionByID(const int & id, double* oPos, double* oDir, int iModelId = -1);

        /**
         * @brief   获取方向。[虚函数]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-11
         */
        virtual bool getEndPointDirection(FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oPos);
            Q_UNUSED(oDir);
            Q_UNUSED(iModelId);
            return false;
        };

        /**
         * @brief   获取方向。[虚函数]
         * @param   id：虚拓扑ID
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   u：截取位置（默认起始点）[缺省]
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        virtual bool getDirectionByID(const int & id, double* oPos, double* oDir, double u = 0., int iModelId = -1);

        /**
         * @brief   获取方向。[虚函数]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   u：截取位置（默认起始点）[缺省]
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        virtual bool getDirection(FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, double u = 0., int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oPos);
            Q_UNUSED(oDir);
            Q_UNUSED(u);
            Q_UNUSED(iModelId);
            return false;
        };

        /**
         * @brief   查询当前对象是否为直线。[虚函数]
         * @param   id：虚拓扑ID[引用]
         * @return  是否为直线
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-10
         */
        virtual bool isLineByID(const int & id);

        /**
         * @brief   查询当前对象是否为直线。[虚函数]
         * @param   vtp：线虚拓扑
         * @return  是否为直线
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-10
         */
        virtual bool isLine(FITKAbsVirtualTopo* vtp)
        {
            Q_UNUSED(vtp);
            return false;
        };

        /**
         * @brief   查询当前对象长度。[虚函数]
         * @param   id：虚拓扑ID[引用]
         * @param   oLen：线长[引用]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-16
         */
        virtual bool getLengthByID(const int & id, double & oLen);

        /**
         * @brief   查询当前对象长度。[虚函数]
         * @param   vtp：线虚拓扑
         * @param   oLen：线长[引用]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-16
         */
        virtual bool getLength(FITKAbsVirtualTopo* vtp, double & oLen)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oLen);
            return false;
        };

        /**
         * @brief   获取边中点坐标。[虚函数]
         * @param   id：边虚拓扑ID
         * @param   oPos：返回坐标信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-01
         */
        virtual bool getMidPointByID(const int & id, double* oPos, int iModelId = -1);

        /**
         * @brief   获取边中点坐标。[虚函数]
         * @param   vtp：边虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-01
         */
        virtual bool getMidPoint(FITKAbsVirtualTopo* vtp, double* oPos, int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oPos);
            Q_UNUSED(iModelId);
            return false;
        };

        /**
         * @brief   获取边上特征点坐标。[虚函数]
         * @param   id：边虚拓扑ID
         * @param   oPoses：返回坐标列表[引用]
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-02
         */
        virtual bool getFeaturePointsByID(const int & id, QList<QList<double>> & oPoses, int iModelId = -1);

        /**
         * @brief   获取边上特征点坐标。[虚函数]
         * @param   vtp：虚拓扑对象
         * @param   oPoses：返回坐标列表[引用]
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-02
         */
        virtual bool getFeaturePoints(FITKAbsVirtualTopo* vtp, QList<QList<double>> & oPoses, int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oPoses);
            Q_UNUSED(iModelId);
            return false;
        };
    };

    /**
     * @brief   面信息查询工具。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-09-05
     */
    class FITKInterfaceGeometryAPI FITKAbstractGeomFaceTool :
        public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        explicit FITKAbstractGeomFaceTool() = default;

        /**
         * @brief   析构函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual ~FITKAbstractGeomFaceTool() = default;

        /**
         * @brief   创建（实例化）工具方法。[静态]
         * @return  查询工具实例
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        static FITKAbstractGeomFaceTool* createTool();

        /**
         * @brief   获取平面信息。[虚函数]
         * @param   id：面虚拓扑ID（必须为平面）[引用]
         * @param   oPos：面中心点坐标
         * @param   oNormal：面法向
         * @param   oUp：面向上方向
         * @param   iModelId：模型ID[缺省]
         * @return  是否为有效平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual bool getPlaneByID(const int & id, double* oPos, double* oNormal, double* oUp, int iModelId = -1);

        /**
         * @brief   获取平面信息。[虚函数]
         * @param   vtp：面虚拓扑（必须为平面）
         * @param   oPos：面中心点坐标
         * @param   oNormal：面法向
         * @param   oUp：面向上方向
         * @param   iModelId：模型ID[缺省]
         * @return  是否为有效平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual bool getPlane(FITKAbsVirtualTopo* vtp, double* oPos, double* oNormal, double* oUp, int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(oPos);
            Q_UNUSED(oNormal);
            Q_UNUSED(oUp);
            Q_UNUSED(iModelId);
            return false;
        };

        /**
         * @brief   获取面上指定位置法向。[虚函数]
         * @param   id：面虚拓扑ID[引用]
         * @param   iPos：面上任意坐标
         * @param   oNormal：法向
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-16
         */
        virtual bool getNormalByID(const int & id, double* iPos, double* oNormal, int iModelId = -1);

        /**
         * @brief   获取面上指定位置法向。[虚函数]
         * @param   vtp：面虚拓扑
         * @param   iPos：面上任意坐标
         * @param   oNormal：法向
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-16
         */
        virtual bool getNormal(FITKAbsVirtualTopo* vtp, double* iPos, double* oNormal, int iModelId = -1)
        {
            Q_UNUSED(vtp);
            Q_UNUSED(iPos);
            Q_UNUSED(oNormal);
            Q_UNUSED(iModelId);
            return false;
        };

        /**
         * @brief   查询当前对象是否为平面。[虚函数]
         * @param   id：虚拓扑ID[引用]
         * @return  是否为平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-10
         */
        virtual bool isPlaneByID(const int & id);

        /**
         * @brief   查询当前对象是否为平面。[虚函数]
         * @param   vtp：面虚拓扑
         * @return  是否为平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-10
         */
        virtual bool isPlane(FITKAbsVirtualTopo* vtp)
        {
            Q_UNUSED(vtp);
            return false;
        };

        /**
         * @brief   查询指定列表拓扑是否均为平面且共面（不包含平行）。[虚函数]
         * @param   ids：虚拓扑ID列表
         * @return  拓扑是否均为平面且共面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-02
         */
        virtual bool isCoplanar(QList<int> ids)
        {
            Q_UNUSED(ids);
            return false;
        }

        /**
         * @brief   查询指定列表拓扑是否均为面且在同一个几何面上。[虚函数]
         * @param   ids：虚拓扑ID列表
         * @return  拓扑是否均为面且在同一个几何面上
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-22
         */
        virtual bool isSameSurface(QList<int> ids)
        {
            Q_UNUSED(ids);
            return false;
        }

    };

    /**
     * @brief   混合信息查询工具。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-04-24
     */
    class FITKInterfaceGeometryAPI FITKAbstractGeomCommonTool :
        public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        explicit FITKAbstractGeomCommonTool() = default;

        /**
         * @brief   析构函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        virtual ~FITKAbstractGeomCommonTool() = default;

        /**
         * @brief   创建（实例化）工具方法。[静态]
         * @return  查询工具实例
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        static FITKAbstractGeomCommonTool* createTool();

        /**
         * @brief   根据拓扑获取二者距离。[虚函数]
         * @param   vTopoId_1：第一个虚拓扑ID
         * @param   vTopoId_2：第二个虚拓扑ID
         * @param   oDist：距离[引用]
         * @param   oPos_1：拓扑1位置
         * @param   oPos_2：拓扑2位置
         * @return  是否存在有效距离
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        virtual bool getDistanceByTopoIDs(const int vTopoId_1, const int vTopoId_2, 
            double & oDist, double oPos_1[3], double oPos_2[3]);

        /**
         * @brief   根据拓扑获取二者距离。[虚函数]
         * @param   vtp_1：第一个虚拓扑对象
         * @param   vtp_2：第二个虚拓扑对象
         * @param   oDist：距离[引用]
         * @param   oPos_1：拓扑1位置
         * @param   oPos_2：拓扑2位置
         * @return  是否存在有效距离
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        virtual bool getDistanceByTopos(FITKAbsVirtualTopo* vtp_1, FITKAbsVirtualTopo* vtp_2
            , double & oDist, double oPos_1[3], double oPos_2[3])
        {
            Q_UNUSED(vtp_1);
            Q_UNUSED(vtp_2);
            Q_UNUSED(oDist);
            Q_UNUSED(oPos_1);
            Q_UNUSED(oPos_2);
            return false;
        };

        /**
         * @brief   获取拓扑与三维坐标点距离。[虚函数]
         * @param   vTopoId：虚拓扑ID
         * @param   iPos3：坐标
         * @param   oDist：距离[引用]
         * @param   oPos：拓扑位置
         * @return  是否存在有效距离
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        virtual bool getDistanceByTopoIDAndPos(const int vTopoId, double iPos3[3], double & oDist, double oPos[3]);

        /**
         * @brief   获取拓扑与三维坐标点距离。[虚函数]
         * @param   vtp：虚拓扑对象
         * @param   iPos3：坐标
         * @param   oDist：距离[引用]
         * @param   oPos：拓扑位置
         * @return  是否存在有效距离
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-24
         */
        virtual bool getDistanceByTopoAndPos(FITKAbsVirtualTopo* vtp, double iPos3[3], double & oDist, double oPos[3])
        {
            Q_UNUSED(vtp);
            Q_UNUSED(iPos3);
            Q_UNUSED(oDist);
            Q_UNUSED(oPos);
            return false;
        };

    };

    /**
     * @brief   特征信息查询工具。
     * @author  fulipeng (flipengqd@yeah.net)
     * @date    2025-01-09
     */
    class FITKInterfaceGeometryAPI FITKAbstractGeomFeatureTool : public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief   构造函数。
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-09
         */
        explicit FITKAbstractGeomFeatureTool() = default;

        /**
         * @brief   析构函数。
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-09
         */
        virtual ~FITKAbstractGeomFeatureTool() = default;

        /**
         * @brief   创建（实例化）工具方法。[静态]
         * @return  查询工具实例
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-09
         */
        static FITKAbstractGeomFeatureTool* createTool();

        /**
         * @brief   通过给定的虚拟拓扑数据对象获取特征信息.[虚函数]
         * @param   comId：命令ID 传递part对象ID
         * @param   featureType：特征类型
         * @param   oFeatures: 返回所有特征的链表 每个特征可能有多个面QList<QList<face>>
         * @return  查询结果是否有效
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-09
         */
        virtual bool getFeatures(int comId, FITKGeoEnum::FITKFeatureType featureType, QList<QList<Interface::FITKAbsVirtualTopo*>>& oFeatures)
        {
            Q_UNUSED(comId);
            Q_UNUSED(featureType);
            Q_UNUSED(oFeatures);
            return false;
        }
    };
    /**
     * @brief 抽象查询类生成器
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-08-18
     */
    class FITKInterfaceGeometryAPI FITKAbstractGeomToolsCreator
    {
    public:
        /**
         * @brief Construct a new FITKAbstractGeomToolsCreator object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        explicit FITKAbstractGeomToolsCreator() = default;
        /**
         * @brief Destroy the FITKAbstractGeomToolsCreator object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        virtual ~FITKAbstractGeomToolsCreator() = 0;
        /**
         * @brief 创建点查询类
         * @return FITKAbstractGeomPointTool*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        virtual FITKAbstractGeomPointTool* createPointTool();

        /**
         * @brief   创建线信息查询工具。[虚函数]
         * @return  线信息查询工具
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-03
         */
        virtual Interface::FITKAbstractGeomEdgeTool* createEdgeTool();

        /**
         * @brief   创建面信息查询工具。[虚函数]
         * @return  平面信息查询工具
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual Interface::FITKAbstractGeomFaceTool* createFaceTool();

        /**
         * @brief       创建通用信息查询工具。[虚函数]
         * @return      通用信息查询工具
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-04-24
         */
        virtual Interface::FITKAbstractGeomCommonTool* createCommonTool();

        /**
         * @brief   创建特征信息查询工具。[虚函数]
         * @return  特征信息查询工具
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-09
         */
        virtual Interface::FITKAbstractGeomFeatureTool* createFeatureTool();

    };
}

#endif
