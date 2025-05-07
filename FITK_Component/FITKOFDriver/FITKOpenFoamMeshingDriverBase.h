/**
 *
 * @file    FITKOpenFoamMeshingDriverBase
 * @brief   OpenFoam网格划分父类
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-07-18
 *
 */
#ifndef FITKOPENFOAMMESHINGDRIVERBASE_H
#define FITKOPENFOAMMESHINGDRIVERBASE_H

#include "FITK_Kernel/FITKAppFramework/FITKLinuxShellDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKProgramDriverFactory.h"

namespace FoamDriver
{

    class FITKOpenFoamMeshingDriverBase : public AppFrame::FITKLinuxShellDriver
    {
        Q_OBJECT
    public:
        explicit FITKOpenFoamMeshingDriverBase() = default;
        virtual ~FITKOpenFoamMeshingDriverBase();


    protected slots:
        /**
         * @brief   线程执行结束
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-07-29
         */
        void threadFinishedSlot();
    };
}
#endif // FITKOFBLOCKMESHDRIVER_H
