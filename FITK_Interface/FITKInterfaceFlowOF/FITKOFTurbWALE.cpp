#include "FITKOFTurbWALE.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

namespace Interface
{
    FITKOFTurbWALE::FITKOFTurbWALE()
    {
        //初始化
        this->init();
        this->setDataObjectName("WALE");
    }

    FITKOFSolverTypeEnum::FITKOFTurbulenceType FITKOFTurbWALE::getTurbulenceType()
    {
        //获取湍流类型
        return FITKOFSolverTypeEnum::FITKOFTurbulenceType::LES;
    }

    void FITKOFTurbWALE::initTurbParam()
    {
        //设置参数
        _turbParams->createDoubleParameter("Ck", 0.094);
        _turbParams->createDoubleParameter("Ce", 1.048);
        _turbParams->createDoubleParameter("Cw", 0.325);
    }

    void FITKOFTurbWALE::initDelta()
    {

    }

    void FITKOFTurbWALE::initDiscretization()
    {

    }

    void FITKOFTurbWALE::initSolution()
    {

    }

    void FITKOFTurbWALE::initBoundary()
    {

    }

    void FITKOFTurbWALE::initInitialConditions()
    {
        //初始化Initial Conditions
    }

}



