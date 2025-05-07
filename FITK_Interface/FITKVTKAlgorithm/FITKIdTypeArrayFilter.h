﻿/*****************************************************************//**
 * @file    FITKIdTypeArrayFilter.h
 * @brief   The filter for generating arrays with the given value for
 *          points and cells data.( vtkIdTypeArray )
 *
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2025-02-28
 *********************************************************************/

#ifndef __FITKIDTYPEARRAYFILTER_H__
#define __FITKIDTYPEARRAYFILTER_H__

#include <vtkDataSetAlgorithm.h>

#include "FITKVTKAlgorithmAPI.h"

// Forward declaration

/**
 * @brief   The filter for generating arrays with the given value for 
 *          points and cells data.( vtkIdTypeArray )
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2025-02-28
 */
class FITKVTKALGORITHMAPI FITKIdTypeArrayFilter : public vtkDataSetAlgorithm
{
public:
    vtkTypeMacro(FITKIdTypeArrayFilter, vtkDataSetAlgorithm);

    /**
     * @brief   Create instance.
     * @return  The instance of this class
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    static FITKIdTypeArrayFilter* New();

    /**
     * @brief   Set or get the name of the id array.
     * @return  The array name[const]
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    vtkSetStringMacro(IdArrayName);
    vtkGetStringMacro(IdArrayName);

    /**
     * @brief   Set or get the value of the id array.
     * @return  The array name[const]
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    vtkSetMacro(IntValue, int);
    vtkGetMacro(IntValue, int);

protected:
    /**
     * @brief   Constructor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    FITKIdTypeArrayFilter();

    /**
     * @brief   Destructor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    ~FITKIdTypeArrayFilter() = default;

    /**
     * @brief   Generate and pass through the input and output.[override]
     * @param   request: Not used
     * @param   inputVector: The input data information
     * @param   outputVector: The output data information
     * @return  Is OK
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
        vtkInformationVector* outputVector) override;

private:
    FITKIdTypeArrayFilter(const FITKIdTypeArrayFilter&) = delete;
    void operator=(const FITKIdTypeArrayFilter&) = delete;

    /**
     * @brief   The id array name.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    char* IdArrayName = nullptr;

    /**
     * @brief   The value for points and cells array.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2025-02-28
     */
    int IntValue = 0;

};

#endif // !__FITKIDTYPEARRAYFILTER_H__
