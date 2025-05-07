#ifndef FITKTransformRepresentation_h
#define FITKTransformRepresentation_h

#include "vtkWidgetRepresentation.h"

#include "FITKVTKAlgorithmAPI.h"

class vtkActor;
class vtkPolyDataMapper;
class vtkLineSource;
class vtkSphereSource;
class vtkCellPicker;
class vtkProperty;
class vtkPolyData;
class vtkPoints;
class vtkPolyDataAlgorithm;
class vtkTransform;
class vtkBox;
class vtkDoubleArray;
class vtkDistanceToCamera;
class vtkGlyph3D;
class vtkArrowSource;
class vtkTransformFilter;

class FITKVTKALGORITHMAPI FITKTransformRepresentation : public vtkWidgetRepresentation
{
public:
    /**
     * Instantiate the class.
     */
    static FITKTransformRepresentation* New();

    void SetColor(double* color3);
    void SetPosition(double* pos3);
    double* GetPosition();

    //@{
    /**
     * Standard methods for the class.
     */
    vtkTypeMacro(FITKTransformRepresentation, vtkWidgetRepresentation);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    //@{
    /**
     * Get the handle properties (the little balls are the handles). The
     * properties of the handles, when selected or normal, can be
     * specified.
     */
    vtkGetObjectMacro(HandleProperty, vtkProperty);
    vtkGetObjectMacro(SelectedHandleProperty, vtkProperty);
    //@}

    //@{
    /**
     * Switches handles (the spheres) on or off by manipulating the underlying
     * actor visibility.
     */
    virtual void HandlesOn();
    virtual void HandlesOff();
    //@}

    //@{
    /**
     * These are methods that satisfy vtkWidgetRepresentation's API.
     */
    void PlaceWidget(double bounds[6]) override;
    void BuildRepresentation() override;
    int ComputeInteractionState(int X, int Y, int modify = 0) override;
    void StartWidgetInteraction(double e[2]) override;
    void WidgetInteraction(double e[2]) override;
    double* GetBounds() VTK_SIZEHINT(6) override;
    void ComplexInteraction(vtkRenderWindowInteractor* iren, vtkAbstractWidget* widget,
        unsigned long event, void* calldata) override;
    int ComputeComplexInteractionState(vtkRenderWindowInteractor* iren, vtkAbstractWidget* widget,
        unsigned long event, void* calldata, int modify = 0) override;
    void EndComplexInteraction(vtkRenderWindowInteractor* iren, vtkAbstractWidget* widget,
        unsigned long event, void* calldata) override;
    //@}

    //@{
    /**
     * Methods supporting, and required by, the rendering process.
     */
    void ReleaseGraphicsResources(vtkWindow*) override;
    int RenderOpaqueGeometry(vtkViewport*) override;
    int RenderTranslucentPolygonalGeometry(vtkViewport*) override;
    vtkTypeBool HasTranslucentPolygonalGeometry() override;
    //@}

    // Used to manage the state of the widget
    enum
    {
        Outside = 0,
        TranslatingX,
        TranslatingY,
        TranslatingZ,
        TranslatingO
    };

    /**
     * The interaction state may be set from a widget or
     * other object. This controls how the interaction with the widget
     * proceeds. Normally this method is used as part of a handshaking
     * process with the widget: First ComputeInteractionState() is invoked that
     * returns a state based on geometric considerations (i.e., cursor near a
     * widget feature), then based on events, the widget may modify this
     * further.
     */
    void SetInteractionState(int state);

    /*
     * Register internal Pickers within PickingManager
     */
    void RegisterPickers() override;

protected:
    FITKTransformRepresentation();
    ~FITKTransformRepresentation() override;

    void SetPosition(double* pos3, double size);

    double Color[3]{ 0.7, 0.7, 0.7 };
    double Position[3]{ 0., 0., 0. };

    // Manage how the representation appears
    double LastEventPosition[3];
    double LastEventOrientation[4];
    double StartEventOrientation[4];

    vtkPoints* Points;
    vtkPolyData** PolyData;
    vtkDoubleArray** Normals;

    vtkDistanceToCamera** HandleDistToCamera;
    vtkGlyph3D** HandleGlyph3D;

    vtkArrowSource* HandleSource;
    vtkTransformFilter* HandleTransFilter;

    vtkSphereSource* CenterSource;

    // glyphs representing hot spots (e.g., handles)
    vtkActor** Handle;
    vtkPolyDataMapper** HandleMapper;
    int HighlightHandle(vtkProp* prop); // returns cell id
    virtual void SizeHandles();

    // Do the picking
    vtkCellPicker* HandlePicker;
    vtkActor* CurrentHandle;

    // Transform the hexahedral points (used for rotations)
    vtkTransform* Transform;

    // Support GetBounds() method
    vtkBox* BoundingBox;

    // Properties used to control the appearance of selected objects and
    // the manipulator in general.
    vtkProperty* HandleProperty;
    vtkProperty* SelectedHandleProperty;
    virtual void CreateDefaultProperties();

    // Helper methods
    virtual void Translate(const double* p1, const double* p2);

private:
    FITKTransformRepresentation(const FITKTransformRepresentation&) = delete;
    void operator=(const FITKTransformRepresentation&) = delete;
};

#endif
