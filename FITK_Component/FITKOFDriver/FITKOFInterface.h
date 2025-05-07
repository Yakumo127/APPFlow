/**
 *
 * @file    FITKOpenFOAMDriverInterface
 * @brief   注册接口
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-06-20
 *
 */
#ifndef FITKOPENFOAMDRIVER_H
#define FITKOPENFOAMDRIVER_H

#include "FITKOFDriverAPI.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"

namespace AppFrame
{
    class FITKAbstractCommandRunner;
}

namespace FoamDriver
{

    class FITKOFDRIVERAPI FITKOFInterface : public AppFrame::FITKComponentInterface
    {
    public:
        explicit FITKOFInterface();
        virtual ~FITKOFInterface();

        /**
         * @brief   初始化，创建完成之后自动化调用
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-06-20
         */
        void init() override;

        /**
         * @brief   获取部件名称#include <cstring>
         * @return  部件名称
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-06-20
         */
        QString getComponentName() override;

    private:
        /**
        * @brief   进程ID
        * @author  fulipeng (fulipengqd@yeah.net)
        * @date    2024-07-25
        */
        qint64 _processId = -1;
        /**
         * @brief 终端命令执行 子类中实例
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-07-25
         */
        AppFrame::FITKAbstractCommandRunner* _commandRunner{};
    };
}

#endif // FITKOPENFOAMDRIVER_H

