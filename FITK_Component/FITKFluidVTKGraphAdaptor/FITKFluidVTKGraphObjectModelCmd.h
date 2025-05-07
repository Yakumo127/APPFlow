/*****************************************************************//**
 * @file    FITKFluidVTKGraphObjectModelCmd.h
 * @brief   Shape graph object 3D model for VTK graph widget.( Legacy )

 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-06-05
 *********************************************************************/

#ifndef __FITKFLUIDVTKGRAPHOBJECTMODELCMD_H__
#define __FITKFLUIDVTKGRAPHOBJECTMODELCMD_H__

#include "FITKFluidVTKGraphObjectModelBase.h"

#include "FITKFluidVTKGraphAdaptorAPI.h"

// Forward declaration
namespace Interface
{
    class FITKAbsGeoCommand;
}

namespace Exchange
{
    /**
     * @brief   Shape graph object 3D model for VTK graph widget.( Legacy )
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-06-05
     */
    class FITKFLUIDGRAPHADAPTORAPI FITKFluidVTKGraphObjectModelCmd : public FITKFluidVTKGraphObjectModelBase
    {
        // Regist
        FITKGraphObjectRegist(FITKFluidVTKGraphObjectModelCmd, FITKFluidVTKGraphObjectModelBase);
        FITKCLASS(Exchange, FITKFluidVTKGraphObjectModelCmd);

    public:
        /**
         * @brief   Constructor.
         * @param   modelData: The shape model data object need to exchange
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-06-05
         */
        FITKFluidVTKGraphObjectModelCmd(Interface::FITKAbsGeoCommand* modelData);

        /**
         * @brief   Destructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-06-05
         */
        ~FITKFluidVTKGraphObjectModelCmd() = default;

        /**
         * @brief   Update all graph actors.[override]
         * @param   forceUpdate: Force update[default]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-07-24
         */
        void update(bool forceUpdate = false) override;

    };
}   // namespace Exchange

#endif // __FITKFLUIDVTKGRAPHOBJECTMODELCMD_H__
