/**********************************************************************
 * @file   FITKOFBoundary.h
 * @brief  流体相关边界数据结构
 * @author BaGuijun (baguijun@163.com)
 * @date   2025-04-14
 *********************************************************************/
#ifndef _FITK_OF_BOUNDARY__H___
#define _FITK_OF_BOUNDARY__H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITKOFEnum.hpp"

namespace Interface
{
    class FITKOFAbsBoundaryType;
    class FITKBoundaryMeshVTK;
    /**
     * @brief  边界数据对象
     * @author BaGuijun (baguijun@163.com)
     * @date   2025-04-14
     */
    class FITKInterfaceFlowOFAPI FITKOFBoundary : public Core::FITKAbstractNDataObject
    {
        Q_OBJECT;
        FITKCLASS(Interface, FITKOFBoundary);
    public:
        /**
         * @brief    构造函数
         * @param[i] bType                      边界类型
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        explicit FITKOFBoundary(FITKOFSolverTypeEnum::FITKOFBoundaryType bType);
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        virtual ~FITKOFBoundary();
        /**
         * @brief    获取边界类型
         * @return   FITKOFSolverTypeEnum::FITKOFBoundaryType           边界类型
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        FITKOFSolverTypeEnum::FITKOFBoundaryType getBoundaryType();
        /**
         * @brief    设置网格边界id
         * @param[i] meshId                      网格边界id
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        void setMeshBoundaryID(int meshId);
        /**
         * @brief    获取网格边界id
         * @return   int                         网格边界id
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        int getMeshBoundaryID();
        /**
         * @brief    获取网格边界
         * @return   FITKBoundaryMeshVTK*         网格边界
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        FITKBoundaryMeshVTK* getMeshBoundary();
        /**
         * @brief    获取流体参数类型数量
         * @return   int                        流体参数类型数量（P、U等）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        int getFlowCount();
        /**
         * @brief    通过索引获取流体参数类型名称
         * @param[i] index                       索引
         * @return   QString                     流体参数类型名称（P、U等）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        QString getFlowVariableName(int index);
        /**
         * @brief    通过索引获取流体参数类型对象
         * @param[i] index                       索引
         * @return   FITKOFAbsBoundaryType*      流体参数类型对象（P、U等）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        FITKOFAbsBoundaryType* getFlowVBType(int index);
        /**
         * @brief    获取湍流参数类型数量
         * @return   int                         湍流参数类型数量（K、omega等）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        int getTurbulenceCount();
        /**
         * @brief    通过索引获取湍流参数类型名称
         * @param[i] index                       索引
         * @return   QString                     湍流参数类型名称（K、omega等）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        QString getTurbulenceVariableName(int index);
        /**
         * @brief    通过索引获取湍流参数类型对象
         * @param[i] index                       索引
         * @return   FITKOFAbsBoundaryType*      湍流参数类型对象（K、omega等）
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        FITKOFAbsBoundaryType* getTurbulenceVBType(int index);

        int getPhasesCount();
        QString getPhasesVariableName(int index);
        FITKOFAbsBoundaryType* getPhasesVBType(int index);
        /**
         * @brief    设置流体边界参数类型对象（数据存在替换、数据不存在添加）
         * @param[i] variableName                      名称
         * @param[i] boundaryType                      参数类型对象
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        void setFlowBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType);
        /**
         * @brief    设置湍流边界参数类型对象（数据存在替换、数据不存在添加）
         * @param[i] variableName                      名称
         * @param[i] boundaryType                      参数类型对象
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        void setTurbulenceBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType);
        void setPhasesBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType);
        /**
         * @brief    设置边界参数类型对象（数据存在替换、数据不存在添加）
         * @param[i] variableName                      名称
         * @param[i] boundaryType                      参数类型对象
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        void setBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType);
        void clearTurbulenceBoundary();
        /**
         * @brief    通过名称获取边界参数类型对象
         * @param[i] variableName                     名称
         * @return   FITKOFAbsBoundaryType*           边界参数类型对象
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        FITKOFAbsBoundaryType* getBoundary(QString variableName);
    private:
        /**
         * @brief  网格边界id
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-14
         */
        int _meshBoundaryID{ -1 };
        /**
         * @brief  边界类型
         * @author BaGuijun (baguijun@163.com)
         * @date   2025-04-14
         */
        FITKOFSolverTypeEnum::FITKOFBoundaryType _boundaryType{ FITKOFSolverTypeEnum::FITKOFBoundaryType::BNone };
        /**
         * @brief  Flow 里的变量边界信息 <变量名称, 边界类型数据对象>
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-26
         */
        QList<QPair<QString, FITKOFAbsBoundaryType*>> _flow{};
        /**
         * @brief  Turbulence 里的变量边界信息 <变量名称, 边界类型数据对象>
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-26
         */
        QList<QPair<QString, FITKOFAbsBoundaryType*>> _turbulence{};
        /**
         * @brief  Phases 里的变量边界信息 <变量名称, 边界类型数据对象>
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-26
         */
        QList<QPair<QString, FITKOFAbsBoundaryType*>> _phases{};
    };
    /**
     * @brief  边界管理器
     * @author BaGuijun (baguijun@163.com)
     * @date   2025-04-14
     */
    class FITKInterfaceFlowOFAPI FITKOFBoundaryManager
        : public Core::FITKAbstractDataManager<FITKOFBoundary>
    {
    public:
        /**
         * @brief    构造函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        explicit FITKOFBoundaryManager() = default;
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        virtual ~FITKOFBoundaryManager() = default;
        /**
         * @brief    获取同种类型的所有边界
         * @param[i] t                               边界类型
         * @return   QList<FITKOFBoundary*>          所有边界
         * @author   BaGuijun (baguijun@163.com)
         * @date     2025-04-14
         */
        QList<FITKOFBoundary*> getBoundarys(FITKOFSolverTypeEnum::FITKOFBoundaryType t);
        /**
         * @brief    根据网格边界ID获取对应的boundary
         * @param[i] boundaryID    网格边界ID
         * @return   FITKOFBoundary*  边界对象
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-08-26
         */
        FITKOFBoundary* getBoundary(int MeshBoundaryID);
    };

}


#endif
