#include "FITKOFTransportModel.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

namespace Interface
{
    FITKAbsOFTransportModel::FITKAbsOFTransportModel()
    {
        _transModelPara = new Core::FITKParameter;
    }

    FITKAbsOFTransportModel::~FITKAbsOFTransportModel()
    {
        if (_transModelPara) delete _transModelPara;
    }

    Core::FITKParameter* FITKAbsOFTransportModel::getTransportModelPara()
    {
        return _transModelPara;
    }

    void FITKAbsOFTransportModel::initTransportModelParam()
    {

    }

    FITKOFTransModelNewtonian::FITKOFTransModelNewtonian()
    {
        this->setDataObjectName("Newtonian");
        this->initTransportModelParam();
    }

    FITKOFTransModelNewtonian::~FITKOFTransModelNewtonian()
    {
    }

    void FITKOFTransModelNewtonian::initTransportModelParam()
    {
        if (!_transModelPara) return;
        _transModelPara->createDoubleParameter("v [m2/s]", 1.5e-05);
    }
}
