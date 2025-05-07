#include "FITKTransformRepresentation.h"

#include "vtkActor.h"
#include "vtkAssemblyPath.h"
#include "vtkBox.h"
#include "vtkCallbackCommand.h"
#include "vtkCamera.h"
#include "vtkCellArray.h"
#include "vtkCellPicker.h"
#include "vtkDoubleArray.h"
#include "vtkEventData.h"
#include "vtkInteractorObserver.h"
#include "vtkMath.h"
#include "vtkObjectFactory.h"
#include "vtkPickingManager.h"
#include "vtkPlane.h"
#include "vtkPlanes.h"
#include "vtkPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkQuaternion.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkSphereSource.h"
#include "vtkTransform.h"
#include "vtkVectorOperators.h"
#include "vtkWindow.h"
#include "vtkDistanceToCamera.h"
#include "vtkGlyph3D.h"
#include "vtkArrowSource.h"
#include "vtkTransformFilter.h"
#include "vtkPointData.h"

#include <assert.h>

vtkStandardNewMacro(FITKTransformRepresentation);

//----------------------------------------------------------------------------
FITKTransformRepresentation::FITKTransformRepresentation()
{
    // The initial state
    this->InteractionState = FITKTransformRepresentation::Outside;

    // Handle size is in pixels for this widget
    this->HandleSize = 80.;

    // Set up the initial properties
    this->CreateDefaultProperties();

    // Create handle position points.
    this->Points = vtkPoints::New();
    this->Points->SetNumberOfPoints(1); // o
    this->PolyData = new vtkPolyData*[3];
    this->Normals = new vtkDoubleArray*[3];

    // Create handle and center source
    this->HandleSource = vtkArrowSource::New();
    this->HandleSource->SetTipResolution(15);
    this->HandleSource->SetShaftResolution(15);
    this->HandleSource->SetTipLength(0.35);
    this->HandleSource->SetTipRadius(0.1);
    this->CenterSource = vtkSphereSource::New();
    this->CenterSource->SetThetaResolution(30);
    this->CenterSource->SetPhiResolution(30);

    // Create the transformer.
    vtkSmartPointer<vtkTransform> trans = vtkSmartPointer<vtkTransform>::New();
    trans->Translate(0.25, 0., 0.);
    trans->Update();

    this->HandleTransFilter = vtkTransformFilter::New();
    this->HandleTransFilter->SetInputConnection(this->HandleSource->GetOutputPort());
    this->HandleTransFilter->SetTransform(trans);

    // Create glyph and poly data.
    this->HandleDistToCamera = new vtkDistanceToCamera*[3];
    this->HandleGlyph3D = new vtkGlyph3D*[3];

    for (int i = 0; i < 3; i++)
    {
        double nor[3]{ 0., 0., 0. };
        nor[i] = 1;

        this->PolyData[i] = vtkPolyData::New();
        this->PolyData[i]->SetPoints(this->Points);
        this->Normals[i] = vtkDoubleArray::New();
        this->Normals[i]->SetNumberOfComponents(3);
        this->Normals[i]->InsertNextTuple3(nor[0], nor[1], nor[2]);
        this->PolyData[i]->GetPointData()->SetNormals(this->Normals[i]);

        this->HandleGlyph3D[i] = vtkGlyph3D::New();
        this->HandleDistToCamera[i] = vtkDistanceToCamera::New();
        this->HandleDistToCamera[i]->SetScreenSize(this->HandleSize);

        this->HandleGlyph3D[i]->SetInputConnection(this->HandleDistToCamera[i]->GetOutputPort());

        // Add the point array name need to be used.      
#if VTK_MAJOR_VERSION < 8
        this->HandleGlyph3D[i]->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, "DistanceToCamera");
#else
        this->HandleGlyph3D[i]->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, this->HandleDistToCamera[i]->GetDistanceArrayName());
#endif

        this->HandleGlyph3D[i]->SetScaling(true);
        this->HandleGlyph3D[i]->SetScaleModeToScaleByScalar();
        this->HandleGlyph3D[i]->SetVectorModeToUseNormal();

        // Set the soure data and input data.
        this->HandleDistToCamera[i]->SetInputData(this->PolyData[i]);
        this->HandleGlyph3D[i]->SetSourceConnection(this->HandleTransFilter->GetOutputPort());
    }

    // Create the handles
    this->Handle = new vtkActor*[4];
    this->HandleMapper = new vtkPolyDataMapper*[4];

    // Create arrow handle actors
    for (int i = 0; i < 3; i++)
    {
        this->HandleMapper[i] = vtkPolyDataMapper::New();
        this->HandleMapper[i]->SetScalarVisibility(false);
        this->HandleMapper[i]->SetInputConnection(this->HandleGlyph3D[i]->GetOutputPort());
        this->Handle[i] = vtkActor::New();
        this->Handle[i]->SetMapper(this->HandleMapper[i]);
        this->Handle[i]->SetProperty(this->HandleProperty);
    }

    // Create center sphere actors
    this->HandleMapper[3] = vtkPolyDataMapper::New();
    this->HandleMapper[3]->SetScalarVisibility(false);
    this->HandleMapper[3]->SetInputConnection(this->CenterSource->GetOutputPort());
    this->Handle[3] = vtkActor::New();
    this->Handle[3]->SetMapper(this->HandleMapper[3]);
    this->Handle[3]->SetProperty(this->HandleProperty);

    // Define the point coordinates
    double bounds[6];
    bounds[0] = -0.5;
    bounds[1] = 0.5;
    bounds[2] = -0.5;
    bounds[3] = 0.5;
    bounds[4] = -0.5;
    bounds[5] = 0.5;

    this->BoundingBox = vtkBox::New();
    this->PlaceWidget(bounds);

    // Manage the picking stuff
    this->HandlePicker = vtkCellPicker::New();
    this->HandlePicker->SetTolerance(0.001);
    for (int i = 0; i < 4; i++)
    {
        this->HandlePicker->AddPickList(this->Handle[i]);
    }
    this->HandlePicker->PickFromListOn();

    this->CurrentHandle = nullptr;

    // Internal data members for performance
    this->Transform = vtkTransform::New();

    this->SetPosition(this->Position);
    this->SetColor(this->Color);
}

//----------------------------------------------------------------------------
FITKTransformRepresentation::~FITKTransformRepresentation()
{
    this->Points->Delete();

    for (int i = 0; i < 4; i++)
    {
        this->HandleMapper[i]->Delete();
        this->Handle[i]->Delete();
    }

    delete[] this->Handle;
    delete[] this->HandleMapper;

    this->HandlePicker->Delete();

    this->Transform->Delete();
    this->BoundingBox->Delete();

    this->HandleProperty->Delete();
    this->SelectedHandleProperty->Delete();
}

void FITKTransformRepresentation::SetColor(double* color3)
{
    this->Color[0] = color3[0];
    this->Color[1] = color3[1];
    this->Color[2] = color3[2];

    this->HandleProperty->SetColor(this->Color);
}

double* FITKTransformRepresentation::GetPosition()
{
    return this->Points->GetPoint(0);
}

void FITKTransformRepresentation::SetPosition(double* pos3)
{
    this->Position[0] = pos3[0];
    this->Position[1] = pos3[1];
    this->Position[2] = pos3[2];

    double size = this->vtkWidgetRepresentation::SizeHandlesInPixels(1., pos3);
    this->SetPosition(pos3, size);
}

void FITKTransformRepresentation::SetPosition(double* pos3, double size)
{
    this->CenterSource->SetCenter(pos3);
    this->CenterSource->SetRadius(size);

    this->Points->SetPoint(0, pos3);
    this->Points->Modified();
}

//----------------------------------------------------------------------
void FITKTransformRepresentation::StartWidgetInteraction(double e[2])
{
    // Store the start position
    this->StartEventPosition[0] = e[0];
    this->StartEventPosition[1] = e[1];
    this->StartEventPosition[2] = 0.0;

    // Store the start position
    this->LastEventPosition[0] = e[0];
    this->LastEventPosition[1] = e[1];
    this->LastEventPosition[2] = 0.0;

    this->ComputeInteractionState(static_cast<int>(e[0]), static_cast<int>(e[1]), 0);
}

//----------------------------------------------------------------------
void FITKTransformRepresentation::WidgetInteraction(double e[2])
{
    // Convert events to appropriate coordinate systems
    vtkCamera* camera = this->Renderer->GetActiveCamera();
    if (!camera)
    {
        return;
    }
    double focalPoint[4], pickPoint[4], prevPickPoint[4];
    double z, vpn[3];
    camera->GetViewPlaneNormal(vpn);

    // Compute the two points defining the motion vector
    double pos[3];
    this->HandlePicker->GetPickPosition(pos);

    vtkInteractorObserver::ComputeWorldToDisplay(this->Renderer, pos[0], pos[1], pos[2], focalPoint);
    z = focalPoint[2];
    vtkInteractorObserver::ComputeDisplayToWorld(this->Renderer, this->LastEventPosition[0], this->LastEventPosition[1], z, prevPickPoint);
    vtkInteractorObserver::ComputeDisplayToWorld(this->Renderer, e[0], e[1], z, pickPoint);

    // Process the motion
    if (this->InteractionState == FITKTransformRepresentation::TranslatingX)
    {
        pickPoint[1] = prevPickPoint[1];
        pickPoint[2] = prevPickPoint[2];
        this->Translate(prevPickPoint, pickPoint);
    }
    else if (this->InteractionState == FITKTransformRepresentation::TranslatingY)
    {
        pickPoint[0] = prevPickPoint[0];
        pickPoint[2] = prevPickPoint[2];
        this->Translate(prevPickPoint, pickPoint);
    }
    else if (this->InteractionState == FITKTransformRepresentation::TranslatingZ)
    {
        pickPoint[0] = prevPickPoint[0];
        pickPoint[1] = prevPickPoint[1];
        this->Translate(prevPickPoint, pickPoint);
    }
    else if (this->InteractionState == FITKTransformRepresentation::TranslatingO)
    {
        this->Translate(prevPickPoint, pickPoint);
    }

    // Store the start position
    this->LastEventPosition[0] = e[0];
    this->LastEventPosition[1] = e[1];
    this->LastEventPosition[2] = 0.0;
}

void FITKTransformRepresentation::ComplexInteraction(
    vtkRenderWindowInteractor*, vtkAbstractWidget*, unsigned long, void* calldata)
{
    vtkEventData* edata = static_cast<vtkEventData*>(calldata);
    vtkEventDataDevice3D* edd = edata->GetAsEventDataDevice3D();
    if (edd)
    {
        // all others
        double eventPos[3];
        edd->GetWorldPosition(eventPos);
        double eventDir[4];
        edd->GetWorldOrientation(eventDir);

        double* prevPickPoint = this->LastEventPosition;
        double* pickPoint = eventPos;

        if (this->InteractionState == FITKTransformRepresentation::TranslatingX)
        {
            pickPoint[1] = prevPickPoint[1];
            pickPoint[2] = prevPickPoint[2];
            this->Translate(prevPickPoint, pickPoint);
        }
        else if (this->InteractionState == FITKTransformRepresentation::TranslatingY)
        {
            pickPoint[0] = prevPickPoint[0];
            pickPoint[2] = prevPickPoint[2];
            this->Translate(prevPickPoint, pickPoint);
        }
        else if (this->InteractionState == FITKTransformRepresentation::TranslatingZ)
        {
            pickPoint[0] = prevPickPoint[0];
            pickPoint[1] = prevPickPoint[1];
            this->Translate(prevPickPoint, pickPoint);
        }
        else if (this->InteractionState == FITKTransformRepresentation::TranslatingO)
        {
            this->Translate(prevPickPoint, pickPoint);
        }

        // Book keeping
        std::copy(eventPos, eventPos + 3, this->LastEventPosition);
        std::copy(eventDir, eventDir + 4, this->LastEventOrientation);
        this->Modified();
    }
}

void FITKTransformRepresentation::EndComplexInteraction(
    vtkRenderWindowInteractor*, vtkAbstractWidget*, unsigned long, void*)
{
}

//----------------------------------------------------------------------------
// Loop through all points and translate them
void FITKTransformRepresentation::Translate(const double* p1, const double* p2)
{
    double v[3] = { p2[0] - p1[0], p2[1] - p1[1], p2[2] - p1[2] };
    double* ct = this->Points->GetPoint(0);
    // Get the new center.
    for (int i = 0; i < 3; i++)
    {
        ct[i] += v[i];
    }

    double size = this->vtkWidgetRepresentation::SizeHandlesInPixels(1, ct);
    this->SetPosition(ct, size);
}

namespace
{
    bool snapToAxis(vtkVector3d& in, vtkVector3d& out, double snapAngle)
    {
        int largest = 0;
        if (fabs(in[1]) > fabs(in[0]))
        {
            largest = 1;
        }
        if (fabs(in[2]) > fabs(in[largest]))
        {
            largest = 2;
        }
        vtkVector3d axis(0, 0, 0);
        axis[largest] = 1.0;
        // 3 degrees of sticky
        if (fabs(in.Dot(axis)) > cos(vtkMath::Pi() * snapAngle / 180.0))
        {
            if (in.Dot(axis) < 0)
            {
                axis[largest] = -1;
            }
            out = axis;
            return true;
        }
        return false;
    }
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::CreateDefaultProperties()
{
    // Handle properties
    this->HandleProperty = vtkProperty::New();
    this->HandleProperty->SetColor(1, 1, 1);

    this->SelectedHandleProperty = vtkProperty::New();
    this->SelectedHandleProperty->SetColor(1, 0, 0);
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::PlaceWidget(double bds[6])
{
    int i;
    double bounds[6], center[3];

    this->AdjustBounds(bds, bounds, center);

    for (i = 0; i < 6; i++)
    {
        this->InitialBounds[i] = bounds[i];
    }

    this->InitialLength = sqrt((bounds[1] - bounds[0]) * (bounds[1] - bounds[0]) +
        (bounds[3] - bounds[2]) * (bounds[3] - bounds[2]) +
        (bounds[5] - bounds[4]) * (bounds[5] - bounds[4]));

    this->ValidPick = 1; // since we have set up widget
    this->SizeHandles();
}

//----------------------------------------------------------------------------
int FITKTransformRepresentation::ComputeInteractionState(int X, int Y, int modify)
{
    // Okay, we can process this. Try to pick handles first;
    // if no handles picked, then pick the bounding box.
    if (!this->Renderer || !this->Renderer->IsInViewport(X, Y))
    {
        this->InteractionState = FITKTransformRepresentation::Outside;
        return this->InteractionState;
    }

    // Try and pick a handle first
    this->CurrentHandle = nullptr;

    vtkAssemblyPath* path = this->GetAssemblyPath(X, Y, 0., this->HandlePicker);

    if (path != nullptr)
    {
        this->ValidPick = 1;
        this->CurrentHandle = reinterpret_cast<vtkActor*>(path->GetFirstNode()->GetViewProp());
        if (this->CurrentHandle == this->Handle[0])
        {
            this->InteractionState = FITKTransformRepresentation::TranslatingX;
        }
        else if (this->CurrentHandle == this->Handle[1])
        {
            this->InteractionState = FITKTransformRepresentation::TranslatingY;
        }
        else if (this->CurrentHandle == this->Handle[2])
        {
            this->InteractionState = FITKTransformRepresentation::TranslatingZ;
        }
        else if (this->CurrentHandle == this->Handle[3])
        {
            this->InteractionState = FITKTransformRepresentation::TranslatingO;
        }
    }
    else
    {
        this->InteractionState = FITKTransformRepresentation::Outside;
    }

    return this->InteractionState;
}

int FITKTransformRepresentation::ComputeComplexInteractionState(
    vtkRenderWindowInteractor*, vtkAbstractWidget*, unsigned long, void* calldata, int)
{
    this->InteractionState = FITKTransformRepresentation::Outside;

    vtkEventData* edata = static_cast<vtkEventData*>(calldata);
    vtkEventDataDevice3D* edd = edata->GetAsEventDataDevice3D();
    if (edd)
    {
        double pos[3];
        edd->GetWorldPosition(pos);

        // Try and pick a handle first
        this->CurrentHandle = nullptr;

        vtkAssemblyPath* path = this->GetAssemblyPath3DPoint(pos, this->HandlePicker);

        if (path != nullptr)
        {
            this->ValidPick = 1;
            this->CurrentHandle = reinterpret_cast<vtkActor*>(path->GetFirstNode()->GetViewProp());
            if (this->CurrentHandle == this->Handle[0])
            {
                this->InteractionState = FITKTransformRepresentation::TranslatingX;
            }
            else if (this->CurrentHandle == this->Handle[1])
            {
                this->InteractionState = FITKTransformRepresentation::TranslatingY;
            }
            else if (this->CurrentHandle == this->Handle[2])
            {
                this->InteractionState = FITKTransformRepresentation::TranslatingZ;
            }
            else if (this->CurrentHandle == this->Handle[3])
            {
                this->InteractionState = FITKTransformRepresentation::TranslatingO;
            }
        }
    }

    return this->InteractionState;
}

//----------------------------------------------------------------------
void FITKTransformRepresentation::SetInteractionState(int state)
{
    // Clamp to allowable values
    state = (state < FITKTransformRepresentation::Outside
        ? FITKTransformRepresentation::Outside
        : (state > FITKTransformRepresentation::TranslatingO ? FITKTransformRepresentation::TranslatingO : state));

    // Depending on state, highlight appropriate parts of representation
    int handle;
    this->InteractionState = state;
    switch (state)
    {
    case FITKTransformRepresentation::TranslatingX:
    case FITKTransformRepresentation::TranslatingY:
    case FITKTransformRepresentation::TranslatingZ:
    case FITKTransformRepresentation::TranslatingO:
        handle = this->HighlightHandle(this->CurrentHandle);
        break;
    default:
        this->HighlightHandle(nullptr);
    }
}

//----------------------------------------------------------------------
double* FITKTransformRepresentation::GetBounds()
{
    this->BuildRepresentation();

    this->BoundingBox->SetBounds(this->Handle[0]->GetBounds());

    for (int j = 0; j < 4; j++)
    {
        this->BoundingBox->AddBounds(this->Handle[j]->GetBounds());
    }
    
    return this->BoundingBox->GetBounds();
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::BuildRepresentation()
{
    // Rebuild only if necessary
    if (this->GetMTime() > this->BuildTime ||
        (this->Renderer && this->Renderer->GetVTKWindow() &&
        (this->Renderer->GetVTKWindow()->GetMTime() > this->BuildTime ||
            this->Renderer->GetActiveCamera()->GetMTime() > this->BuildTime)))
    {
        this->SizeHandles();
        this->BuildTime.Modified();
    }
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::ReleaseGraphicsResources(vtkWindow* w)
{
    // render the handles
    for (int j = 0; j < 4; j++)
    {
        this->Handle[j]->ReleaseGraphicsResources(w);
    }
}

//----------------------------------------------------------------------------
int FITKTransformRepresentation::RenderOpaqueGeometry(vtkViewport* v)
{
    int count = 0;
    this->BuildRepresentation();

    for (int j = 0; j < 4; j++)
    {
        if (this->Handle[j]->GetVisibility())
        {
            this->Handle[j]->SetPropertyKeys(this->GetPropertyKeys());
            count += this->Handle[j]->RenderOpaqueGeometry(v);
        }
    }

    return count;
}

//----------------------------------------------------------------------------
int FITKTransformRepresentation::RenderTranslucentPolygonalGeometry(vtkViewport* v)
{
    int count = 0;
    this->BuildRepresentation();

    // render the handles
    for (int j = 0; j < 4; j++)
    {
        if (this->Handle[j]->GetVisibility())
        {
            this->Handle[j]->SetPropertyKeys(this->GetPropertyKeys());
            count += this->Handle[j]->RenderTranslucentPolygonalGeometry(v);
        }
    }
    return count;
}

//----------------------------------------------------------------------------
vtkTypeBool FITKTransformRepresentation::HasTranslucentPolygonalGeometry()
{
    int result = 0;
    this->BuildRepresentation();

    // render the handles
    for (int j = 0; j < 4; j++)
    {
        result |= this->Handle[j]->HasTranslucentPolygonalGeometry();
    }

    return result;
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::HandlesOn()
{
    for (int i = 0; i < 3; i++)
    {
        this->Handle[i]->VisibilityOn();
    }
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::HandlesOff()
{
    for (int i = 0; i < 3; i++)
    {
        this->Handle[i]->VisibilityOff();
    }
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::SizeHandles()
{
    for (int i = 0; i < 3; i++)
    {
        this->HandleDistToCamera[i]->SetRenderer(this->Renderer);
    }

    double* ct = this->Points->GetPoint(0);
    double radius = this->vtkWidgetRepresentation::SizeHandlesInPixels(1., ct);
    this->SetPosition(ct, radius);
}

//----------------------------------------------------------------------------
int FITKTransformRepresentation::HighlightHandle(vtkProp* prop)
{
    // first unhighlight anything picked
    if (this->CurrentHandle)
    {
        this->CurrentHandle->SetProperty(this->HandleProperty);
    }

    this->CurrentHandle = static_cast<vtkActor*>(prop);

    if (this->CurrentHandle)
    {
        this->CurrentHandle->SetProperty(this->SelectedHandleProperty);
        for (int i = 0; i < 4; i++)
        {
            if (this->CurrentHandle == this->Handle[i])
            {
                return i;
            }
        }
    }

    return -1;
}

//------------------------------------------------------------------------------
void FITKTransformRepresentation::RegisterPickers()
{
    vtkPickingManager* pm = this->GetPickingManager();
    if (!pm)
    {
        return;
    }
    pm->AddPicker(this->HandlePicker, this);
}

//----------------------------------------------------------------------------
void FITKTransformRepresentation::PrintSelf(ostream& os, vtkIndent indent)
{
    this->Superclass::PrintSelf(os, indent);

    double* bounds = this->InitialBounds;
    os << indent << "Initial Bounds: "
        << "(" << bounds[0] << "," << bounds[1] << ") "
        << "(" << bounds[2] << "," << bounds[3] << ") "
        << "(" << bounds[4] << "," << bounds[5] << ")\n";

    if (this->HandleProperty)
    {
        os << indent << "Handle Property: " << this->HandleProperty << "\n";
    }
    else
    {
        os << indent << "Handle Property: (none)\n";
    }
    if (this->SelectedHandleProperty)
    {
        os << indent << "Selected Handle Property: " << this->SelectedHandleProperty << "\n";
    }
    else
    {
        os << indent << "SelectedHandle Property: (none)\n";
    } 
}