/*****************************************************************//**
 * @file    FITKGraphActor.h
 * @brief   External vtkActor with some common functions.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-03-20
 *********************************************************************/

#ifndef __FITKGRAPHACTOR_H__
#define __FITKGRAPHACTOR_H__

#include <vtkActor.h>
#include "FITKActorClipTool.h"

#include "FITKVTKAlgorithmAPI.h"

#include <vtkObjectFactory.h>
#include <vtkRenderingCoreModule.h>

#include <QColor>

// Forward declaration
namespace Comp
{
    class FITKGraphObjectVTK;
}

class vtkDataSet;
class vtkDataSetMapper;
class vtkAlgorithmOutput;
class vtkDataObject;
class vtkPassThrough;
class vtkTableBasedClipDataSet;
class vtkImplicitFunction;

/**
 * @brief   The type of the actor.
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-04-23
 */
enum ActorType
{
    // Others.
    OtherActor = -1,

    // Solid actor.
    SolidActor = 0,

    // Face actor.
    SurfaceActor,

    // Edge model.
    EdgeActor,

    // The original vertex actor of the model.
    VertexActor
};

/**
 * @brief   The actor's data type.
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-06-11
 */
enum DataType
{
    // Others.
    OtherData = -1,

    // Geometry.
    GeometryData = 0,

    // Mesh.
    MeshData,

    // Post.
    PostData
};

/**
 * @brief   Sub-class of vtkActor, add some new interfaces for setting input.
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-03-25
 */
class FITKVTKALGORITHMAPI FITKGraphActor : public vtkActor, public FITKActorClipTool
{
public:
    vtkTypeMacro(FITKGraphActor, vtkActor);

    /**
     * @brief   VTK new.
     * @return  The instance
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-20
     */
    static FITKGraphActor* New();

    /**
     * @brief   Set the mapper.[override]
     * @param   mapper: The mapper
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-01
     */
    void SetMapper(vtkMapper* mapper) override;

    /**
     * @brief   Set the polygon offset.
     * @param   val: The value
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-11-08
     */
    void setRelativeCoincidentTopologyPolygonOffsetParameters(double val);

    /**
     * @brief   Auto remove the cell's normals if the input data is not empty.( DO NOT USE FOR NOW !!! )
     * @param   flag: Whether to remove the normals
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-13
     */
    void setAutoRemoveNormals(bool flag);

    /**
     * @brief   Set both front and back face color.
     * @param   color: The color
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-13
     */
    void setColor(QColor color);

    /**
     * @brief   Set the front face color.
     * @param   color: The color
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-02
     */
    void setFrontFaceColor(QColor color);

    /**
     * @brief   Set the back face color.
     * @param   color: The color
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-02
     */
    void setBackFaceColor(QColor color);

    /**
     * @brief   Set enable the back face color.
     * @param   isOn: Enable or not
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-02
     */
    void setEnableBackFaceColor(bool isOn);

    /**
     * @brief   Set the data object.
     * @param   obj: Data object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-21
     */
    void setGraphObject(Comp::FITKGraphObjectVTK* obj);

    /**
     * @brief   Get the data object.
     * @return  Data object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-21
     */
    Comp::FITKGraphObjectVTK* getGraphObject();

    /**
     * @brief   Get the graph object as the given type.[template]
     * @return  The graph object.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-06-05
     */
    template<class T>
    T* getGraphObjectAs()
    {
        return dynamic_cast<T*>(m_graphObj);
    }
    
    /**
     * @brief   Set the actor's data type.
     * @param   type: Surface or edge or vertex
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-23
     */
    void setActorType(ActorType type);

    /**
     * @brief   Get the actor's data type.
     * @return  Is surface or edge or vertex
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-23
     */
    ActorType getActorType();

    /**
     * @brief   Set the actor's data type.
     * @param   type: Geometry or mesh or post
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-06-11
     */
    void setDataType(DataType type);

    /**
     * @brief   Get the actor's data type.
     * @return  Is geometry or mesh or post
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-06-11
     */
    DataType getDataType();

    /**
     * @brief   Get the input as the vtkDataSet.
     * @return  The data set
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-12-04
     */
    vtkDataSet* getInputAsDataSet();

    /**
     * @brief   Set if show the scalar.
     * @param   isOn: Is on
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-01
     */
    void setScalarVisibility(bool isOn);

    /**
     * @brief   Set the color with default color.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    void setScalarModeToDefault();

    /**
     * @brief   Set the color with point scalar.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-02
     */
    void setScalarModeToUsePointData();

    /**
     * @brief   Set the color with cell scalar.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-02
     */
    void setScalarModeToUseCellData();

    /**
     * @brief   Set the color with point field scalar.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-07
     */
    void setScalarModeToUsePointFieldData();

    /**
     * @brief   Set the color with cell field scalar.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-07
     */
    void setScalarModeToUseCellFieldData();

    /**
     * @brief   Select the array need to be the scalars.
     * @param   name: The colored array name
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-07
     */
    void selectScalarArray(QString name);

    /**
     * @brief   Update the actor's mapper.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-21
     */
    void update();

    ///**
    // * @brief   Enable or disable the clip mode.
    // * @param   flag: Enable or not
    // * @author  ChengHaotian (yeguangbaozi@foxmail.com)
    // * @date    2025-04-09
    // */
    //void setClipEnabled(bool flag);

    ///**
    // * @brief   Set the clipped function.
    // * @param   func: The implicit function of the clip dataset
    // * @author  ChengHaotian (yeguangbaozi@foxmail.com)
    // * @date    2025-04-09
    // */
    //void setClipImplicitFunction(vtkImplicitFunction* func);

protected:
    /**
     * @brief   Constructor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-20
     */
    FITKGraphActor();

    /**
     * @brief   Destructor.[virtual]
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-20
     */
    virtual ~FITKGraphActor();

    /**
     * @brief   Copy constructor.
     * @param   The object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-16
     */
    FITKGraphActor(const FITKGraphActor&) = delete;

    /**
     * @brief   Operator overloading.
     * @param   The object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-16
     */
    void operator=(const FITKGraphActor&) = delete;

    /**
     * @brief   Remove the cell normals array.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-13
     */
    void removeCellNormals();

protected:
    /**
     * @brief   VTK function override.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    //@{
    /**
     * @brief   Release any graphics resources that are being consumed by this actor.
     *          The parameter window could be used to determine which graphic
     *          resources to release.
     * @param   window: The vtk window
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    virtual void ReleaseGraphicsResources(vtkWindow* window) override;

    /**
     * @brief   For rendering opaque's actor.[override]
     * @param   viewport: The view port
     * @return  Is opaque render
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    int RenderOpaqueGeometry(vtkViewport* viewport) override;

    /**
     * @brief   For rendering opaque's actor.[override]
     * @param   viewport: The view port
     * @return  Is opaque render
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-09
     */
    int RenderTranslucentPolygonalGeometry(vtkViewport* viewport) override;
    //@}

    /**
     * @brief   Render function override.[virtual][override]
     * @param   ren: The renderer
     * @param   mapper: The actor's mapper
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    virtual void Render(vtkRenderer* ren, vtkMapper* mapper) override;

    /**
     * @brief   Shallow copy.[override]
     * @param   prop: The source prop
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    void ShallowCopy(vtkProp* prop) override;
    //@}

protected:
    // VTK function override need
    //@{
    /**
     * @brief   The actor device needed by vtkActor.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-07
     */
    vtkActor* Device{ nullptr };
    //@}

    /**
     * @brief   A mapper initialized in the constructor
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-25
     */
    vtkMapper* m_mapper{ nullptr };

    /**
     * @brief   The data object
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-03-25
     */
    Comp::FITKGraphObjectVTK* m_graphObj{ nullptr };

    /**
     * @brief   The data type of the actor.( Surface, edge or vertex. )
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-04-23
     */
    ActorType m_actorType = OtherActor;

    /**
     * @brief   The data type of the actor.( Geometry, mesh or post. )
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-06-11
     */
    DataType m_dataType = OtherData;

    /**
     * @brief   Is the back face render enabled.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-09
     */
    bool m_enableBackFace = true;

    /**
     * @brief   The color of the front face.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-09
     */
    QColor m_frontFaceColor = QColor(255, 255, 255);

    /**
     * @brief   The color of the back face.
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-09
     */
    QColor m_backFaceColor = QColor();

    /**
     * @brief   Remove the input data's normals.( For input data only )( DO NOT USE FOR NOW !!! )
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-05-13
     */
    bool m_autoRemoveNormals = false;

};

#endif // __FITKGRAPHACTOR_H__
