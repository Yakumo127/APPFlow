/*****************************************************************//**
 * @file    FITKFluidVTKViewAdaptorMaterialPoints.h
 * @brief   Adaptor for all material points data.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-07-30
 *********************************************************************/

#ifndef __FITKFLUIDVTKVIEWADAPTORMATERIALPOINTS_H__
#define __FITKFLUIDVTKVIEWADAPTORMATERIALPOINTS_H__

#include "FITKFluidVTKViewAdaptorBase.h"

#include "FITKFluidVTKGraphAdaptorAPI.h"

namespace Exchange
{
    /**
     * @brief   Graph object data adaptor for all material points data.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-07-30
     */
    class FITKFLUIDGRAPHADAPTORAPI FITKFluidVTKViewAdaptorMaterialPoints : public FITKFluidVTKViewAdaptorBase
    {
        // Regist
        FITKCLASS(Exchange, FITKFluidVTKViewAdaptorMaterialPoints);

    public:
        /**
         * @brief   Constructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
        explicit FITKFluidVTKViewAdaptorMaterialPoints() = default;

        /**
         * @brief   Destructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
        ~FITKFluidVTKViewAdaptorMaterialPoints() = default;

        /**
         * @brief   Execute the data exchange.[override]
         * @return  Is OK
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-30
         */
        bool update() override;

    };

    // Regist material points manager adaptor
    Register2FITKViewAdaptorFactory(MaterialPoints, Interface::FITKZonePointManager, FITKFluidVTKViewAdaptorMaterialPoints);
}   // namespace Exchange

#endif // __FITKFLUIDVTKVIEWADAPTORMATERIALPOINTS_H__