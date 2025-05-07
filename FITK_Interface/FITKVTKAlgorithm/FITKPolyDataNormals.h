/*****************************************************************//**
 * @file    FITKPolyDataNormals.h
 * @brief   The filter for getting polydata's normals.
 *
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-04-30
 *********************************************************************/

#ifndef FITKPOLYDATANORMALS_H
#define FITKPOLYDATANORMALS_H

#include "vtkPolyDataAlgorithm.h"

#include "FITKVTKAlgorithmAPI.h"

class vtkFloatArray;
class vtkIdList;
class vtkPolyData;

class FITKVTKALGORITHMAPI FITKPolyDataNormals : public vtkPolyDataAlgorithm
{
public:
    vtkTypeMacro(FITKPolyDataNormals, vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    /**
     * Construct with feature angle=30, splitting and consistency turned on,
     * flipNormals turned off, and non-manifold traversal turned on.
     * ComputePointNormals is on and ComputeCellNormals is off.
     */
    static FITKPolyDataNormals* New();

    //@{
    /**
     * Specify the angle that defines a sharp edge. If the difference in
     * angle across neighboring polygons is greater than this value, the
     * shared edge is considered "sharp".
     */
    vtkSetClampMacro(FeatureAngle, double, 0.0, 180.0);
    vtkGetMacro(FeatureAngle, double);
    //@}

    //@{
    /**
     * Turn on/off the splitting of sharp edges.
     */
    vtkSetMacro(Splitting, vtkTypeBool);
    vtkGetMacro(Splitting, vtkTypeBool);
    vtkBooleanMacro(Splitting, vtkTypeBool);
    //@}

    //@{
    /**
     * Turn on/off the enforcement of consistent polygon ordering.
     */
    vtkSetMacro(Consistency, vtkTypeBool);
    vtkGetMacro(Consistency, vtkTypeBool);
    vtkBooleanMacro(Consistency, vtkTypeBool);
    //@}

    //@{
    /**
     * Turn on/off the automatic determination of correct normal
     * orientation. NOTE: This assumes a completely closed surface
     * (i.e. no boundary edges) and no non-manifold edges. If these
     * constraints do not hold, all bets are off. This option adds some
     * computational complexity, and is useful if you don't want to have
     * to inspect the rendered image to determine whether to turn on the
     * FlipNormals flag. However, this flag can work with the FlipNormals
     * flag, and if both are set, all the normals in the output will
     * point "inward".
     */
    vtkSetMacro(AutoOrientNormals, vtkTypeBool);
    vtkGetMacro(AutoOrientNormals, vtkTypeBool);
    vtkBooleanMacro(AutoOrientNormals, vtkTypeBool);
    //@}

    //@{
    /**
     * Turn on/off the computation of point normals.
     */
    vtkSetMacro(ComputePointNormals, vtkTypeBool);
    vtkGetMacro(ComputePointNormals, vtkTypeBool);
    vtkBooleanMacro(ComputePointNormals, vtkTypeBool);
    //@}

    //@{
    /**
     * Turn on/off the computation of cell normals.
     */
    vtkSetMacro(ComputeCellNormals, vtkTypeBool);
    vtkGetMacro(ComputeCellNormals, vtkTypeBool);
    vtkBooleanMacro(ComputeCellNormals, vtkTypeBool);
    //@}

    //@{
    /**
     * Turn on/off the global flipping of normal orientation. Flipping
     * reverves the meaning of front and back for Frontface and Backface
     * culling in vtkProperty.  Flipping modifies both the normal
     * direction and the order of a cell's points.
     */
    vtkSetMacro(FlipNormals, vtkTypeBool);
    vtkGetMacro(FlipNormals, vtkTypeBool);
    vtkBooleanMacro(FlipNormals, vtkTypeBool);
    //@}

    //@{
    /**
     * Turn on/off traversal across non-manifold edges. This will prevent
     * problems where the consistency of polygonal ordering is corrupted due
     * to topological loops.
     */
    vtkSetMacro(NonManifoldTraversal, vtkTypeBool);
    vtkGetMacro(NonManifoldTraversal, vtkTypeBool);
    vtkBooleanMacro(NonManifoldTraversal, vtkTypeBool);
    //@}

    //@{
    /**
     * Set/get the desired precision for the output types. See the documentation
     * for the vtkAlgorithm::DesiredOutputPrecision enum for an explanation of
     * the available precision settings.
     */
    vtkSetClampMacro(OutputPointsPrecision, int, SINGLE_PRECISION, DEFAULT_PRECISION);
    vtkGetMacro(OutputPointsPrecision, int);
    //@}

protected:
    FITKPolyDataNormals();
    ~FITKPolyDataNormals() override {}

    // Usual data generation method
    int RequestData(vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

    double FeatureAngle;
    vtkTypeBool Splitting;
    vtkTypeBool Consistency;
    vtkTypeBool FlipNormals;
    vtkTypeBool AutoOrientNormals;
    vtkTypeBool NonManifoldTraversal;
    vtkTypeBool ComputePointNormals;
    vtkTypeBool ComputeCellNormals;
    int NumFlips;
    int OutputPointsPrecision;

private:
    vtkIdList* Wave;
    vtkIdList* Wave2;
    vtkIdList* CellIds;
    vtkIdList* CellPoints;
    vtkIdList* NeighborPoints;
    vtkIdList* Map;
    vtkPolyData* OldMesh;
    vtkPolyData* NewMesh;
    int* Visited;
    vtkFloatArray* PolyNormals;
    double CosAngle;

    // Uses the list of cell ids (this->Wave) to propagate a wave of
    // checked and properly ordered polygons.
    void TraverseAndOrder(void);

    // Check the point id give to see whether it lies on a feature
    // edge. If so, split the point (i.e., duplicate it) to topologically
    // separate the mesh.
    void MarkAndSplit(vtkIdType ptId);

private:
    FITKPolyDataNormals(const FITKPolyDataNormals&) = delete;
    void operator=(const FITKPolyDataNormals&) = delete;
};

#endif // FITKPOLYDATANORMALS_H
