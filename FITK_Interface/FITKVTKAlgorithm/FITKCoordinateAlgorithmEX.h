﻿/*****************************************************************//**
 * @file    FITKCoordinateAlgorithmEX.h
 * @brief   External filter for creating axes grid data with label string array.
 *          ( Each axes will be shown as an arrow by default. )
 *          This filter contains two output:
 *          1. The first output is a dataset contains the full grid data
 *          with color array.( without text array )
 *          2. The second output is the given direction line grid with
 *          the text array of axes name.
 * 
 *          P.S. This filter can only create ONE axes in this version,
 *          and this filter MUST use vtkDistanceToCamera output as the input.
 *
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-07-09
 *********************************************************************/

#ifndef FITKCOORDINATEALGORITHMEX_H
#define FITKCOORDINATEALGORITHMEX_H

#include "vtkUnstructuredGridAlgorithm.h"

#include "FITKVTKAlgorithmAPI.h"

class vtkTransform;
class vtkArrowSource;
class vtkConeSource;

class FITKVTKALGORITHMAPI FITKCoordinateAlgorithmEX : public vtkUnstructuredGridAlgorithm
{
public:
    vtkTypeMacro(FITKCoordinateAlgorithmEX, vtkUnstructuredGridAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    /**
     * Construct object with scaling on, scaling mode is by scalar value, scale factor = 1.0.
     */
    static FITKCoordinateAlgorithmEX* New();

    //@{
    /**
     * Set/get whether use cone to render axes.
     */
    vtkSetMacro(UseCone, bool);
    vtkGetMacro(UseCone, bool);

    //@{
    /**
     * Set/Get the direction array names.
     */
    vtkSetMacro(DirectionArrayName, const char*);
    vtkGetMacro(DirectionArrayName, const char*);
    //@}

    //@{
    /**
     * Set/Get the name of axes.
     */
    vtkSetMacro(Label, const char*);
    vtkGetMacro(Label, const char*);
    //@}

    //@{
    /**
     * Get the name of the axes label text array name.
     */
    vtkGetMacro(LabelArrayName, const char*);
    //@}

    //@{
    /**
     * Set/get the desired precision for the output types. See the documentation
     * for the vtkAlgorithm::DesiredOutputPrecision enum for an explanation of
     * the available precision settings.
     */
    vtkSetMacro(OutputPointsPrecision, int);
    vtkGetMacro(OutputPointsPrecision, int);
    //@}

protected:
    FITKCoordinateAlgorithmEX();
    ~FITKCoordinateAlgorithmEX();

    int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector, vtkInformationVector* outputVector) override;
    int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;
    int FillInputPortInformation(int, vtkInformation*) override;
    // int FillOutputPortInformation(int, vtkInformation*) override;

    //@{
    /**
     * Method called in RequestData() to do the actual data processing. This will
     * glyph the \c input, filling up the \c output based on the filter
     * parameters.
     */
    virtual bool Execute(vtkDataSet* input, vtkInformationVector* sourceVector, vtkUnstructuredGrid* output);
    virtual bool Execute(vtkDataSet* input, vtkInformationVector* sourceVector, vtkUnstructuredGrid* output,
        vtkDataArray* inSScalars, vtkDataArray* inVectors);
    //@}

    bool UseCone;

    const char* LabelArrayName = "Labels";
   
    int OutputPointsPrecision;

    const char* Label = "Axes";

    const char* DirectionArrayName = "N";

    vtkArrowSource* ArrowSource;
    vtkConeSource* ConeSource;

private:
    FITKCoordinateAlgorithmEX(const FITKCoordinateAlgorithmEX&) = delete;
    void operator=(const FITKCoordinateAlgorithmEX&) = delete;
};

#endif // FITKCOORDINATEALGORITHMEX_H
