#include "FITKOpenFoamMeshingDriverBase.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

namespace FoamDriver
{
    FITKOpenFoamMeshingDriverBase::~FITKOpenFoamMeshingDriverBase()
    {
    }


    //执行完成的槽函数
    void FITKOpenFoamMeshingDriverBase::threadFinishedSlot()
    {
        //发送执行完成信号
        emit sig_Finish();
    }
}


