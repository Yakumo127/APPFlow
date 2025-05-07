#include "FITKInterfaceHDF5AdaptorOperGeometrySolid.h"
//Interface
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelBox.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSphere.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelCylinder.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperSolid.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoFeature.h"

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorOperGeometrySolid::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorOperGeometrySolid";
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readOperGeometrySolid(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeOperGeometrySolid(comm, *_h5Group);
    }


    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolid(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        switch (comm->getGeometryCommandType())
        {
        case Interface::FITKGeoEnum::FGTBox:                        return readOperGeometrySolidBox(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSphere:                     return readOperGeometrySolidSphere(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCylinder:                   return readOperGeometrySolidCylinder(comm, h5Group);
        case Interface::FITKGeoEnum::FGTChamferSolid:               return readOperGeometrySolidChamfer(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRemoveChamfer:              return readOperGeometrySolidRemoveChamfer(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFilletSolid:                return readOperGeometrySolidFillet(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRemoveFillet:               return readOperGeometrySolidRemoveFillet(comm, h5Group);
        case Interface::FITKGeoEnum::FGTDefeature:                  return readOperGeometrySolidDefeature(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFillHole:                   return readOperGeometrySolidFillHole(comm, h5Group);
        case Interface::FITKGeoEnum::FGTClosedSurfaceSolid:         return readOperGeometrySolidClosedSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTExtrudeSolid:               return readOperGeometrySolidExtrude(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRevolSolid:                 return readOperGeometrySolidRevol(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSweepSolid:                 return readOperGeometrySolidSweep(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMultiSectionSolid:          return readOperGeometrySolidMultiSection(comm, h5Group);
        case Interface::FITKGeoEnum::FGTStiffener:                  return readOperGeometrySolidStiffener(comm, h5Group);

        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolid(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        switch (comm->getGeometryCommandType())
        {
        case Interface::FITKGeoEnum::FGTBox:                        return writeOperGeometrySolidBox(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSphere:                     return writeOperGeometrySolidSphere(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCylinder:                   return writeOperGeometrySolidCylinder(comm, h5Group);
        case Interface::FITKGeoEnum::FGTChamferSolid:               return writeOperGeometrySolidChamfer(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRemoveChamfer:              return writeOperGeometrySolidRemoveChamfer(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFilletSolid:                return writeOperGeometrySolidFillet(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRemoveFillet:               return writeOperGeometrySolidRemoveFillet(comm, h5Group);
        case Interface::FITKGeoEnum::FGTDefeature:                  return writeOperGeometrySolidDefeature(comm, h5Group);
        case Interface::FITKGeoEnum::FGTFillHole:                   return writeOperGeometrySolidFillHole(comm, h5Group);
        case Interface::FITKGeoEnum::FGTClosedSurfaceSolid:         return writeOperGeometrySolidClosedSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTExtrudeSolid:               return writeOperGeometrySolidExtrude(comm, h5Group);
        case Interface::FITKGeoEnum::FGTRevolSolid:                 return writeOperGeometrySolidRevol(comm, h5Group);
        case Interface::FITKGeoEnum::FGTSweepSolid:                 return writeOperGeometrySolidSweep(comm, h5Group);
        case Interface::FITKGeoEnum::FGTMultiSectionSolid:          return writeOperGeometrySolidMultiSection(comm, h5Group);
        case Interface::FITKGeoEnum::FGTStiffener:                  return readOperGeometrySolidStiffener(comm, h5Group);
        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidChamfer(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelChamferSolid* cSolid = dynamic_cast<Interface::FITKAbsGeoModelChamferSolid*>(comm);
        if (cSolid == nullptr) return false;

        int inputID = readIntAttribute(h5Group, "InputCmdID");
        cSolid->setInputCmdId(inputID);

        int edgeToposCount = readIntAttribute(h5Group, "Count");
        QList<Interface::VirtualShape> vShapeList;

        for (int i = 0; i < edgeToposCount; i++)
        {
            int vShapeArray[3];
            if (!readIntAttribute(h5Group, std::to_string(i), vShapeArray, 1, 3)) return false;
            vShapeList.append(Interface::VirtualShape(vShapeArray[0], vShapeArray[1], vShapeArray[2]));
        }

        cSolid->setEdgeTopos(vShapeList);
        double distance = readDoubleAttribute(h5Group, "Distance");
        cSolid->setDistance(distance);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidChamfer(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelChamferSolid* cSolid = dynamic_cast<Interface::FITKAbsGeoModelChamferSolid*>(comm);
        if (cSolid == nullptr) return false;

        int inputID = cSolid->getInputCmdId();
        writeIntAttribute(h5Group, "InputCmdID", &inputID);

        auto edgeTopos = cSolid->getEdgeTopos();
        int edgeToposCount = edgeTopos.size();
        writeIntAttribute(h5Group, "Count", &edgeToposCount);

        for (int i = 0; i < edgeToposCount; i++)
        {
            auto vShape = edgeTopos[i];
            int vShapeArray[3]{ vShape.CmdId, vShape.VirtualTopoId, vShape.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), vShapeArray, 1, 3);
        }
        double distance = cSolid->getDistance();
        writeDoubleAttribute(h5Group, "Distance", &distance);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidFillet(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelFilletSolid* fSolid = dynamic_cast<Interface::FITKAbsGeoModelFilletSolid*>(comm);
        if (fSolid == nullptr) return false;

        int inputID = readIntAttribute(h5Group, "InputCmdID");
        fSolid->setInputCmdId(inputID);
        int edgeToposCount = readIntAttribute(h5Group, "Count");
        QList<Interface::VirtualShape> vShapeList;

        for (int i = 0; i < edgeToposCount; i++)
        {
            int vShapeArray[3];
            if (!readIntAttribute(h5Group, std::to_string(i), vShapeArray, 1, 3)) return false;
            vShapeList.append(Interface::VirtualShape(vShapeArray[0], vShapeArray[1], vShapeArray[2]));
        }

        fSolid->setEdgeTopos(vShapeList);
        double radius = readDoubleAttribute(h5Group, "Radius");
        fSolid->setRadius(radius);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidFillet(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelFilletSolid* fSolid = dynamic_cast<Interface::FITKAbsGeoModelFilletSolid*>(comm);
        if (fSolid == nullptr) return false;

        int inputID = fSolid->getInputCmdId();
        writeIntAttribute(h5Group, "InputCmdID", &inputID);

        auto edgeTopos = fSolid->getEdgeTopos();
        int edgeToposCount = edgeTopos.size();
        writeIntAttribute(h5Group, "Count", &edgeToposCount);

        for (int i = 0; i < edgeToposCount; i++)
        {
            auto vShape = edgeTopos[i];
            int vShapeArray[3]{ vShape.CmdId, vShape.VirtualTopoId, vShape.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), vShapeArray, 1, 3);
        }

        double radius = fSolid->getRadius();
        writeDoubleAttribute(h5Group, "Radius", &radius);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidRemoveChamfer(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRemoveChamferSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelRemoveChamferSolid*>(comm);
        if (rSolid == nullptr) return false;
        return readOperGeometrySolidDefeature(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidRemoveChamfer(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRemoveChamferSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelRemoveChamferSolid*>(comm);
        if (rSolid == nullptr) return false;
        return writeOperGeometrySolidDefeature(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidRemoveFillet(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRemoveFilletSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelRemoveFilletSolid*>(comm);
        if (rSolid == nullptr) return false;
        return readOperGeometrySolidDefeature(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidRemoveFillet(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRemoveFilletSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelRemoveFilletSolid*>(comm);
        if (rSolid == nullptr) return false;
        return writeOperGeometrySolidDefeature(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidDefeature(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelDefeatureSolid* dSolid = dynamic_cast<Interface::FITKAbsGeoModelDefeatureSolid*>(comm);
        if (dSolid == nullptr) return false;

        int inputID = readIntAttribute(h5Group, "InputCmdID");
        dSolid->setInputCmdId(inputID);
        int faceToposCount = readIntAttribute(h5Group, "Count");
        QList<Interface::VirtualShape> vShapeList;

        for (int i = 0; i < faceToposCount; i++)
        {
            int vShapeArray[3];
            if (!readIntAttribute(h5Group, std::to_string(i), vShapeArray, 1, 3)) return false;
            vShapeList.append(Interface::VirtualShape(vShapeArray[0], vShapeArray[1], vShapeArray[2]));
        }

        dSolid->setFaceTopos(vShapeList);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidDefeature(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelDefeatureSolid* dSolid = dynamic_cast<Interface::FITKAbsGeoModelDefeatureSolid*>(comm);
        if (dSolid == nullptr) return false;

        int inputID = dSolid->getInputCmdId();
        writeIntAttribute(h5Group, "InputCmdID", &inputID);

        auto faceTopos = dSolid->getFaceTopos();
        int faceToposCount = faceTopos.size();
        writeIntAttribute(h5Group, "Count", &faceToposCount);

        for (int i = 0; i < faceToposCount; i++)
        {
            auto vShape = faceTopos[i];
            int vShapeArray[3]{ vShape.CmdId, vShape.VirtualTopoId, vShape.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), vShapeArray, 1, 3);
        }

        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidFillHole(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelFillHoleSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelFillHoleSolid*>(comm);
        if (rSolid == nullptr) return false;
        return readOperGeometrySolidDefeature(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidFillHole(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelFillHoleSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelFillHoleSolid*>(comm);
        if (rSolid == nullptr) return false;
        return writeOperGeometrySolidDefeature(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelSolid*>(comm);
        if (rSolid == nullptr) return false;
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelSolid*>(comm);
        if (rSolid == nullptr) return false;
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidClosedSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelClosedSurfaceSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelClosedSurfaceSolid*>(comm);
        if (rSolid == nullptr) return false;
        int count = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < count; i++)
        {
            int faceArray[3];
            if (!readIntAttribute(h5Group, std::to_string(i), faceArray, 1, 3)) return false;
            Interface::VirtualShape vshape(faceArray[0], faceArray[1], faceArray[2]);
            rSolid->addFace(vshape);
        }
        return readOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidClosedSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelClosedSurfaceSolid* csSolid = dynamic_cast<Interface::FITKAbsGeoModelClosedSurfaceSolid*>(comm);
        if (csSolid == nullptr) return false;

        auto faces = csSolid->faces();
        int count = faces.size();
        for (int i = 0; i < count; i++)
        {
            auto face = faces[i];
            int faceArray[3]{ face.CmdId, face.VirtualTopoId, face.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), faceArray, 1, 3);
        }
        writeIntAttribute(h5Group, "Count", &count);
        return writeOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidExtrude(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelExtrudeSolid* eSolid = dynamic_cast<Interface::FITKAbsGeoModelExtrudeSolid*>(comm);
        if (eSolid == nullptr) return false;

        auto sourceSurface = eSolid->sourceSurface();
        int sourceSurfaceArray[3];
        double directionArray[3];
        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3)) return false;
        Interface::VirtualShape vShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]);
        eSolid->setSourceSurface(vShape);

        if (!readDoubleAttribute(h5Group, "Direction", directionArray, 1, 3)) return false;
        eSolid->setDirection(directionArray[0], directionArray[1], directionArray[2]);
        double length = readDoubleAttribute(h5Group, "Length");
        eSolid->setLength(length);

        return readOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidExtrude(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelExtrudeSolid* eSolid = dynamic_cast<Interface::FITKAbsGeoModelExtrudeSolid*>(comm);
        if (eSolid == nullptr) return false;

        auto sourceSurface = eSolid->sourceSurface();
        int sourceSurfaceArray[3]{ sourceSurface.CmdId,sourceSurface.VirtualTopoId, sourceSurface.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3);

        auto direction = eSolid->direction();
        double directionArray[3]{ direction[0],direction[1],direction[2] };
        writeDoubleAttribute(h5Group, "Direction", directionArray, 1, 3);
        double length = eSolid->length();
        writeDoubleAttribute(h5Group, "Length", &length);

        return writeOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidRevol(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRevolSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelRevolSolid*>(comm);
        if (rSolid == nullptr) return false;

        int sourceSurfaceArray[3];
        double rotateAxisPoint1[3], rotateAxisPoint2[3];
        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3)) return false;
        Interface::VirtualShape vShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]);
        rSolid->setSourceSurface(vShape);

        if (!readDoubleAttribute(h5Group, "RotateAxisPoint1", rotateAxisPoint1, 1, 3)) return false;
        rSolid->setRotateAxisPoint1(rotateAxisPoint1[0], rotateAxisPoint1[1], rotateAxisPoint1[2]);

        if (!readDoubleAttribute(h5Group, "RotateAxisPoint2", rotateAxisPoint2, 1, 3)) return false;
        rSolid->setRotateAxisPoint2(rotateAxisPoint2[0], rotateAxisPoint2[1], rotateAxisPoint2[2]);

        return readOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidRevol(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelRevolSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelRevolSolid*>(comm);
        if (rSolid == nullptr) return false;

        auto sourceSurface = rSolid->sourceSurface();
        int sourceSurfaceArray[3]{ sourceSurface.CmdId,sourceSurface.VirtualTopoId, sourceSurface.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3);

        std::array<double, 3>  rotateAxisPoint1 = rSolid->rotateAxisPoint1();
        double rotateAxisPoint1Array[3]{ rotateAxisPoint1[0], rotateAxisPoint1[1], rotateAxisPoint1[2] };
        writeDoubleAttribute(h5Group, "RotateAxisPoint1", rotateAxisPoint1Array, 1, 3);

        std::array<double, 3>  rotateAxisPoint2 = rSolid->rotateAxisPoint2();
        double rotateAxisPoint2Array[3]{ rotateAxisPoint2[0], rotateAxisPoint2[1], rotateAxisPoint2[2] };
        writeDoubleAttribute(h5Group, "RotateAxisPoint2", rotateAxisPoint2Array, 1, 3);

        return writeOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidSweep(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSweepSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelSweepSolid*>(comm);
        if (rSolid == nullptr) return false;
        int profileArray[2], curveArray[2];
        if (!readIntAttribute(h5Group, "Profile", profileArray, 1, 3)) return false;
        Interface::VirtualShape profile(profileArray[0], profileArray[1], profileArray[2]);
        rSolid->setProfile(profile);

        if (!readIntAttribute(h5Group, "Curve", curveArray, 1, 3)) return false;
        Interface::VirtualShape curve(curveArray[0], curveArray[1], curveArray[2]);
        rSolid->setCurve(curve);

        return readOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidSweep(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSweepSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelSweepSolid*>(comm);
        if (rSolid == nullptr) return false;

        auto profile = rSolid->profile();
        int profileArray[3]{ profile.CmdId,profile.VirtualTopoId, profile.VirtualTopoIndex };
        writeIntAttribute(h5Group, "Profile", profileArray, 1, 3);

        auto curve = rSolid->curve();
        int curveArray[3]{ curve.CmdId,curve.VirtualTopoId, curve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "Curve", curveArray, 1, 3);

        return writeOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidMultiSection(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelMultiSectionSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelMultiSectionSolid*>(comm);
        if (rSolid == nullptr) return false;

        int count = readIntAttribute(h5Group, "Count");
        int sectionArray[3];
        for (int i = 0; i < count; i++)
        {
            if (!readIntAttribute(h5Group, std::to_string(i), sectionArray, 1, 3)) return false;
            Interface::VirtualShape section(sectionArray[0], sectionArray[1], sectionArray[2]);
            rSolid->addSection(section);
        }
        return writeOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidMultiSection(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelMultiSectionSolid* rSolid = dynamic_cast<Interface::FITKAbsGeoModelMultiSectionSolid*>(comm);
        if (rSolid == nullptr) return false;

        auto sections = rSolid->sections();
        int count = sections.size();
        for (int i = 0; i < count; i++)
        {
            auto section = sections[i];
            int sectionArray[3]{ section.CmdId,section.VirtualTopoId, section.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), sectionArray, 1, 3);
        }
        writeIntAttribute(h5Group, "Count", &count);
        return writeOperGeometrySolidBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::readOperGeometrySolidStiffener(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoStiffener* stiffener = dynamic_cast<Interface::FITKAbsGeoStiffener*>(comm);
        if (stiffener == nullptr) return false;
        int source[3], profile[3];
        if (!readIntAttribute(h5Group, "SourceShape", source, 1, 3)) return false;
        if (!readIntAttribute(h5Group, "ProfileShape", profile, 1, 3)) return false;
        Interface::VirtualShape sourceShape(source[0], source[1], source[2]);
        Interface::VirtualShape profileShape(profile[0], profile[1], profile[2]);

        stiffener->setSourceShape(sourceShape);
        stiffener->setProfileShape(profileShape);

        double thickness1 = readDoubleAttribute(h5Group, "Thickness1");
        stiffener->setThickness1(thickness1);
        double thickness2 = readDoubleAttribute(h5Group, "Thickness2");
        stiffener->setThickness2(thickness2);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometrySolid::writeOperGeometrySolidStiffener(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoStiffener* stiffener = dynamic_cast<Interface::FITKAbsGeoStiffener*>(comm);
        if (stiffener == nullptr) return false;
        auto sourceShape = stiffener->sourceShape();
        int source[3]{ sourceShape.CmdId, sourceShape.VirtualTopoId, sourceShape.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceShape", source, 1, 3);
        auto profileShape = stiffener->profileShape();

        int profile[3]{ profileShape.CmdId, profileShape.VirtualTopoId, profileShape.VirtualTopoIndex };
        writeIntAttribute(h5Group, "ProfileShape", profile, 1, 3);
        double thickness1 = stiffener->thickness1();
        writeDoubleAttribute(h5Group, "Thickness1", &thickness1);
        double thickness2 = stiffener->thickness2();
        writeDoubleAttribute(h5Group, "Thickness2", &thickness2);
        return true;
    }

    //@}
}   // namespace IO
