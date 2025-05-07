#include "FITKGraphActor.h"

#include <vtkObjectFactory.h>
#include <vtkUnstructuredGrid.h>
#include <vtkAlgorithmOutput.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkTexture.h>
#include <vtkRenderer.h>
#include <vtkInformation.h>
#include <vtkTransform.h>
#include <vtkCellData.h>
#include <vtkPassThrough.h>
#include <vtkTableBasedClipDataSet.h>
#include <vtkImplicitFunction.h>

FITKGraphActor* FITKGraphActor::New()
{
    // Return the instance.
    return new FITKGraphActor;
}

void FITKGraphActor::SetMapper(vtkMapper* mapper)
{
    m_mapper = mapper;

    //if (m_mapper)
    //{
    //    m_mapper->SetUseLookupTableScalarRange(true);
    //}

    vtkActor::SetMapper(mapper);
}

void FITKGraphActor::setRelativeCoincidentTopologyPolygonOffsetParameters(double val)
{
    if (m_mapper)
    {
        m_mapper->SetRelativeCoincidentTopologyPolygonOffsetParameters(val, val);
        m_mapper->SetRelativeCoincidentTopologyLineOffsetParameters(val, val);
        m_mapper->SetRelativeCoincidentTopologyPointOffsetParameter(val);
    }
}

FITKGraphActor::FITKGraphActor() : FITKActorClipTool(this)
{
    // Create a mapper and set to the actor.
    this->Device = vtkActor::New();
    m_mapper = vtkDataSetMapper::New();
    this->SetMapper(m_mapper);

    //// Default show face and edge.
    //this->GetProperty()->SetRepresentation(2);
    //this->GetProperty()->SetEdgeVisibility(true);
}

FITKGraphActor::~FITKGraphActor()
{
    // Delete the mapper created by self.
    if (m_mapper)
    {
        m_mapper->Delete();
        m_mapper = nullptr;
    }

    m_mapper = nullptr;

    // Delete the actor device.
    if (this->Device)
    {
        this->Device->Delete();
        this->Device = nullptr;
    }

    //if (m_passThrough)
    //{
    //    m_passThrough->Delete();
    //    m_passThrough = nullptr;
    //}

    //if (m_clipper)
    //{
    //    m_clipper->Delete();
    //    m_clipper = nullptr;
    //}

    m_graphObj = nullptr;
}

void FITKGraphActor::setAutoRemoveNormals(bool flag)
{
    m_autoRemoveNormals = flag;

    // Try to remove the normals.
    if (m_autoRemoveNormals)
    {
        removeCellNormals();
    }
}

void FITKGraphActor::removeCellNormals()
{
    // Check the mapper.
    if (!m_mapper)
    {
        return;
    }

    // Check the input data.
    vtkDataSet* dataset = m_mapper->GetInput();
    if (!dataset)
    {
        return;
    }

    // Check the cell data.
    vtkCellData* cellData = dataset->GetCellData();
    if (!cellData)
    {
        return;
    }

    // Get the normals array.
    vtkDataArray* normals = cellData->GetNormals();
    if (!normals)
    {
        return;
    }

    cellData->SetNormals(nullptr);
    normals->Delete();

    update();
}

void FITKGraphActor::setColor(QColor color)
{
    if (!color.isValid())
    {
        return;
    }

    setFrontFaceColor(color);
    setBackFaceColor(color);
}

void FITKGraphActor::setFrontFaceColor(QColor color)
{
    if (!color.isValid())
    {
        return;
    }

    m_frontFaceColor = color;

    // Initialize front face property.
    vtkProperty* prop = this->GetProperty();
    if (!prop)
    {
        prop = vtkProperty::New();
        this->SetProperty(prop);
    }

    prop->SetColor(color.redF(), color.greenF(), color.blueF());
}

void FITKGraphActor::setBackFaceColor(QColor color)
{
    if (!color.isValid())
    {
        return;
    }

    m_backFaceColor = color;

    if (!m_enableBackFace)
    {
        return;
    }

    // Initialize back face property.
    vtkProperty* prop = this->GetBackfaceProperty();
    if (!prop)
    {
        prop = vtkProperty::New();
        this->SetBackfaceProperty(prop);
    }

    prop->SetColor(color.redF(), color.greenF(), color.blueF());
}

void FITKGraphActor::setEnableBackFaceColor(bool isOn)
{
    if (isOn)
    {
        setBackFaceColor(m_backFaceColor);
    }
    else
    {
        vtkProperty* prop = this->GetBackfaceProperty();
        if (!prop)
        {
            prop = vtkProperty::New();
            this->SetBackfaceProperty(prop);
        }

        prop->SetColor(m_frontFaceColor.redF(), m_frontFaceColor.greenF(), m_frontFaceColor.blueF());
    }

    m_enableBackFace = isOn;
}

void FITKGraphActor::setGraphObject(Comp::FITKGraphObjectVTK* obj)
{
    m_graphObj = obj;
}

Comp::FITKGraphObjectVTK* FITKGraphActor::getGraphObject()
{
    return m_graphObj;
}

void FITKGraphActor::setActorType(ActorType type)
{
    m_actorType = type;
}

ActorType FITKGraphActor::getActorType()
{
    return m_actorType;
}

void FITKGraphActor::setDataType(DataType type)
{
    m_dataType = type;
}

DataType FITKGraphActor::getDataType()
{
    return m_dataType;
}

vtkDataSet* FITKGraphActor::getInputAsDataSet()
{
    if (!m_mapper)
    {
        return nullptr;
    }

    return m_mapper->GetInputAsDataSet();
}

void FITKGraphActor::setScalarVisibility(bool isOn)
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SetScalarVisibility(isOn);
}

void FITKGraphActor::setScalarModeToDefault()
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SetScalarModeToDefault();
}

void FITKGraphActor::setScalarModeToUsePointData()
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SetScalarModeToUsePointData();
}

void FITKGraphActor::setScalarModeToUseCellData()
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SetScalarModeToUseCellData();
}

void FITKGraphActor::setScalarModeToUsePointFieldData()
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SetScalarModeToUsePointFieldData();
}

void FITKGraphActor::setScalarModeToUseCellFieldData()
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SetScalarModeToUseCellFieldData();
}

void FITKGraphActor::selectScalarArray(QString name)
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    m_mapper->SelectColorArray(name.toUtf8().data());
}

void FITKGraphActor::update()
{
    // If mapper is empty, return.
    if (!m_mapper)
    {
        return;
    }

    // Update the actor's mapper.
    m_mapper->Update();
}

// Override from vtkActor
//@{
void FITKGraphActor::ReleaseGraphicsResources(vtkWindow* window)
{
    // Override release resources function.
    this->Device->ReleaseGraphicsResources(window);
    this->Superclass::ReleaseGraphicsResources(window);
}

int FITKGraphActor::RenderOpaqueGeometry(vtkViewport* viewport)
{
    // Override render opaque function.
    if (!this->Mapper)
    {
        return 0;
    }
    if (!this->Property)
    {
        this->GetProperty();
    }

    if (this->GetIsOpaque())
    {
        vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);
        this->Render(ren, this->Mapper);
        return 1;
    }

    return 0;
}

int FITKGraphActor::RenderTranslucentPolygonalGeometry(vtkViewport* viewport)
{
    // Override render opaque function.
    if (!this->Mapper)
    {
        return 0;
    }
    if (!this->Property)
    {
        this->GetProperty();
    }

    if (!this->GetIsOpaque())
    {
        vtkRenderer* ren = static_cast<vtkRenderer*>(viewport);
        this->Render(ren, this->Mapper);
        return 1;
    }

    return 0;
}

void FITKGraphActor::Render(vtkRenderer* ren, vtkMapper* mapper)
{
    Q_UNUSED(mapper);

    // Override render function.
    this->Property->Render(this, ren);

    this->Device->SetProperty(this->Property);
    this->Property->Render(this, ren);
    if (this->BackfaceProperty)
    {
        this->BackfaceProperty->BackfaceRender(this, ren);
        this->Device->SetBackfaceProperty(this->BackfaceProperty);
    }

    /* render the texture */
    if (this->Texture)
    {
        this->Texture->Render(ren);
    }
    this->Device->SetTexture(this->GetTexture());

    // make sure the device has the same matrix
    this->ComputeMatrix();
    this->Device->SetUserMatrix(this->Matrix);
    if (this->GetPropertyKeys())
    {
        this->Device->SetPropertyKeys(this->GetPropertyKeys());
    }
    this->Device->Render(ren, this->Mapper);
}

void FITKGraphActor::ShallowCopy(vtkProp* prop)
{
    // Override shallow copy.
    this->Superclass::ShallowCopy(prop);
}
//@}

// vtkStandardNewMacro(vtkActorEx);