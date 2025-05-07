﻿/*****************************************************************//**
 * @file    FITKDataSetDealer.h
 * @brief   The external data set dealer for reading vtk files.
 *
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-08-30
 *********************************************************************/

#ifndef FITKDATASETDELAER_H
#define FITKDATASETDELAER_H

#include "vtkDataSetAlgorithm.h"

#include "FITKVTKAlgorithmAPI.h"

class vtkDataSetAttributes;
class vtkCellData;

class FITKVTKALGORITHMAPI FITKDataSetDealer : public vtkDataSetAlgorithm
{
public:
    static FITKDataSetDealer* New();
    vtkTypeMacro(FITKDataSetDealer, vtkDataSetAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    //@{
    /**
     * Get the output of this filter
     */
    vtkDataSet* GetOutput();
    vtkDataSet* GetOutput(int idx);
    //@}

protected:
    /**
     * @brief   Constructor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    FITKDataSetDealer() = default;

    /**
     * @brief   Destructor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    virtual ~FITKDataSetDealer() = default;

    /**
     * @brief   Fill the input port's information.
     * @param   port: The input port
     * @param   info: Information
     * @return  Is valid
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    int FillInputPortInformation(int port, vtkInformation* info);

    /**
     * @brief   Fill the output port's information.
     * @param   port: The input port
     * @param   info: Information
     * @return  Is valid
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    int FillOutputPortInformation(int port, vtkInformation* info);

    /**
     * @brief   Preprocess function before the algorithm begin.
     * @param   request: The requested data
     * @param   inputVector: The input vector
     * @param   outputVector: The ouput data
     * @return  Is valid
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);

    /**
     * @brief   The algorithm excute.
     * @param   request: The requested data
     * @param   inputVector: The input vector
     * @param   outputVector: The ouput data
     * @return  Is valid
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    int RequestData(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector);

private:
    FITKDataSetDealer(const FITKDataSetDealer&) = delete;
    void operator=(const FITKDataSetDealer&) = delete;

    /**
     * @brief   Initialize array names.
     * @param   obj: The data set
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    void initArrayNames(vtkDataObject* obj);

    /**
     * @brief   Give the array's component a name if the component has no name.
     * @param   dArray
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    void initArrayName(vtkDataArray* dArray);

    /**
     * @brief   Add a cell id array to the cell data.
     * @param   cellData: The data set cell data
     * @param   nCell: The number of cells
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    void addCellIdArray(vtkCellData* cellData, int nCell);

};

#endif // FITKDATASETDELAER_h
