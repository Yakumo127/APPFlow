/**
 *
 * @file    FITKSnappyHexMeshDriver
 * @brief   SnappyHexMesh网格划分类驱动类
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-06-20
 *
 */
#ifndef FITKOFSNAPPYHEXMESHDRIVER_H
#define FITKOFSNAPPYHEXMESHDRIVER_H

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKProgramDriverFactory.h"
#include "FITKOpenFoamMeshingDriverBase.h"

namespace AppFrame
{
    class FITKProgramInputInfo;
}

namespace FoamDriver
{

    class FITKOFSnappyHexMeshDriver : public FITKOpenFoamMeshingDriverBase
    {
        Q_OBJECT
    public:
        explicit FITKOFSnappyHexMeshDriver() = default;
        virtual ~FITKOFSnappyHexMeshDriver() = default;

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
    Register2FITKProgramDriverFactory(1, FITKOFSnappyHexMeshDriver, FITKOFSnappyHexMeshDriver)
}

#endif // FITKOFSNAPPYHEXMESHDRIVER_H
