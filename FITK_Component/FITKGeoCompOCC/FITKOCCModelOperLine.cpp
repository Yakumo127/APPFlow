#include "FITKOCCModelOperLine.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"
#include <TopoDS.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Compound.hxx>

#include <gp_Pnt.hxx>
#include <BRepLib.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeBuild.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>

// Global data
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

// Geometry
#include "FITKOCCVirtualTopoCreator.h"

#include <QDebug>
namespace OCC
{
    FITKOCCModelOperLine::FITKOCCModelOperLine() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelOperLine::update()
    {
        if (m_tempVShapes.size() < 1) return false;
        QList<TopoDS_Shape> shapeLines;

        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            //数据获取
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr) return false;
            OCC::FITKOCCTopoShape* vOCCShapeEdge = comm->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_tempVShapes[i].VirtualTopoIndex);
            if (vOCCShapeEdge == nullptr) return false;

            shapeLines.append(vOCCShapeEdge->getTopoShape());
        }
        //按类型处理
        if (_lineOperType == Interface::FITKAbsGeoModelOperLine::GBTMerge)
        {
            return updateMerge(shapeLines);
        }
        if (_lineOperType == Interface::FITKAbsGeoModelOperLine::GBTSplitByAngle)
        {
            return updateSplitByAngle(shapeLines);
        }
        return false;
    }

    bool FITKOCCModelOperLine::updateMerge(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() < 1) return false;

        BRepBuilderAPI_MakeWire mergeWires;
        for (int i = 0; i < shapes.size(); i++)
        {
            TopoDS_Edge edge = TopoDS::Edge(shapes[i]);
            if (edge.IsNull()) return false;
            mergeWires.Add(BRepBuilderAPI_MakeWire(edge));
        }
        mergeWires.Build();
        qDebug() << mergeWires.Error();
        if (!mergeWires.IsDone()) return false;
        _occShapeAgent->updateShape(mergeWires);
        return true;
    }
    
    bool FITKOCCModelOperLine::updateSplitByAngle(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() != 1) return false;
        if (shapes[0].ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE && shapes[0].ShapeType() != TopAbs_ShapeEnum::TopAbs_WIRE) return false;



        return true;
    }


    FITKOCCModelMiddleOperLine::FITKOCCModelMiddleOperLine() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelMiddleOperLine::update()
    {
        if (m_tempVShapes.size() < 1) return false;
        QList<TopoDS_Shape> shapeLines;

        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            //数据获取
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr) return false;

            OCC::FITKOCCTopoShape* vOCCShapeEdge = comm->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_tempVShapes[i].VirtualTopoIndex);
            if (vOCCShapeEdge == nullptr) return false;

            shapeLines.append(vOCCShapeEdge->getTopoShape());
        }

        return updateSplitByMiddlePosition(shapeLines);
    }

    bool FITKOCCModelMiddleOperLine::updateSplitByMiddlePosition(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() != 1) return false;
        //暂时只处理了edge
        if (shapes[0].ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE /*&& shapes[0].ShapeType() != TopAbs_ShapeEnum::TopAbs_WIRE*/) return false;

        TopoDS_Edge edge = TopoDS::Edge(shapes[0]);
        if (edge.IsNull()) return false;
        TopoDS_Edge partOfEOne, partOfETwo;
        Standard_Real startParam(0.), endParam(0.);
        Handle(Geom_Curve) c = BRep_Tool::Curve(edge, startParam, endParam);//得到底层曲线
        //底层曲线没有创建，要手动创建
        if (c.IsNull())
        {
            BRepLib::BuildCurves3d(edge, 1.0e-5, GeomAbs_C1);//创建曲线
            c = BRep_Tool::Curve(edge, startParam, endParam);
        }
        //简单分割方法，该方法分割的可能不是均匀的曲线
        if (!c.IsNull())
        {
            //截取曲线并创建边
            Handle(Geom_TrimmedCurve) tc1 = new Geom_TrimmedCurve(c, startParam, (startParam + endParam) * 0.5);//截取边的的一半
            partOfEOne = BRepBuilderAPI_MakeEdge(tc1);
            //截取曲线并创建边
            Handle(Geom_TrimmedCurve) tc2 = new Geom_TrimmedCurve(c, (startParam + endParam) * 0.5, endParam);//截取边的的一半
            partOfETwo = BRepBuilderAPI_MakeEdge(tc2);
            _occShapeAgent->updateShape(BRepBuilderAPI_MakeWire(partOfEOne, partOfETwo));
            return true;
        }
        return false;
    }

}