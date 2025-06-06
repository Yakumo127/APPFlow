﻿#include "FITKPolyPlacementMapper.h"

#include "vtkActor2D.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkExecutive.h"
#include "vtkIdTypeArray.h"
#include "vtkInformation.h"
#include "vtkLabelHierarchy.h"
#include "vtkLabelHierarchyCompositeIterator.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPoints.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataMapper2D.h"
#include "vtkRenderWindow.h"
#include "vtkRenderer.h"
#include "vtkSelectVisiblePoints.h"
#include "vtkSmartPointer.h"
#include "vtkTimerLog.h"
#include "vtkTransformCoordinateSystems.h"

#include "FITKPolyRenderStrategy.h"

// For VTK 7-8
#include "vtkRenderer.h"

class LabelRect
{
public:
    // Rotation origin.
    double RotationOrigin[2];

    // Rotation amount (radians).
    double Rotation;

    // Rotated label bounds (xmin, xmax, ymin, ymax).
    double Bounds[4];

    // Corners of the rotated box, where 0 is the lower left.
    // Corner 0 is lower-left, 1 is lower-right, 2 is upper-right, 3 is upper-left.
    double Corner[4][2];

    // Two edges of the box extended away from corner[0].
    double Axis[2][2];

    // origin[a] = corner[0].dot(axis[a]);
    double Origin[2];

    LabelRect(double center[2], const double w, const double h, double rotation)
    {
        double X[2];
        double Y[2];
        X[0] = cos(rotation) * w / 2;
        X[1] = sin(rotation) * w / 2;
        Y[0] = -sin(rotation) * h / 2;
        Y[1] = cos(rotation) * h / 2;

        Corner[0][0] = center[0] - X[0] - Y[0];
        Corner[0][1] = center[1] - X[1] - Y[1];
        Corner[1][0] = center[0] + X[0] - Y[0];
        Corner[1][1] = center[1] + X[1] - Y[1];
        Corner[2][0] = center[0] + X[0] + Y[0];
        Corner[2][1] = center[1] + X[1] + Y[1];
        Corner[3][0] = center[0] - X[0] + Y[0];
        Corner[3][1] = center[1] - X[1] + Y[1];

        RotationOrigin[0] = center[0];
        RotationOrigin[1] = center[1];

        Rotation = rotation;

        ComputeAxes();
    }

    LabelRect(double x[4], double rotateOrigin[2], double rotation)
    {
        Rotation = rotation;
        RotationOrigin[0] = rotateOrigin[0];
        RotationOrigin[1] = rotateOrigin[1];

        Corner[0][0] = x[0];
        Corner[0][1] = x[2];
        Corner[1][0] = x[1];
        Corner[1][1] = x[2];
        Corner[2][0] = x[1];
        Corner[2][1] = x[3];
        Corner[3][0] = x[0];
        Corner[3][1] = x[3];

        double ca = cos(rotation);
        double sa = sin(rotation);
        for (int i = 0; i < 4; ++i)
        {
            Corner[i][0] -= RotationOrigin[0];
            Corner[i][1] -= RotationOrigin[1];
            double rotx = Corner[i][0] * ca - Corner[i][1] * sa;
            double roty = Corner[i][1] * ca + Corner[i][0] * sa;
            Corner[i][0] = rotx;
            Corner[i][1] = roty;
            Corner[i][0] += RotationOrigin[0];
            Corner[i][1] += RotationOrigin[1];
        }

        ComputeAxes();
    }

    // Returns true if the intersection of the boxes is non-empty.
    bool Overlaps(const LabelRect& other) const
    {
        // Take care of easy case first
        if (Rotation == 0.0 && other.Rotation == 0.0)
        {
            double d0 = Corner[0][0] - other.Corner[2][0];
            double d1 = other.Corner[0][0] - Corner[2][0];
            double d2 = Corner[0][1] - other.Corner[2][1];
            double d3 = other.Corner[0][1] - Corner[2][1];
            if (d0 < 0. && d1 < 0. && d2 < 0. && d3 < 0.)
            {
                return true;
            }
            return false;
        }
        else
        {
            return Overlaps1Way(other) && other.Overlaps1Way(*this);
        }
    }

private:
    // Returns true if other overlaps one dimension of this.
    bool Overlaps1Way(const LabelRect& other) const
    {
        for (int a = 0; a < 2; ++a)
        {
            // double t = other.corner[0].dot(axis[a]);
            double t = other.Corner[0][0] * Axis[a][0] + other.Corner[0][1] * Axis[a][1];

            // Find the extent of box 2 on axis a
            double tMin = t;
            double tMax = t;

            for (int c = 1; c < 4; ++c)
            {
                // t = other.corner[c].dot(axis[a]);
                t = other.Corner[c][0] * Axis[a][0] + other.Corner[c][1] * Axis[a][1];

                if (t < tMin)
                {
                    tMin = t;
                }
                else if (t > tMax)
                {
                    tMax = t;
                }
            }

            // We have to subtract off the origin

            // See if [tMin, tMax] intersects [0, 1]
            if ((tMin > 1 + Origin[a]) || (tMax < Origin[a]))
            {
                // There was no intersection along this dimension;
                // the boxes cannot possibly overlap.
                return false;
            }
        }

        // There was no dimension along which there is no intersection.
        // Therefore the boxes overlap.
        return true;
    }

    // Updates the axes after the corners move.  Assumes the
    // corners actually form a rectangle.
    void ComputeAxes()
    {
        Axis[0][0] = Corner[1][0] - Corner[0][0];
        Axis[0][1] = Corner[1][1] - Corner[0][1];
        Axis[1][0] = Corner[3][0] - Corner[0][0];
        Axis[1][1] = Corner[3][1] - Corner[0][1];

        // Make the length of each axis 1/edge length so we know any
        // dot product must be less than 1 to fall within the edge.

        for (int a = 0; a < 2; ++a)
        {
            double len = Axis[a][0] * Axis[a][0] + Axis[a][1] * Axis[a][1];
            Axis[a][0] /= len;
            Axis[a][1] /= len;
            Origin[a] = Corner[0][0] * Axis[a][0] + Corner[0][1] * Axis[a][1];
        }

        Bounds[0] = Corner[0][0];
        Bounds[1] = Corner[0][0];
        Bounds[2] = Corner[0][1];
        Bounds[3] = Corner[0][1];
        for (int i = 1; i < 4; ++i)
        {
            if (Corner[i][0] < Bounds[0])
            {
                Bounds[0] = Corner[i][0];
            }
            if (Corner[i][0] > Bounds[1])
            {
                Bounds[1] = Corner[i][0];
            }
            if (Corner[i][1] < Bounds[2])
            {
                Bounds[2] = Corner[i][1];
            }
            if (Corner[i][1] > Bounds[3])
            {
                Bounds[3] = Corner[i][1];
            }
        }
    }
};

class FITKPolyPlacementMapper::Internal
{
public:
    /// A rectangular tile on the screen. It contains a set of labels that overlap it.
    struct ScreenTile
    {
        std::vector<LabelRect> Labels;
        ScreenTile() = default;
        /// Is there space to place the given rectangle in this tile so that it doesn't overlap any
        /// labels in this tile?
        bool IsSpotOpen(const LabelRect& r)
        {
            for (std::vector<LabelRect>::iterator it = this->Labels.begin(); it != this->Labels.end();
                 ++it)
            {
                if (r.Overlaps(*it))
                {
                    return false;
                }
            }
            return true;
        }

        /// Prepare for the next frame.
        void Reset() { this->Labels.clear(); }
        void Insert(const LabelRect& rect) { this->Labels.push_back(rect); }
    };
    std::vector<std::vector<ScreenTile> > Tiles;
    float ScreenOrigin[2];
    float TileSize[2];
    int NumTiles[2];
    vtkSmartPointer<vtkIdTypeArray> NewLabelsPlaced;
    vtkSmartPointer<vtkIdTypeArray> LastLabelsPlaced;

    Internal(float viewport[4], float tilesize[2])
    {
        this->NewLabelsPlaced = vtkSmartPointer<vtkIdTypeArray>::New();
        this->LastLabelsPlaced = vtkSmartPointer<vtkIdTypeArray>::New();
        this->ScreenOrigin[0] = viewport[0];
        this->ScreenOrigin[1] = viewport[2];
        this->TileSize[0] = tilesize[0];
        this->TileSize[1] = tilesize[1];
        this->NumTiles[0] = static_cast<int>(ceil((viewport[1] - viewport[0]) / tilesize[0]));
        this->NumTiles[1] = static_cast<int>(ceil((viewport[3] - viewport[2]) / tilesize[1]));
        this->Tiles.resize(this->NumTiles[0]);
        for (int i = 0; i < this->NumTiles[0]; ++i)
            this->Tiles[i].resize(this->NumTiles[1]);
    }

    bool PlaceLabel(const LabelRect& r)
    {
        // Determine intersected tiles
        float rx0 = r.Bounds[0] / TileSize[0];
        float rx1 = r.Bounds[1] / TileSize[0];
        float ry0 = r.Bounds[2] / TileSize[1];
        float ry1 = r.Bounds[3] / TileSize[1];
        int tx0 = static_cast<int>(floor(rx0));
        int tx1 = static_cast<int>(ceil(rx1));
        int ty0 = static_cast<int>(floor(ry0));
        int ty1 = static_cast<int>(ceil(ry1));
        if (tx0 > NumTiles[0] || tx1 < 0 || ty0 > NumTiles[1] || ty1 < 0)
            return false; // Don't intersect screen.
        if (tx0 < 0)
        {
            tx0 = 0;
            rx0 = 0.;
        }
        if (ty0 < 0)
        {
            ty0 = 0;
            ry0 = 0.;
        }
        if (tx1 >= this->NumTiles[0])
        {
            tx1 = this->NumTiles[0] - 1;
            rx1 = tx1;
        }
        if (ty1 >= this->NumTiles[1])
        {
            ty1 = this->NumTiles[1] - 1;
            ry1 = ty1;
        }
        // Check all applicable tiles for overlap.
        for (int tx = tx0; tx <= tx1; ++tx)
        {
            for (int ty = ty0; ty <= ty1; ++ty)
            {
                std::vector<ScreenTile>* trow = &this->Tiles[tx];
                // Do this check here for speed, even though we repeat w/ small mod below.
                if (!(*trow)[ty].IsSpotOpen(r))
                    return false;
            }
        }
        // OK, we made it this far... we can place the label.
        // Add it to each tile it overlaps.
        for (int tx = tx0; tx <= tx1; ++tx)
        {
            for (int ty = ty0; ty <= ty1; ++ty)
            {
                this->Tiles[tx][ty].Insert(r);
            }
        }
        return true;
    }

    void Reset(float viewport[4], float tileSize[2])
    {
        // Clear out any tiles we get to reuse
        for (int tx = 0; tx < this->NumTiles[0]; ++tx)
            for (int ty = 0; ty < this->NumTiles[1]; ++ty)
                this->Tiles[tx][ty].Reset();

        // Set new parameter values in case the viewport changed
        this->ScreenOrigin[0] = viewport[0];
        this->ScreenOrigin[1] = viewport[2];
        this->TileSize[0] = tileSize[0];
        this->TileSize[1] = tileSize[1];
        this->NumTiles[0] = static_cast<int>(ceil((viewport[1] - viewport[0]) / tileSize[0]));
        this->NumTiles[1] = static_cast<int>(ceil((viewport[3] - viewport[2]) / tileSize[1]));

        // Allocate new tiles (where required...)
        this->Tiles.resize(this->NumTiles[0]);
        for (int i = 0; i < this->NumTiles[0]; ++i)
            this->Tiles[i].resize(this->NumTiles[1]);

        // Save labels from the last frame for use later...
        vtkSmartPointer<vtkIdTypeArray> tmp = this->LastLabelsPlaced;
        this->LastLabelsPlaced = this->NewLabelsPlaced;
        this->NewLabelsPlaced = tmp;
        this->NewLabelsPlaced->Reset();
    }
};

vtkStandardNewMacro(FITKPolyPlacementMapper);
vtkCxxSetObjectMacro(FITKPolyPlacementMapper, AnchorTransform, vtkCoordinate);
vtkCxxSetObjectMacro(FITKPolyPlacementMapper, RenderStrategy, FITKPolyRenderStrategy);

//void FITKPolyPlacementMapper::SetRenderStrategy(FITKPolyRenderStrategy* s)
//{
//    this->RenderStrategy = s;
//
//    if (this->RenderStrategy)
//    {
//        this->PixelSize = this->RenderStrategy->GetPixelSize();
//    }
//}

//----------------------------------------------------------------------------
FITKPolyPlacementMapper::FITKPolyPlacementMapper()
{
    this->AnchorTransform = vtkCoordinate::New();
    this->AnchorTransform->SetCoordinateSystemToWorld();
    this->MaximumLabelFraction = 0.05; // Take up no more than 5% of screen real estate with labels.
    this->Buckets = nullptr;
    this->PositionsAsNormals = false;
    this->IteratorType = vtkLabelHierarchy::QUEUE;
    this->VisiblePoints = vtkSelectVisiblePoints::New();
    this->VisiblePoints->SetTolerance(0.002);
    this->PlaceAllLabels = false;
    this->OutputTraversedBounds = false;
    this->GeneratePerturbedLabelSpokes = false;

    this->LastRendererSize[0] = 0;
    this->LastRendererSize[1] = 0;
    this->LastCameraPosition[0] = 0.0;
    this->LastCameraPosition[1] = 0.0;
    this->LastCameraPosition[2] = 0.0;
    this->LastCameraFocalPoint[0] = 0.0;
    this->LastCameraFocalPoint[1] = 0.0;
    this->LastCameraFocalPoint[2] = 0.0;
    this->LastCameraViewUp[0] = 0.0;
    this->LastCameraViewUp[1] = 0.0;
    this->LastCameraViewUp[2] = 0.0;
    this->LastCameraParallelScale = 0.0;

    this->UseDepthBuffer = false;

    this->RenderStrategy = nullptr;
    vtkSmartPointer<FITKPolyRenderStrategy> s =
            vtkSmartPointer<FITKPolyRenderStrategy>::New();
    this->SetRenderStrategy(s);
}

FITKPolyPlacementMapper::~FITKPolyPlacementMapper()
{
    this->AnchorTransform->Delete();
    delete this->Buckets;
    this->VisiblePoints->Delete();
    if (this->RenderStrategy)
    {
        this->RenderStrategy->Delete();
    }
}

int FITKPolyPlacementMapper::FillInputPortInformation(int vtkNotUsed(port), vtkInformation* info)
{
    info->Set(vtkAlgorithm::INPUT_REQUIRED_DATA_TYPE(), "vtkLabelHierarchy");
    info->Set(vtkAlgorithm::INPUT_IS_REPEATABLE(), 1);
    info->Set(vtkAlgorithm::INPUT_IS_OPTIONAL(), 1);
    return 1;
}

void FITKPolyPlacementMapper::RenderOverlay(vtkViewport* viewport, vtkActor2D* vtkNotUsed(actor))
{
    vtkSmartPointer<vtkTimerLog> log = vtkSmartPointer<vtkTimerLog>::New();
    log->StartTimer();

    vtkRenderer* ren = vtkRenderer::SafeDownCast(viewport);
    if (!ren)
    {
        vtkErrorMacro("No renderer -- can't determine screen space size.");
        return;
    }

    if (!ren->GetRenderWindow())
    {
        vtkErrorMacro("No render window -- can't get window size to query z buffer.");
        return;
    }

    // This will trigger if you do something like ResetCamera before the Renderer or
    // RenderWindow have allocated their appropriate system resources (like creating
    // an OpenGL context). Resource allocation must occur before we can use the Z
    // buffer.
    if (ren->GetRenderWindow()->GetNeverRendered())
    {
        vtkDebugMacro("RenderWindow not initialized -- aborting update.");
        return;
    }

    vtkCamera* cam = ren->GetActiveCamera();
    if (!cam)
    {
        return;
    }

    // If the renderer size is zero, silently place no labels.
    const int* renSize = ren->GetSize();
    if (renSize[0] == 0 || renSize[1] == 0)
    {
        return;
    }

    // Update the pipeline if necessary
    this->Update();

    int tvpsz[4]; // tiled viewport size (and origin)
    // kd-tree bounds on screenspace (as floats... eventually we
    // should use a median kd-tree -- not naive version)
    float kdbounds[4];
    ren->GetTiledSizeAndOrigin(tvpsz, tvpsz + 1, tvpsz + 2, tvpsz + 3);
    kdbounds[0] = tvpsz[2];
    kdbounds[1] = tvpsz[0] + tvpsz[2];
    kdbounds[2] = tvpsz[3];
    kdbounds[3] = tvpsz[1] + tvpsz[3];
    float tileSize[2] = { 128., 128. }; // fixed for now
    if (!this->Buckets || this->Buckets->NumTiles[0] * this->Buckets->TileSize[0] < tvpsz[2] ||
            this->Buckets->NumTiles[1] * this->Buckets->TileSize[1] < tvpsz[3])
    {
        this->Buckets = new Internal(kdbounds, tileSize);
    }
    else
    {
        this->Buckets->Reset(kdbounds, tileSize);
    }

    float* zPtr = nullptr;
    int placed = 0;
    int occluded = 0;

    double ll[2];
    double ur[2];
    double x[3];
    double sz[4];
    int origin[2];
    int dispx[2];

    // Compute frustum for excluding labels that are outside the visible region.
    double frustumPlanes[24];
#if VTK_MAJOR_VERSION < 9
    GetAnchorFrustumPlanes(frustumPlanes, ren, this->AnchorTransform);
#else
    vtkLabelHierarchy::GetAnchorFrustumPlanes(frustumPlanes, ren, this->AnchorTransform);
#endif

    unsigned long allowableLabelArea = static_cast<unsigned long>(
                ((kdbounds[1] - kdbounds[0]) * (kdbounds[3] - kdbounds[2])) * this->MaximumLabelFraction);
    (void)allowableLabelArea;
    unsigned long renderedLabelArea = 0;
    unsigned long iteratedLabelArea = 0;
    double camVec[3];
    if (this->PositionsAsNormals)
    {
        cam->GetViewPlaneNormal(camVec);
    }

    // Make a composite iterator that will iterate over all the input
    // label hierarchies in a round-robin sequence.
    vtkSmartPointer<vtkLabelHierarchyCompositeIterator> inIter =
            vtkSmartPointer<vtkLabelHierarchyCompositeIterator>::New();

    vtkSmartPointer<vtkPolyData> boundsPoly = vtkSmartPointer<vtkPolyData>::New();
    if (this->OutputTraversedBounds)
    {
        vtkSmartPointer<vtkPoints> pts = vtkSmartPointer<vtkPoints>::New();
        boundsPoly->SetPoints(pts);
        vtkSmartPointer<vtkCellArray> lines = vtkSmartPointer<vtkCellArray>::New();
        boundsPoly->SetLines(lines);
        inIter->SetTraversedBounds(boundsPoly);
    }

    int numInputs = this->GetNumberOfInputConnections(0);
    for (int i = 0; i < numInputs; ++i)
    {
        vtkLabelHierarchy* inData = vtkLabelHierarchy::SafeDownCast(this->GetInputDataObject(0, i));
        vtkLabelHierarchyIterator* it = inData->NewIterator(
                    this->IteratorType, ren, cam, frustumPlanes, this->PositionsAsNormals, tileSize);
        inIter->AddIterator(it);
        it->Delete();
    }

    vtkSmartPointer<vtkTimerLog> timer = vtkSmartPointer<vtkTimerLog>::New();
    timer->StartTimer();

    inIter->Begin(this->Buckets->LastLabelsPlaced);
    this->Buckets->NewLabelsPlaced->Initialize();

    if (this->UseDepthBuffer)
    {
        this->VisiblePoints->SetRenderer(ren);
        zPtr = this->VisiblePoints->Initialize(true);
    }

    // Start rendering labels
    int pixelSize = this->RenderStrategy->GetPixelSize();
    this->RenderStrategy->SetPixelSize(pixelSize);
    this->RenderStrategy->SetRenderer(ren);

    timer->StopTimer();
    vtkDebugMacro("Iterator initialization time: " << timer->GetElapsedTime());
    timer->StartTimer();

    for (; !inIter->IsAtEnd(); inIter->Next())
    {
        inIter->GetPoint(x);

        if (this->AnchorTransform->GetCoordinateSystem() == VTK_WORLD)
        {
            // Cull points behind the camera. Cannot rely on hither-yon planes because the camera
            // position gets changed during vtkInteractorStyle::Dolly() and RequestData() called from
            // within ResetCameraClippingRange() before the frustum planes are updated.
            // Cull points outside hither-yon planes (other planes get tested below)
            double* eye = cam->GetPosition();
            double* dir = cam->GetViewPlaneNormal();
            if ((x[0] - eye[0]) * dir[0] + (x[1] - eye[1]) * dir[1] + (x[2] - eye[2]) * dir[2] > 0)
            {
                continue;
            }

            // Ignore labels pointing the wrong direction (HACK)
            if (this->PositionsAsNormals)
            {
                if (camVec[0] * x[0] + camVec[1] * x[1] + camVec[2] * x[2] < 0.)
                {
                    continue;
                }
            }

            // Test for occlusion using the z-buffer
            if (this->UseDepthBuffer && !this->VisiblePoints->IsPointOccluded(x, zPtr))
            {
                occluded++;
                continue;
            }
        }

        this->AnchorTransform->SetValue(x);
        int* originPtr = this->AnchorTransform->GetComputedDisplayValue(ren);
        origin[0] = originPtr[0];
        origin[1] = originPtr[1];

        // Added by ChengHaotian
        // Set the bounds by the given pixel size.
        //@{
        double bds[4];
        bds[0] = -pixelSize / 2;
        bds[1] = pixelSize / 2;
        bds[2] = -pixelSize / 2;
        bds[3] = pixelSize / 2;
        //@}

        // Offset display position by lower left corner of bounding box
        dispx[0] = static_cast<int>(origin[0] + bds[0]);
        dispx[1] = static_cast<int>(origin[1] + bds[2]);

        sz[0] = bds[1] - bds[0];
        sz[1] = bds[3] - bds[2];

        if (sz[0] < 0)
            sz[0] = -sz[0];
        if (sz[1] < 0)
            sz[1] = -sz[1];

        // If it has no size, skip it
        if (sz[0] == 0.0 || sz[1] == 0.0)
        {
            continue;
        }

        ll[0] = dispx[0];
        ll[1] = dispx[1];
        ur[0] = dispx[0] + sz[0];
        ur[1] = dispx[1] + sz[1];

        if (ll[1] > kdbounds[3] || ur[1] < kdbounds[2] || ll[0] > kdbounds[1] || ur[0] < kdbounds[0])
        {
            continue; // cull label not in frame
        }

        iteratedLabelArea += static_cast<unsigned long>(sz[0] * sz[1]);

        // Translate to origin to simplify bucketing
        double xTrans[4];
        xTrans[0] = ll[0] - kdbounds[0];
        xTrans[1] = ur[0] - kdbounds[0];
        xTrans[2] = ll[1] - kdbounds[2];
        xTrans[3] = ur[1] - kdbounds[2];

        double originTrans[2];
        originTrans[0] = origin[0] - kdbounds[0];
        originTrans[1] = origin[1] - kdbounds[2];

        double orientRad = vtkMath::RadiansFromDegrees(0.);
        LabelRect r(xTrans, originTrans, orientRad);

        if (this->PlaceAllLabels || this->Buckets->PlaceLabel(r))
        {
            renderedLabelArea += static_cast<unsigned long>(sz[0] * sz[1]);
            this->RenderStrategy->RenderPoly(origin);
            placed++;
        }
    }

    // Done rendering labels
    this->RenderStrategy->SetRenderer(nullptr);

    if (this->OutputTraversedBounds)
    {
        // For some reason I cannot use vtkPolyDataMapper, I need to use
        // vtkPolyDataMapper2D. This causes lines behind the camera to be sometimes
        // transformed on-screen. Since this is for debugging, I'm going to punt
        // on this one.
        vtkSmartPointer<vtkTransformCoordinateSystems> trans =
                vtkSmartPointer<vtkTransformCoordinateSystems>::New();
        vtkSmartPointer<vtkPolyDataMapper2D> boundsMapper = vtkSmartPointer<vtkPolyDataMapper2D>::New();
        vtkSmartPointer<vtkActor2D> boundsActor = vtkSmartPointer<vtkActor2D>::New();
        trans->SetInputCoordinateSystemToWorld();
        trans->SetOutputCoordinateSystemToDisplay();
        trans->SetInputData(boundsPoly);
        trans->SetViewport(ren);
        boundsMapper->SetInputConnection(trans->GetOutputPort());
        boundsMapper->RenderOverlay(ren, boundsActor);
    }

    vtkDebugMacro("------");
    vtkDebugMacro("Placed: " << placed);
    vtkDebugMacro("Labels Occluded: " << occluded);

    delete[] zPtr;

    timer->StopTimer();
    vtkDebugMacro("Iteration time: " << timer->GetElapsedTime());
    log->StopTimer();
    // cerr << log->GetElapsedTime() << endl;
}

//----------------------------------------------------------------------------
void FITKPolyPlacementMapper::ReleaseGraphicsResources(vtkWindow* win)
{
    this->RenderStrategy->ReleaseGraphicsResources(win);
}

//----------------------------------------------------------------------------
void FITKPolyPlacementMapper::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);
    os << indent << "AnchorTransform: " << this->AnchorTransform << "\n";
    os << indent << "MaximumLabelFraction: " << this->MaximumLabelFraction << "\n";
    os << indent << "PositionsAsNormals: " << (this->PositionsAsNormals ? "ON" : "OFF") << "\n";
    os << indent << "IteratorType: " << this->IteratorType << "\n";
    os << indent << "RenderStrategy: " << this->RenderStrategy << "\n";
    os << indent << "PlaceAllLabels: " << (this->PlaceAllLabels ? "ON" : "OFF") << "\n";
    os << indent << "OutputTraversedBounds: " << (this->OutputTraversedBounds ? "ON" : "OFF") << "\n";
    os << indent
       << "GeneratePerturbedLabelSpokes: " << (this->GeneratePerturbedLabelSpokes ? "ON" : "OFF")
       << "\n";
    os << indent << "UseDepthBuffer: " << (this->UseDepthBuffer ? "ON" : "OFF") << "\n";
}

#if VTK_MAJOR_VERSION < 9
void FITKPolyPlacementMapper::GetAnchorFrustumPlanes(
    double frustumPlanes[24], vtkRenderer* ren, vtkCoordinate* anchorTransform)
{
    // We set infinitely large frustum (disable clipping) for all coordinate systems other than world
    // and normalized coordinate systems.
    // To improve performance, accurate view frustum could be computed for all other coordinate
    // systems, too (such as DISPLAY, VIEWPORT, VIEW, POSE - see vtkCoordinate).
    int coordinateSystem = anchorTransform->GetCoordinateSystem();

    if (coordinateSystem == VTK_WORLD)
    {
        vtkCamera* cam = ren->GetActiveCamera();
        if (cam)
        {
            cam->GetFrustumPlanes(ren->GetTiledAspectRatio(), frustumPlanes);
            return;
        }
    }

    double minPosition = VTK_DOUBLE_MAX;
    double maxPosition = VTK_DOUBLE_MAX;

    if (coordinateSystem == VTK_NORMALIZED_DISPLAY || coordinateSystem == VTK_NORMALIZED_VIEWPORT)
    {
        minPosition = 0.0;
        maxPosition = 1.0;
    }

    frustumPlanes[0] = 1.0;
    frustumPlanes[1] = 0.0;
    frustumPlanes[2] = 0.0;
    frustumPlanes[3] = minPosition;

    frustumPlanes[4] = -1.0;
    frustumPlanes[5] = 0.0;
    frustumPlanes[6] = 0.0;
    frustumPlanes[7] = maxPosition;

    frustumPlanes[8] = 0.0;
    frustumPlanes[9] = 1.0;
    frustumPlanes[10] = 0.0;
    frustumPlanes[11] = minPosition;

    frustumPlanes[12] = 0.0;
    frustumPlanes[13] = -1.0;
    frustumPlanes[14] = 0.0;
    frustumPlanes[15] = maxPosition;

    frustumPlanes[16] = 0.0;
    frustumPlanes[17] = 0.0;
    frustumPlanes[18] = -1.0;
    frustumPlanes[19] = VTK_DOUBLE_MAX;

    frustumPlanes[20] = 0.0;
    frustumPlanes[21] = 0.0;
    frustumPlanes[22] = 1.0;
    frustumPlanes[23] = VTK_DOUBLE_MAX;
}
#endif