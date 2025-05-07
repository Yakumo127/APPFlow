﻿#include "FITKOFTurbRNGKEpsilon.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

namespace Interface
{
    FITKOFTurbRNGKEpsilon::FITKOFTurbRNGKEpsilon()
    {
        //初始化
        this->init();
        this->setDataObjectName("RNG k-Epsilon");
    }

    FITKOFSolverTypeEnum::FITKOFTurbulenceType FITKOFTurbRNGKEpsilon::getTurbulenceType()
    {
        //获取湍流类型
        return FITKOFSolverTypeEnum::FITKOFTurbulenceType::RANS;
    }

    void FITKOFTurbRNGKEpsilon::initTurbParam()
    {
        //设置参数
        _turbParams->createDoubleParameter("eta0", 4.38);//设置参数
        _turbParams->createDoubleParameter("sigmak", 0.71942);//设置参数
        _turbParams->createDoubleParameter("sigmaEps", 0.71942);//设置参数
        _turbParams->createDoubleParameter("Cmu", 0.0845);//设置参数
        _turbParams->createDoubleParameter("C1", 1.42);//设置参数
        _turbParams->createDoubleParameter("beta", 0.012);//设置参数
        _turbParams->createDoubleParameter("C2", 1.68);//设置参数
    }

    void FITKOFTurbRNGKEpsilon::initDelta()
    {

    }

    void FITKOFTurbRNGKEpsilon::initDiscretization()
    {

    }

    void FITKOFTurbRNGKEpsilon::initSolution()
    {

    }

    void FITKOFTurbRNGKEpsilon::initBoundary()
    {

    }

    void FITKOFTurbRNGKEpsilon::initInitialConditions()
    {
        //初始化Initial Conditions
    }

}



