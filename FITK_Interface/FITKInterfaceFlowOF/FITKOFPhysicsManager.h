/**********************************************************************
 * @file   FITKOFPhysicsManager.h
 * @brief  物理数据管理器
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-21
 *********************************************************************/
#ifndef _FITKOF_PHYSICS_MANAGER_H___
#define _FITKOF_PHYSICS_MANAGER_H___

#include "FITKInterfaceFlowOFAPI.h"
#include "FITKOFEnum.hpp"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include <QMutex>

namespace Interface
{
    class FITKOFSolverManager;
    class FITKOFTurbulenceManager;
    class FITKOFSolutionSolverManager;
    class FITKOFTransportModelManager;
    class FITKOFBoundaryTypeManager;
}

namespace Interface
{
    class FITKOFPhysicsManagerDeleator;
    /**
     * @brief  物理场数据管理器
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-08-21
     */
    class FITKInterfaceFlowOFAPI FITKOFPhysicsManager
    {
        friend FITKOFPhysicsManagerDeleator;
        DeclSingleton(FITKOFPhysicsManager);
    public:
        /**
         * @brief    获取求解器管理器
         * @return   FITKOFSolverManager *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        FITKOFSolverManager* getSolverManager();
        /**
         * @brief    获取湍流模型管理器
         * @return   FITKOFTurbulenceManager *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        FITKOFTurbulenceManager* getTurbulenceManager();
        /**
         * @brief    获取SolutionSolver管理器
         * @return   FITKOFSolutionSolverManager *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-22
         */
        FITKOFSolutionSolverManager* getSolutionSolverManager();
        /**
         * @brief    获取物理材料模型管理器
         * @return   FITKOFTransportModelManager *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-23
         */
        FITKOFTransportModelManager* getTransportModelManager();
        /**
         * @brief    获取边界类型管理器
         * @return   FITKOFBoundaryTypeManager *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        FITKOFBoundaryTypeManager* getBoundaryTypeManager();

    private:
        /**
         * @brief    初始化函数
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        void initialize();
        /**
         * @brief    销毁函数
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        void finalize();

    private:
        /**
         * @brief  求解器管理器
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-21
         */
        FITKOFSolverManager* m_solverManager{};
        /**
         * @brief  湍流管理器
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-21
         */
        FITKOFTurbulenceManager* m_turbulenceManager{};
        /**
         * @brief  solution Solver管理器
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-22
         */
        FITKOFSolutionSolverManager* m_solutionSolverManager{};
        /**
         * @brief  物理材料模型管理器
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-23
         */
        FITKOFTransportModelManager* m_transportModelManager{};
        /**
         * @brief  边界类型管理器
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-26
         */
        FITKOFBoundaryTypeManager* m_boundaryTypeManager{};
    };

    class FITKOFPhysicsManagerDeleator
    {
    public:
        explicit FITKOFPhysicsManagerDeleator() = default;
        virtual ~FITKOFPhysicsManagerDeleator();
    };
}


#endif // !_FITKOF_PHYSICS_MANAGER_H___
