#include "FITKOCCModelSurface.h"
#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepFill_Filling.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <GeomAPI_PointsToBSplineSurface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomLib_Tool.hxx>
#include <Geom_BezierSurface.hxx>
#include <TopExp_Explorer.hxx>
#include <GeomAdaptor_HCurve.hxx>
#include <GeomFill_SimpleBound.hxx>
#include <GeomFill_ConstrainedFilling.hxx>
#include <Geom_BSplineSurface.hxx>
#include <TopoDS_Iterator.hxx>
#include <TopExp_Explorer.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <Precision.hxx>
#include <BRepBndLib.hxx>
#include <Geom_BSplineCurve.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <FITK_Interface/FITKInterfaceGeometry/FITKGeoEnum.h>
#include <FITK_Interface/FITKInterfaceGeometry/FITKVirtualTopoManager.h>
#include "FITKOCCVirtualTopoCreator.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSurface.h"

#include <FITKOCCModelCurve.h>


namespace OCC
{

    FITKOCCModelClosedWireSurface::FITKOCCModelClosedWireSurface()
        : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelClosedWireSurface::update()
    {
        if (m_Edges.isEmpty()) return false;

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        BRepBuilderAPI_MakeWire wire;
        BRepFill_Filling fillFace;
        for (int i = 0; i < m_Edges.size(); ++i) {
            auto edge = m_Edges.at(i);
            if (edge.isNull()) continue;

            auto cmd = geoCmdList->getDataByID(edge.CmdId);
            if (cmd == nullptr) return false;
            Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
            auto vshape = cmd->getShapeT<FITKOCCTopoShape>(type, edge.VirtualTopoId);
            if (vshape == nullptr) return false;
            auto topoShape = vshape->getTopoShape();
            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE) {
                TopoDS_Edge e = TopoDS::Edge(topoShape);
                if (e.IsNull()) continue;
                fillFace.Add(e, GeomAbs_Shape::GeomAbs_C0, true);
                wire.Add(e);
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND) {
                TopExp_Explorer exp;
                for (exp.Init(topoShape, TopAbs_EDGE); exp.More(); exp.Next())
                {
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    fillFace.Add(edge, GeomAbs_Shape::GeomAbs_C0, true);
                    wire.Add(edge);
                }

            }
            else {
                continue;
            }

        }

        /*@{*/
        // 封闭性检查
        TopoDS_Wire topowire = TopoDS::Wire(wire.Shape());
        if (topowire.IsNull() || !topowire.Closed()) {
            printLog(tr("Must be closed wire."), 3);
            return false;
        }
        /*@}*/

        try
        {
            fillFace.Build();
            if (!fillFace.IsDone())
            {
                printLog(tr("Failed to make face!"), 3);
                return false;
            }

            TopoDS_Shape face = fillFace.Face();
            if (face.IsNull())
            {
                printLog(tr("Failed to make face!"), 3);
                return false;
            }

            _occShapeAgent->updateShape(face);
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }

        return true;

        /*if (m_Edges.isEmpty()) return false;
        auto aConstrainedFilling = new GeomFill_ConstrainedFilling(5, 2);

        auto edge = m_Edges.at(0);
        if (edge.isNull()) return nullptr;
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();
        auto cmd = geoCmdList->getDataByID(edge.CmdId);
        if (cmd == nullptr) return nullptr;
        auto vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, edge.VirtualTopoId);
        if (vshape == nullptr) return nullptr;
        auto topoShape = vshape->getTopoShape();
        TopoDS_Edge e = TopoDS::Edge(topoShape);
        if (e.IsNull()) return nullptr;

        Standard_Real first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(e, first, last);

        Handle(GeomAdaptor_HCurve) SPL1Adaptor = new GeomAdaptor_HCurve(curve);
        Handle(GeomFill_SimpleBound) B1 = new GeomFill_SimpleBound(SPL1Adaptor, Precision::Approximation(), Precision::Angular());


        edge = m_Edges.at(1);
        if (edge.isNull()) return nullptr;
        cmd = geoCmdList->getDataByID(edge.CmdId);
        if (cmd == nullptr) return nullptr;
        vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, edge.VirtualTopoId);
        if (vshape == nullptr) return nullptr;
        topoShape = vshape->getTopoShape();
        e = TopoDS::Edge(topoShape);
        if (e.IsNull()) return nullptr;
        Handle(Geom_Curve) curve1 = BRep_Tool::Curve(e, first, last);

        Handle(GeomAdaptor_HCurve) SPL1Adaptor1 = new GeomAdaptor_HCurve(curve1);
        Handle(GeomFill_SimpleBound) B2 = new GeomFill_SimpleBound(SPL1Adaptor1, Precision::Approximation(), Precision::Angular());


        edge = m_Edges.at(2);
        if (edge.isNull()) return nullptr;
        cmd = geoCmdList->getDataByID(edge.CmdId);
        if (cmd == nullptr) return nullptr;
        vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, edge.VirtualTopoId);
        if (vshape == nullptr) return nullptr;
        topoShape = vshape->getTopoShape();
        e = TopoDS::Edge(topoShape);
        if (e.IsNull()) return nullptr;
        Handle(Geom_Curve) curve2 = BRep_Tool::Curve(e, first, last);

        Handle(GeomAdaptor_HCurve) SPL1Adaptor2 = new GeomAdaptor_HCurve(curve2);
        Handle(GeomFill_SimpleBound) B3 = new GeomFill_SimpleBound(SPL1Adaptor2, Precision::Approximation(), Precision::Angular());


        edge = m_Edges.at(3);
        if (edge.isNull()) return nullptr;
        cmd = geoCmdList->getDataByID(edge.CmdId);
        if (cmd == nullptr) return nullptr;
        vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, edge.VirtualTopoId);
        if (vshape == nullptr) return nullptr;
        topoShape = vshape->getTopoShape();
        e = TopoDS::Edge(topoShape);
        if (e.IsNull()) return nullptr;
        Handle(Geom_Curve) curve3 = BRep_Tool::Curve(e, first, last);

        Handle(GeomAdaptor_HCurve) SPL1Adaptor3 = new GeomAdaptor_HCurve(curve3);
        Handle(GeomFill_SimpleBound) B4 = new GeomFill_SimpleBound(SPL1Adaptor3, Precision::Approximation(), Precision::Angular());

        aConstrainedFilling->Init(B1, B2, B3, B4, false);


        Handle(Geom_BSplineSurface) aBSplineSurface = aConstrainedFilling->Surface();

        BRepBuilderAPI_MakeFace face(aBSplineSurface, Precision::Confusion());
        if (!face.IsDone()) {
            printLog(tr("Failed to make shape."), 3);
            return false;
        }
        _occShapeAgent->updateShape(face.Shape());

        return true;*/



        /*if (m_Edges.isEmpty()) return false;

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        BRepBuilderAPI_MakeWire wire;
        for (int i = 0; i < m_Edges.size(); ++i) {
            auto edge = m_Edges.at(i);
            if (edge.isNull()) continue;

            auto cmd = geoCmdList->getDataByID(edge.CmdId);
            if (cmd == nullptr) return false;
            auto vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, edge.VirtualTopoId);
            if (vshape == nullptr) return false;
            auto topoShape = vshape->getTopoShape();
            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE) {
                TopoDS_Edge e = TopoDS::Edge(topoShape);
                if (e.IsNull()) continue;
                wire.Add(e);
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_WIRE) {
                TopoDS_Wire w = TopoDS::Wire(topoShape);
                if (w.IsNull()) continue;
                wire.Add(w);
            }
            else {
                printLog(tr("Error topo shape type for make wire."), 3);
                return false;
            }
        }
        wire.Build();
        if (!wire.IsDone()) {
            switch (wire.Error())
            {
            case BRepBuilderAPI_EmptyWire:
                printLog(tr("Empty Wire."), 3);
                break;
            case BRepBuilderAPI_DisconnectedWire:
                printLog(tr("Disconnected Wire."), 3);
                break;
            case  BRepBuilderAPI_NonManifoldWire:
                printLog(tr("NonManifold Wire."), 3);
                break;
            case  BRepBuilderAPI_WireDone:
                printLog(tr("Wire Done."), 3);
                break;
            default:
                break;
            }
        }
        TopoDS_Wire topowire = TopoDS::Wire(wire.Shape());
        if (topowire.IsNull() || !topowire.Closed()) {
            printLog(tr("Must be closed wire."), 3);
            return false;
        }
        BRepBuilderAPI_MakeFace face(wire);
        if (!face.IsDone()) {
            printLog(tr("Failed to make shape."), 3);
            return false;
        }
        _occShapeAgent->updateShape(face.Shape());

        return true;*/
    }

    FITKOCCModelOffsetSurface::FITKOCCModelOffsetSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelOffsetSurface::update()
    {
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto cmd = geoCmdList->getDataByID(m_SourceSurface.CmdId);
        if (cmd == nullptr) return false;
        auto vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, m_SourceSurface.VirtualTopoId);
        if (vshape == nullptr) return false;
        auto topoShape = vshape->getTopoShape();

        try
        {
            BRepOffset_MakeOffset offsetSurface(topoShape, m_Offset, 1e-6);
            if (!offsetSurface.IsDone()) return false;

            _occShapeAgent->updateShape(offsetSurface.Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }
        return true;
    }
    FITKOCCModelExtrudeSurface::FITKOCCModelExtrudeSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelExtrudeSurface::update()
    {

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto cmd = geoCmdList->getDataByID(m_SourceCurve.CmdId);
        if (cmd == nullptr) return false;
        Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
        auto vshape = cmd->getShapeT<FITKOCCTopoShape>(type, m_SourceCurve.VirtualTopoId);
        if (vshape == nullptr) return false;
        auto topoShape = vshape->getTopoShape();
        //m_OriginId;
        gp_Vec dir(m_Direction[0], m_Direction[1], m_Direction[2]);
        auto mag = dir.Magnitude();
        if (mag <= Precision::Confusion()) {
            printLog(tr("The direction cannot be a zero vector!"), 3);
            return false;
        }
        dir = dir * m_Length / mag;


        // 如果是草绘则返回的是线的组合体，需要合并面
        if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND)
        {
            BRep_Builder builder;
            TopoDS_Compound compound;
            builder.MakeCompound(compound);
            TopExp_Explorer exp;

            // 按封闭曲线分组
            for (exp.Init(topoShape, TopAbs_EDGE); exp.More(); exp.Next())
            {
                TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                if (edge.IsNull()) continue;

                builder.Add(compound, edge);
            }
            topoShape = compound;
        }
        try {
            _occShapeAgent->updateShape(BRepPrimAPI_MakePrism(topoShape, dir).Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }
        return true;
    }
    FITKOCCModelRevolSurface::FITKOCCModelRevolSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelRevolSurface::update()
    {
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        gp_Pnt start(m_RotateAxisPoint1[0], m_RotateAxisPoint1[1], m_RotateAxisPoint1[2]);
        gp_Pnt end(m_RotateAxisPoint2[0], m_RotateAxisPoint2[1], m_RotateAxisPoint2[2]);
        if (start.Distance(end) <= Precision::Confusion()) {
            printLog(tr("The two ends of the axis of rotation can not coincide!"), 3);
            return false;
        }
        auto cmd = geoCmdList->getDataByID(m_SourceCurve.CmdId);
        if (cmd == nullptr) return false;
        Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
        auto vshape = cmd->getShapeT<FITKOCCTopoShape>(type, m_SourceCurve.VirtualTopoId);
        if (vshape == nullptr) return false;
        auto topoShape = vshape->getTopoShape();
        //m_OriginId;
        gp_Ax1 ax1(start, gp_Dir(end.XYZ() - start.XYZ()));

        // 如果是草绘则返回的是线的组合体，需要合并面
        if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND)
        {
            BRep_Builder builder;
            TopoDS_Compound compound;
            builder.MakeCompound(compound);
            TopExp_Explorer exp;

            // 按封闭曲线分组
            for (exp.Init(topoShape, TopAbs_EDGE); exp.More(); exp.Next())
            {
                TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                if (edge.IsNull()) continue;

                builder.Add(compound, edge);
            }
            topoShape = compound;
        }
        try {
            _occShapeAgent->updateShape(BRepPrimAPI_MakeRevol(topoShape, ax1, m_Angle  * M_PI / 180).Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }
        return true;
    }
    FITKOCCModelRectangularTrimmedSurface::FITKOCCModelRectangularTrimmedSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelRectangularTrimmedSurface::update()
    {
        return false;
    }
    FITKOCCModelSweepSurface::FITKOCCModelSweepSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelSweepSurface::update()
    {
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto profileCmd = geoCmdList->getDataByID(m_Profile.CmdId);
        auto curveCmd = geoCmdList->getDataByID(m_Curve.CmdId);
        if (profileCmd == nullptr || curveCmd == nullptr) return false;

        Interface::FITKGeoEnum::VTopoShapeType profileType = profileCmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
        auto profileShape = profileCmd->getShapeT<FITKOCCTopoShape>(profileType, m_Profile.VirtualTopoId);


        Interface::FITKGeoEnum::VTopoShapeType curveType = curveCmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
        auto curveShape = curveCmd->getShapeT<FITKOCCTopoShape>(curveType, m_Curve.VirtualTopoId);
        if (profileShape == nullptr || curveShape == nullptr) return false;
        auto profileTopoShape = profileShape->getTopoShape();
        auto curveTopoShape = curveShape->getTopoShape();


        TopoDS_Wire sweepWire;
        auto type = curveTopoShape.ShapeType();
        if (type == TopAbs_ShapeEnum::TopAbs_WIRE)
        {
            sweepWire = TopoDS::Wire(curveTopoShape);
        }
        else if (type == TopAbs_ShapeEnum::TopAbs_EDGE) {
            sweepWire = BRepBuilderAPI_MakeWire(TopoDS::Edge(curveTopoShape));
        }
        else if (type == TopAbs_ShapeEnum::TopAbs_COMPOUND) {
            TopoDS_Compound compound = TopoDS::Compound(curveTopoShape);
            TopExp_Explorer exp;
            BRepBuilderAPI_MakeWire makeWire;
            for (exp.Init(compound, TopAbs_EDGE); exp.More(); exp.Next())
            {
                TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                if (edge.IsNull()) continue;
                makeWire.Add(edge);
            }
            makeWire.Build();
            if (!makeWire.IsDone()) return false;
            sweepWire = TopoDS::Wire(makeWire.Shape());
        }
        else return false;

        // 如果是草绘则返回的是线的组合体，需要合并面
        if (profileTopoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND)
        {
            BRep_Builder builder;
            TopoDS_Compound compound;
            builder.MakeCompound(compound);
            TopExp_Explorer exp;

            // 按封闭曲线分组
            for (exp.Init(profileTopoShape, TopAbs_EDGE); exp.More(); exp.Next())
            {
                TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                if (edge.IsNull()) continue;

                builder.Add(compound, edge);
            }
            profileTopoShape = compound;
        }
        try {

            BRepOffsetAPI_MakePipe pipe(sweepWire, profileTopoShape);
            pipe.Build();
            if (!pipe.IsDone()) return false;

            _occShapeAgent->updateShape(pipe.Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }
        return true;
    }

    FITKOCCModelMultiSectionSurface::FITKOCCModelMultiSectionSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelMultiSectionSurface::update()
    {

        if (m_Sections.size() < 2) return false;

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        BRepOffsetAPI_ThruSections thruSection(false);

        for (auto section : m_Sections) {
            auto cmd = geoCmdList->getDataByID(section.CmdId);
            if (cmd == nullptr) return false;
            Interface::FITKGeoEnum::VTopoShapeType type = cmd->getGeometryCommandType() == Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D ? Interface::FITKGeoEnum::VTopoShapeType::VSAssembly : Interface::FITKGeoEnum::VTopoShapeType::VSEdge;
            auto vshape = cmd->getShapeT<FITKOCCTopoShape>(type, section.VirtualTopoId);
            if (vshape == nullptr) return false;
            auto topoShape = vshape->getTopoShape();

            if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE) {
                BRepLib_MakeWire wire(TopoDS::Edge(topoShape));
                thruSection.AddWire(wire.Wire());
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_WIRE) {
                thruSection.AddWire(TopoDS::Wire(topoShape));
            }
            else if (topoShape.ShapeType() == TopAbs_ShapeEnum::TopAbs_COMPOUND) {
                TopExp_Explorer exp;
                BRepLib_MakeWire wire;
                // 按封闭曲线分组
                for (exp.Init(topoShape, TopAbs_EDGE); exp.More(); exp.Next())
                {
                    TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                    if (edge.IsNull()) continue;
                    wire.Add(edge);
                }
                try
                {
                    wire.Build();
                    if (!wire.IsDone()) return false;
                    thruSection.AddWire(wire.Wire());
                }
                catch (...)
                {
                    printLog(tr("Failed to make wire!"), 3);
                    return false;
                }
            }
        }

        try {
            thruSection.Build();
            if (!thruSection.IsDone()) return false;
            _occShapeAgent->updateShape(thruSection.Shape());
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }
        return true;
    }

    FITKOCCModelBridgeSurface::FITKOCCModelBridgeSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelBridgeSurface::update()
    {
        if (m_SourceSurface1.isNull() || m_SourceSurface2.isNull()) return false;

        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        /** 第一条曲面端点 */
        /*@{*/
        auto surfaceCmd1 = geoCmdList->getDataByID(m_SourceSurface1.CmdId);
        if (surfaceCmd1 == nullptr) return false;
        auto faceVshape1 = surfaceCmd1->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, m_SourceSurface1.VirtualTopoId);
        auto edgeVShape1 = surfaceCmd1->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_EdgeVirtualTopoId1);
        if (faceVshape1 == nullptr || edgeVShape1 == nullptr) return false;
        TopoDS_Shape faceShape1 = faceVshape1->getTopoShape();
        if (faceShape1.ShapeType() != TopAbs_ShapeEnum::TopAbs_FACE) return false;
        TopoDS_Face face1 = TopoDS::Face(faceShape1);
        if (face1.IsNull()) return false;

        TopoDS_Shape edgeShape1 = edgeVShape1->getTopoShape();
        if (edgeShape1.ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE) return false;
        TopoDS_Edge edge1 = TopoDS::Edge(edgeShape1);
        if (edge1.IsNull()) return false;

        Standard_Real first1, last1;
        Handle(Geom_Curve) curve1 = BRep_Tool::Curve(edge1, first1, last1);

        gp_Pnt pnt1 = curve1->Value(first1);
        gp_Pnt pnt2 = curve1->Value(last1);

        TopoDS_Edge adjacentEdge11;
        TopoDS_Edge adjacentEdge12;
        // 邻接边
        TopExp_Explorer exp1;
        for (exp1.Init(face1, TopAbs_ShapeEnum::TopAbs_EDGE); exp1.More(); exp1.Next()) {
            TopoDS_Edge edge = TopoDS::Edge(exp1.Current());
            if (edge.IsNull()) return false;


            Standard_Real first, last;
            Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

            gp_Pnt firstPnt = curve->Value(first);
            gp_Pnt lastPnt = curve->Value(last);
            // 忽略要桥接的边
            if (
                (firstPnt.Distance(pnt1) < Precision::Confusion() && lastPnt.Distance(pnt2) < Precision::Confusion())
                || (firstPnt.Distance(pnt2) < Precision::Confusion() && lastPnt.Distance(pnt1) < Precision::Confusion())) {
                continue;
            }


            if (firstPnt.Distance(pnt1) < Precision::Confusion() || lastPnt.Distance(pnt1) < Precision::Confusion()) {
                adjacentEdge11 = edge;
            }
            else if (firstPnt.Distance(pnt2) < Precision::Confusion() || lastPnt.Distance(pnt2) < Precision::Confusion()) {
                adjacentEdge12 = edge;
            }
        }
        if (adjacentEdge11.IsNull() || adjacentEdge12.IsNull()) return false;

        /*@}*/

        /** 第二条曲面端点 */
        /*@{*/
        auto surfaceCmd2 = geoCmdList->getDataByID(m_SourceSurface2.CmdId);
        if (surfaceCmd2 == nullptr) return false;
        auto faceVshape2 = surfaceCmd2->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, m_SourceSurface2.VirtualTopoId);
        auto edgeVShape2 = surfaceCmd2->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_EdgeVirtualTopoId2);
        if (faceVshape2 == nullptr || edgeVShape2 == nullptr) return false;
        TopoDS_Shape faceShape2 = faceVshape2->getTopoShape();
        if (faceShape2.ShapeType() != TopAbs_ShapeEnum::TopAbs_FACE) return false;
        TopoDS_Face face2 = TopoDS::Face(faceShape2);
        if (face2.IsNull()) return false;

        TopoDS_Shape edgeShape2 = edgeVShape2->getTopoShape();
        if (edgeShape2.ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE) return false;
        TopoDS_Edge edge2 = TopoDS::Edge(edgeShape2);
        if (edge2.IsNull()) return false;

        Standard_Real first2, last2;
        Handle(Geom_Curve) curve2 = BRep_Tool::Curve(edge2, first2, last2);

        gp_Pnt pnt3 = curve2->Value(first2);
        gp_Pnt pnt4 = curve2->Value(last2);

        TopoDS_Edge adjacentEdge21;
        TopoDS_Edge adjacentEdge22;
        // 邻接边
        TopExp_Explorer exp2;
        for (exp2.Init(face2, TopAbs_ShapeEnum::TopAbs_EDGE); exp2.More(); exp2.Next()) {
            TopoDS_Edge edge = TopoDS::Edge(exp2.Current());
            if (edge.IsNull()) return false;
            Standard_Real first, last;
            Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);

            gp_Pnt firstPnt = curve->Value(first);
            gp_Pnt lastPnt = curve->Value(last);

            // 忽略要桥接的边
            if (
                (firstPnt.Distance(pnt3) < Precision::Confusion() && lastPnt.Distance(pnt4) < Precision::Confusion())
                || (firstPnt.Distance(pnt4) < Precision::Confusion() && lastPnt.Distance(pnt3) < Precision::Confusion())) {
                continue;
            }

            if (firstPnt.Distance(pnt3) < Precision::Confusion() || lastPnt.Distance(pnt3) < Precision::Confusion()) {
                adjacentEdge21 = edge;
            }
            else if (firstPnt.Distance(pnt4) < Precision::Confusion() || lastPnt.Distance(pnt4) < Precision::Confusion()) {
                adjacentEdge22 = edge;
            }
        }
        if (adjacentEdge21.IsNull() || adjacentEdge22.IsNull()) return false;
        /*@}*/

        /* 桥接Pnt1和Pnt3的样条曲线 */
        /*@{*/
        // 取Pnt1附近的点
        Standard_Real first, last;
        Handle(Geom_Curve) curve11 = BRep_Tool::Curve(adjacentEdge11, first, last);
        bool pnt1IsStart = curve11->Value(first).Distance(pnt1) < Precision::Confusion();
        gp_Vec vec11 = pnt1IsStart ? curve11->DN(first, 1) : curve11->DN(last, 1);
        //vec11.Scale(m_Parameter2 / last11.Magnitude());
        gp_Pnt adjustPnt1;
        if (pnt1IsStart)
            adjustPnt1 = gp_Pnt(pnt1.X() - vec11.X(), pnt1.Y() - vec11.Y(), pnt1.Z() - vec11.Z());
        else
            adjustPnt1 = gp_Pnt(pnt1.X() + vec11.X(), pnt1.Y() + vec11.Y(), pnt1.Z() + vec11.Z());
        // 取Pnt3附近的点
        Handle(Geom_Curve) curve22 = BRep_Tool::Curve(adjacentEdge21, first, last);
        bool pnt3IsStart = curve22->Value(first).Distance(pnt1) < Precision::Confusion();
        gp_Vec vec22 = pnt3IsStart ? curve22->DN(first, 1) : curve11->DN(last, 1);
        //vec11.Scale(m_Parameter2 / last11.Magnitude());
        gp_Pnt adjustPnt3;
        if (pnt3IsStart)
            adjustPnt3 = gp_Pnt(pnt3.X() - vec11.X(), pnt3.Y() - vec11.Y(), pnt3.Z() - vec11.Z());
        else
            adjustPnt3 = gp_Pnt(pnt3.X() + vec11.X(), pnt3.Y() + vec11.Y(), pnt3.Z() + vec11.Z());
        // 构造样条
        TColgp_Array1OfPnt pnts13(1, 4);
        pnts13.SetValue(1, pnt1);
        pnts13.SetValue(2, adjustPnt1);
        pnts13.SetValue(3, adjustPnt3);
        pnts13.SetValue(4, pnt3);

        Standard_Integer KNum13 = 3;
        TColStd_Array1OfReal knots13(1, KNum13);
        for (int i = 0; i < KNum13; ++i)
        {
            knots13.SetValue(i + 1, i);
        }
        TColStd_Array1OfInteger mults13(1, KNum13);
        for (int i = 0; i < KNum13; ++i)
        {
            if (i == 0 || i == KNum13 - 1)
            {
                mults13.SetValue(i + 1, 3);
            }
            else
            {
                mults13.SetValue(i + 1, 1);
            }
        }

        Handle(Geom_BSplineCurve) hCurve13 = new Geom_BSplineCurve(pnts13, knots13, mults13, 2);
        GeomLib_Tool parameterTool;
        Standard_Real p1, p3;
        parameterTool.Parameter(hCurve13, pnt1, Precision::Confusion(), p1);
        parameterTool.Parameter(hCurve13, pnt3, Precision::Confusion(), p3);
        BRepBuilderAPI_MakeEdge anEdge13(hCurve13, p1, p3);
        if (!anEdge13.IsDone()) return false;
        /*@}*/


        /* 桥接Pnt2和Pnt4的样条曲线 */
        /*@{*/
        // 取Pnt2附近的点
        curve11 = BRep_Tool::Curve(adjacentEdge12, first, last);
        bool pnt2IsStart = curve11->Value(first).Distance(pnt2) < Precision::Confusion();
        vec11 = pnt2IsStart ? curve11->DN(first, 1) : curve11->DN(last, 1);
        //vec11.Scale(m_Parameter2 / last11.Magnitude());
        gp_Pnt adjustPnt2;
        if (pnt2IsStart)
            adjustPnt2 = gp_Pnt(pnt2.X() - vec11.X(), pnt2.Y() - vec11.Y(), pnt2.Z() - vec11.Z());
        else
            adjustPnt2 = gp_Pnt(pnt2.X() + vec11.X(), pnt2.Y() + vec11.Y(), pnt2.Z() + vec11.Z());
        // 取Pnt4附近的点
        curve22 = BRep_Tool::Curve(adjacentEdge22, first, last);
        bool pnt4IsStart = curve22->Value(first).Distance(pnt4) < Precision::Confusion();
        vec22 = pnt4IsStart ? curve22->DN(first, 1) : curve11->DN(last, 1);
        //vec11.Scale(m_Parameter2 / last11.Magnitude());
        gp_Pnt adjustPnt4;
        if (pnt4IsStart)
            adjustPnt4 = gp_Pnt(pnt4.X() - vec11.X(), pnt4.Y() - vec11.Y(), pnt4.Z() - vec11.Z());
        else
            adjustPnt4 = gp_Pnt(pnt4.X() + vec11.X(), pnt4.Y() + vec11.Y(), pnt4.Z() + vec11.Z());
        // 构造样条
        TColgp_Array1OfPnt pnts24(1, 4);
        pnts24.SetValue(1, pnt2);
        pnts24.SetValue(2, adjustPnt2);
        pnts24.SetValue(3, adjustPnt4);
        pnts24.SetValue(4, pnt4);

        Standard_Integer KNum24 = 3;
        TColStd_Array1OfReal knots24(1, KNum24);
        for (int i = 0; i < KNum24; ++i)
        {
            knots24.SetValue(i + 1, i);
        }
        TColStd_Array1OfInteger mults24(1, KNum24);
        for (int i = 0; i < KNum24; ++i)
        {
            if (i == 0 || i == KNum24 - 1)
            {
                mults24.SetValue(i + 1, 3);
            }
            else
            {
                mults24.SetValue(i + 1, 1);
            }
        }

        Handle(Geom_BSplineCurve) hCurve24 = new Geom_BSplineCurve(pnts24, knots24, mults24, 2);
        Standard_Real p2, p4;
        parameterTool.Parameter(hCurve24, pnt2, Precision::Confusion(), p2);
        parameterTool.Parameter(hCurve24, pnt4, Precision::Confusion(), p4);
        BRepBuilderAPI_MakeEdge anEdge24(hCurve24, p2, p4);
        if (!anEdge24.IsDone()) return false;
        /*@}*/

        BRepFill_Filling fillFace;
        fillFace.Add(edge1, GeomAbs_Shape::GeomAbs_C0, true);
        fillFace.Add(anEdge13, GeomAbs_Shape::GeomAbs_C0, true);
        fillFace.Add(edge2, GeomAbs_Shape::GeomAbs_C0, true);
        fillFace.Add(anEdge24, GeomAbs_Shape::GeomAbs_C0, true);

        try
        {
            fillFace.Build();
            if (!fillFace.IsDone()) return false;
            _occShapeAgent->updateShape(fillFace.Face());
            return true;
        }
        catch (...)
        {
            printLog("Failed to make face.", 3);
            return false;
        }


        /*Handle(GeomAdaptor_HCurve) SPL1Adaptor = new GeomAdaptor_HCurve(curve1);
        Handle(GeomFill_SimpleBound) B1 = new GeomFill_SimpleBound(SPL1Adaptor, Precision::Approximation(), Precision::Angular());

        Handle(GeomAdaptor_HCurve) SPL2Adaptor = new GeomAdaptor_HCurve(hCurve13);
        Handle(GeomFill_SimpleBound) B2 = new GeomFill_SimpleBound(SPL2Adaptor, Precision::Approximation(), Precision::Angular());

        Handle(GeomAdaptor_HCurve) SPL3Adaptor = new GeomAdaptor_HCurve(curve2);
        Handle(GeomFill_SimpleBound) B3 = new GeomFill_SimpleBound(SPL3Adaptor, Precision::Approximation(), Precision::Angular());

        Handle(GeomAdaptor_HCurve) SPL4Adaptor = new GeomAdaptor_HCurve(hCurve24);
        Handle(GeomFill_SimpleBound) B4 = new GeomFill_SimpleBound(SPL4Adaptor, Precision::Approximation(), Precision::Angular());

        int MaxDeg = 5;
        int MaxSeg = 2;
        GeomFill_ConstrainedFilling aConstrainedFilling(MaxDeg, MaxSeg);
        aConstrainedFilling.Init(B1, B2, B3, B4, false);

        Handle(Geom_BSplineSurface) aBSplineSurface = aConstrainedFilling.Surface();
        auto face = BRepBuilderAPI_MakeFace(aBSplineSurface, Precision::Approximation());



        _occShapeAgent->updateShape(face.Shape());

        _occShapeAgent->writeToFile("d:\\123.stp");
        _occShapeAgent->writeSTLFile("d:\\123.stl");

        return false;*/

        /*TColgp_Array2OfPnt pnts(1, 2, 1, 2);
        pnts.SetValue(1, 1, pnt1);
        pnts.SetValue(2, 1, pnt2);
        pnts.SetValue(1, 2, pnt3);
        pnts.SetValue(2, 2, pnt4);

        try {
            GeomAPI_PointsToBSplineSurface splineSurface(pnts);
            if (splineSurface.IsDone())
            {
                Handle(Geom_BSplineSurface) hSurface = splineSurface.Surface();

                BRepBuilderAPI_MakeFace anFace(hSurface, first1, last1, first2, last2, Precision::Confusion());

                _occShapeAgent->updateShape(anFace.Shape());
                return true;
            }
            else return false;
        }
        catch (...)
        {
            printLog(tr("Failed to make face!"), 3);
            return false;
        }*/
        /*Handle(Geom_BezierCurve) hCurve = new Geom_BezierCurve(pnts);
        GeomLib_Tool parameterTool;
        Standard_Real p1, p4;
        parameterTool.Parameter(hCurve, pnt1, Precision::Confusion(), p1);
        parameterTool.Parameter(hCurve, pnt4, Precision::Confusion(), p4);
        BRepBuilderAPI_MakeEdge anEdge(hCurve, p1, p4);
        _occShapeAgent->updateShape(anEdge.Shape());
        return true;*/
    }

    FITKOCCModelSolidSurface::FITKOCCModelSolidSurface() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelSolidSurface::update()
    {
        if (m_SourceSolid.isNull() || m_FaceVirtualTopoId < 0) return false;
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();
        /** 获取原始体形状 */
         /*@{*/
        auto solidCmd = geoCmdList->getDataByID(m_SourceSolid.CmdId);
        if (solidCmd == nullptr) return false;
        auto faceVShape = solidCmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, m_FaceVirtualTopoId);
        if (faceVShape == nullptr) return false;
        TopoDS_Shape faceShape = faceVShape->getTopoShape();
        if (faceShape.ShapeType() != TopAbs_ShapeEnum::TopAbs_FACE) return false;
        TopoDS_Face face = TopoDS::Face(faceShape);
        if (face.IsNull()) return false;
        /*@}*/

        /*if (face.IsNull()) return false;

        Handle(Geom_Surface) surface = BRep_Tool::Surface(face);
        if (surface.IsNull()) return false;

        BRepBuilderAPI_MakeFace anFace(surface, BRep_Tool::Tolerance(face));


        if (!anFace.IsDone()) {
            switch (anFace.Error())
            {
            case BRepBuilderAPI_FaceDone:
                printLog("Face Done", 3);
                break;
            case BRepBuilderAPI_NoFace:
                printLog("No Face", 3);
                break;
            case BRepBuilderAPI_NotPlanar:
                printLog("Not Planar", 3);
                break;
            case BRepBuilderAPI_CurveProjectionFailed:
                printLog("Curve Projection Failed", 3);
                break;
            case BRepBuilderAPI_ParametersOutOfRange:
                printLog("Parameters Out Of Range", 3);
                break;
            default:
                break;
            }
        }
        if (anFace.Shape().IsNull()) {
            printLog("Failed to make face.", 3);
            return false;
        }*/
        _occShapeAgent->updateShape(face);
        return true;
    }



}
