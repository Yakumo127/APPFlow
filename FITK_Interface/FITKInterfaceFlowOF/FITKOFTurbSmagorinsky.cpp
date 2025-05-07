#include "FITKOFTurbSmagorinsky.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

namespace Interface
{
    FITKOFTurbSmagorinsky::FITKOFTurbSmagorinsky()
    {
        //初始化
        this->init();
        this->setDataObjectName("Smagorinsky");
    }

    FITKOFSolverTypeEnum::FITKOFTurbulenceType FITKOFTurbSmagorinsky::getTurbulenceType()
    {
        //获取湍流类型
        return FITKOFSolverTypeEnum::FITKOFTurbulenceType::LES;
    }

    void FITKOFTurbSmagorinsky::initTurbParam()
    {
        //设置参数
        _turbParams->createDoubleParameter("Ck", 0.094);
        _turbParams->createDoubleParameter("Ce", 1.048);
    }

    void FITKOFTurbSmagorinsky::initDelta()
    {

    }

    void FITKOFTurbSmagorinsky::initDiscretization()
    {

    }

    void FITKOFTurbSmagorinsky::initSolution()
    {

    }

    void FITKOFTurbSmagorinsky::initBoundary()
    {

    }

    void FITKOFTurbSmagorinsky::initInitialConditions()
    {
        //初始化Initial Conditions
    }

}



