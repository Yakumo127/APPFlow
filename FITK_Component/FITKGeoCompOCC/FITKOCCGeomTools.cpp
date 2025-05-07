#include "FITKOCCGeomTools.h"

// OCC
#include <TopoDS.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <gp_Pln.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Circle.hxx>
#include <Geom_Ellipse.hxx>
#include <ShapeAnalysis_Surface.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAdaptor_Surface.hxx>

#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsVirtualTopo.h"
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractModel.h"
#include "FITKOCCVirtualTopoCreator.h"

namespace OCC
{
    Interface::FITKAbstractGeomPointTool* FITKOCCToolCreator::createPointTool()
    {
        //创建点工具
        return new FITKOCCPointTool;
    }

    Interface::FITKAbstractGeomEdgeTool* FITKOCCToolCreator::createEdgeTool()
    {
        //创建边工具
        return new FITKOCCEdgeTool;
    }

    Interface::FITKAbstractGeomFaceTool* FITKOCCToolCreator::createFaceTool()
    {
        //创建平面工具
        return new FITKOCCFaceTool;
    }

    // 点查询工具。
    //@{
    bool FITKOCCPointTool::getXYZ(Interface::FITKAbsVirtualTopo* topo, double* xyz, int iModelId)
    {
        if (topo == nullptr || xyz == nullptr) return false;
        if (topo->getShapeType() != Interface::FITKGeoEnum::VSPoint) return false;
        //获取形状数据
        FITKOCCTopoShape* occShape = topo->getShapeT<FITKOCCTopoShape>();
        if (occShape == nullptr) return false;
        const TopoDS_Shape& shape = occShape->getTopoShape();
        //获取坐标
        TopoDS_Vertex vertex = TopoDS::Vertex(shape);
        gp_Pnt pt = BRep_Tool::Pnt(vertex);
        xyz[0] = pt.X(); xyz[1] = pt.Y(); xyz[2] = pt.Z();

        // Try to transform the point.
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformPoint(xyz, xyz);
        }

        return true;
    }
    //@}

    // 边查询工具。
    //@{
    bool FITKOCCEdgeTool::getStartPointDirection(Interface::FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, int iModelId)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }

        Standard_Real first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
        if (!curve)
        {
            return false;
        }

        gp_Pnt startPt;
        gp_Vec startDir;
        curve->D1(first, startPt, startDir);

        // 翻转。
        if (edge.Orientation() == TopAbs_Orientation::TopAbs_REVERSED)
        {
            startDir.Reverse();
        }

        for (int i = 0; i < 3; i++)
        {
            oPos[i] = startPt.Coord(i + 1);
            oDir[i] = startDir.Coord(i + 1);
        }

        // 变换坐标与方向。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformDirection(oDir, oDir);
            model->transformPoint(oPos, oPos);
        }

        return true;
    }

    bool FITKOCCEdgeTool::getEndPointDirection(Interface::FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, int iModelId)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }

        Standard_Real first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
        if (!curve)
        {
            return false;
        }

        gp_Pnt lastPt;
        gp_Vec lastDir;
        curve->D1(last, lastPt, lastDir);

        // 翻转。
        if (edge.Orientation() == TopAbs_Orientation::TopAbs_REVERSED)
        {
            lastDir.Reverse();
        }

        for (int i = 0; i < 3; i++)
        {
            oPos[i] = lastPt.Coord(i + 1);
            oDir[i] = lastDir.Coord(i + 1);
        }

        // 变换坐标与方向。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformDirection(oDir, oDir);
            model->transformPoint(oPos, oPos);
        }

        return true;
    }

    bool FITKOCCEdgeTool::getDirection(Interface::FITKAbsVirtualTopo* vtp, double* oPos, double* oDir, double iU, int iModelId)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }

        Standard_Real first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
        if (!curve)
        {
            return false;
        }

        gp_Pnt pt;
        gp_Vec dir;
        curve->D1(iU, pt, dir);

        // 翻转。
        if (edge.Orientation() == TopAbs_Orientation::TopAbs_REVERSED)
        {
            dir.Reverse();
        }

        for (int i = 0; i < 3; i++)
        {
            oPos[i] = pt.Coord(i + 1);
            oDir[i] = dir.Coord(i + 1);
        }

        // 变换坐标与方向。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformDirection(oDir, oDir);
            model->transformPoint(oPos, oPos);
        }

        return true;
    }

    bool FITKOCCEdgeTool::isLine(Interface::FITKAbsVirtualTopo* vtp)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }
         
        BRepAdaptor_Curve baCurve(edge);
        return baCurve.GetType() == GeomAbs_CurveType::GeomAbs_Line;
    }

    bool FITKOCCEdgeTool::getLength(Interface::FITKAbsVirtualTopo* vtp, double & oLen)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }

        // 获取长度。
        GProp_GProps props;
        BRepGProp::LinearProperties(edge, props);
        oLen = props.Mass();

        return true;
    }

    bool FITKOCCEdgeTool::getMidPoint(Interface::FITKAbsVirtualTopo* vtp, double* oPos, int iModelId)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }

        // 获取曲线。
        double first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
        if (!curve)
        {
            return false;
        }

        gp_Pnt midPt;
        curve->D0(first + (last - first) * 0.5, midPt);
        oPos[0] = midPt.Coord(1);
        oPos[1] = midPt.Coord(2);
        oPos[2] = midPt.Coord(3);

        // 变换坐标。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformPoint(oPos, oPos);
        }

        return true;
    }

    bool FITKOCCEdgeTool::getFeaturePoints(Interface::FITKAbsVirtualTopo* vtp, QList<QList<double>> & oPoses, int iModelId)
    {
        if (!vtp)
        {
            return false;
        }

        // 检查拓扑类型。
        if (vtp->getShapeType() != Interface::FITKGeoEnum::VSEdge)
        {
            return false;
        }

        // 获取形状。
        FITKOCCTopoShape* vShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!vShape)
        {
            return false;
        }

        const TopoDS_Edge & edge = TopoDS::Edge(vShape->getTopoShape());
        if (edge.IsNull())
        {
            return false;
        }

        // 获取曲线。
        double first, last;
        Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
        if (!curve)
        {
            return false;
        }

        double pos3[3]{ 0., 0., 0. };

        // 获取中点。
        gp_Pnt midPt;
        curve->D0(first + (last - first) * 0.5, midPt);
        pos3[0] = midPt.Coord(1);
        pos3[1] = midPt.Coord(2);
        pos3[2] = midPt.Coord(3);

        // 变换坐标。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformPoint(pos3, pos3);
        }

        // 保存坐标。
        oPoses.push_back(QList<double>{ pos3[0], pos3[1], pos3[2] });

        // 获取各类型曲线特征点。
        BRepAdaptor_Curve baCurve(edge);
        GeomAbs_CurveType curveType = baCurve.GetType();
        switch (curveType)
        {
        case GeomAbs_Circle:
        case GeomAbs_Ellipse:
        {
            Handle(Geom_Conic) conic = Handle(Geom_Conic)::DownCast(curve);
            if (!conic)
            {
                break;
            }

            // 获取(椭)圆心坐标。
            const gp_Pnt & center = conic->Position().Location();
            pos3[0] = center.Coord(1);
            pos3[1] = center.Coord(2);
            pos3[2] = center.Coord(3);

            // 变换坐标。
            if (model)
            {
                model->transformPoint(pos3, pos3);
            }

            // 保存坐标。
            oPoses.push_back(QList<double>{ pos3[0], pos3[1], pos3[2] });

            break;
        }
        case GeomAbs_Hyperbola:
            break;
        case GeomAbs_Parabola:
            break;
        case GeomAbs_BezierCurve:
            break;
        case GeomAbs_BSplineCurve:
            break;
        case GeomAbs_Line:
        case GeomAbs_OffsetCurve:
        case GeomAbs_OtherCurve:
        default:
            break;
        }

        return true;
    }
    //@}

    // 面查询工具。
    //@{
    bool FITKOCCFaceTool::getPlane(Interface::FITKAbsVirtualTopo* vtp, double* pos, double* normal, double* up, int iModelId)
    {
        if (!vtp || !pos || !normal || !up)
        {
            return false;
        }

        // 获取抽象形状。
        FITKOCCTopoShape* occShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!occShape)
        {
            return false;
        }

        // 获取面。
        const TopoDS_Shape& shape = occShape->getTopoShape();
        TopoDS_Face face = TopoDS::Face(shape);
        if (face.IsNull())
        {
            return false;
        }

        // 判断是否为平面。
        BRepAdaptor_Surface baSurf(face);
        if (baSurf.GetType() != GeomAbs_SurfaceType::GeomAbs_Plane)
        {
            return false;
        }

        // 获取信息。
        gp_Pln gpPln = baSurf.Plane();
        gp_Pnt gpPos = gpPln.Location();
        gp_Dir gpNor = gpPln.Position().Direction();
        gp_Dir gpUp = gpPln.Position().YDirection();

        // 翻转。
        if (shape.Orientation() == TopAbs_Orientation::TopAbs_REVERSED)
        {
            gpNor.Reverse();
            gpUp.Reverse();
        }

        // 返回数据。
        for (int i = 0; i < 3; i++)
        {
            pos[i] = gpPos.Coord(i + 1);
            normal[i] = gpNor.Coord(i + 1);
            up[i] = gpUp.Coord(i + 1);
        }

        // 变换坐标与方向。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformPoint(pos, pos);
            model->transformDirection(normal, normal);
            model->transformDirection(up, up);
        }

        return true;
    }

    bool FITKOCCFaceTool::getNormal(Interface::FITKAbsVirtualTopo* vtp, double* iPos, double* oNormal, int iModelId)
    {
        if (!vtp || !iPos || !oNormal)
        {
            return false;
        }

        // 获取抽象形状。
        FITKOCCTopoShape* occShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!occShape)
        {
            return false;
        }

        // 获取面。
        const TopoDS_Shape & shape = occShape->getTopoShape();
        const TopoDS_Face & face = TopoDS::Face(shape);
        if (face.IsNull())
        {
            return false;
        }

        // 判断是否为平面。
        BRepAdaptor_Surface baSurf(face);
        if (baSurf.GetType() != GeomAbs_SurfaceType::GeomAbs_Plane)
        {
            return false;
        }

        // 获取信息。
        gp_Pln gpPln = baSurf.Plane();
        gp_Pnt gpPos = gpPln.Location();
        gp_Dir gpNor = gpPln.Position().Direction();
        gp_Dir gpUp = gpPln.Position().YDirection();

        // 翻转。
        if (shape.Orientation() == TopAbs_Orientation::TopAbs_REVERSED)
        {
            gpNor.Reverse();
            gpUp.Reverse();
        }

        gp_Pnt iPt(iPos[0], iPos[1], iPos[2]);
        Handle(Geom_Surface) surface = BRep_Tool::Surface(face);
        ShapeAnalysis_Surface surfTool(surface);
        gp_Pnt2d uv = surfTool.ValueOfUV(iPt, 1e-3);

        if (surfTool.Gap() > 1e-3) 
        {
            return false;
        }

        gp_Vec du, dv;
        double u = uv.X();
        double v = uv.Y();
        surface->D1(u, v, iPt, du, dv);

        // 叉积取方向。
        gp_Vec normalVec = du.Crossed(dv);
        if (normalVec.SquareMagnitude() < gp::Resolution()) 
        {
            return false;
        }

        normalVec.Normalize();
        normalVec = gp_Dir(normalVec);

        // 返回数据。
        for (int i = 0; i < 3; i++)
        {
            oNormal[i] = normalVec.Coord(i + 1);
        }

        // 变换坐标与方向。
        Interface::FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(iModelId);
        if (model)
        {
            model->transformDirection(oNormal, oNormal);
        }

        return true;
    }

    bool FITKOCCFaceTool::isPlane(Interface::FITKAbsVirtualTopo* vtp)
    {
        if (!vtp)
        {
            return false;
        }

        // 获取抽象形状。
        FITKOCCTopoShape* occShape = vtp->getShapeT<FITKOCCTopoShape>();
        if (!occShape)
        {
            return false;
        }

        // 获取面。
        const TopoDS_Shape& shape = occShape->getTopoShape();
        TopoDS_Face face = TopoDS::Face(shape);
        if (face.IsNull())
        {
            return false;
        }

        // 判断是否为平面。
        BRepAdaptor_Surface baSurf(face);
        if (baSurf.GetType() != GeomAbs_SurfaceType::GeomAbs_Plane)
        {
            return false;
        }

        return true;
    }
    //@}
}
