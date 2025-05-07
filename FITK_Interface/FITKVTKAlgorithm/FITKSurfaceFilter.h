﻿/*****************************************************************//**
 * @file   FITKSurfaceFilter.cpp
 * @brief  Surface filter with cell id map.
 *
 * @author ChengHaotian (yeguangbaozi@foxmail.com)
 * @date   2024-03-21
 *********************************************************************/

#ifndef FITKSURFACEFILTER_H
#define FITKSURFACEFILTER_H

#include "vtkPolyDataAlgorithm.h"

#include "FITKVTKAlgorithmAPI.h"

#include <map>

class vtkPointData;
class vtkPoints;
class vtkIdTypeArray;
class vtkStructuredGrid;

// Helper structure for hashing faces.
struct FITKFastGeomQuadStruct
{
    struct FITKFastGeomQuadStruct *Next;
    vtkIdType SourceId;
    int numPts;
    vtkIdType* ptArray;
    int CellDim;
};
typedef struct FITKFastGeomQuadStruct FITKFastGeomQuad;

/**
 * @brief   Override vtkSurfaceFilter.
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-03-25
 */
class FITKVTKALGORITHMAPI FITKSurfaceFilter : public vtkPolyDataAlgorithm
{
public:
    static FITKSurfaceFilter* New();
    vtkTypeMacro(FITKSurfaceFilter, vtkPolyDataAlgorithm);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    int getOriginCellIdBySurfaceCellId(int surfaceCellId);

    int getOriginPointIdBySurfacePointId(int surfacePointId);

    /**
     * @brief   Get the original cell id with the given surface data cell id, and get its surface index too.
     * @param   surfaceCellId: The surface cell id
     * @param   cellId: The original cell id
     * @param   surfaceIndex: The index of the given surface
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-18
     */
    void getSurfaceCellInfo(int surfaceCellId, int& cellId, int& surfaceIndex);

    //@{
    /**
     * When input is structured data, this flag will generate faces with
     * triangle strips.  This should render faster and use less memory, but no
     * cell data is copied.  By default, UseStrips is Off.
     */
    vtkSetMacro(UseStrips, vtkTypeBool);
    vtkGetMacro(UseStrips, vtkTypeBool);
    vtkBooleanMacro(UseStrips, vtkTypeBool);
    //@}

    //@{
    /**
     * If PieceInvariant is true, vtkDataSetSurfaceFilter requests
     * 1 ghost level from input in order to remove internal surface
     * that are between processes. False by default.
     */
    vtkSetMacro(PieceInvariant, int);
    vtkGetMacro(PieceInvariant, int);
    //@}

    //@{
    /**
     * If on, the output polygonal dataset will have a celldata array that
     * holds the cell index of the original 3D cell that produced each output
     * cell. This is useful for cell picking. The default is off to conserve
     * memory. Note that PassThroughCellIds will be ignored if UseStrips is on,
     * since in that case each tringle strip can represent more than on of the
     * input cells.
     */
    vtkSetMacro(PassThroughCellIds, vtkTypeBool);
    vtkGetMacro(PassThroughCellIds, vtkTypeBool);
    vtkBooleanMacro(PassThroughCellIds, vtkTypeBool);
    vtkSetMacro(PassThroughPointIds, vtkTypeBool);
    vtkGetMacro(PassThroughPointIds, vtkTypeBool);
    vtkBooleanMacro(PassThroughPointIds, vtkTypeBool);
    //@}

    //@{
    /**
     * If PassThroughCellIds or PassThroughPointIds is on, then these ivars
     * control the name given to the field in which the ids are written into.  If
     * set to nullptr, then vtkOriginalCellIds or vtkOriginalPointIds (the default)
     * is used, respectively.
     */
    vtkSetStringMacro(OriginalCellIdsName);
    virtual const char *GetOriginalCellIdsName()
    {
        return (this->OriginalCellIdsName
            ? this->OriginalCellIdsName : "vtkOriginalCellIds");
    }
    vtkSetStringMacro(OriginalPointIdsName);
    virtual const char *GetOriginalPointIdsName()
    {
        return (this->OriginalPointIdsName
            ? this->OriginalPointIdsName : "vtkOriginalPointIds");
    }

    const char *GetOriginalCellDimsName()
    {
        return "vtkOriginalCellDims";
    }
    //@}

    //@{
    /**
     * If the input is an unstructured grid with nonlinear faces, this parameter
     * determines how many times the face is subdivided into linear faces.  If 0,
     * the output is the equivalent of its linear counterpart (and the midpoints
     * determining the nonlinear interpolation are discarded).  If 1 (the
     * default), the nonlinear face is triangulated based on the midpoints.  If
     * greater than 1, the triangulated pieces are recursively subdivided to reach
     * the desired subdivision.  Setting the value to greater than 1 may cause
     * some point data to not be passed even if no nonlinear faces exist.  This
     * option has no effect if the input is not an unstructured grid.
     */
    vtkSetMacro(NonlinearSubdivisionLevel, int);
    vtkGetMacro(NonlinearSubdivisionLevel, int);
    //@}

    //@{
    /**
     * Direct access methods that can be used to use the this class as an
     * algorithm without using it as a filter.
     */
    virtual int StructuredExecute(vtkDataSet *input,
        vtkPolyData *output, vtkIdType *ext, vtkIdType *wholeExt);
#ifdef VTK_USE_64BIT_IDS
    virtual int StructuredExecute(vtkDataSet *input,
        vtkPolyData *output, int *ext32, int *wholeExt32)
    {
        vtkIdType ext[6]; vtkIdType wholeExt[6];
        for (int cc = 0; cc < 6; cc++)
        {
            ext[cc] = ext32[cc];
            wholeExt[cc] = wholeExt32[cc];
        }
        return this->StructuredExecute(input, output, ext, wholeExt);
    }
#endif
    virtual int UnstructuredGridExecute(vtkDataSet *input,
        vtkPolyData *output);
    virtual int DataSetExecute(vtkDataSet *input, vtkPolyData *output);

#if VTK_MAJOR_VERSION >= 9
    virtual int StructuredWithBlankingExecute(vtkStructuredGrid *input, vtkPolyData *output);
#endif

    virtual int UniformGridExecute(
        vtkDataSet *input, vtkPolyData *output,
        vtkIdType *ext, vtkIdType *wholeExt, bool extractface[6]);
#ifdef VTK_USE_64BIT_IDS
    virtual int UniformGridExecute(vtkDataSet *input,
        vtkPolyData *output, int *ext32, int *wholeExt32, bool extractface[6])
    {
        vtkIdType ext[6]; vtkIdType wholeExt[6];
        for (int cc = 0; cc < 6; cc++)
        {
            ext[cc] = ext32[cc];
            wholeExt[cc] = wholeExt32[cc];
        }
        return this->UniformGridExecute(input, output, ext, wholeExt, extractface);
    }
#endif
    //@}

protected:
    FITKSurfaceFilter();
    ~FITKSurfaceFilter() override;

    vtkTypeBool UseStrips;

    int RequestUpdateExtent(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

    int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;
    int FillInputPortInformation(int port, vtkInformation *info) override;


    // Helper methods.

    /**
     * Estimates the total number of points & cells on the surface to render
     * ext -- the extent of the structured data in question (in)
     * wholeExt -- the global extent of the structured data (in)
     * numPoints -- the estimated number of points (out)
     * numCells -- the estimated number of cells (out)
     */
    void EstimateStructuredDataArraySizes(
        vtkIdType *ext, vtkIdType *wholeExt,
        vtkIdType &numPoints, vtkIdType &numCells);

    void ExecuteFaceStrips(vtkDataSet *input, vtkPolyData *output,
        int maxFlag, vtkIdType *ext,
        int aAxis, int bAxis, int cAxis,
        vtkIdType *wholeExt);

    void ExecuteFaceQuads(vtkDataSet *input, vtkPolyData *output,
        int maxFlag, vtkIdType *ext, int aAxis, int bAxis, int cAxis,
        vtkIdType *wholeExt, bool checkVisibility);

    void ExecuteFaceQuads(vtkDataSet *input, vtkPolyData *output,
        int maxFlag, vtkIdType *ext,
        int aAxis, int bAxis, int cAxis,
        vtkIdType *wholeExt);

    void InitializeQuadHash(vtkIdType numPoints);
    void DeleteQuadHash();
    virtual void InsertQuadInHash(vtkIdType a, vtkIdType b, vtkIdType c, vtkIdType d,
        vtkIdType sourceId, int cellDim);
    virtual void InsertTriInHash(vtkIdType a, vtkIdType b, vtkIdType c,
        vtkIdType sourceId, int cellDim, vtkIdType faceId = -1);
    virtual void InsertPolygonInHash(vtkIdType* ids, int numpts,
        vtkIdType sourceId, int cellDim);
    void InitQuadHashTraversal();
    FITKFastGeomQuad *GetNextVisibleQuadFromHash();

    FITKFastGeomQuad **QuadHash;
    vtkIdType QuadHashLength;
    FITKFastGeomQuad *QuadHashTraversal;
    vtkIdType QuadHashTraversalIndex;

    vtkIdType *PointMap;
    vtkIdType GetOutputPointId(vtkIdType inPtId, vtkDataSet *input,
        vtkPoints *outPts, vtkPointData *outPD);

    class vtkEdgeInterpolationMap;

    vtkEdgeInterpolationMap *EdgeMap;
    vtkIdType GetInterpolatedPointId(vtkIdType edgePtA, vtkIdType edgePtB,
        vtkDataSet *input, vtkCell *cell,
        double pcoords[3], vtkPoints *outPts,
        vtkPointData *outPD);

    vtkIdType NumberOfNewCells;

    // Better memory allocation for faces (hash)
    void InitFastGeomQuadAllocation(vtkIdType numberOfCells);
    FITKFastGeomQuad* NewFastGeomQuad(int numPts);
    void DeleteAllFastGeomQuads();
    // -----
    vtkIdType FastGeomQuadArrayLength;
    vtkIdType NumberOfFastGeomQuadArrays;
    unsigned char** FastGeomQuadArrays;  // store this data as an array of bytes
    // These indexes allow us to find the next available face.
    vtkIdType NextArrayIndex;
    vtkIdType NextQuadIndex;

    int PieceInvariant;

    vtkTypeBool PassThroughCellIds;
    void            RecordOrigCellId(vtkIdType newIndex, vtkIdType origId, vtkIdType cellDim, vtkIdType oriCellIndex = -1);
    virtual void    RecordOrigCellId(vtkIdType newIndex, FITKFastGeomQuad* quad, vtkIdType oriCellIndex = -1);
    vtkIdTypeArray *OriginalCellIds;
    vtkIntArray *OriginalCellDims;
    char *OriginalCellIdsName;

    vtkTypeBool PassThroughPointIds;
    void RecordOrigPointId(vtkIdType newIndex, vtkIdType origId);
    vtkIdTypeArray *OriginalPointIds;
    char *OriginalPointIdsName;

    int NonlinearSubdivisionLevel;

private:
    FITKSurfaceFilter(const FITKSurfaceFilter&) = delete;
    void operator=(const FITKSurfaceFilter&) = delete;

    //key为表面节点号
    //value为原始数据节点号
    std::map< int, int > _pointMap;

    //key为表面单元号
    //value first为原始数据单元号
    //value second为原始数据单元面索引
    std::map< int, std::pair<int, int> > _originAndSurfaceCellMap;
};

#endif // FITKSURFACEFILTER_H
