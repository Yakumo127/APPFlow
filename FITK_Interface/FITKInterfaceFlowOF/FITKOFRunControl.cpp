#include "FITKOFRunControl.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

namespace Interface
{

    FITKOFRunControl::FITKOFRunControl()
    {
        _timeControl = new Core::FITKParameter;
        _outputControl = new Core::FITKParameter;
    }

    FITKOFRunControl::~FITKOFRunControl()
    {
        if (_timeControl) delete _timeControl;
        if (_outputControl) delete _outputControl;
    }

    Core::FITKParameter* FITKOFRunControl::getTimeControl()
    {
        return _timeControl;
    }

    Core::FITKParameter* FITKOFRunControl::getOutputControl()
    {
        return _outputControl;
    }
}
