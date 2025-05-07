#include "FITKInterfaceHDF5AdaptorBasicGeometryFace.h"
//Interface
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSurface.h"

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorBasicGeometryFace::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorBasicGeometryFace";
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryFace(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (!comm) return false;
        auto commType = comm->getGeometryCommandType();
        switch (commType)
        {
            //Face
        case Interface::FITKGeoEnum::FGTBridgeSurface:       return readBasicGeometryBridgeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSurfaceFromSolid:    return readBasicGeometrySolidSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMultiSectionSurface: return readBasicGeometryMultiSectionSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSweepSurface:        return readBasicGeometrySweepSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRevolSurface:        return readBasicGeometryRevolSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTExtrudeSurface:      return readBasicGeometryExtrudeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTOffsetSurface:       return readBasicGeometryOffsetSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTClosedWireSurface:   return readBasicGeometryClosedWireSurface(comm, h5Group);
        default:return false;
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryFace(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (!comm) return false;
        auto commType = comm->getGeometryCommandType();
        switch (commType)
        {
            //Face
        case Interface::FITKGeoEnum::FGTBridgeSurface:       return writeBasicGeometryBridgeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSurfaceFromSolid:    return writeBasicGeometrySolidSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMultiSectionSurface: return writeBasicGeometryMultiSectionSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSweepSurface:        return writeBasicGeometrySweepSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRevolSurface:        return writeBasicGeometryRevolSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTExtrudeSurface:      return writeBasicGeometryExtrudeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTOffsetSurface:       return writeBasicGeometryOffsetSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTClosedWireSurface:   return writeBasicGeometryClosedWireSurface(comm, h5Group);
        default:return false;
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryFaceBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryFaceBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryClosedWireSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelClosedWireSurface* circleArc = dynamic_cast<Interface::FITKAbsGeoModelClosedWireSurface*>(comm);
        if (!circleArc) return false;
        int edgeArray[3];
        auto edges = circleArc->edges();
        int count = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < count; i++)
        {
            if (!readIntAttribute(h5Group, std::to_string(i), edgeArray, 1, 3)) return false;
            circleArc->addEdge(Interface::VirtualShape(edgeArray[0], edgeArray[1], edgeArray[2]));
        }
        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryClosedWireSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelClosedWireSurface* circleArc = dynamic_cast<Interface::FITKAbsGeoModelClosedWireSurface*>(comm);
        if (!circleArc) return false;
        auto edges = circleArc->edges();
        int count = edges.count();
        for (int i = 0; i < count; i++)
        {
            auto edge = edges[i];
            int edgeArray[3]{ edge.CmdId ,edge.VirtualTopoId, edge.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), &edgeArray, 1, 3);
        }
        writeIntAttribute(h5Group, "Count", &count);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryOffsetSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOffsetSurface* offsetSurface = dynamic_cast<Interface::FITKAbsGeoModelOffsetSurface*>(comm);
        if (!offsetSurface) return false;
        Interface::VirtualShape sourceSurface;
        int sourceSurfaceArray[3];
        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3)) return false;
        offsetSurface->setSourceSurface(Interface::VirtualShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]));

        double offset = readDoubleAttribute(h5Group, "Offset");
        offsetSurface->setOffset(offset);

        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryOffsetSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOffsetSurface* offsetSurface = dynamic_cast<Interface::FITKAbsGeoModelOffsetSurface*>(comm);
        if (!offsetSurface) return false;
        Interface::VirtualShape sourceSurface = offsetSurface->sourceSurface();
        int sourceSurfaceArray[3]{ sourceSurface.CmdId ,sourceSurface.VirtualTopoId, sourceSurface.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", &sourceSurfaceArray, 1, 3);

        double offset = offsetSurface->offset();
        writeDoubleAttribute(h5Group, "Offset", &offset);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryExtrudeSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelExtrudeSurface* extrudeSurface = dynamic_cast<Interface::FITKAbsGeoModelExtrudeSurface*>(comm);
        if (!extrudeSurface) return false;
        int sourceCurveArray[3];
        double directionArray[3];
        if (!readIntAttribute(h5Group, "ExtrudeSurface", sourceCurveArray, 1, 3)) return false;
        extrudeSurface->setSourceCurve(Interface::VirtualShape(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]));

        if (!readDoubleAttribute(h5Group, "Direction", directionArray, 1, 3)) return false;
        extrudeSurface->setDirection(directionArray[0], directionArray[1], directionArray[2]);
        double length = readDoubleAttribute(h5Group, "Length");
        extrudeSurface->setLength(length);
        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryExtrudeSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelExtrudeSurface* extrudeSurface = dynamic_cast<Interface::FITKAbsGeoModelExtrudeSurface*>(comm);
        if (!extrudeSurface) return false;
        Interface::VirtualShape sourceCurve = extrudeSurface->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId ,sourceCurve.VirtualTopoId, sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "ExtrudeSurface", &sourceCurveArray, 1, 3);

        auto direction = extrudeSurface->direction();
        double directionArray[3]{ direction[0],direction[1],direction[2] };
        writeDoubleAttribute(h5Group, "Direction", directionArray, 1, 3);
        double length = extrudeSurface->length();
        writeDoubleAttribute(h5Group, "Length", &length);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryRevolSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRevolSurface* revolSurface = dynamic_cast<Interface::FITKAbsGeoModelRevolSurface*>(comm);
        if (!revolSurface) return false;
        int sourceCurveArray[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurveArray, 1, 3)) return false;
        revolSurface->setSourveCurve(Interface::VirtualShape(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]));

        double rotateAxisPoint1Array[3], rotateAxisPoint2Array[3];
        if (!readDoubleAttribute(h5Group, "RotateAxisPoint1", rotateAxisPoint1Array, 1, 3)) return false;
        revolSurface->setRotateAxisPoint1(rotateAxisPoint1Array[0], rotateAxisPoint1Array[1], rotateAxisPoint1Array[2]);
        if (!readDoubleAttribute(h5Group, "RotateAxisPoint2", rotateAxisPoint2Array, 1, 3)) return false;
        revolSurface->setRotateAxisPoint2(rotateAxisPoint2Array[0], rotateAxisPoint2Array[1], rotateAxisPoint2Array[2]);

        int angle = readIntAttribute(h5Group, "Angle");
        revolSurface->setAngle(angle);

        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryRevolSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRevolSurface* revolSurface = dynamic_cast<Interface::FITKAbsGeoModelRevolSurface*>(comm);
        if (!revolSurface) return false;
        Interface::VirtualShape sourceCurve = revolSurface->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId ,sourceCurve.VirtualTopoId, sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurveArray, 1, 3);

        auto rotateAxisPoint1 = revolSurface->rotateAxisPoint1();
        double rotateAxisPoint1Array[3]{ rotateAxisPoint1[0],rotateAxisPoint1[1],rotateAxisPoint1[2] };
        writeDoubleAttribute(h5Group, "RotateAxisPoint1", rotateAxisPoint1Array, 1, 3);

        auto rotateAxisPoint2 = revolSurface->rotateAxisPoint2();
        double rotateAxisPoint2Array[3]{ rotateAxisPoint2[0],rotateAxisPoint2[1],rotateAxisPoint2[2] };
        writeDoubleAttribute(h5Group, "RotateAxisPoint2", rotateAxisPoint2Array, 1, 3);

        int angle = revolSurface->angle();
        writeIntAttribute(h5Group, "Angle", &angle);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return false;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return false;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometrySweepSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSweepSurface* sweepSurface = dynamic_cast<Interface::FITKAbsGeoModelSweepSurface*>(comm);
        if (!sweepSurface) return false;
        int profileArray[3], curveArray[3];

        if (!readIntAttribute(h5Group, "Profile", profileArray, 1, 3)) return false;
        sweepSurface->setProfile(Interface::VirtualShape(profileArray[0], profileArray[1], profileArray[2]));

        if (!readIntAttribute(h5Group, "Curve", curveArray, 1, 3)) return false;
        sweepSurface->setCurve(Interface::VirtualShape(curveArray[0], curveArray[1], curveArray[2]));

        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometrySweepSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSweepSurface* sweepSurface = dynamic_cast<Interface::FITKAbsGeoModelSweepSurface*>(comm);
        if (!sweepSurface) return false;
        Interface::VirtualShape profile = sweepSurface->profile();
        int profileArray[3]{ profile.CmdId ,profile.VirtualTopoId, profile.VirtualTopoIndex };
        writeIntAttribute(h5Group, "Profile", &profileArray, 1, 3);

        Interface::VirtualShape curve = sweepSurface->curve();
        int curveArray[3]{ curve.CmdId ,curve.VirtualTopoId, curve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "Curve", &curveArray, 1, 3);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryMultiSectionSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelMultiSectionSurface* multiSectionSurface = dynamic_cast<Interface::FITKAbsGeoModelMultiSectionSurface*>(comm);
        if (!multiSectionSurface) return false;

        int count = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < count; i++)
        {
            int curveArray[3];
            if (!readIntAttribute(h5Group, std::to_string(i), curveArray, 1, 3)) return false;
            multiSectionSurface->addSection(Interface::VirtualShape(curveArray[0], curveArray[1], curveArray[2]));
        }
        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryMultiSectionSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelMultiSectionSurface* multiSectionSurface = dynamic_cast<Interface::FITKAbsGeoModelMultiSectionSurface*>(comm);
        if (!multiSectionSurface) return false;

        auto sections = multiSectionSurface->sections();
        int count = sections.size();
        for (int i = 0; i < count; i++)
        {
            auto section = sections[i];
            int curveArray[3]{ section.CmdId ,section.VirtualTopoId, section.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), &curveArray, 1, 3);
        }
        writeIntAttribute(h5Group, "Count", &count);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometryBridgeSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBridgeSurface* bridgeSurface = dynamic_cast<Interface::FITKAbsGeoModelBridgeSurface*>(comm);
        if (!bridgeSurface) return false;
        int sourceSurface1Array[3], sourceSurface2Array[3];

        if (!readIntAttribute(h5Group, "SourceSurface1", sourceSurface1Array, 1, 3)) return false;
        bridgeSurface->setSourceSurface1(Interface::VirtualShape(sourceSurface1Array[0], sourceSurface1Array[1], sourceSurface1Array[2]));

        int edgeVirtualTopoId1 = readIntAttribute(h5Group, "EdgeVirtualTopoId1");
        bridgeSurface->setEdgeVirtualTopoId1(edgeVirtualTopoId1);

        if (!readIntAttribute(h5Group, "SourceSurface2", sourceSurface2Array, 1, 3)) return false;
        bridgeSurface->setSourceSurface2(Interface::VirtualShape(sourceSurface2Array[0], sourceSurface2Array[1], sourceSurface2Array[2]));

        int edgeVirtualTopoId2 = readIntAttribute(h5Group, "EdgeVirtualTopoId2");
        bridgeSurface->setEdgeVirtualTopoId2(edgeVirtualTopoId2);
        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometryBridgeSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBridgeSurface* bridgeSurface = dynamic_cast<Interface::FITKAbsGeoModelBridgeSurface*>(comm);
        if (!bridgeSurface) return false;

        Interface::VirtualShape sourceSurface1 = bridgeSurface->sourceSurface1();
        int sourceSurface1Array[3]{ sourceSurface1.CmdId ,sourceSurface1.VirtualTopoId,sourceSurface1.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface1", &sourceSurface1Array, 1, 3);
        int edgeVirtualTopoId1 = bridgeSurface->edgeVirtualTopoId1();
        writeIntAttribute(h5Group, "EdgeVirtualTopoId1", &edgeVirtualTopoId1);

        Interface::VirtualShape sourceSurface2 = bridgeSurface->sourceSurface2();
        int sourceSurface2Array[3]{ sourceSurface2.CmdId ,sourceSurface2.VirtualTopoId,sourceSurface2.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface2", &sourceSurface2Array, 1, 3);
        int edgeVirtualTopoId2 = bridgeSurface->edgeVirtualTopoId2();
        writeIntAttribute(h5Group, "EdgeVirtualTopoId2", &edgeVirtualTopoId2);
        return writeBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::readBasicGeometrySolidSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSolidSurface* solidSurface = dynamic_cast<Interface::FITKAbsGeoModelSolidSurface*>(comm);
        if (!solidSurface) return false;
        int sourceSolidArray[3];
        if (!readIntAttribute(h5Group, "SourceSolid", sourceSolidArray, 1, 3)) return false;
        solidSurface->setSourceSolid(Interface::VirtualShape(sourceSolidArray[0], sourceSolidArray[1], sourceSolidArray[2]));

        int faceVirtualTopoId = readIntAttribute(h5Group, "FaceVirtualTopoId");
        solidSurface->setFaceVirtualTopoId(faceVirtualTopoId);

        return readBasicGeometryFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryFace::writeBasicGeometrySolidSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSolidSurface* solidSurface = dynamic_cast<Interface::FITKAbsGeoModelSolidSurface*>(comm);
        if (!solidSurface) return false;

        Interface::VirtualShape sourceSolid = solidSurface->sourceSolid();
        int sourceSolidArray[3]{ sourceSolid.CmdId ,sourceSolid.VirtualTopoId,sourceSolid.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSolid", &sourceSolidArray, 1, 3);
        int faceVirtualTopoId = solidSurface->faceVirtualTopoId();
        writeIntAttribute(h5Group, "FaceVirtualTopoId", &faceVirtualTopoId);

        return writeBasicGeometryFaceBase(comm, h5Group);
    }



    //@}
}   // namespace IO
