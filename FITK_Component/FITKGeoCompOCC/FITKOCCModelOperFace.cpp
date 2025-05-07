#include "FITKOCCModelOperFace.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"

// Geometry
#include "FITKOCCVirtualTopoCreator.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsVirtualTopoMapper.h"
//OCC
#include <BRepTools_ReShape.hxx>
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
#include <BRepOffsetAPI_Sewing.hxx>
#include <ShapeUpgrade_UnifySameDomain.hxx>

#include <TopExp_Explorer.hxx>
#include <BRep_Builder.hxx>
#include <ShapeFix_Shell.hxx>
#include <BRepFill_Filling.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>

// Global data
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

#include <QDebug>
namespace OCC
{
    FITKOCCModelOperFace::FITKOCCModelOperFace() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCModelOperFace::update()
    {
        if (m_tempVShapes.size() < 1) return false;
        QList<TopoDS_Shape> shapes;
        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            //数据获取
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr) return false;

            OCC::FITKOCCTopoShape* vOCCShapeEdge = comm->getShapeT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_tempVShapes[i].VirtualTopoId);
            if (vOCCShapeEdge == nullptr) return false;

            shapes.append(vOCCShapeEdge->getTopoShape());
        }

        //按类型处理
        if (_faceOperType == Interface::FITKAbsGeoModelOperFace::GBTFillHoles)
        {
            return updateFillHoles(shapes);
        }
        else if (_faceOperType == Interface::FITKAbsGeoModelOperFace::GBTImprintMapPointToFace)
        {
            return updateImprintMapPointToFace(shapes);
        }
        else if (_faceOperType == Interface::FITKAbsGeoModelOperFace::GBTImprintMapLineToFace)
        {
            return updateImprintMapLineToFace(shapes);
        }
        else if (_faceOperType == Interface::FITKAbsGeoModelOperFace::GBTImprintMapCircleToFace)
        {
            return updateImprintMapCircleToFace(shapes);
        }
        return false;
    }

    bool FITKOCCModelOperFace::updateFillHoles(QList<TopoDS_Shape> shapes)
    {
        TopoDS_Face face;
        QList<TopoDS_Edge> holes;

        //数据筛选
        for (int i = 0; i < shapes.size(); ++i)
        {
            if (shapes[i].ShapeType() == TopAbs_ShapeEnum::TopAbs_FACE && face.IsNull())
                face = TopoDS::Face(shapes[i]);
            else if (shapes[i].ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE)
                holes.append(TopoDS::Edge(shapes[i]));
            else
                return false;
        }
        if (face.IsNull() || holes.size() < 1) return false;

        BRepFill_Filling fill;
        fill.LoadInitSurface(face);
        for (int i = 0; i < holes.size(); ++i)
        {
            fill.Add(holes[i], GeomAbs_Shape::GeomAbs_C0);
        }
        fill.Build();
        auto topoDsShape = fill.Face();
        TopoDS_Compound aComp;
        BRep_Builder BuildTool;
        BuildTool.MakeCompound(aComp);
        BuildTool.Add(aComp, face);
        BuildTool.Add(aComp, topoDsShape);
        //缝合
        BRepOffsetAPI_Sewing sewing;
        //缝合初始化
        sewing.Init(_tolerance, Standard_True);

        sewing.Load(aComp);
        sewing.Perform();
        //检查是否修改成功
        if (!sewing.IsModified(sewing.SewedShape())) return false;
        //消除缝合线
        ShapeUpgrade_UnifySameDomain unif(sewing.SewedShape(), true, true, false);
        unif.Build();
        _occShapeAgent->updateShape(unif.Shape());
        return true;
    }

    bool FITKOCCModelOperFace::updateImprintMapPointToFace(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() != 2) return false;
        TopoDS_Face face;
        TopoDS_Vertex point;

        if (shapes[0].ShapeType() == TopAbs_ShapeEnum::TopAbs_FACE)
        {
            face = TopoDS::Face(shapes[0]);
            point = TopoDS::Vertex(shapes[1]);
        }
        else
        {
            point = TopoDS::Vertex(shapes[0]);
            face = TopoDS::Face(shapes[1]);
        }

        if (point.IsNull() || face.IsNull()) return false;




        return false;
    }

    bool FITKOCCModelOperFace::updateImprintMapLineToFace(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() != 2) return false;

        return false;
    }

    bool FITKOCCModelOperFace::updateImprintMapCircleToFace(QList<TopoDS_Shape> shapes)
    {
        return false;
    }

    ///////////////FITKOCCModelOperFaceFillHoles///////////////////////////

    FITKOCCModelOperFaceFillHoles::FITKOCCModelOperFaceFillHoles() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelOperFaceFillHoles::update()
    {
        if (m_tempVShapes.size() < 1) return false;
        QList<TopoDS_Shape> shapes;
        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            //数据获取
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr) return false;

            OCC::FITKOCCTopoShape* vOCCShapeEdge = comm->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_tempVShapes[i].VirtualTopoIndex);
            if (vOCCShapeEdge == nullptr) return false;

            shapes.append(vOCCShapeEdge->getTopoShape());
        }

        return updateFillHoles(shapes);
    }
    bool FITKOCCModelOperFaceFillHoles::updateFillHoles(QList<TopoDS_Shape> shapes)
    {
        TopoDS_Face face;
        QList<TopoDS_Edge> holes;

        //数据筛选
        for (int i = 0; i < shapes.size(); ++i)
        {
            if (shapes[i].ShapeType() == TopAbs_ShapeEnum::TopAbs_FACE && face.IsNull())
                face = TopoDS::Face(shapes[i]);
            else if (shapes[i].ShapeType() == TopAbs_ShapeEnum::TopAbs_EDGE)
                holes.append(TopoDS::Edge(shapes[i]));
            else
                return false;
        }
        if (face.IsNull() || holes.size() < 1) return false;

        BRepFill_Filling fill;
        fill.LoadInitSurface(face);
        for (int i = 0; i < holes.size(); ++i)
        {
            fill.Add(holes[i], GeomAbs_Shape::GeomAbs_C0);
        }
        fill.Build();
        auto topoDsShape = fill.Face();
        TopoDS_Compound aComp;
        BRep_Builder BuildTool;
        BuildTool.MakeCompound(aComp);
        BuildTool.Add(aComp, face);
        BuildTool.Add(aComp, topoDsShape);
        //缝合
        BRepOffsetAPI_Sewing sewing;
        //缝合初始化
        sewing.Init(_tolerance, Standard_True);

        sewing.Load(aComp);
        sewing.Perform();
        //检查是否修改成功
        if (!sewing.IsModified(sewing.SewedShape())) return false;
        //消除缝合线
        ShapeUpgrade_UnifySameDomain unif(sewing.SewedShape(), true, true, false);
        unif.Build();
        _occShapeAgent->updateShape(unif.Shape());
        return true;
    }

    ///////////////FITKOCCModelOperFaceFillGaps///////////////////////////

    FITKOCCModelOperFaceFillGaps::FITKOCCModelOperFaceFillGaps() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelOperFaceFillGaps::update()
    {
        if (m_tempVShapes.size() < 1) return false;
        QList<TopoDS_Shape> shapes;
        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            //数据获取
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr) return false;

            OCC::FITKOCCTopoShape* vOCCShapeEdge = comm->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, m_tempVShapes[i].VirtualTopoIndex);
            if (vOCCShapeEdge == nullptr) return false;

            shapes.append(vOCCShapeEdge->getTopoShape());
        }

        return updateFillGaps(shapes);
    }

    bool FITKOCCModelOperFaceFillGaps::updateFillGaps(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() < 1) return false;
        //主面
        TopoDS_Face mFace;
        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr) return false;

            // 向上查找所选边对应体数据。
            auto vTopoManager = comm->getVirtualTopoManager()->getShapeVirtualTopoManager(Interface::FITKGeoEnum::VTopoShapeType::VSFace);

            // 获取查询结果。
            for (int i = 0; i < vTopoManager->getDataCount(); i++)
            {
                Interface::FITKAbsVirtualTopo* vFace = vTopoManager->getDataByIndex(i);
                auto occShape = vFace->getShapeT<OCC::FITKOCCTopoShape>();
                if (occShape == nullptr) return false;
                mFace = TopoDS::Face(occShape->getTopoShape());
            }
        }
        //主面判断是否为空（填充面）
        if (mFace.IsNull() || mFace.ShapeType() != TopAbs_ShapeEnum::TopAbs_FACE)
        {
            printLog(tr("data retrieval error."), 3);
            return false;
        }

        bool isSuccessful = false;
        auto tempWireShape = CheckAndForceCurveClosure(shapes, isSuccessful);
        if (!isSuccessful || tempWireShape.IsNull()) return false;
        TopoDS_Wire closedCurve = TopoDS::Wire(tempWireShape);
        if (closedCurve.IsNull()) return false;
        TopoDS_Face nFace = BRepBuilderAPI_MakeFace(closedCurve);

        //TopoDS_Compound aComp;
        //BRep_Builder BuildTool;
        //BuildTool.MakeCompound(aComp);
        //BuildTool.Add(aComp, mFace);
        //BuildTool.Add(aComp, nFace);

        ////使用 BRepBuilderAPI_Sewing 缝合
        BRepOffsetAPI_Sewing sewing;
        //sewing.Init(1, Standard_True);
        //sewing.Load(aComp);
        sewing.Add(mFace);
        sewing.Add(nFace);
        sewing.Perform();
        auto sewingFace = sewing.SewedShape();
        //检查是否修改成功
        if (sewing.IsModified(sewingFace)) return false;
        //消除缝合线 统一拓扑
        ShapeUpgrade_UnifySameDomain unif(sewingFace, false, true, false);
        unif.Build();
        _occShapeAgent->updateShape(unif.Shape());
        return true;

        //TopTools_ListOfShape aLSObjects; //进行连接的形状
        //aLSObjects.Append(shape1);
        //aLSObjects.Append(shape2);

        //BOPAlgo_Builder aBuilder;
        //aBuilder.SetArguments(aLSObjects);
        ////设置GF的选项
        ////设置并行处理模式（默认为false）
        //Standard_Boolean bRunParallel = Standard_True;
        //aBuilder.SetRunParallel(bRunParallel);
        ////设置模糊值（默认为Precision :: Confusion（））  
        //Standard_Real aFuzzyValue = 1e-5;
        //aBuilder.SetFuzzyValue(aFuzzyValue);
        ////设置安全处理模式（默认为false）
        //Standard_Boolean bSafeMode = Standard_True;
        //aBuilder.SetNonDestructive(bSafeMode);
        ////为重合的参数设置粘合模式（默认为关闭）
        //BOPAlgo_GlueEnum aGlue = BOPAlgo_GlueShift;
        //aBuilder.SetGlue(aGlue);
        ////禁用/启用对倒置固体的检查（默认为true）
        //Standard_Boolean bCheckInverted = Standard_False;
        //aBuilder.SetCheckInverted(bCheckInverted);
        ////设置OBB用法（默认为false）
        //Standard_Boolean bUseOBB = Standard_True;
        //aBuilder.SetUseOBB(bUseOBB);
        ////执行操作 
        //aBuilder.Perform();
        ////检查错误
        //if (aBuilder.HasErrors()) return TopoDS_Shape();
        //if (aBuilder.HasWarnings()) return TopoDS_Shape();
        //// result of the operation
        //return aBuilder.Shape();
    }

    TopoDS_Shape FITKOCCModelOperFaceFillGaps::CheckAndForceCurveClosure(QList<TopoDS_Shape> shapes, bool& isSuccessful)
    {
        isSuccessful = false;
        BRepBuilderAPI_MakeWire mergeWires;
        TopTools_ListOfShape edgeList;
        for (int i = 0; i < shapes.size(); i++)
        {
            //if (shapes[i].ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE) return TopoDS_Shape;
            qDebug() << "shape Type : " << shapes[i].ShapeType();
            TopoDS_Edge edge = TopoDS::Edge(shapes[i]);
            if (edge.IsNull()) return TopoDS_Shape();
            edgeList.Append(edge);
        }
        mergeWires.Add(edgeList);
        mergeWires.Build();
        if (!mergeWires.IsDone())
        {
            printLog(tr("parameter check error."), 3);
            return TopoDS_Shape();
        }
        isSuccessful = true;
        return mergeWires.Shape();
    }

    ///////////////FITKOCCModelOperFaceDeleteFloatingEdge///////////////////////////

    FITKOCCModelOperFaceDeleteFloatingEdge::FITKOCCModelOperFaceDeleteFloatingEdge() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelOperFaceDeleteFloatingEdge::update()
    {
        if (m_tempVShapes.size() < 1) return false;
        QList<TopoDS_Shape> shapes;
        for (int i = 0; i < m_tempVShapes.size(); ++i)
        {
            if (m_tempVShapes[i].CmdId == 0) continue;
            //数据获取
            FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<FITKAbsGeoCommand>(m_tempVShapes[i].CmdId);
            if (comm == nullptr)
            {
                printLog(tr("data retrieval error."), 3);
                return false;
            }
            //OCC::FITKOCCTopoShape* vOCCShapeFace = comm->getShapeT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, m_tempVShapes[i].VirtualTopoId);

            auto model = comm->getTShapeAgent<FITKAbstractOCCModel>();

            TopoDS_Compound aComp;
            BRep_Builder BuildTool;
            BuildTool.MakeCompound(aComp);

            auto sVManager = comm->getVirtualTopoManager()->getShapeVirtualTopoManager(Interface::FITKGeoEnum::VTopoShapeType::VSEdge);
            for (int i = 0; i < sVManager->getDataCount(); i++)
            {
                bool isReusePoint = false;
                auto vObject = sVManager->getDataByIndex(i);
                int subCount = vObject->getSubTopoCount();
                for (int j = 0; j < subCount; j++)
                {
                    auto childVTopo = vObject->getSubTopo(j);
                    int parentVTopoCount = childVTopo->getParentTopoCount();
                    isReusePoint = parentVTopoCount == 1;
                }
                if (isReusePoint) BuildTool.Add(aComp, *vObject->getShapeT<FITKAbstractOCCModel>()->getShape());
            }

            if (aComp.IsNull()) return false;
            BRepTools_ReShape reShape;
            reShape.Remove(aComp);
            auto rShape = reShape.Apply(*model->getShape());
            _occShapeAgent->updateShape(rShape);
            return true;
        }
        return false;
    }

    bool FITKOCCModelOperFaceDeleteFloatingEdge::updateDeleteFloatingEdge(QList<TopoDS_Shape> shapes)
    {
        if (shapes.size() < 1 || shapes[0].IsNull())
        {
            printLog(tr("parameter error."), 3);
            return false;
        }
        BRepTools_ReShape reShape;
        reShape.Remove(shapes[0]);

        //消除缝合线 统一拓扑
        ShapeUpgrade_UnifySameDomain unif(shapes[0], true, true, false);
        TopTools_MapOfShape shapeList;
        for (int i = 1; i < shapes.size(); i++)
        {
            shapeList.Add(shapes[i]);
        }
        unif.KeepShapes(shapeList);
        unif.Build();

        _occShapeAgent->updateShape(unif.Shape());
        return true;
    }
}