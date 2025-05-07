﻿/**********************************************************************
 * @file   FITKFlowPhysicsHandlerFactory.h
 * @brief  物理场数据搬运工厂
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-21
 *********************************************************************/
#ifndef FITKFLOWPHYSICSHANDLERFACTORY_H_
#define FITKFLOWPHYSICSHANDLERFACTORY_H_

#include "FITKInterfaceFlowOFAPI.h"
#include "FITKOFEnum.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"

namespace Interface
{
    class FITKAbstractOFSolver;
    class FITKAbstractOFTurbulence;
    class FITKOFBoundary;
    /**
     * @brief  物理场数据搬运工厂
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-08-21
     */
    class FITKInterfaceFlowOFAPI FITKFlowPhysicsHandlerFactory : public AppFrame::FITKComponentInterface
    {
    public:
        explicit FITKFlowPhysicsHandlerFactory() = default;
        virtual ~FITKFlowPhysicsHandlerFactory() = default;

        /**
        * @brief 获取部件名称，不能重复  return "FITKFlowPhysicsHandlerFactory"
        * @return QString
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-03-04
        */
        virtual QString getComponentName() override;

        /**
         * @brief    设置求解器
         * @param[i] solverName 求解器名称
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        void setSolver(QString solverName);

        /**
         * @brief    设置湍流模型
         * @param[i] turbulenceName 湍流模型名称
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        void setTurbence(QString turbulenceName);
        /**
         * @brief    设置SolutionSolver
         * @param[i] index 变量标号
         * @param[i] solutionSolverName solution名称
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-23
         */
        void setSolutionSolver(int vIndex, QString solutionSolverName);
        /**
         * @brief    设置TransportModel
         * @param[i] phaseIndex 
         * @param[i] modelName 
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setTransportModel(int phaseIndex, QString modelName);
        /**
         * @brief    设置边界
         * @param[i] meshBoundaryId 网格边界Id
         * @param[i] bType 边界类型
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setBoundary(int meshBoundaryId, FITKOFSolverTypeEnum::FITKOFBoundaryType bType);
        /**
         * @brief    设置边界类型
         * @param[i] boundaryIndex 
         * @param[i] bType 
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setBoundaryType(int boundaryIndex, FITKOFSolverTypeEnum::FITKOFBoundaryType bType);
        /**
         * @brief    设置变量边界类型
         * @param[i] boundaryId 
         * @param[i] variableName 
         * @param[i] boundaryType 
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setVariableBoundaryType(int boundaryId, QString variableName, QString boundaryType);
        /**
         * @brief    边界记录一下网格边界的名称，确保新边界网格复用
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-18
         */
        void recordBoundaryMeshName();
        /**
         * @brief    更新边界与边界网格的对应关系, 必须记录网格边界的名称才能使用
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-18
         */
        void resetBoundaryMesh();
        /**
         * @brief    设置几何补丁
         * @param[i] geometryId 
         * @param[i] vNameList 
         * @param[i] type 
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-04
         */
        void setPatch(int geometryId, QStringList vNameList, FITKOFSolverInitialEnum::FITKPatchApplyObjectType type);
        /**
         * @brief    筛选器-补丁类型
         * @return   QStringList
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-11
         */
        QStringList filterPatchFieldsType();
        /**
         * @brief    是否启用setFields
         * @return   bool
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-05
         */
        bool isExecuteSetFields();
        /**
         * @brief    清理物理数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-11
         */
        void clearPhysicsData();

    protected:
        /**
         * @brief    设置求解器动作 - 初始化物理场数据
         * @param[i] solver 
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void actionSetSolver(FITKAbstractOFSolver* solver);
        /**
         * @brief    设置湍流模型动作
         * @param[i] turbulence 
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void actionSetTurbulence(FITKAbstractOFTurbulence* turbulence);
        /**
         * @brief    设置物理场离散数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setPhysicsDiscretization();
        /**
         * @brief    设置物理场solution
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setPhysicsSolution();
        /**
         * @brief    设置物理场Initial
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setPhysicsInitialConditions();
        /**
         * @brief    设置物理场材料
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void setPhysicsTransportProp();
        /**
         * @brief    设置物理场求解运行配置
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-31
         */
        void setPhysicsRunControl();
        /**
         * @brief    设置物理场求解工作条件
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-04
         */
        void setPhysicsOperatingConditions();
        /**
         * @brief    更新物理场离散变量数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void updatePhysicsDiscretization();
        /**
         * @brief    更新物理场solution变量数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void updatePhysicsSolution();
        /**
         * @brief    更新物理场initial变量数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void updatePhysicsInitialConditions();
        /**
         * @brief    更新物理场Boundary变量数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        void updatePhysicsBoundaryConditions();

    };
}

#endif // !FITKFLOWPHYSICSHANDLERFACTORY_H_
