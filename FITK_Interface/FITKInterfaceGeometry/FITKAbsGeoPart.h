/*****************************************************************//**
 * @file    FITKAbsGeoPart.h
 * @brief   模型部件命令数据抽象类。

 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-11-27
 *********************************************************************/

#ifndef  FITKABSGEOPART_H
#define  FITKABSGEOPART_H

#include "FITKAbsGeoCommand.h"

#include "FITKGeoEnum.h"

#include "FITKInterfaceGeometryAPI.h"

namespace Interface
{
    /**
     * @brief   模型部件命令数据抽象类。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-27
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoPart : public Interface::FITKAbsGeoCommand, public FITKGeoCommandManager
    {
        FITKCLASS(Interface, FITKAbsGeoPart);
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-11-27
         */
        FITKAbsGeoPart() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-11-27
         */
        virtual ~FITKAbsGeoPart() = default;

        /**
         * @brief   获取数据类型。[重写]
         * @return  数据类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-11-27
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

        /**
         * @brief   回溯最终的形状[虚函数]
         * @return  是否回溯成功
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2025-04-27
         */
        virtual bool backtrackingShape();

        /**
         * @brief   更新命令。[虚函数][重写]
         * @return  是否更新成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-11-27
         */
        virtual bool update() override;

    };
}

#endif // !FITKABSGEOPART_H
