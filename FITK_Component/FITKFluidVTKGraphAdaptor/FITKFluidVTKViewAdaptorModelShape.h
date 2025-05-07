/*****************************************************************//**
 * @file    FITKFluidVTKViewAdaptorModelShape.h
 * @brief   Adaptor for 'model' data.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2025-03-31
 *********************************************************************/

#ifndef __FITKFLUIDVTKVIEWADAPTORMODELSHAPE_H__
#define __FITKFLUIDVTKVIEWADAPTORMODELSHAPE_H__

#include "FITKFluidVTKViewAdaptorBase.h"

#include "FITKFluidVTKGraphAdaptorAPI.h"

namespace Exchange
{
    /**
     * @brief   Graph object data adaptor for 'model' data.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-03-31
     */
    class FITKFLUIDGRAPHADAPTORAPI FITKFluidVTKViewAdaptorModelShape : public FITKFluidVTKViewAdaptorBase
    {
        // Regist
        FITKCLASS(Exchange, FITKFluidVTKViewAdaptorModelShape);

    public:
        /**
         * @brief   Constructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-31
         */
        explicit FITKFluidVTKViewAdaptorModelShape() = default;

        /**
         * @brief   Destructor.
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-31
         */
        ~FITKFluidVTKViewAdaptorModelShape() = default;

        /**
         * @brief   Execute the data exchange.[override]
         * @return  Is OK
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-31
         */
        bool update() override;

    };

    // Regist model shape adaptor
    Register2FITKViewAdaptorFactory(GeoModelShape, Interface::FITKAbsGeoShapeAgent, FITKFluidVTKViewAdaptorModelShape);
}   // namespace Exchange

#endif // __FITKFLUIDVTKVIEWADAPTORMODELSHAPE_H__