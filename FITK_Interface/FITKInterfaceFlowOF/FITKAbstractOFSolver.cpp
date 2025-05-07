#include "FITKAbstractOFSolver.h"
#include "FITKOFTransportProp.h"
#include "FITKOFDiscretization.h"
#include "FITKOFSolution.h"
#include "FITKOFBoundary.h"
#include "FITKOFRunControl.h"
#include "FITKOFInitialConditions.h"
#include "FITKOFOperatingConditions.h"

namespace Interface
{
    FITKAbstractOFSolver::FITKAbstractOFSolver()
    {
        //创建数据对象
        _discretization = new FITKOFDiscretization;
        _solution = new FITKOFSolution;
        _initialCond = new FITKOFInitialConditions;
        _runControl = new FITKOFRunControl;
    }

    FITKAbstractOFSolver::~FITKAbstractOFSolver()
    {
        //销毁数据
        if (_transportProp) delete _transportProp;
        if (_discretization) delete _discretization;
        if (_solution) delete _solution;
        if (_initialCond) delete _initialCond;
        if (_operatingCond) delete _operatingCond;

        for (FITKOFBoundary* bd : _boundaryInfos)
            if (bd) delete bd;
        _boundaryInfos.clear();
    }

    QString FITKAbstractOFSolver::getSolverCommand()
    {
        return QString();
    }

    bool FITKAbstractOFSolver::turbEnabled() const
    {
        //是否启用湍流
        return _enableTurb;
    }

    FITKOFSolverTypeEnum::FITKOFSolverType FITKAbstractOFSolver::getSolverType()
    {
        //获取求解器类型
        return FITKOFSolverTypeEnum::FITKOFSolverType::SolverNone;
    }

    FITKOFDiscretization* FITKAbstractOFSolver::getDiscretization()
    {
        //获取离散
        return _discretization;
    }

    FITKOFTransportProp* FITKAbstractOFSolver::getTransportProp()
    {
        //获取材料
        return _transportProp;
    }

    FITKOFSolution* FITKAbstractOFSolver::getSolution()
    {
        //获取solution数据
        return _solution;
    }

    FITKOFInitialConditions* FITKAbstractOFSolver::getInitialConditions()
    {
        //获取Initial Conditions数据
        return _initialCond;
    }

    FITKOFBoundary* FITKAbstractOFSolver::getBoundary(FITKOFSolverTypeEnum::FITKOFBoundaryType bType)
    {
        //获取边界数据
        for (FITKOFBoundary* bd : _boundaryInfos)
        {
            if (!bd)continue;
            if (bd->getBoundaryType() == bType)
                return bd;
        }
        return nullptr;
    }

    FITKOFRunControl* FITKAbstractOFSolver::getRunControl()
    {
        //获取运行配置数据
        return _runControl;
    }

    FITKOFOperatingConditions* FITKAbstractOFSolver::getOperatingConditions()
    {
        //获取求解工作条件
        return _operatingCond;
    }

    void FITKAbstractOFSolver::init()
    {
        //初始化数据
        this->initTransportProp();
        this->initDiscretization();
        this->initSolution();
        this->initBoundarys();
        this->initInitialConditions();
        this->initRunControl();
        this->initOperatingConditions();
    }

    void FITKAbstractOFSolver::initTransportProp()
    {
        //初始化材料
    }

    void FITKAbstractOFSolver::initDiscretization()
    {
        //初始化离散数据
    }

    void FITKAbstractOFSolver::initSolution()
    {
        //初始化solution
    }

    void FITKAbstractOFSolver::initBoundarys()
    {
        //初始化边界
    }

    void FITKAbstractOFSolver::initInitialConditions()
    {
        //初始化Initial Conditions数据
    }

    void FITKAbstractOFSolver::initRunControl()
    {
        //初始化运行配置数据
    }

    void FITKAbstractOFSolver::initOperatingConditions()
    {
        //初始化工作条件
    }
}


