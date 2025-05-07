#include "FITKGeoCompOCCInterface.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoDelete.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoMultiDelete.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoSketch2D.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsConstruction.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"
#include "FITKOCCGeomTools.h"
#include "FITKOCCModelSimpleShape.h"
#include "FITKOCCModelImport.h"
#include "FITKOCCModelExport.h"
#include "FITKOCCOperBool.h"
#include "FITKOCCModelPoint.h"
#include "FITKOCCModelCurve.h"
#include "FITKOCCModelSurface.h"
#include "FITKOCCModelSolid.h"
#include "FITKOCCModelOperSolid.h"
#include "FITKOCCModelOperLine.h"
#include "FITKOCCModelOperFace.h"
#include "FITKOCCModelOperImprintSolid.h"
#include "FITKOCCReferencePoint.h"
#include "FITKOCCReferenceLine.h"
#include "FITKOCCReferencePlane.h"
#include "FITKOCCModelSketch2D.h"
#include "FITKOCCModelOperCompound.h"
#include "FITKOCCTransformation.h"
#include "FITKOCCSplitter.h"
#include "FITKOCCFeature.h"
#include "FITKOCCSampleCurve.h"
#include "FITKOCCModelNearestPointLine.h"
#include "FITKOCCModelExtractCenter.h"
#include "FITKOCCModelPart.h"
#include "FITKOCCModelImportFlattenAssembly.h"

#include "FITK_Interface/FITKInterfaceModel/FITKAbsInterfaceFactory.h"
#include "FITKOCCAlgTools.h"

namespace OCC
{

    FITKGeoCompOCCInterface::FITKGeoCompOCCInterface()
    {
        Interface::FITKInterfaceGeometryFactory* fac =
            Interface::FITKInterfaceGeometryFactory::getInstance();
        if (fac == nullptr) return;
        fac->setGeomToolsCreator(new FITKOCCToolCreator);

        // 注册算法工具。
        Interface::FITKInterfaceAlgorithmFactory* facAlg = Interface::FITKInterfaceAlgorithmFactory::getInstance();
        if (facAlg == nullptr) return;
        facAlg->setAlgToolsCreator(new FITKOCCAlgToolCreator);

        // 基准元素。
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTPoint, [&]() {return new FITKOCCReferencePoint; });
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTLine, [&]() {return new FITKOCCReferenceLine; });
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTPlane, [&]() {return new FITKOCCReferencePlane; });
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTOffsetPlane, [&]() {return new FITKOCCReferenceOffsetPlane; });
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTThreePointsPlane, [&]() {return new FITKOCCReferenceThreePointsPlane; });
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTEquationPlane, [&]() {return new FITKOCCReferenceEquationPlane; });
        fac->insertDatumCreateFun(Interface::FITKGeoEnum::FDTPointAndDirectionPlane, [&]() {return new FITKOCCReferencePointAndDirectionPlane; });

        // 2D草图。
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSketch2D, [&]() {return new FITKOCCModelSketch2D; });

        // 构造线。
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTConstruction, [&]() {return new Interface::FITKAbsConstruction; });

        // 模型移除。
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTDelete, [&]() {return new Interface::FITKAbsGeoDelete; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTMultiDelete, [&]() {return new Interface::FITKAbsGeoMultiDelete; });

        // 模型。
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTImport, [&]() {return new FITKOCCModelImport; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTImportFlattenAssembly, [&]() {return new FITKOCCModelImportFlattenAssembly; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTExport, [&]() {return new FITKOCCModelExport; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTPart, [&]() {return new FITKOCCModelPart; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTBox, [&]() {return new FITKOCCModelBox; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCylinder, [&]() {return new FITKOCCModelCylinder; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSphere, [&]() {return new FITKOCCModelSphere; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTBool, [&]() {return new FITKOCCOperBool; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTPoint, [&]() {return new FITKOCCModelPoint; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveEnd, [&]() {return new FITKOCCModelCurveEnd; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveEndDistance, [&]() {return new FITKOCCModelCurveEndDistance; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveRadio, [&]() {return new FITKOCCModelCurveRadio; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTPointProjectionOnCurve, [&]() {return new FITKOCCModelPointProjectionOnCurve; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTTwoCurveIntersectPoint, [&]() {return new FITKOCCModelTwoCurveIntersection; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTPointProjectionOnSurface, [&]() {return new FITKOCCModelPointProjectionOnSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveIntersectSurface, [&]() {return new FITKOCCModelCurveIntersectionSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSegment, [&]() {return new FITKOCCModelSegment; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTWire, [&]() {return new FITKOCCModelWire; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCircle, [&]() {return new FITKOCCModelCircle; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCircleArc, [&]() {return new FITKOCCModelCircleArc; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTThreePointsCircle, [&]() {return new FITKOCCModelThreePointsCircle; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTThreePointsEllipse, [&]() {return new FITKOCCModelThreePointsEllipse; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTThreePointsHyperbola, [&]() {return new FITKOCCModelThreePointsHyperbola; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTThreePointsParabola, [&]() {return new FITKOCCModelThreePointsParabola; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveProjectionOnSurface, [&]() {return new FITKOCCModelCurveProjectionOnSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSurfaceIntersectSurface, [&]() {return new FITKOCCModelSurfaceIntersectionSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTEllipse, [&]() {return new FITKOCCModelEllipse; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTHyperbola, [&]() {return new FITKOCCModelHyperbola; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTParabola, [&]() {return new FITKOCCModelParabola; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTEllipseArc, [&]() {return new FITKOCCModelEllipseArc; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTHyperbolaArc, [&]() {return new FITKOCCModelHyperbolaArc; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTParabolaArc, [&]() {return new FITKOCCModelParabolaArc; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTBezierByControlPoints, [&]() {return new FITKOCCModelBeizeByControlPoints; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTBSplineByThroughPoints, [&]() {return new FITKOCCModelBsplineByThroughPoints; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTOffsetCurve, [&]() {return new FITKOCCModelOffsetCurve; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTBridgeCurve, [&]() {return new FITKOCCModelBridgeCurve; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveFromSurface, [&]() {return new FITKOCCModelSurfaceEdge; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTClosedWireSurface, [&]() {return new FITKOCCModelClosedWireSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTExtrudeSurface, [&]() {return new FITKOCCModelExtrudeSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTRevolSurface, [&]() {return new FITKOCCModelRevolSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTOffsetSurface, [&]() {return new FITKOCCModelOffsetSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSweepSurface, [&]() {return new FITKOCCModelSweepSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTBridgeSurface, [&]() {return new  FITKOCCModelBridgeSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTMultiSectionSurface, [&]() {return new  FITKOCCModelMultiSectionSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSurfaceFromSolid, [&]() {return new FITKOCCModelSolidSurface; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTClosedSurfaceSolid, [&]() {return new FITKOCCModelClosedSurfaceSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTExtrudeSolid, [&]() {return new FITKOCCModelExtrudeSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTRevolSolid, [&]() {return new FITKOCCModelRevolSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSweepSolid, [&]() {return new FITKOCCModelSweepSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTMultiSectionSolid, [&]() {return new  FITKOCCModelMultiSectionSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTChamferSolid, [&]() {return new FITKOCCModelChamferSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTFilletSolid, [&]() {return new FITKOCCModelFilletSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTDefeature, [&]() {return new FITKOCCModelDefeatureSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTRemoveChamfer, [&]() {return new FITKOCCModelRemoveChamferSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTRemoveFillet, [&]() {return new FITKOCCModelRemoveFilletSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTFillHole, [&]() {return new FITKOCCModelFillHoleSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTMergeLine, [&]() {return new FITKOCCModelOperLine; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTDeleteFloatingEdge, [&]() {return new FITKOCCModelOperFaceDeleteFloatingEdge; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTFillGapsFace, [&]() {return new FITKOCCModelOperFaceFillGaps; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSplitByMiddlePositionLine, [&]() {return new FITKOCCModelMiddleOperLine; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTImprintSolid, [&]() {return new FITKOCCModelOperImprintSolid; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCompoundAppendShape, [&]() {return new FITKOCCModelOperAddCompound; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCompoundRemoveShape, [&]() {return new FITKOCCModelOperRemoveCompound; });
        //      fac->regVirtualTopoCreator(new FITKOCCVirtualTopoCreator);

        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTTransform, [&]() {return new FITKOCCModelTransform; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTTransformByTwoPoints, [&]() {return new FITKOCCModelTransformByTwoPoints; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTTransformByDirAndDis, [&]() {return new FITKOCCModelTransformByDirAndDis; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTRotate, [&]() {return new FITKOCCModelRotate; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTScale, [&]() {return new FITKOCCModelScale; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTMirror, [&]() {return new FITKOCCModelMirror; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTRectangularPattern, [&]() {return new FITKOCCModelRectangularPattern; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCircularPattern, [&]() {return new FITKOCCModelCircularPattern; });

        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTCurveSplitter, [&]() {return new FITKOCCCurveSplitter; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSurfaceSplitter, [&]() {return new FITKOCCSurfaceSplitter; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSolidSplitter, [&]() {return new FITKOCCSolidSplitter; });

        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTStiffener, [&]() {return new FITKOCCStiffener; });

        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTInteractionPoint, [&]() {return new FITKOCCModelInteractionPoint; });

        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTSampleCurve, [&]() {return new FITKOCCSampleCurve; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTNearestPointLine, [&]() {return new FITKOCCModelNearestPointLine; });
        fac->insertCommandCreateFun(Interface::FITKGeoEnum::FGTExtractCenter, [&]() {return new FITKOCCModelExtractCenter; });
    }

    FITKGeoCompOCCInterface::~FITKGeoCompOCCInterface()
    {
        Interface::FITKInterfaceGeometryFactory* fac =
            Interface::FITKInterfaceGeometryFactory::getInstance();
        if (fac == nullptr) return;
        fac->clearAllInterface();
    }

    QString FITKGeoCompOCCInterface::getComponentName()
    {
        //返回类型名
        return "FITKGeoCompOCC";
    }


    bool FITKGeoCompOCCInterface::exec(const int indexPort)
    {
        Q_UNUSED(indexPort);
        return true;
    }
}
