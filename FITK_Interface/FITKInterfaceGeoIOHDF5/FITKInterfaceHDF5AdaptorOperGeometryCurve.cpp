#include "FITKInterfaceHDF5AdaptorOperGeometryCurve.h"
//Interface
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelCurve.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperLine.h"

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorOperGeometryCurve::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorOperGeometryCurve";
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readOperGeometryCurve(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeOperGeometryCurve(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        auto commType = comm->getGeometryCommandType();
        if (commType == Interface::FITKGeoEnum::FITKGeometryComType::FGTNone) return false;
        switch (commType)
        {
        case Interface::FITKGeoEnum::FGTLine:                       return readBasicGeometryLine(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSegment:                    return readBasicGeometrySegment(comm, h5Group);
        case Interface::FITKGeoEnum::FGTWire:                       return readBasicGeometryWire(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCircle:                     return readBasicGeometryCircle(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCircleArc:                  return readBasicGeometryCircleArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTEllipse:                    return readBasicGeometryEllipse(comm, h5Group);
        case Interface::FITKGeoEnum::FGTEllipseArc:                 return readBasicGeometryEllipseArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTHyperbola:                  return readBasicGeometryHyperbola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTHyperbolaArc:               return readBasicGeometryHyperbolaArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTParabola:                   return readBasicGeometryParabola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTParabolaArc:                return readBasicGeometryParabolaArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTOffsetCurve:                return readOperGeometryOffsetCurve(comm, h5Group);
            //Bezier Bspline
        case Interface::FITKGeoEnum::FGTBezierByControlPoints:      return readBasicGeometryBeizeByControlPoints(comm, h5Group);
        case Interface::FITKGeoEnum::FGTBezierByThroughPoints:      return false;
        case Interface::FITKGeoEnum::FGTBSplineByControlPoints:     return false;
        case Interface::FITKGeoEnum::FGTBSplineByThroughPoints:     return readBasicGeometryBsplineByThroughPoints(comm, h5Group);
            //ThreePoints
        case Interface::FITKGeoEnum::FGTThreePointsCircle:          return readBasicGeometryThreePointsCircle(comm, h5Group);
        case Interface::FITKGeoEnum::FGTThreePointsEllipse:         return readBasicGeometryThreePointsEllipse(comm, h5Group);
        case Interface::FITKGeoEnum::FGTThreePointsHyperbola:       return readBasicGeometryThreePointsHyperbola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTThreePointsParabola:        return readBasicGeometryThreePointsParabola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveProjectionOnSurface:   return readOperGeometryCurveProjectionOnSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTTrimmed:                    return readOperGeometryTrimmedCurve(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSurfaceIntersectSurface:    return readOperGeometrySurfaceIntersectionSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTBridgeCurve:                return readOperGeometryBridgeCurve(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveFromSurface:           return readOperGeometrySurfaceEdge(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMergeLine:                  return readOperGeometryMergeOperLine(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSplitByMiddlePositionLine:  return readOperGeometryMiddleOperLine(comm, h5Group);
            break;

        default: return false;
        }

        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        //if (!writeOperGeometryCurveBase(comm, h5Group)) return false;
        //获取命令类型
        auto commType = comm->getGeometryCommandType();
        if (commType == Interface::FITKGeoEnum::FITKGeometryComType::FGTNone) return false;
        switch (commType)
        {
        case Interface::FITKGeoEnum::FGTLine:                       return writeBasicGeometryLine(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSegment:                    return writeBasicGeometrySegment(comm, h5Group);
        case Interface::FITKGeoEnum::FGTWire:                       return writeBasicGeometryWire(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCircle:                     return writeBasicGeometryCircle(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCircleArc:                  return writeBasicGeometryCircleArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTEllipse:                    return writeBasicGeometryEllipse(comm, h5Group);
        case Interface::FITKGeoEnum::FGTEllipseArc:                 return writeBasicGeometryEllipseArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTHyperbola:                  return writeBasicGeometryHyperbola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTHyperbolaArc:               return writeBasicGeometryHyperbolaArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTParabola:                   return writeBasicGeometryParabola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTParabolaArc:                return writeBasicGeometryParabolaArc(comm, h5Group);
        case Interface::FITKGeoEnum::FGTOffsetCurve:                return writeOperGeometryOffsetCurve(comm, h5Group);
            //Bezier Bspline
        case Interface::FITKGeoEnum::FGTBezierByControlPoints:      return writeBasicGeometryBeizeByControlPoints(comm, h5Group);
        case Interface::FITKGeoEnum::FGTBezierByThroughPoints:      return false;
        case Interface::FITKGeoEnum::FGTBSplineByControlPoints:     return false;
        case Interface::FITKGeoEnum::FGTBSplineByThroughPoints:     return writeBasicGeometryBsplineByThroughPoints(comm, h5Group);
            //ThreePoints
        case Interface::FITKGeoEnum::FGTThreePointsCircle:          return writeBasicGeometryThreePointsCircle(comm, h5Group);
        case Interface::FITKGeoEnum::FGTThreePointsEllipse:         return writeBasicGeometryThreePointsEllipse(comm, h5Group);
        case Interface::FITKGeoEnum::FGTThreePointsHyperbola:       return writeBasicGeometryThreePointsHyperbola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTThreePointsParabola:        return writeBasicGeometryThreePointsParabola(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveProjectionOnSurface:   return writeOperGeometryCurveProjectionOnSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTTrimmed:                    return writeOperGeometryTrimmedCurve(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSurfaceIntersectSurface:    return writeOperGeometrySurfaceIntersectionSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTBridgeCurve:                return writeOperGeometryBridgeCurve(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveFromSurface:           return writeOperGeometrySurfaceEdge(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMergeLine:                  return writeOperGeometryMergeOperLine(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSplitByMiddlePositionLine:  return writeOperGeometryMiddleOperLine(comm, h5Group);
            break;

        default: return false;
        }

        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryTrimmedCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelTrimmedCurve* trimmedCurve = dynamic_cast<Interface::FITKAbsGeoModelTrimmedCurve*>(comm);
        if (!trimmedCurve) return false;
        int id = readIntAttribute(h5Group, "SourceCurveId");
        trimmedCurve->setSourceCurveId(id);

        double startTrimmed = readDoubleAttribute(h5Group, "StartTrimmed");
        trimmedCurve->setStartTrimmed(startTrimmed);

        double endTrimmed = readDoubleAttribute(h5Group, "EndTrimmed");
        trimmedCurve->setEndTrimmed(endTrimmed);
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryTrimmedCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelTrimmedCurve* trimmedCurve = dynamic_cast<Interface::FITKAbsGeoModelTrimmedCurve*>(comm);
        if (!trimmedCurve) return false;
        int id = trimmedCurve->sourceCurveId();
        writeIntAttribute(h5Group, "SourceCurveId", &id);

        double startTrimmed = trimmedCurve->startTrimmed();
        writeDoubleAttribute(h5Group, "StartTrimmed", &startTrimmed);

        double endTrimmed = trimmedCurve->endTrimmed();
        writeDoubleAttribute(h5Group, "EndTrimmed", &endTrimmed);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryOffsetCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOffsetCurve* offsetCurve = dynamic_cast<Interface::FITKAbsGeoModelOffsetCurve*>(comm);
        if (!offsetCurve) return false;
        Interface::VirtualShape vShape1;
        vShape1.CmdId = readIntAttribute(h5Group, "cmdID");
        vShape1.VirtualTopoId = readIntAttribute(h5Group, "vTopoID");
        vShape1.VirtualTopoIndex = readIntAttribute(h5Group, "vTopoIndex");
        offsetCurve->setSourceCurve(vShape1);

        double directionList[3];
        if (!readDoubleAttribute(h5Group, "Direction", directionList, 1, 3)) return false;
        offsetCurve->setDir(directionList[0], directionList[1], directionList[2]);

        double offset = readDoubleAttribute(h5Group, "Offset");
        offsetCurve->setOffset(offset);

        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryOffsetCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOffsetCurve* offsetCurve = dynamic_cast<Interface::FITKAbsGeoModelOffsetCurve*>(comm);
        if (!offsetCurve) return false;
        auto vshape = offsetCurve->sourceCurve();
        int cmdID = vshape.CmdId;
        int  vTopoID = vshape.VirtualTopoId;
        int  vTopoIndex = vshape.VirtualTopoIndex;
        writeIntAttribute(h5Group, "cmdID", &cmdID);
        writeIntAttribute(h5Group, "vTopoID", &vTopoID);
        writeIntAttribute(h5Group, "vTopoIndex", &vTopoIndex);

        auto dir = offsetCurve->dir();
        double directionList[3]{ dir[0],dir[1],dir[2] };
        writeDoubleAttribute(h5Group, "Direction", directionList, 1, 3);

        double offset = offsetCurve->offset();
        writeDoubleAttribute(h5Group, "Offset", &offset);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryCurveProjectionOnSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveProjectionOnSurface* curveProjectionOnSurface = dynamic_cast<Interface::FITKAbsGeoModelCurveProjectionOnSurface*>(comm);
        if (!curveProjectionOnSurface) return false;
        int sourceCurve[3], sourceSurface[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurve, 1, 3)) return false;
        Interface::VirtualShape vShape1(sourceCurve[0], sourceCurve[1], sourceCurve[2]);
        curveProjectionOnSurface->setSourceCurve(vShape1);

        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurface, 1, 3)) return false;
        Interface::VirtualShape vShape2(sourceSurface[0], sourceSurface[1], sourceSurface[2]);
        curveProjectionOnSurface->setSourceSurface(vShape2);

        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryCurveProjectionOnSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveProjectionOnSurface* curveProjectionOnSurface = dynamic_cast<Interface::FITKAbsGeoModelCurveProjectionOnSurface*>(comm);
        if (!curveProjectionOnSurface) return false;

        auto sourceCurveGet = curveProjectionOnSurface->sourceCurve();
        int sourceCurve[3]{ sourceCurveGet.CmdId, sourceCurveGet.VirtualTopoId, sourceCurveGet.VirtualTopoId };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurve, 1, 3);

        auto sourceSurfaceGet = curveProjectionOnSurface->sourceSurface();
        int sourceSurface[3]{ sourceSurfaceGet.CmdId, sourceSurfaceGet.VirtualTopoId, sourceSurfaceGet.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", &sourceSurface, 1, 3);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometrySurfaceIntersectionSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSurfaceIntersectionSurface* surfaceIntersectionSurface = dynamic_cast<Interface::FITKAbsGeoModelSurfaceIntersectionSurface*>(comm);
        if (!surfaceIntersectionSurface) return false;
        int sourceSurface1[2], sourceSurface2[2];

        if (!readIntAttribute(h5Group, "SourceSurface1", sourceSurface1, 1, 3)) return false;
        Interface::VirtualShape vShape1(sourceSurface1[0], sourceSurface1[1], sourceSurface1[2]);
        surfaceIntersectionSurface->setSourceSurface1(vShape1);

        if (!readIntAttribute(h5Group, "SourceSurface2", sourceSurface2, 1, 3)) return false;
        Interface::VirtualShape vShape2(sourceSurface2[0], sourceSurface2[1], sourceSurface2[2]);
        surfaceIntersectionSurface->setSourceSurface2(vShape2);

        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometrySurfaceIntersectionSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSurfaceIntersectionSurface* surfaceIntersectionSurface = dynamic_cast<Interface::FITKAbsGeoModelSurfaceIntersectionSurface*>(comm);
        if (!surfaceIntersectionSurface) return false;

        auto sourceSurface1Get = surfaceIntersectionSurface->sourceSurface1();
        int sourceSurface1[3]{ sourceSurface1Get.CmdId ,sourceSurface1Get.VirtualTopoId, sourceSurface1Get.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface1", &sourceSurface1, 1, 3);

        auto sourceSurface2Get = surfaceIntersectionSurface->sourceSurface2();
        int sourceSurface2[3]{ (sourceSurface2Get.CmdId) ,(sourceSurface2Get.VirtualTopoId),sourceSurface2Get.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface2", &sourceSurface2, 1, 3);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryBridgeCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBridgeCurve* bridgeCurve = dynamic_cast<Interface::FITKAbsGeoModelBridgeCurve*>(comm);
        if (!bridgeCurve) return false;
        int sourceCurve1[3], sourceCurve2[3];

        if (!readIntAttribute(h5Group, "SourceCurve1", sourceCurve1, 1, 3)) return false;
        Interface::VirtualShape vShape1(sourceCurve1[0], sourceCurve1[1], sourceCurve1[2]);
        bridgeCurve->setSourceCurve1(vShape1);

        bool useStartEnd1 = readBoolAttribute(h5Group, "UseStartEnd1");
        bridgeCurve->setUseStartEnd1(useStartEnd1);
        double parameter1 = readDoubleAttribute(h5Group, "Parameter1");
        bridgeCurve->setParameter1(parameter1);

        if (!readIntAttribute(h5Group, "SourceCurve2", sourceCurve2, 1, 3)) return false;
        Interface::VirtualShape vShape2(sourceCurve2[0], sourceCurve2[1], sourceCurve2[2]);
        bridgeCurve->setSourceCurve2(vShape2);

        bool useStartEnd2 = readBoolAttribute(h5Group, "UseStartEnd2");
        bridgeCurve->setUseStartEnd2(useStartEnd2);
        double parameter2 = readDoubleAttribute(h5Group, "Parameter2");
        bridgeCurve->setParameter2(parameter2);
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryBridgeCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBridgeCurve* bridgeCurve = dynamic_cast<Interface::FITKAbsGeoModelBridgeCurve*>(comm);
        if (!bridgeCurve) return false;

        auto sourceCurve1Get = bridgeCurve->sourceCurve1();
        int sourceCurve1[3]{ sourceCurve1Get.CmdId, sourceCurve1Get.VirtualTopoId, sourceCurve1Get.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve1", &sourceCurve1, 1, 3);
        bool useStartEnd1 = bridgeCurve->useStartEnd1();
        writeBoolAttribute(h5Group, "UseStartEnd1", &useStartEnd1);
        double parameter1 = bridgeCurve->parameter1();
        writeDoubleAttribute(h5Group, "Parameter1", &parameter1);

        auto sourceCurve2Get = bridgeCurve->sourceCurve2();
        int sourceCurve2[3]{ sourceCurve2Get.CmdId, sourceCurve2Get.VirtualTopoId, sourceCurve2Get.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve2", &sourceCurve2, 1, 3);
        bool useStartEnd2 = bridgeCurve->useStartEnd2();
        writeBoolAttribute(h5Group, "UseStartEnd2", &useStartEnd2);
        double parameter2 = bridgeCurve->parameter2();
        writeDoubleAttribute(h5Group, "Parameter2", &parameter2);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometrySurfaceEdge(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSurfaceEdge* surfaceEdge = dynamic_cast<Interface::FITKAbsGeoModelSurfaceEdge*>(comm);
        if (!surfaceEdge) return false;
        int sourceSurface[3];
        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurface, 1, 3)) return false;
        Interface::VirtualShape vShape(sourceSurface[0], sourceSurface[1], sourceSurface[2]);
        surfaceEdge->setSourceSurface(vShape);

        int edgeVirtualTopoId = readIntAttribute(h5Group, "EdgeVirtualTopoId");
        surfaceEdge->setEdgeVirtualTopoId(edgeVirtualTopoId);
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometrySurfaceEdge(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSurfaceEdge* surfaceEdge = dynamic_cast<Interface::FITKAbsGeoModelSurfaceEdge*>(comm);
        if (!surfaceEdge) return false;

        auto sourceSurfaceGet = surfaceEdge->sourceSurface();
        int sourceSurface[3]{ sourceSurfaceGet.CmdId ,sourceSurfaceGet.VirtualTopoId,sourceSurfaceGet.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", &sourceSurface, 1, 3);
        int edgeVirtualTopoId = surfaceEdge->edgeVirtualTopoId();
        writeIntAttribute(h5Group, "EdgeVirtualTopoId", &edgeVirtualTopoId);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryOperLineBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperLine* operLine = dynamic_cast<Interface::FITKAbsGeoModelOperLine*>(comm);
        if (!operLine) return false;

        int type = readIntAttribute(h5Group, "Type");
        operLine->setType((Interface::FITKAbsGeoModelOperLine::GeoLineOperType)type);

        double angle = readDoubleAttribute(h5Group, "Angle");
        operLine->setAngle(angle);

        int count = readIntAttribute(h5Group, "Count");

        int sourceSurfaceArray[3];
        for (int i = 0; i < count; i++)
        {
            if (!readIntAttribute(h5Group, std::to_string(i), sourceSurfaceArray, 1, 3)) return false;
            Interface::VirtualShape vShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]);
            operLine->add(vShape);
        }

        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryOperLineBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperLine* operLine = dynamic_cast<Interface::FITKAbsGeoModelOperLine*>(comm);
        if (!operLine) return false;

        int type = operLine->getType();
        writeIntAttribute(h5Group, "Type", &type);

        double angle = operLine->getAngle();
        writeDoubleAttribute(h5Group, "Angle", &angle);

        auto shapes = operLine->getVShapes();
        int count = shapes.size();
        writeIntAttribute(h5Group, "Count", &count);

        for (int i = 0; i < count; i++)
        {
            int vShape[3]{ shapes[i].CmdId, shapes[i].VirtualTopoId, shapes[i].VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), &vShape, 1, 3);
        }

        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryMergeOperLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return readOperGeometryOperLineBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryMergeOperLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return writeOperGeometryOperLineBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryMiddleOperLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return readOperGeometryOperLineBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryMiddleOperLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return writeOperGeometryOperLineBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::readOperGeometryAngleOperLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return readOperGeometryOperLineBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryCurve::writeOperGeometryAngleOperLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return writeOperGeometryOperLineBase(comm, h5Group);
    }

    //@}
}   // namespace IO
