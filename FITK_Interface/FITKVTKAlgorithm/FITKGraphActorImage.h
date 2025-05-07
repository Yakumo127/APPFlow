﻿/*****************************************************************//**
 * @file    FITKGraphActorImage.h
 * @brief   External vtkImageActor with some common functions.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-11-07
 *********************************************************************/

#ifndef __FITKGRAPHACTORIMAGE_H__
#define __FITKGRAPHACTORIMAGE_H__

#include <vtkImageActor.h>

#include "FITKVTKAlgorithmAPI.h"

#include <vtkObjectFactory.h>
#include <vtkRenderingCoreModule.h>

// Forward declaration
namespace Comp
{
    class FITKGraphObjectVTK;
}

/**
 * @brief   Override vtkImageActor, add some new interfaces for setting input.
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-11-07
 */
class FITKVTKALGORITHMAPI FITKGraphActorImage : public vtkImageActor
{
public:
    vtkTypeMacro(FITKGraphActorImage, vtkImageActor);

    /**
     * @brief   VTK new.
     * @return  The instance
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    static FITKGraphActorImage* New();

    /**
     * @brief   Set the data object.
     * @param   obj: Data object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    void setGraphObject(Comp::FITKGraphObjectVTK* obj);

    /**
     * @brief   Get the data object.
     * @return  Data object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    Comp::FITKGraphObjectVTK* getGraphObject();

    /**
     * @brief   Get the graph object as the given type.[template]
     * @return  The graph object.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    template<class T>
    T* getGraphObjectAs()
    {
        return dynamic_cast<T*>(m_graphObj);
    }

protected:
    /**
     * @brief   Constructor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    FITKGraphActorImage();

    /**
     * @brief   Destructor.[virtual]
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    virtual ~FITKGraphActorImage();

    /**
     * @brief   Copy constructor.
     * @param   The object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    FITKGraphActorImage(const FITKGraphActorImage&) = delete;

    /**
     * @brief   Operator overloading.
     * @param   The object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    void operator=(const FITKGraphActorImage&) = delete;

protected:
    /**
     * @brief   Shallow copy.[override]
     * @param   prop: The source prop
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    void ShallowCopy(vtkProp* prop) override;
    //@}

protected:
    /**
     * @brief   The data object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-07
     */
    Comp::FITKGraphObjectVTK* m_graphObj{ nullptr };

};

#endif // __FITKGraphActorImage_H__
