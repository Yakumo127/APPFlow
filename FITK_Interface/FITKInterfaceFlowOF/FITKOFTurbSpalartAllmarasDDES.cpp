#include "FITKOFTurbSpalartAllmarasDDES.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

namespace Interface
{
    FITKOFTurbSpalartAllmarasDDES::FITKOFTurbSpalartAllmarasDDES()
    {
        //初始化
        this->init();
        this->setDataObjectName("Spalart-Allmaras DDES");
    }

    FITKOFSolverTypeEnum::FITKOFTurbulenceType FITKOFTurbSpalartAllmarasDDES::getTurbulenceType()
    {
        //获取湍流类型
        return FITKOFSolverTypeEnum::FITKOFTurbulenceType::LES;
    }

    void FITKOFTurbSpalartAllmarasDDES::initTurbParam()
    {
        //设置参数
        _turbParams->createDoubleParameter("Cb2", 0.622);
        _turbParams->createDoubleParameter("Cb1", 0.1355);
        _turbParams->createDoubleParameter("kappa", 0.41);
        _turbParams->createDoubleParameter("sigmaNut", 0.66666);
        _turbParams->createDoubleParameter("Cw3", 2.0);
        _turbParams->createDoubleParameter("Cv2", 5.0);
        _turbParams->createDoubleParameter("Cw2", 0.3);
        _turbParams->createDoubleParameter("Cv1", 7.1);
    }

    void FITKOFTurbSpalartAllmarasDDES::initDelta()
    {

    }

    void FITKOFTurbSpalartAllmarasDDES::initDiscretization()
    {

    }

    void FITKOFTurbSpalartAllmarasDDES::initSolution()
    {

    }

    void FITKOFTurbSpalartAllmarasDDES::initBoundary()
    {

    }

    void FITKOFTurbSpalartAllmarasDDES::initInitialConditions()
    {
        //初始化Initial Conditions
    }

}



