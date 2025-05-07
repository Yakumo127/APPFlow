#include "FITKOFPhysicsData.h"
#include "FITKAbstractOFSolver.h"
#include "FITKAbstractOFTurbulence.h"
#include "FITKOFTransportProp.h"
#include "FITKOFDiscretization.h"
#include "FITKOFBoundary.h"
#include "FITKOFSolution.h"
#include "FITKOFInitialConditions.h"
#include "FITKOFRunControl.h"
#include "FITKOFOperatingConditions.h"

namespace Interface
{
    FITKOFPhysicsData::FITKOFPhysicsData()
    {
    }

    FITKOFPhysicsData::~FITKOFPhysicsData()
    {
        //销毁数据
        if (_solver) delete _solver;
        if (_turbulence) delete _turbulence;
        if (_transPortProp) delete _transPortProp;
        if (_discretization) delete _discretization;
        if (_boundaryManager) delete _boundaryManager;
        if (_solution) delete _solution;
        if (_initialCond) delete _initialCond;
        if (_runControl) delete _runControl;
        if (_operatingCond) delete _operatingCond;
    }

    FITKAbstractOFSolver* FITKOFPhysicsData::getSolver()
    {
        //获取求解器
        return _solver;
    }

    bool FITKOFPhysicsData::isEnableTurbulenceEqu()
    {
        //获取是否启用湍流
        return _enableTurb;
    }

    FITKAbstractOFTurbulence* FITKOFPhysicsData::getTurbulence()
    {
        //获取湍流数据
        return _turbulence;
    }

    FITKOFTransportProp* FITKOFPhysicsData::getTransportProp()
    {
        //获取材料
        return _transPortProp;
    }

    FITKOFDiscretization* FITKOFPhysicsData::getDiscretization()
    {
        //获取离散
        return _discretization;
    }

    FITKOFSolution* FITKOFPhysicsData::getSolution()
    {
        //获取solution数据
        return _solution;
    }

    FITKOFInitialConditions* FITKOFPhysicsData::getInitialConditions()
    {
        //获取Initial Conditions数据
        return _initialCond;
    }

    FITKOFBoundaryManager* FITKOFPhysicsData::getBoundaryManager()
    {
        //获取边界数据
        return _boundaryManager;
    }

    FITKOFRunControl* FITKOFPhysicsData::getRunControl()
    {
        //获取运行配置数据
        return _runControl;
    }

    FITKOFOperatingConditions* FITKOFPhysicsData::getOperatingConditions()
    {
        //获取求解工作条件
        return _operatingCond;
    }

    void FITKOFPhysicsData::setSolver(FITKAbstractOFSolver* solver)
    {
        //设置求解器
        if (solver != _solver && _solver) delete _solver;
        _solver = solver;
    }

    void FITKOFPhysicsData::setEnableTurbulenceEqu(bool isEnable)
    {
        //设置是否启用湍流
        _enableTurb = isEnable;
    }

    void FITKOFPhysicsData::setTurbulence(FITKAbstractOFTurbulence* turbulence)
    {
        //设置湍流数据
        if (turbulence != _turbulence && _turbulence) delete _turbulence;
        _turbulence = turbulence;
    }

    void FITKOFPhysicsData::setTransportProp(FITKOFTransportProp* transProp)
    {
        //设置材料数据
        if (transProp != _transPortProp && _transPortProp) delete _transPortProp;
        _transPortProp = transProp;
    }

    void FITKOFPhysicsData::setDiscretization(FITKOFDiscretization* discretization)
    {
        //设置离散数据
        if (discretization != _discretization && _discretization) delete _discretization;
        _discretization = discretization;
    }

    void FITKOFPhysicsData::setSolution(FITKOFSolution* solution)
    {
        //设置solution数据
        if (solution != _solution && _solution) delete _solution;
        _solution = solution;
    }

    void FITKOFPhysicsData::setInitialConditions(FITKOFInitialConditions* initial)
    {
        //设置初始值参数配置
        if (initial != _initialCond && _initialCond) delete _initialCond;
        _initialCond = initial;
    }

    void FITKOFPhysicsData::setBoundaryManager(FITKOFBoundaryManager* manager)
    {
        //设置边界管理器
        if (manager != _boundaryManager && _boundaryManager) delete _boundaryManager;
        _boundaryManager = manager;
    }

    void FITKOFPhysicsData::setRunControl(FITKOFRunControl* run)
    {
        //设置运行配置数据
        if (run != _runControl && _runControl)delete _runControl;
        _runControl = run;
    }

    void FITKOFPhysicsData::setOperatingConditions(FITKOFOperatingConditions* operatingCond)
    {
        //设置求解工作条件
        if (operatingCond != _operatingCond && _operatingCond)delete _operatingCond;
        _operatingCond = operatingCond;
    }
}
