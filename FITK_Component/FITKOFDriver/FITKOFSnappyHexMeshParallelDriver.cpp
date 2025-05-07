#include "FITKOFSnappyHexMeshParallelDriver.h"

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

namespace FoamDriver
{
    int FITKOFSnappyHexMeshParallelDriver::getProgramType()
    {
        return 1;
    }

    QString FITKOFSnappyHexMeshParallelDriver::getProgramName()
    {
        return "mpirun";
    }

    void FITKOFSnappyHexMeshParallelDriver::start()
    {
        //输入参数判空
        if (!_inputInfo) return;

    }

    void FITKOFSnappyHexMeshParallelDriver::stop()
    {
        _commandRunner->killProcess(_commandRunner->getID());
    }
}
