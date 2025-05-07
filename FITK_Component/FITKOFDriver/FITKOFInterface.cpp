#include "FITKOFInterface.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

namespace FoamDriver
{

    FITKOFInterface::FITKOFInterface()
    {
        _commandRunner = new AppFrame::FITKLinuxCommandRunner();
    }

    FITKOFInterface::~FITKOFInterface()
    {
        if (_commandRunner != nullptr)
        {
            delete _commandRunner;
            _commandRunner = nullptr;
        }
    }

    void FITKOFInterface::init()
    {
        //初始化 todo
    }

    QString FITKOFInterface::getComponentName()
    {
        //自定义名称
        return "FITKopenFOAMDriver";
    }
}
