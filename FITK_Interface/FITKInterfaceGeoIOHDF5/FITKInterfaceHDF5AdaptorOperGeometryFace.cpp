#include "FITKInterfaceHDF5AdaptorOperGeometryFace.h"
//Interface
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSurface.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperFace.h"

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorOperGeometryFace::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorOperGeometryFace";
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readOperGeometryFace(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeOperGeometryFace(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::readOperGeometryFace(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (!comm) return false;
        auto commType = comm->getGeometryCommandType();
        switch (commType)
        {
        case Interface::FITKGeoEnum::FGTRectangularTrimmedSurface: return false;
        case Interface::FITKGeoEnum::FGTBridgeSurface:          return readBasicGeometryBridgeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSurfaceFromSolid:       return readBasicGeometrySolidSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMultiSectionSurface:    return readBasicGeometryMultiSectionSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSweepSurface:           return readBasicGeometrySweepSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRevolSurface:           return readBasicGeometryRevolSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTExtrudeSurface:         return readBasicGeometryExtrudeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTOffsetSurface:          return readBasicGeometryOffsetSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTClosedWireSurface:      return readBasicGeometryClosedWireSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFillGapsFace:           return readOperGeometryOperFaceFillGaps(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFillHolesFace:          return readOperGeometryOperFaceFillHoles(comm, h5Group);
        case Interface::FITKGeoEnum::FGTDeleteFloatingEdge:     return readOperGeometryOperFaceDeleteFloatingEdge(comm, h5Group);
            //Oper Face
        default:return false;
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::writeOperGeometryFace(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (!comm) return false;
        auto commType = comm->getGeometryCommandType();
        switch (commType)
        {
        case Interface::FITKGeoEnum::FGTRectangularTrimmedSurface: return false;
        case Interface::FITKGeoEnum::FGTBridgeSurface:          return writeBasicGeometryBridgeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSurfaceFromSolid:       return writeBasicGeometrySolidSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMultiSectionSurface:    return writeBasicGeometryMultiSectionSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSweepSurface:           return writeBasicGeometrySweepSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRevolSurface:           return writeBasicGeometryRevolSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTExtrudeSurface:         return writeBasicGeometryExtrudeSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTOffsetSurface:          return writeBasicGeometryOffsetSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTClosedWireSurface:      return writeBasicGeometryClosedWireSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFillGapsFace:           return writeOperGeometryOperFaceFillGaps(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFillHolesFace:          return writeOperGeometryOperFaceFillHoles(comm, h5Group);
        case Interface::FITKGeoEnum::FGTDeleteFloatingEdge:     return writeOperGeometryOperFaceDeleteFloatingEdge(comm, h5Group);
        default:return false;
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::readOperGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return false;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::writeOperGeometryRectangularTrimmedSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return false;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::readOperGeometryOperFaceBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFace* operFace = dynamic_cast<Interface::FITKAbsGeoModelOperFace*>(comm);
        if (!operFace) return false;

        int type = readIntAttribute(h5Group, "Type");
        operFace->setType((Interface::FITKAbsGeoModelOperFace::GeoFaceOperType)type);

        double tolerance = readDoubleAttribute(h5Group, "Tolerance");
        operFace->setTolerance(tolerance);

        int count = readIntAttribute(h5Group, "Count");

        int sourceSurfaceArray[3];
        for (int i = 0; i < count; i++)
        {
            if (!readIntAttribute(h5Group, std::to_string(i), sourceSurfaceArray, 1, 3)) return false;

            Interface::VirtualShape vShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]);
            operFace->add(vShape);
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::writeOperGeometryOperFaceBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFace* operFace = dynamic_cast<Interface::FITKAbsGeoModelOperFace*>(comm);
        if (!operFace) return false;

        int type = operFace->getType();
        writeIntAttribute(h5Group, "Type", &type);

        double tolerance = operFace->getTolerance();
        writeDoubleAttribute(h5Group, "Tolerance", &tolerance);

        auto shapes = operFace->getVShapes();
        int count = shapes.size();
        writeIntAttribute(h5Group, "Count", &count);

        for (int i = 0; i < count; i++)
        {
            int vShape[3]{ shapes[i].CmdId, shapes[i].VirtualTopoId,shapes[i].VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), &vShape, 1, 3);
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::readOperGeometryOperFaceFillGaps(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFaceFillHoles* fillHoles = dynamic_cast<Interface::FITKAbsGeoModelOperFaceFillHoles*>(comm);
        if (!fillHoles) return false;
        return readOperGeometryOperFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::writeOperGeometryOperFaceFillGaps(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFaceFillGaps* fillGaps = dynamic_cast<Interface::FITKAbsGeoModelOperFaceFillGaps*>(comm);
        if (!fillGaps) return false;
        return writeOperGeometryOperFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::readOperGeometryOperFaceFillHoles(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFaceFillHoles* fillHoles = dynamic_cast<Interface::FITKAbsGeoModelOperFaceFillHoles*>(comm);
        if (!fillHoles) return false;
        return readOperGeometryOperFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::writeOperGeometryOperFaceFillHoles(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFaceFillHoles* fillHoles = dynamic_cast<Interface::FITKAbsGeoModelOperFaceFillHoles*>(comm);
        if (!fillHoles) return false;
        return writeOperGeometryOperFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::readOperGeometryOperFaceDeleteFloatingEdge(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFaceDeleteFloatingEdge* deleteFloatingEdge = dynamic_cast<Interface::FITKAbsGeoModelOperFaceDeleteFloatingEdge*>(comm);
        if (!deleteFloatingEdge) return false;

        int vFaceArray[3];
        if (!readIntAttribute(h5Group, "vFace", vFaceArray, 1, 3)) return false;
        Interface::VirtualShape vShape(vFaceArray[0], vFaceArray[1], vFaceArray[2]);
        deleteFloatingEdge->setMFace(vShape);
        return readOperGeometryOperFaceBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometryFace::writeOperGeometryOperFaceDeleteFloatingEdge(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperFaceDeleteFloatingEdge* deleteFloatingEdge = dynamic_cast<Interface::FITKAbsGeoModelOperFaceDeleteFloatingEdge*>(comm);
        if (!deleteFloatingEdge) return false;

        auto vFace = deleteFloatingEdge->getMFace();
        int vFaceArray[3]{ vFace.CmdId,vFace.VirtualTopoId, vFace.VirtualTopoIndex };
        writeIntAttribute(h5Group, "vFace", vFaceArray, 1, 3);
        return writeOperGeometryOperFaceBase(comm, h5Group);
    }

    //@}
}   // namespace IO
