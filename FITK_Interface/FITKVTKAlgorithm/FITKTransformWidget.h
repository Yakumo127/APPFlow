﻿#ifndef FITKTransformWidget_h
#define FITKTransformWidget_h

#include "vtkAbstractWidget.h"

#include "FITKVTKAlgorithmAPI.h"

class FITKTransformRepresentation;
class vtkHandleWidget;

class FITKVTKALGORITHMAPI FITKTransformWidget : public vtkAbstractWidget
{
public:
    /**
     * Instantiate the object.
     */
    static FITKTransformWidget* New();

    //@{
    /**
     * Standard class methods for type information and printing.
     */
    vtkTypeMacro(FITKTransformWidget, vtkAbstractWidget);
    void PrintSelf(ostream& os, vtkIndent indent) override;
    //@}

    /**
     * Specify an instance of vtkWidgetRepresentation used to represent this
     * widget in the scene. Note that the representation is a subclass of vtkProp
     * so it can be added to the renderer independent of the widget.
     */
    void SetRepresentation(FITKTransformRepresentation* r)
    {
        this->Superclass::SetWidgetRepresentation(reinterpret_cast<vtkWidgetRepresentation*>(r));
    }

    //@{
    /**
     * Control the behavior of the widget
     */
    vtkSetMacro(TranslationEnabled, vtkTypeBool);
    vtkGetMacro(TranslationEnabled, vtkTypeBool);
    vtkBooleanMacro(TranslationEnabled, vtkTypeBool);
    //@}

    /**
     * Create the default widget representation if one is not set. By default,
     * this is an instance of the FITKTransformRepresentation class.
     */
    void CreateDefaultRepresentation() override;

    /**
     * Override superclasses' SetEnabled() method because the line
     * widget must enable its internal handle widgets.
     */
    void SetEnabled(int enabling) override;

protected:
    FITKTransformWidget();
    ~FITKTransformWidget() override;

    // Manage the state of the widget
    int WidgetState;
    enum _WidgetState
    {
        Start = 0,
        Active
    };

    // These methods handle events
    static void SelectAction(vtkAbstractWidget*);
    static void EndSelectAction(vtkAbstractWidget*);
    static void TranslateAction(vtkAbstractWidget*);
    static void MoveAction(vtkAbstractWidget*);
    static void SelectAction3D(vtkAbstractWidget*);
    static void EndSelectAction3D(vtkAbstractWidget*);
    static void MoveAction3D(vtkAbstractWidget*);
    static void StepAction3D(vtkAbstractWidget*);

    // Control whether scaling, rotation, and translation are supported
    vtkTypeBool TranslationEnabled;

private:
    FITKTransformWidget(const FITKTransformWidget&) = delete;
    void operator=(const FITKTransformWidget&) = delete;
};

#endif
