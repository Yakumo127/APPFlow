﻿/*****************************************************************//**
 * @file    FITKLegendScaleActor.h
 * @brief   Scale actor with a single legend.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-05-28
 *********************************************************************/

#ifndef FITKLegendScaleActor_h
#define FITKLegendScaleActor_h

#include "vtkCoordinate.h" // For vtkViewportCoordinateMacro
#include "vtkProp.h"
#include "vtkRenderingAnnotationModule.h" // For export macro

#include "FITKRenderWindowVTKAPI.h"

class vtkAxisActor2D;
class vtkTextProperty;
class vtkPolyData;
class vtkPolyDataMapper2D;
class vtkActor2D;
class vtkTextMapper;
class vtkPoints;
class vtkCoordinate;

class FITKRenderWindowVTKAPI FITKLegendScaleActor : public vtkProp
{
public:
    /**
     * Instantiate the class.
     */
    static FITKLegendScaleActor* New();

    //@{
    /**
     * Standard methods for the class.
     */
    vtkTypeMacro(FITKLegendScaleActor, vtkProp);
    void PrintSelf(ostream& os, vtkIndent indent) override;
    //@}

    //@{
    /**
     * These are methods to retrieve the vtkAxisActors used to represent
     * the four axes that form this representation. Users may retrieve and
     * then modify these axes to control their appearance.
     */
    vtkGetObjectMacro(BottomAxis, vtkAxisActor2D);
    //@}

    //@{
    /**
     * Standard methods supporting the rendering process.
     */
    virtual void BuildRepresentation(vtkViewport* viewport);
    void GetActors2D(vtkPropCollection*) override;
    void ReleaseGraphicsResources(vtkWindow*) override;
    int RenderOverlay(vtkViewport*) override;
    int RenderOpaqueGeometry(vtkViewport*) override;
    //@}

protected:
    FITKLegendScaleActor();
    ~FITKLegendScaleActor() override;

    // The four axes around the borders of the renderer
    vtkAxisActor2D* BottomAxis;

    // Control the display of the axes
    vtkTypeBool BottomAxisVisibility;

    // Support for the legend.
    vtkPolyData* Legend;
    vtkPoints* LegendPoints;
    vtkPolyDataMapper2D* LegendMapper;
    vtkActor2D* LegendActor;
    vtkTextMapper* LabelMappers[5];
    vtkActor2D* LabelActors[5];
    vtkTextProperty* LegendLabelProperty;
    vtkCoordinate* Coordinate;

    vtkTimeStamp BuildTime;

private:
    FITKLegendScaleActor(const FITKLegendScaleActor&) = delete;
    void operator=(const FITKLegendScaleActor&) = delete;
};

#endif
