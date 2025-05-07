﻿/**********************************************************************
 * @file   FITKOFTurbKOmega.h
 * @brief  k-Omega 湍流数据接口声明
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-21
 *********************************************************************/
#ifndef _FITKOF_TURB_KOmega_H___
#define _FITKOF_TURB_KOmega_H___
 
#include "FITKAbstractOFTurbulence.h"

namespace Interface
{
    /**
     * @brief  k-Omega 湍流数据对象
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-08-21
     */
    class FITKInterfaceFlowOFAPI FITKOFTurbKOmega : public FITKAbstractOFTurbulence
    {
    public:
        explicit FITKOFTurbKOmega();
        virtual ~FITKOFTurbKOmega() = default;
        
        /**
         * @brief    获取湍流类型
         * @return   FITKOFSolverTypeEnum::FITKOFTurbulenceType
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        virtual FITKOFSolverTypeEnum::FITKOFTurbulenceType getTurbulenceType() override;

    protected:
        /**
         * @brief    初始化湍流模型参数
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        virtual void initTurbParam() override;
        /**
         * @brief    初始化Delta数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        virtual void initDelta() override;
        /**
         * @brief    初始湍流模型下特定的离散数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-21
         */
        virtual void initDiscretization() override;
        /**
         * @brief    初始化solution数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-22
         */
        virtual void initSolution() override;
        /**
         * @brief    初始化 Initial Conditions数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-23
         */
        virtual void initInitialConditions() override;
        /**
         * @brief    初始化 Boundary 数据
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-26
         */
        virtual void initBoundary() override;

    private:
    };
}


#endif
