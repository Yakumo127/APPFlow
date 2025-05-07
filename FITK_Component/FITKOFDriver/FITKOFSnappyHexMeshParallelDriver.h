/**
 *
 * @file    FITKOFSnappyHexMeshParallelDriver
 * @brief
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-07-04
 *
 */
#ifndef FITKOFSNAPPYHEXMESHPARALLELDRIVER_H
#define FITKOFSNAPPYHEXMESHPARALLELDRIVER_H

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKProgramDriverFactory.h"
#include "FITKOpenFoamMeshingDriverBase.h"

namespace AppFrame
{
    class FITKProgramInputInfo;
}

namespace FoamDriver
{
    class FITKOFSnappyHexMeshParallelDriver : public FITKOpenFoamMeshingDriverBase
    {
        Q_OBJECT
    public:
        explicit FITKOFSnappyHexMeshParallelDriver() = default;
        virtual ~FITKOFSnappyHexMeshParallelDriver() = default;

        /**
         * @brief   获取SnappyHexMesh程序类型
         * @return  1
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-07-02
         */
        int getProgramType() override;

        /**
         * @brief   获取程序名称
         * @return  "SnappyHexMesh"
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-07-02
         */
        QString getProgramName() override;

        /**
         * @brief   启动SnappyHexMesh格划分程序
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-07-02
         */
        void start() override;
        /**
         * @brief   终止程序
         * @author fulipeng (fulipengqd@yeah.net)
         * @date    2024-07-18
         */
        void stop() override;

    };
    Register2FITKProgramDriverFactory(1, FITKOFSnappyHexMeshParallelDriver, FITKOFSnappyHexMeshParallelDriver)
}

#endif // FITKOFSNAPPYHEXMESHPARALLELDRIVER_H
