/*****************************************************************//**
 * @file    FITKFluidVTKViewAdaptorModelCmd.h
 * @brief   Adaptor for 'model' data.( Legacy )
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-06-11
 *********************************************************************/

#ifndef __FITKFLUIDVTKVIEWADAPTORMODELCMD_H__
#define __FITKFLUIDVTKVIEWADAPTORMODELCMD_H__

#include "FITKFluidVTKViewAdaptorBase.h"

#include "FITKFluidVTKGraphAdaptorAPI.h"

namespace Exchange
{
    /**
     * @brief   Graph object data adaptor for 'model' data.( Legacy )
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-06-11
     */
    class FITKFLUIDGRAPHADAPTORAPI FITKFluidVTKViewAdaptorModelCmd : public FITKFluidVTKViewAdaptorBase
    {
        // Regist
        FITKCLASS(Exchange, FITKFluidVTKViewAdaptorModelCmd);

    public:
        /**
         * @brief   Constructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-06-11
         */
        explicit FITKFluidVTKViewAdaptorModelCmd() = default;

        /**
         * @brief   Destructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-06-11
         */
        ~FITKFluidVTKViewAdaptorModelCmd() = default;

        /**
         * @brief   Execute the data exchange.[override]
         * @return  Is OK
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-06-11
         */
        bool update() override;

    };

    // Regist model adaptor
    Register2FITKViewAdaptorFactory(GeoModelCmd, Interface::FITKAbsGeoCommand, FITKFluidVTKViewAdaptorModelCmd);
}   // namespace Exchange

#endif // __FITKFLUIDVTKVIEWADAPTORMODELCMD_H__