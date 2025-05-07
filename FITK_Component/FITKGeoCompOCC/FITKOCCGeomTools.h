/**
 * 
 * @file FITKOCCGeomTools.h
 * @brief OCC 几何工具类实现
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-08-18
 * 
 */

#ifndef _FITKOCC_GEOM_TOOLS_H___
#define _FITKOCC_GEOM_TOOLS_H___
 
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeomTools.h"

namespace OCC
{
    /**
     * @brief OCC工具生成器，注册到Interface层geomToolsCreator中
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-08-18
     */
    class FITKOCCToolCreator : public Interface::FITKAbstractGeomToolsCreator
    {
    public:
        /**
         * @brief Construct a new FITKOCCToolCreator object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        explicit FITKOCCToolCreator() = default;
        /**
         * @brief Destroy the FITKOCCToolCreator object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        virtual ~FITKOCCToolCreator() = default;
        /**
         * @brief 创建点工具类
         * @return Interface::FITKAbstractGeomPointTool* 
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        Interface::FITKAbstractGeomPointTool* createPointTool() override;

        /**
         * @brief   创建边查询工具[重写]
         * @return  边查询工具
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        Interface::FITKAbstractGeomEdgeTool* createEdgeTool() override;

        /**
         * @brief   创建平面查询工具。[重写]
         * @return  平面查询工具
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        Interface::FITKAbstractGeomFaceTool* createFaceTool() override;
    };

    /**
     * @brief 点工具类实现
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-08-18
     */
    class FITKOCCPointTool : public Interface::FITKAbstractGeomPointTool
    {
    public:
        /**
         * @brief Construct a new FITKOCCPointTool object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        explicit FITKOCCPointTool() = default;
        /**
         * @brief Destroy the FITKOCCPointTool object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         */
        virtual ~FITKOCCPointTool() = default;

        /**
         * @brief 获取点坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-18
         * @param vtp 虚拓扑对象
         * @param xyz 点的坐标
         * @return true 成功
         * @return false 失败
         */
        bool getXYZ(Interface::FITKAbsVirtualTopo* vtp, double* xyz, int iModelId = -1) override;
    };

    /**
     * @brief   OCC边查询工具。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-03-27
     */
    class FITKOCCEdgeTool : public Interface::FITKAbstractGeomEdgeTool
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        explicit FITKOCCEdgeTool() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        virtual ~FITKOCCEdgeTool() = default;

        /**
         * @brief   获取方向。[重写]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool getStartPointDirection(Interface::FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, int iModelId = -1) override;

        /**
         * @brief   获取方向。[重写]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool getEndPointDirection(Interface::FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, int iModelId = -1) override;

        /**
         * @brief   获取方向。[重写]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   oDir：返回方向信息
         * @param   u：截取位置（默认起始点）[缺省]
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool getDirection(Interface::FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, double iU = 0., int iModelId = -1) override;

        /**
         * @brief   查询当前对象是否为直线。[重写]
         * @param   vtp：线虚拓扑
         * @return  是否为直线
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool isLine(Interface::FITKAbsVirtualTopo* vtp) override;

        /**
         * @brief   查询当前对象长度。[重写]
         * @param   vtp：线虚拓扑
         * @param   oLen：线长[引用]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool getLength(Interface::FITKAbsVirtualTopo* vtp, double & oLen) override;

        /**
         * @brief   获取中点坐标。[重写]
         * @param   vtp：虚拓扑对象
         * @param   oPos：返回坐标信息
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-02
         */
        bool getMidPoint(Interface::FITKAbsVirtualTopo* vtp, double* oPos, int iModelId = -1) override;

        /**
         * @brief   获取边上特征点坐标。[重写]
         * @param   vtp：虚拓扑对象
         * @param   oPoses：返回坐标列表[引用]
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-02
         */
        bool getFeaturePoints(Interface::FITKAbsVirtualTopo* vtp, QList<QList<double>> & oPoses, int iModelId = -1) override;

    };

    /**
     * @brief   OCC面查询工具。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-09-05
     */
    class FITKOCCFaceTool : public Interface::FITKAbstractGeomFaceTool
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        explicit FITKOCCFaceTool() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        virtual ~FITKOCCFaceTool() = default;

        /**
         * @brief   获取查询信息。[重写]
         * @param   vtp：面虚拓扑（必须为平面）
         * @param   pos：面中心点坐标
         * @param   normal：面法向
         * @param   up：面向上方向
         * @param   iModelId：模型ID[缺省]
         * @return  是否为有效平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        bool getPlane(Interface::FITKAbsVirtualTopo* vtp, double* pos, double* normal, double* up, int iModelId = -1) override;

        /**
         * @brief   获取面上指定位置法向。[重写]
         * @param   id：面虚拓扑ID[引用]
         * @param   iPos：面上任意坐标
         * @param   oNormal：法向
         * @param   iModelId：模型ID[缺省]
         * @return  查询结果是否有效
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool getNormal(Interface::FITKAbsVirtualTopo* vtp, double* iPos, double* oNormal, int iModelId = -1) override;

        /**
         * @brief   查询当前对象是否为平面。[重写]
         * @param   vtp：面虚拓扑
         * @return  是否为平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        bool isPlane(Interface::FITKAbsVirtualTopo* vtp) override;

    };       
}

#endif
