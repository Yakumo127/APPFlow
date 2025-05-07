﻿#include "FITKOFSolverManager.h"
#include "FITKOFPhysicsData.h"
#include "FITKOFSolverSIMPLE.h"
#include "FITKOFSolverInter.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"

namespace Interface
{
    FITKOFSolverManager::FITKOFSolverManager()
    {
        this->initSolvers();
    }

    FITKOFSolverManager::~FITKOFSolverManager()
    {

    }

    QStringList FITKOFSolverManager::filterSolvers(QList<FITKOFSolverTypeEnum::FITKOFSolverFiltersType> filtersList)
    {
        QStringList solvers;
        Core::FITKEnumTransfer<FITKOFSolverTypeEnum::FITKOFSolverFiltersType> filterTypeTransfer;
        //获取过滤器
        QStringList filters;
        for (FITKOFSolverTypeEnum::FITKOFSolverFiltersType type : filtersList)
        {
            bool ok = false;
            QString filterStr = filterTypeTransfer.toString(type, ok);
            if (!ok)return QStringList();
            filters.append(filterStr);
        }
        //求解器遍历
        for (QList<FITKOFSolverInfo>::iterator iter = m_solvers.begin(); iter != m_solvers.end(); ++iter)
        {
            //false 被过滤掉 true保留
            bool isFilter = true;
            //进行过滤
            for (QString type : filters)
            {
                isFilter = iter->_solverLabels.contains(type);
                if (!isFilter)break;
            }
            if (!isFilter)continue;
            //添加求解器
            solvers.append(iter->_solverName);
        }
        return solvers;
    }

    FITKOFSolverInfo FITKOFSolverManager::getSolverInfoBySolverName(QString solverName)
    {
        for (QList<FITKOFSolverInfo>::iterator iter = m_solvers.begin(); iter != m_solvers.end(); ++iter)
        {
            if ((*iter)._solverName == solverName) return *iter;
        }
        return FITKOFSolverInfo();
    }

    void FITKOFSolverManager::initSolvers()
    {
        //SINPLE求解器
        FITKOFSolverInfo infoSIMPLE;
        infoSIMPLE._solverName = "SIMPLE";
        infoSIMPLE._solverType = FITKOFSolverTypeEnum::FITKOFSolverType::SIMPLE;
        infoSIMPLE._solverLabels << "NoneFiltersType" << "SteadyState" << "Incompressible" << "Turbulences" << "MRF" << "Porosity";
        infoSIMPLE._createFuns = [&] {return new FITKOFSolverSIMPLE; };
        m_solvers.append(infoSIMPLE);

        //Inter求解器
        FITKOFSolverInfo infoInter;
        infoInter._solverName = "Inter";
        infoInter._solverType = FITKOFSolverTypeEnum::FITKOFSolverType::INTER;
        infoInter._solverLabels << "NoneFiltersType" << "Transient" << "Incompressible" << "Turbulences" << "MRF" << "Porosity" << "DynamicMesh" << "Buoyancy" << "Multiphase";
        infoInter._createFuns = [&] {return new FITKOFSolverInter; };
        m_solvers.append(infoInter);
    }

    

}