#include "FITKOCCReferencePlane.h"

#include <FITK_Interface/FITKInterfaceGeometry/FITKGeoEnum.h>
#include <FITK_Interface/FITKInterfaceGeometry/FITKVirtualTopoManager.h>
#include "FITKOCCVirtualTopoCreator.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSurface.h"

#include <TopoDS.hxx>
#include <TopoDS_Face.hxx>
#include <Geom_Plane.hxx>
#include <BRep_Tool.hxx>
#include <gp_Vec.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Shell.hxx>
#include <TopExp_Explorer.hxx>
#include <gce_MakePln.hxx>


namespace OCC {
    FITKOCCReferencePlane::FITKOCCReferencePlane() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCReferencePlane::update()
    {
        return false;
    }

    FITKOCCReferenceOffsetPlane::FITKOCCReferenceOffsetPlane() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCReferenceOffsetPlane::update()
    {
        auto geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        auto cmd = geoCmdList->getDataByID(m_SourceSurface.CmdId);
        // 实体面
        if (cmd == nullptr) {
            // 基准面
            cmd = geoCmdList->getDatumManager()->getDataByID(m_SourceSurface.CmdId);
            if (cmd == nullptr) return false;
        }
        auto vshape = cmd->getShapeT<FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, m_SourceSurface.VirtualTopoId);
        if (vshape == nullptr) return false;
        auto topoShape = vshape->getTopoShape();
        if (topoShape.IsNull() || topoShape.ShapeType() != TopAbs_FACE) return false;

        Handle(Geom_Surface) surface = BRep_Tool::Surface(TopoDS::Face(topoShape));
        if (surface.IsNull() || surface->DynamicType() != STANDARD_TYPE(Geom_Plane)) return false;
        Handle(Geom_Plane) plane = Handle(Geom_Plane)::DownCast(surface);

        auto dir = plane->Position().Direction();
        gp_Dir normalDir(dir.X(), dir.Y(), dir.Z());
        gp_Dir direction(m_Direction[0], m_Direction[1], m_Direction[2]);

        if (!normalDir.IsParallel(direction, Precision::Angular())) {
            printLog(tr("The offset direction must be parallel to the source plane normal."), 3);
            return false;
        }
        // 反向
        if (normalDir.IsOpposite(direction, Precision::Angular())) {
            m_Offset *= -1;
        }

        BRepOffset_MakeOffset offsetSurface(topoShape, m_Offset, 1e-6);
        auto newShape = offsetSurface.Shape();
        if (newShape.IsNull()) return false;

        if (newShape.ShapeType() == TopAbs_FACE)
        {
            TopoDS_Face face = TopoDS::Face(newShape);
            if (face.IsNull()) return false;
            Handle(Geom_Surface) surface = BRep_Tool::Surface(face);
            auto type = surface->DynamicType();
            if (surface.IsNull() || surface->DynamicType() != STANDARD_TYPE(Geom_Plane)) return false;
            Handle(Geom_Plane) plane = Handle(Geom_Plane)::DownCast(surface);
            auto pos = plane->Position();
            auto loc = plane->Position().Location();
            auto direction = plane->Position().Direction();
            auto yDirection = plane->Position().YDirection();
            setPosition(loc.X(), loc.Y(), loc.Z());
            setNormal(direction.X(), direction.Y(), direction.Z());
            setUp(yDirection.X(), yDirection.Y(), yDirection.Z());
            try
            {
                gp_Pln pln(gp_Pnt(m_pos[0], m_pos[1], m_pos[2]), gp_Dir(m_nor[0], m_nor[1], m_nor[2]));

                BRepBuilderAPI_MakeFace face(pln);
                _occShapeAgent->updateShape(face);
                return true;
            }
            catch (...)
            {
                printLog(tr("Failed to make plane."), 3);
                return false;
            }
        }
        else if (newShape.ShapeType() == TopAbs_SHELL)
        {
            TopoDS_Shell shell = TopoDS::Shell(newShape);
            if (shell.IsNull()) return false;

            TopExp_Explorer exp;
            for (exp.Init(shell, TopAbs_FACE); exp.More(); exp.Next()) {
                if (exp.Current().ShapeType() != TopAbs_FACE) continue;
                TopoDS_Face face = TopoDS::Face(exp.Current());
                if (face.IsNull()) continue;
                Handle(Geom_Surface) surface = BRep_Tool::Surface(face);
                if (surface.IsNull() || surface->DynamicType() != STANDARD_TYPE(Geom_Plane)) continue;
                Handle(Geom_Plane) plane = Handle(Geom_Plane)::DownCast(surface);

                auto pos = plane->Position();
                auto loc = plane->Position().Location();
                auto direction = plane->Position().Direction();
                auto yDirection = plane->Position().YDirection();
                setPosition(loc.X(), loc.Y(), loc.Z());
                setNormal(direction.X(), direction.Y(), direction.Z());
                setUp(yDirection.X(), yDirection.Y(), yDirection.Z());
                try
                {
                    gp_Pln pln(gp_Pnt(m_pos[0], m_pos[1], m_pos[2]), gp_Dir(m_nor[0], m_nor[1], m_nor[2]));

                    BRepBuilderAPI_MakeFace face(pln);
                    _occShapeAgent->updateShape(face);
                    return true;
                }
                catch (...)
                {
                    printLog(tr("Failed to make plane."), 3);
                    return false;
                }
            }
        }


        return false;
    }


    FITKOCCReferenceThreePointsPlane::FITKOCCReferenceThreePointsPlane() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCReferenceThreePointsPlane::update()
    {
        gp_Pnt p1(m_Points.at(0).at(0), m_Points.at(0).at(1), m_Points.at(0).at(2));
        gp_Pnt p2(m_Points.at(1).at(0), m_Points.at(1).at(1), m_Points.at(1).at(2));
        gp_Pnt p3(m_Points.at(2).at(0), m_Points.at(2).at(1), m_Points.at(2).at(2));
        gce_MakePln pln(p1, p2, p3);
        if (!pln.IsDone()) return false;
        auto plane = pln.Value();
        auto loc = plane.Position().Location();
        auto direction = plane.Position().Direction();
        auto yDirection = plane.Position().YDirection();
        setPosition(loc.X(), loc.Y(), loc.Z());
        setNormal(direction.X(), direction.Y(), direction.Z());
        setUp(yDirection.X(), yDirection.Y(), yDirection.Z());
        try
        {
            gp_Pln pln(gp_Pnt(m_pos[0], m_pos[1], m_pos[2]), gp_Dir(m_nor[0], m_nor[1], m_nor[2]));

            BRepBuilderAPI_MakeFace face(pln);
            _occShapeAgent->updateShape(face);
            return true;
        }
        catch (...)
        {
            printLog(tr("Failed to make plane."), 3);
            return false;
        }
    }

    FITKOCCReferenceEquationPlane::FITKOCCReferenceEquationPlane() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCReferenceEquationPlane::update()
    {
        gce_MakePln pln(m_A, m_B, m_C, m_D);
        if (!pln.IsDone()) return false;
        auto plane = pln.Value();
        auto loc = plane.Position().Location();
        auto direction = plane.Position().Direction();
        auto yDirection = plane.Position().YDirection();
        setPosition(loc.X(), loc.Y(), loc.Z());
        setNormal(direction.X(), direction.Y(), direction.Z());
        setUp(yDirection.X(), yDirection.Y(), yDirection.Z());

        try
        {
            gp_Pln pln(gp_Pnt(m_pos[0], m_pos[1], m_pos[2]), gp_Dir(m_nor[0], m_nor[1], m_nor[2]));

            BRepBuilderAPI_MakeFace face(pln);
            _occShapeAgent->updateShape(face);
            return true;
        }
        catch (...)
        {
            printLog(tr("Failed to make plane."), 3);
            return false;
        }
    }

    FITKOCCReferencePointAndDirectionPlane::FITKOCCReferencePointAndDirectionPlane() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCReferencePointAndDirectionPlane::update()
    {
        try
        {
            gce_MakePln pln(gp_Pnt(m_Point[0], m_Point[1], m_Point[2]), gp_Dir(m_Direction[0], m_Direction[1], m_Direction[2]));
            if (!pln.IsDone()) return false;
            auto plane = pln.Value();
            auto loc = plane.Position().Location();
            auto direction = plane.Position().Direction();
            auto yDirection = plane.Position().YDirection();
            setPosition(loc.X(), loc.Y(), loc.Z());
            setNormal(direction.X(), direction.Y(), direction.Z());
            setUp(yDirection.X(), yDirection.Y(), yDirection.Z());
            gp_Pln pln2(gp_Pnt(m_pos[0], m_pos[1], m_pos[2]), gp_Dir(m_nor[0], m_nor[1], m_nor[2]));

            BRepBuilderAPI_MakeFace face(pln2);
            _occShapeAgent->updateShape(face);
            return true;
        }
        catch (...)
        {
            printLog(tr("Failed to make plane."), 3);
            return false;
        }
    }
}

