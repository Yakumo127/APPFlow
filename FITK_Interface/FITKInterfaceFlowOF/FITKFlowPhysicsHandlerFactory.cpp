﻿#include "FITKFlowPhysicsHandlerFactory.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITKOFPhysicsData.h"
#include "FITKAbstractOFSolver.h"
#include "FITKAbstractOFTurbulence.h"
#include "FITKOFSolution.h"
#include "FITKOFDiscretization.h"
#include "FITKOFBoundary.h"
#include "FITKOFRunControl.h"
#include "FITKOFBoundaryType.h"
#include "FITKOFSolutionSolver.h"
#include "FITKOFInitialConditions.h"
#include "FITKOFTransportProp.h"
#include "FITKOFTransportModel.h"
#include "FITKOFPhysicsManager.h"
#include "FITKOFSolverManager.h"
#include "FITKOFSolutionSolverManager.h"
#include "FITKOFTurbulenceManager.h"
#include "FITKOFBoundaryTypeManager.h"
#include "FITKOFTransportModelManager.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredFluidMeshVTK.h"
#include "FITKOFOperatingConditions.h"

namespace Interface
{
    QString FITKFlowPhysicsHandlerFactory::getComponentName()
    {
        return "FITKFlowPhysicsHandlerFactory";
    }

    void FITKFlowPhysicsHandlerFactory::setSolver(QString solverName)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //查看是否是当前求解器
        if (physicsData->getSolver() && physicsData->getSolver()->getDataObjectName() == solverName)return;
        //获取求解器管理器
        FITKOFSolverManager* solverManager = physicsManager->getSolverManager();
        if (!solverManager)return;
        //通过求解器名称获取求解器信息
        FITKOFSolverInfo solverInfo = solverManager->getSolverInfoBySolverName(solverName);
        //创建求解器
        FITKAbstractOFSolver* solver = solverInfo._createFuns();
        this->actionSetSolver(solver);
    }

    void FITKFlowPhysicsHandlerFactory::setTurbence(QString turbulenceName)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //查看是否是湍流数据
        if (physicsData->getTurbulence() && physicsData->getTurbulence()->getDataObjectName() == turbulenceName)return;
        //获取湍流模型管理器
        FITKOFTurbulenceManager* turbulenceManager = physicsManager->getTurbulenceManager();
        if (!turbulenceManager)return;
        //通过湍流模型名称获取湍流模型信息
        FITKOFTurbulenceInfo turbulenceInfo = turbulenceManager->getTurbenceInfoByTurbulenceName(turbulenceName);
        if (turbulenceInfo._turbType == FITKOFSolverTypeEnum::FITKOFTurbulenceType::TurbNone)
        {
            physicsData->setTurbulence(nullptr);
            return;
        }
        //创建湍流模型
        FITKAbstractOFTurbulence* turbulence = turbulenceInfo._createFuns();
        this->actionSetTurbulence(turbulence);
    }

    void FITKFlowPhysicsHandlerFactory::setSolutionSolver(int vIndex, QString solutionSolverName)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //查看是否设置类型重复
        FITKOFSolution* solution = physicsData->getSolution();
        if (!solution)return;
        FITKOFAlgebraicEquationsPara* vPara = solution->getSolverVariablePara(vIndex);
        if (!vPara) return;
        if (vPara->getSolutionSolver() && vPara->getSolutionSolver()->getDataObjectName() == solutionSolverName)return;
        //获取湍流模型管理器
        FITKOFSolutionSolverManager* solutionSolverManager = physicsManager->getSolutionSolverManager();
        if (!solutionSolverManager)return;
        //通过名称获取solutionSolver信息
        FITKOFSolutionSolverInfo info = solutionSolverManager->getSolutionSolverInfo(solutionSolverName);
        if (info._solutionSolverName.isEmpty())return;
        FITKOFAbsSolutionSolver* solutionSolver = info._createFuns();
        vPara->setSolutionSolver(solutionSolver);
    }

    void FITKFlowPhysicsHandlerFactory::setTransportModel(int phaseIndex, QString modelName)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取物理场材料
        FITKOFTransportProp* transportProp = physicsData->getTransportProp();
        if (!transportProp)return;
        //获取Phase数据对象
        FITKOFTransportPhase* phase = transportProp->getPhase(phaseIndex);
        if (!phase)return;
        //获取Transport Model管理器
        FITKOFTransportModelManager* transportModelManager = physicsManager->getTransportModelManager();
        //通过名称获取Transport Model信息
        FITKOFTransportModelInfo info = transportModelManager->getTransportModelInfo(modelName);
        if (info._transModelName.isEmpty())return;
        FITKAbsOFTransportModel* modelNew = info._createFuns();
        phase->setTransportModel(modelNew);
    }

    void FITKFlowPhysicsHandlerFactory::setBoundary(int meshBoundaryId, FITKOFSolverTypeEnum::FITKOFBoundaryType bType)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取物理场边界管理器
        FITKOFBoundaryManager* boundaryManagerPhy = physicsData->getBoundaryManager();
        if (!boundaryManagerPhy)return;
        //获取边界类型管理器
        FITKOFBoundaryTypeManager* boundaryTypeManager = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeManager)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器里的边界信息
        FITKOFBoundary* boundarySol = solver->getBoundary(bType);
        if (!boundarySol)return;
        //创建新边界并添加到物理场边界管理器
        FITKOFBoundary* boundaryPhy = new FITKOFBoundary(bType);
        boundaryManagerPhy->appendDataObj(boundaryPhy);
        boundaryPhy->setMeshBoundaryID(meshBoundaryId);
        //将solver边界添加到物理场Flow
        int countSolFlow = boundarySol->getFlowCount();
        for (int i = 0; i < countSolFlow; ++i)
        {
            //获取求解器的变量名和边界
            QString variableName = boundarySol->getFlowVariableName(i);
            FITKOFAbsBoundaryType* boundaryType = boundarySol->getFlowVBType(i);
            if (!boundaryType)continue;
            //获取边界类型信息
            FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundarySol->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())continue;
            //创建新的边界类型对象
            FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
            Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
            //拷贝数据对象
            para->copyPara(boundaryType->getBoundaryTypePara());
            //设置边界数据对象
            boundaryPhy->setFlowBoundary(variableName, boundaryTypeNew);
        }
        //将solver边界添加到物理场Phase
        int countSolPhases = boundarySol->getPhasesCount();
        for (int i = 0; i < countSolPhases; ++i)
        {
            //获取求解器的变量名和边界
            QString variableName = boundarySol->getPhasesVariableName(i);
            FITKOFAbsBoundaryType* boundaryType = boundarySol->getPhasesVBType(i);
            if (!boundaryType)continue;
            //获取边界类型信息
            FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundarySol->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())continue;
            //创建新的边界类型对象
            FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
            Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
            //拷贝数据对象
            para->copyPara(boundaryType->getBoundaryTypePara());
            //设置边界数据对象
            boundaryPhy->setPhasesBoundary(variableName, boundaryTypeNew);
        }
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        if (!turbulence)return;
        //获取湍流里的边界信息
        FITKOFBoundary* boundaryTur = turbulence->getBoundary(bType);
        if (!boundaryTur)return;
        //将湍流边界添加到物理场Turbulence
        int countSolTurbulence = boundaryTur->getTurbulenceCount();
        for (int i = 0; i < countSolTurbulence; ++i)
        {
            //获取求解器的变量名和边界
            QString variableName = boundaryTur->getTurbulenceVariableName(i);
            FITKOFAbsBoundaryType* boundaryType = boundaryTur->getTurbulenceVBType(i);
            if (!boundaryType)continue;
            //获取边界类型信息
            FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundaryTur->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())continue;
            //创建新的边界类型对象
            FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
            Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
            //拷贝数据对象
            para->copyPara(boundaryType->getBoundaryTypePara());
            //设置边界数据对象
            boundaryPhy->setTurbulenceBoundary(variableName, boundaryTypeNew);
        }
    }

    void FITKFlowPhysicsHandlerFactory::setBoundaryType(int boundaryIndex, FITKOFSolverTypeEnum::FITKOFBoundaryType bType)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取物理场边界管理器
        FITKOFBoundaryManager* boundaryManagerPhy = physicsData->getBoundaryManager();
        if (!boundaryManagerPhy)return;
        //获取边界类型管理器
        FITKOFBoundaryTypeManager* boundaryTypeManager = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeManager)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器里的边界信息
        FITKOFBoundary* boundarySol = solver->getBoundary(bType);
        if (!boundarySol)return;
        //获取物理场边界
        FITKOFBoundary* boundaryPhy = boundaryManagerPhy->getDataByIndex(boundaryIndex);
        if (!boundaryPhy)return;
        //将solver边界添加到物理场Flow
        int countSolFlow = boundarySol->getFlowCount();
        for (int i = 0; i < countSolFlow; ++i)
        {
            //获取求解器的变量名和边界
            QString variableName = boundarySol->getFlowVariableName(i);
            FITKOFAbsBoundaryType* boundaryType = boundarySol->getFlowVBType(i);
            if (!boundaryType)continue;
            //获取边界类型信息
            FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundarySol->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())continue;
            //创建新的边界类型对象
            FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
            Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
            //拷贝数据对象
            para->copyPara(boundaryType->getBoundaryTypePara());
            //设置边界数据对象
            boundaryPhy->setFlowBoundary(variableName, boundaryTypeNew);
        }
        //将solver边界添加到物理场Phase
        int countSolPhases = boundarySol->getPhasesCount();
        for (int i = 0; i < countSolPhases; ++i)
        {
            //获取求解器的变量名和边界
            QString variableName = boundarySol->getPhasesVariableName(i);
            FITKOFAbsBoundaryType* boundaryType = boundarySol->getPhasesVBType(i);
            if (!boundaryType)continue;
            //获取边界类型信息
            FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundarySol->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())continue;
            //创建新的边界类型对象
            FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
            Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
            //拷贝数据对象
            para->copyPara(boundaryType->getBoundaryTypePara());
            //设置边界数据对象
            boundaryPhy->setPhasesBoundary(variableName, boundaryTypeNew);
        }
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        if (!turbulence)return;
        //获取湍流里的边界信息
        FITKOFBoundary* boundaryTur = turbulence->getBoundary(bType);
        if (!boundaryTur)return;
        //将湍流边界添加到物理场Turbulence
        int countSolTurbulence = boundaryTur->getTurbulenceCount();
        for (int i = 0; i < countSolTurbulence; ++i)
        {
            //获取求解器的变量名和边界
            QString variableName = boundaryTur->getTurbulenceVariableName(i);
            FITKOFAbsBoundaryType* boundaryType = boundaryTur->getTurbulenceVBType(i);
            if (!boundaryType)continue;
            //获取边界类型信息
            FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundaryTur->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())continue;
            //创建新的边界类型对象
            FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
            Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
            //拷贝数据对象
            para->copyPara(boundaryType->getBoundaryTypePara());
            //设置边界数据对象
            boundaryPhy->setTurbulenceBoundary(variableName, boundaryTypeNew);
        }
    }

    void FITKFlowPhysicsHandlerFactory::setVariableBoundaryType(int boundaryId, QString variableName, QString boundaryType)
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取物理场边界管理器
        FITKOFBoundaryManager* boundaryManagerPhy = physicsData->getBoundaryManager();
        if (!boundaryManagerPhy)return;
        //获取边界类型管理器
        FITKOFBoundaryTypeManager* boundaryTypeManager = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeManager)return;
        //获取物理场边界
        FITKOFBoundary* boundaryPhy = boundaryManagerPhy->getDataByID(boundaryId);
        if (!boundaryPhy)return;
        //获取边界类型信息
        FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType, solver->getSolverType(), variableName, boundaryPhy->getBoundaryType());
        if (info._boundaryTypeName.isEmpty())return;
        //创建新的边界类型对象
        FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
        boundaryPhy->setBoundary(variableName, boundaryTypeNew);
    }

    void FITKFlowPhysicsHandlerFactory::recordBoundaryMeshName()
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取物理场边界管理器
        FITKOFBoundaryManager* boundaryManagerPhy = physicsData->getBoundaryManager();
        if (!boundaryManagerPhy)return;
        //记录网格边界名称
        int count = boundaryManagerPhy->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            FITKOFBoundary* boundary = boundaryManagerPhy->getDataByIndex(i);
            if (!boundary)continue;
            FITKBoundaryMeshVTK* boundaryMesh = boundary->getMeshBoundary();
            if (!boundaryMesh)continue;
            QString name = boundaryMesh->getDataObjectName();
            boundary->setUserData(Core::FITKUserData::FITKUserRole, name);
        }
    }

    void FITKFlowPhysicsHandlerFactory::resetBoundaryMesh()
    {
        //获取全局数据
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return;
        //获取网格数据
        Interface::FITKUnstructuredFluidMeshVTK* meshData = globalData->getMeshData<Interface::FITKUnstructuredFluidMeshVTK>();
        if (!meshData)return;
        //获取边界网格管理器
        Interface::FITKBoundaryMeshVTKManager* boundaryMeshMgr = meshData->getBoundaryMeshManager();
        if (!boundaryMeshMgr)return;
        //获取物理数据
        FITKOFPhysicsData* physicsData = globalData->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取物理场边界管理器
        FITKOFBoundaryManager* boundaryManagerPhy = physicsData->getBoundaryManager();
        if (!boundaryManagerPhy)return;
        int count = boundaryManagerPhy->getDataCount();
        for (int i = count - 1; i >= 0; --i)
        {
            FITKOFBoundary* boundary = boundaryManagerPhy->getDataByIndex(i);
            if (!boundary)continue;
            QString name = boundary->getUserDataT<QString>(Core::FITKUserData::FITKUserRole);
            Interface::FITKBoundaryMeshVTK* boundaryMesh = boundaryMeshMgr->getDataByName(name);
            if (boundaryMesh)
            {
                boundary->setMeshBoundaryID(boundaryMesh->getDataObjectID());
                continue;
            }
            boundaryManagerPhy->removeDataByIndex(i);
        }
    }

    void FITKFlowPhysicsHandlerFactory::setPatch(int geometryId, QStringList vNameList, FITKOFSolverInitialEnum::FITKPatchApplyObjectType type)
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器下的init数据
        FITKOFInitialConditions* physicsInitial = physicsData->getInitialConditions();
        if (!physicsInitial)return;
        //获取物理数据的init数据
        FITKOFInitialConditions* solverInitial = solver->getInitialConditions();
        if (!solverInitial)return;
        //创建patch
        FITKOFGeometryPatch* patch = new FITKOFGeometryPatch(geometryId, type);
        physicsInitial->appendPatch(patch);
        Core::FITKParameter* fieldData = patch->getFieldPara();
        //
        Core::FITKParameter* basicSol = solverInitial->getBasicData();
        int count = basicSol->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKAbstractEasyParam* data = basicSol->getDataByIndex(i);
            if (!data)continue;
            QString name = data->getDataObjectName();
            if (!vNameList.contains(name))continue;
            fieldData->copyAppendPara(data);
        }
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        if (!turbulence)return;
        //获取湍流下的离散数据变化量
        FITKOFInitialConditions* turbulenceInitial = turbulence->getInitialConditions();
        if (!turbulenceInitial)return;
        Core::FITKParameter* basicTur = turbulenceInitial->getBasicData();
        count = basicTur->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKAbstractEasyParam* data = basicTur->getDataByIndex(i);
            if (!data)continue;
            QString name = data->getDataObjectName();
            if (!vNameList.contains(name))continue;
            fieldData->copyAppendPara(data);
        }
    }

    QStringList FITKFlowPhysicsHandlerFactory::filterPatchFieldsType()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return QStringList();
        //获取求解器下的init数据
        FITKOFInitialConditions* physicsInitial = physicsData->getInitialConditions();
        if (!physicsInitial)return QStringList();
        //获取初始化参数
        Core::FITKParameter* basic = physicsInitial->getBasicData();
        if (!basic)return QStringList();
        QStringList strList;
        int count = basic->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKAbstractEasyParam* data = basic->getDataByIndex(i);
            if (!data)continue;
            strList.append(data->getDataObjectName());
        }
        return strList;
    }

    bool FITKFlowPhysicsHandlerFactory::isExecuteSetFields()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取求解器下的init数据
        FITKOFInitialConditions* physicsInitial = physicsData->getInitialConditions();
        if (!physicsInitial)return false;
        //获取patch数量
        return physicsInitial->getPatchCount() > 0;
    }

    void FITKFlowPhysicsHandlerFactory::clearPhysicsData()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //清理所有物理数据
        physicsData->setSolver(nullptr);
        physicsData->setEnableTurbulenceEqu(false);
        physicsData->setTurbulence(nullptr);
        physicsData->setTransportProp(nullptr);
        physicsData->setDiscretization(nullptr);
        physicsData->setSolution(nullptr);
        physicsData->setInitialConditions(nullptr);
        physicsData->setBoundaryManager(nullptr);
        physicsData->setRunControl(nullptr);
        physicsData->setOperatingConditions(nullptr);
    }

    void FITKFlowPhysicsHandlerFactory::actionSetSolver(FITKAbstractOFSolver* solver)
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //设置求解器
        physicsData->setSolver(solver);
        if (!solver)return;
        //设置是否启用湍流数据
        physicsData->setEnableTurbulenceEqu(solver->turbEnabled());
        //设置湍流为空
        physicsData->setTurbulence(nullptr);
        //设置离散
        this->setPhysicsDiscretization();
        //设置solution数据
        this->setPhysicsSolution();
        //设置init数据
        this->setPhysicsInitialConditions();
        //设置材料数据
        this->setPhysicsTransportProp();
        //设置边界管理器
        physicsData->setBoundaryManager(new FITKOFBoundaryManager);
        //设置运行配置
        this->setPhysicsRunControl();
        //设置工作条件
        this->setPhysicsOperatingConditions();
    }

    void FITKFlowPhysicsHandlerFactory::actionSetTurbulence(FITKAbstractOFTurbulence* turbulence)
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //设置湍流
        physicsData->setTurbulence(turbulence);
        //更新变量
        this->updatePhysicsDiscretization();
        this->updatePhysicsSolution();
        this->updatePhysicsInitialConditions();
        this->updatePhysicsBoundaryConditions();
    }

    void FITKFlowPhysicsHandlerFactory::setPhysicsDiscretization()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器下的离散数据
        FITKOFDiscretization* discretizationSol = solver->getDiscretization();
        if (!discretizationSol)return;
        //创建离散数据，初始化离散数据复制到实际数据中
        FITKOFDiscretization* discretizationPhy = new FITKOFDiscretization;
        //拷贝Time
        Core::FITKParameter* timePhy = discretizationPhy->getTimeOption();
        Core::FITKParameter* timeSol = discretizationSol->getTimeOption();
        if (timePhy && timeSol)
            timePhy->copyPara(timeSol);
        //拷贝Gradients
        Core::FITKParameter* gradientsPhy = discretizationPhy->getGradients();
        Core::FITKParameter* gradientsSol = discretizationSol->getGradients();
        if (gradientsPhy && gradientsSol)
            gradientsPhy->copyPara(gradientsSol);
        //拷贝Interpolation
        Core::FITKParameter* interpolationPhy = discretizationPhy->getInterpolation();
        Core::FITKParameter* interpolationSol = discretizationSol->getInterpolation();
        if (interpolationPhy && interpolationSol)
            interpolationPhy->copyPara(interpolationSol);
        //拷贝对流数据
        int count = discretizationSol->getConvectionCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKParameter* para = discretizationSol->getConvectionVPara(i);
            if (!para)continue;
            Core::FITKParameter* newPara = new Core::FITKParameter;
            newPara->copyPara(para);
            discretizationPhy->insertConvection(discretizationSol->getConvectionVName(i), newPara);
        }
        //设置数据到物理数据
        physicsData->setDiscretization(discretizationPhy);
    }

    void FITKFlowPhysicsHandlerFactory::setPhysicsSolution()
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取湍流模型管理器
        FITKOFSolutionSolverManager* solutionSolverManager = physicsManager->getSolutionSolverManager();
        if (!solutionSolverManager)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器下的solution数据
        FITKOFSolution* solutionSol = solver->getSolution();
        if (!solutionSol)return;
        //创建solution,初始化solution数据复制到实际数据中
        FITKOFSolution* solutionPhy = new FITKOFSolution;
        //拷贝Solvers
        int count = solutionSol->getSolversCount();
        for (int i = 0; i < count; ++i)
        {
            //获取求解器代数变量数据对象
            FITKOFAlgebraicEquationsPara* solutionSolverSol = solutionSol->getSolverVariablePara(i);
            if (!solutionSolverSol)continue;
            FITKOFAbsSolutionSolver* data = solutionSolverSol->getSolutionSolver();
            if (!data)continue;
            //获取代数变量求解器信息
            FITKOFSolutionSolverInfo info = solutionSolverManager->getSolutionSolverInfo(data->getDataObjectName());
            if (info._solutionSolverName.isEmpty())continue;
            FITKOFAbsSolutionSolver* newData = info._createFuns();
            if (!newData)continue;
            Core::FITKParameter* para = newData->getSolverSolutionPara();
            para->copyPara(data->getSolverSolutionPara());
            //获取变量求解增加的参数对象并设置数据
            Core::FITKParameter* additionPSol = solutionSolverSol->getSolverAdditionalPara();
            Core::FITKParameter* additionPPhy = nullptr;
            if (additionPSol)
            {
                additionPPhy = new Core::FITKParameter;
                additionPPhy->copyPara(additionPSol);
            }
            //获取变量名称
            QString vname = solutionSolverSol->getVariableName();
            //创建新的数据对象
            FITKOFAlgebraicEquationsPara* solutionSolverPhy = new FITKOFAlgebraicEquationsPara;
            solutionSolverPhy->setVariableName(vname);
            solutionSolverPhy->setSolutionSolver(newData);
            solutionSolverPhy->setSolverAdditionalPara(additionPPhy);
            solutionPhy->appendSolutionSolver(solutionSolverPhy);
        }
        //拷贝求解器有关的特殊数据
        Core::FITKParameter* speciallySol = solutionSol->getSolverSpeciallyDataPara();
        if (speciallySol)
        {
            Core::FITKParameter* speciallyPhy = new Core::FITKParameter;
            speciallyPhy->copyPara(speciallySol);
            solutionPhy->setSpeciallyData(solutionSol->getSolverSpeciallyDataName(), speciallyPhy);
        }
        //拷贝residuals
        count = solutionSol->getResidualsCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKParameter* para = solutionSol->getResidualVariablePara(i);
            if (!para)continue;
            Core::FITKParameter* newPara = new Core::FITKParameter;
            newPara->copyPara(para);
            solutionPhy->setResidualData(solutionSol->getResidualVariableName(i), newPara);
        }
        //拷贝relaxation
        Core::FITKParameter* relaxationSol = solutionSol->getRelaxation();
        Core::FITKParameter* relaxationPhy = solutionPhy->getRelaxation();
        if (relaxationPhy && relaxationSol)
            relaxationPhy->copyPara(relaxationSol);
        //拷贝limits
        Core::FITKParameter* limitsSol = solutionSol->getLimits();
        Core::FITKParameter* limitsPhy = solutionPhy->getLimits();
        if (limitsPhy && limitsSol)
            limitsPhy->copyPara(limitsSol);
        //设置数据到物理数据
        physicsData->setSolution(solutionPhy);
    }

    void FITKFlowPhysicsHandlerFactory::setPhysicsInitialConditions()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器下的离散数据
        FITKOFInitialConditions* solverInitial = solver->getInitialConditions();
        if (!solverInitial)return;
        //创建Initial数据，初始化Initial数据复制到实际数据中
        FITKOFInitialConditions* physicsInitial = new FITKOFInitialConditions;
        //拷贝Basic
        Core::FITKParameter* basicSol = solverInitial->getBasicData();
        Core::FITKParameter* basicPhy = physicsInitial->getBasicData();
        if (basicPhy && basicSol)
            basicPhy->copyPara(basicSol);
        //设置数据到物理数据
        physicsData->setInitialConditions(physicsInitial);
    }

    void FITKFlowPhysicsHandlerFactory::setPhysicsTransportProp()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取物理材料管理器
        FITKOFTransportModelManager* transportModelManager = physicsManager->getTransportModelManager();
        if (!transportModelManager)return;
        // 获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器下的物理材料
        FITKOFTransportProp* transSol = solver->getTransportProp();
        if (!transSol)return;
        //创建物理材料数据，初始化物理材料数据复制到实际数据中
        FITKOFTransportProp* transPhy = new FITKOFTransportProp;
        //拷贝材料所需参数
        Core::FITKParameter* addTransSol = transSol->getTransportAdditionalData();
        Core::FITKParameter* addTransPhy = transPhy->getTransportAdditionalData();
        if (addTransPhy && addTransSol)
            addTransPhy->copyPara(addTransSol);
        //拷贝Phase
        int count = transSol->getPhasesCount();
        for (int i = 0; i < count; ++i)
        {
            FITKOFTransportPhase* phaseSol = transSol->getPhase(i);
            if (!phaseSol) continue;

            Core::FITKParameter* addPhaseParaSol = phaseSol->getPhaseAdditionalData();
            FITKAbsOFTransportModel* modelSol = phaseSol->getTransportModel();
            FITKOFTransportModelInfo info = transportModelManager->getTransportModelInfo(modelSol->getDataObjectName());
            if (info._transModelName.isEmpty())continue;

            FITKAbsOFTransportModel* newModel = info._createFuns();
            Core::FITKParameter* modelPara = newModel->getTransportModelPara();
            modelPara->copyPara(modelSol->getTransportModelPara());
            Core::FITKParameter* addPhaseParaPhy = nullptr;
            if (addPhaseParaSol)
            {
                addPhaseParaPhy = new Core::FITKParameter;
                addPhaseParaPhy->copyPara(addPhaseParaSol);
            }
            //创建新对象
            FITKOFTransportPhase* phaseNew = new FITKOFTransportPhase;
            phaseNew->setPhaseName(phaseSol->getPhaseName());
            phaseNew->setPhaseAdditionalData(addPhaseParaPhy);
            phaseNew->setTransportModel(newModel);

            transPhy->appendPhase(phaseNew);
        }
        physicsData->setTransportProp(transPhy);
    }

    void FITKFlowPhysicsHandlerFactory::setPhysicsRunControl()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器下的运行配置数据
        FITKOFRunControl* solverRun = solver->getRunControl();
        if (!solverRun)return;
        //创建运行配置数据对象，初始化运行配置数据复制到实际数据中
        FITKOFRunControl* physicsRun = new FITKOFRunControl;
        //拷贝TimeControl
        Core::FITKParameter* timeConPhy = physicsRun->getTimeControl();
        Core::FITKParameter* timeConSol = solverRun->getTimeControl();
        if (timeConPhy && timeConSol)
            timeConPhy->copyPara(timeConSol);
        //拷贝OutputControl
        Core::FITKParameter* outputConPhy = physicsRun->getOutputControl();
        Core::FITKParameter* outputConSol = solverRun->getOutputControl();
        if (outputConPhy && outputConSol)
            outputConPhy->copyPara(outputConSol);
        //设置数据到物理数据
        physicsData->setRunControl(physicsRun);
    }

    void FITKFlowPhysicsHandlerFactory::setPhysicsOperatingConditions()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取求解器里的数据
        FITKOFOperatingConditions* operatingSol = solver->getOperatingConditions();
        if (!operatingSol)return;
        //创建新数据
        FITKOFOperatingConditions* operatingPhy = new FITKOFOperatingConditions;
        //拷贝引力与加速度条件参数
        Core::FITKParameter* gaPhy = operatingPhy->getGravitationalAcceleration();
        Core::FITKParameter* gaSol = operatingSol->getGravitationalAcceleration();
        if (gaPhy && gaSol)
            gaPhy->copyPara(gaSol);
        //拷贝OutputControl
        Core::FITKParameter* rpPhy = operatingPhy->getReferencePressure();
        Core::FITKParameter* rpSol = operatingSol->getReferencePressure();
        if (rpPhy && rpSol)
            rpPhy->copyPara(rpSol);
        physicsData->setOperatingConditions(operatingPhy);
    }

    void FITKFlowPhysicsHandlerFactory::updatePhysicsDiscretization()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器和物理数据离散数据
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        FITKOFDiscretization* physicsDis = physicsData->getDiscretization();
        if (!solver || !physicsDis)return;
        //获取求解器的离散数据
        FITKOFDiscretization* solverDis = solver->getDiscretization();
        if (!solverDis)return;
        //获取需要保留的离散数据名称
        QStringList nameList;
        int count = solverDis->getConvectionCount();
        for (int i = 0; i < count; ++i)
        {
            nameList.append(solverDis->getConvectionVName(i));
        }
        //设置需要保留物理数据离散数据
        physicsDis->onlyKeepConvection(nameList);
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        if (!turbulence)return;
        //获取湍流下的离散数据变化量
        FITKOFDiscretization* turbulenceDis = turbulence->getDiscretization();
        if (!turbulenceDis)return;
        //设置湍流下的离散数据变化量到物理数据离散数据
        count = turbulenceDis->getConvectionCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKParameter* para = turbulenceDis->getConvectionVPara(i);
            if (!para)continue;
            Core::FITKParameter* newPara = new Core::FITKParameter;
            newPara->copyPara(para);
            physicsDis->insertConvection(turbulenceDis->getConvectionVName(i), newPara);
        }
    }

    void FITKFlowPhysicsHandlerFactory::updatePhysicsSolution()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取湍流模型管理器
        FITKOFSolutionSolverManager* solutionSolverManager = physicsManager->getSolutionSolverManager();
        if (!solutionSolverManager)return;
        //获取求解器和物理数据solution数据
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        FITKOFSolution* physicsSol = physicsData->getSolution();
        if (!solver || !physicsSol)return;
        //获取求解器的solution数据
        FITKOFSolution* solverSol = solver->getSolution();
        if (!solverSol)return;
        //获取relaxation参数
        Core::FITKParameter* relaxationPhy = physicsSol->getRelaxation();
        if (!relaxationPhy)return;
        //获取需要保留的solution数据名称
        QStringList nameSolversList, nameResidualsList;
        int count = solverSol->getSolversCount();
        for (int i = 0; i < count; ++i)
        {
            FITKOFAlgebraicEquationsPara* para = solverSol->getSolverVariablePara(i);
            if (!para)continue;
            nameSolversList.append(para->getVariableName());
        }
        count = solverSol->getResidualsCount();
        for (int i = 0; i < count; ++i)
        {
            nameResidualsList.append(solverSol->getResidualVariableName(i));
        }
        //设置需要保留物理数据离散数据
        solverSol->onlyKeepSolvers(nameSolversList);
        solverSol->onlyKeepResiduals(nameResidualsList);
        relaxationPhy->onlyKeepPara(solverSol->getRelaxation());
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        if (!turbulence)return;
        //获取湍流下的solution数据变化量
        FITKOFSolution* turbulenceSlo = turbulence->getSolution();
        if (!turbulenceSlo)return;
        //设置湍流下的solution数据变化量到物理数据solution数据
        count = turbulenceSlo->getSolversCount();
        for (int i = 0; i < count; ++i)
        {
            //获取求解器代数变量数据对象
            FITKOFAlgebraicEquationsPara* solutionSolverTur = turbulenceSlo->getSolverVariablePara(i);
            if (!solutionSolverTur)continue;
            FITKOFAbsSolutionSolver* data = solutionSolverTur->getSolutionSolver();
            if (!data)continue;
            FITKOFSolutionSolverInfo info = solutionSolverManager->getSolutionSolverInfo(data->getDataObjectName());
            if (info._solutionSolverName.isEmpty())continue;
            FITKOFAbsSolutionSolver* solutionSolver = info._createFuns();
            if (!solutionSolver)continue;
            //获取变量求解增加的参数对象并设置数据
            Core::FITKParameter* additionPTur = solutionSolverTur->getSolverAdditionalPara();
            Core::FITKParameter* additionPPhy = nullptr;
            if (additionPTur)
            {
                additionPPhy = new Core::FITKParameter;
                additionPPhy->copyPara(additionPTur);
            }
            //获取变量名称
            QString vname = solutionSolverTur->getVariableName();
            //创建新的数据对象
            FITKOFAlgebraicEquationsPara* solutionSolverPhy = new FITKOFAlgebraicEquationsPara;
            solutionSolverPhy->setVariableName(vname);
            solutionSolverPhy->setSolutionSolver(solutionSolver);
            solutionSolverPhy->setSolverAdditionalPara(additionPPhy);
            physicsSol->appendSolutionSolver(solutionSolverPhy);
        }
        //residuals
        count = turbulenceSlo->getResidualsCount();
        for (int i = 0; i < count; ++i)
        {
            QString vName = turbulenceSlo->getResidualVariableName(i);
            physicsSol->initAppendResidual(vName, physicsSol->getSolverSpeciallyDataName());
        }
        //relaxation
        relaxationPhy->appendPara(turbulenceSlo->getRelaxation());
    }

    void FITKFlowPhysicsHandlerFactory::updatePhysicsInitialConditions()
    {
        //获取物理数据
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        if (!physicsData)return;
        //获取求解器和物理数据Initial数据
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        FITKOFInitialConditions* physicsInitial = physicsData->getInitialConditions();
        if (!solver || !physicsInitial)return;
        //清理patch
        int count = physicsInitial->getPatchCount();
        for (int i = count - 1; i >= 0; ++i)
        {
            physicsInitial->removePatch(i);
        }
        //获取求解器的Initial数据
        FITKOFInitialConditions* solverInitial = solver->getInitialConditions();
        if (!solverInitial)return;
        //获取Basic参数
        Core::FITKParameter* basicPhy = physicsInitial->getBasicData();
        if (!basicPhy)return;
        //设置需要保留物理数据离散数据
        basicPhy->onlyKeepPara(solverInitial->getBasicData());
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        if (!turbulence)return;
        //获取湍流下的离散数据变化量
        FITKOFInitialConditions* turbulenceInitial = turbulence->getInitialConditions();
        if (!turbulenceInitial)return;
        //追加Basic参数
        basicPhy->appendPara(turbulenceInitial->getBasicData());
    }

    void FITKFlowPhysicsHandlerFactory::updatePhysicsBoundaryConditions()
    {
        //获取物理数据与物理场管理器
        FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<FITKOFPhysicsData>();
        FITKOFPhysicsManager* physicsManager = FITKOFPhysicsManager::getInstance();
        if (!physicsManager || !physicsData)return;
        //获取求解器
        FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return;
        //获取物理场边界管理器
        FITKOFBoundaryManager* boundaryManagerPhy = physicsData->getBoundaryManager();
        if (!boundaryManagerPhy)return;
        //获取边界类型管理器
        FITKOFBoundaryTypeManager* boundaryTypeManager = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeManager)return;
        //获取湍流数据
        FITKAbstractOFTurbulence* turbulence = physicsData->getTurbulence();
        //获取物理场边界
        int boundCount = boundaryManagerPhy->getDataCount();
        for (int index = 0; index < boundCount; ++index)
        {
            FITKOFBoundary* boundaryPhy = boundaryManagerPhy->getDataByIndex(index);
            if (!boundaryPhy)continue;
            boundaryPhy->clearTurbulenceBoundary();
            if (!turbulence)continue;
            //获取边界类型
            FITKOFSolverTypeEnum::FITKOFBoundaryType bType = boundaryPhy->getBoundaryType();
            //获取湍流里的边界信息
            FITKOFBoundary* boundaryTur = turbulence->getBoundary(bType);
            if (!boundaryTur)return;
            //将湍流边界添加到物理场Turbulence
            int countSolTurbulence = boundaryTur->getTurbulenceCount();
            for (int i = 0; i < countSolTurbulence; ++i)
            {
                //获取求解器的变量名和边界
                QString variableName = boundaryTur->getTurbulenceVariableName(i);
                FITKOFAbsBoundaryType* boundaryType = boundaryTur->getTurbulenceVBType(i);
                if (!boundaryType)continue;
                //获取边界类型信息
                FITKOFBoundaryTypeInfo info = boundaryTypeManager->getBoundaryTypeInfo(boundaryType->getDataObjectName(), solver->getSolverType(), variableName, boundaryTur->getBoundaryType());
                if (info._boundaryTypeName.isEmpty())continue;
                //创建新的边界类型对象
                FITKOFAbsBoundaryType* boundaryTypeNew = info._createFuns();
                Core::FITKParameter* para = boundaryTypeNew->getBoundaryTypePara();
                //拷贝数据对象
                para->copyPara(boundaryType->getBoundaryTypePara());
                //设置边界数据对象
                boundaryPhy->setTurbulenceBoundary(variableName, boundaryTypeNew);
            }
        }
    }
}
