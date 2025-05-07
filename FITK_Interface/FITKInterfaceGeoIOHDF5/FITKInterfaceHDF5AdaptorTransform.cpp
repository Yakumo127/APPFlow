#include "FITKInterfaceHDF5AdaptorTransform.h"
#include "FITKInterfaceHDF5AdaptorOperGeometry.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometryCurve.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometryFace.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometrySolid.h"

//Geommtry
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoTransformation.h"

namespace IO
{
    QString FITKInterfaceHDF5AdaptorTransform::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorTransform";
    }

    bool FITKInterfaceHDF5AdaptorTransform::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return read(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return write(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::read(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (!comm) return false;
        auto t = comm->getGeometryCommandType();
        switch (t)
        {
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTTransform:              return readTransformation(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTTransformByDirAndDis:   return readTransformationByDirAndDis(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTTransformByTwoPoints:   return readTransformationByTwoPoints(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTRotate:                 return readRotate(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTScale:                  return readScale(comm, h5Group);
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorTransform::write(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (!comm) return false;
        auto t = comm->getGeometryCommandType();
        switch (t)
        {
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTTransform:              return writeTransformation(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTTransformByDirAndDis:   return writeTransformationByDirAndDis(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTTransformByTwoPoints:   return writeTransformationByTwoPoints(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTRotate:                 return writeRotate(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTScale:                  return writeScale(comm, h5Group);
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorTransform::readTransfromBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoTransformation*>(comm);
        if (transform == nullptr) return false;
        int sShape[3];
        if (!readIntAttribute(h5Group, "SourceShape", sShape, 1, 3)) return false;
        Interface::VirtualShape vShape(sShape[0], sShape[1], sShape[2]);
        transform->setSourceShape(vShape);
        bool isCopy = readBoolAttribute(h5Group, "IsCopy");
        transform->setCopy(isCopy);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorTransform::writeTransfromBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoTransformation*>(comm);
        if (transform == nullptr) return false;
        int sShape[3];
        sShape[0] = transform->sourceShape().CmdId;
        sShape[1] = transform->sourceShape().VirtualTopoId;
        sShape[2] = transform->sourceShape().VirtualTopoIndex;
        writeIntAttribute(h5Group, "SourceShape", sShape, 1, 3);
        bool isCopy = transform->isCopy();
        writeBoolAttribute(h5Group, "IsCopy", &isCopy);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorTransform::readTransformation(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelTransform*>(comm);
        if (transform == nullptr) return false;
        double v3List[3];
        if (!readDoubleAttribute(h5Group, "Vector", v3List, 1, 3)) return false;
        transform->setVector(v3List[0], v3List[1], v3List[2]);
        return readTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::writeTransformation(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelTransform*>(comm);
        if (transform == nullptr) return false;
        double v3List[3];
        auto v3 = transform->vector();
        v3List[0] = v3[0];
        v3List[1] = v3[1];
        v3List[2] = v3[2];
        writeDoubleAttribute(h5Group, "Vector", v3List, 1, 3);
        return writeTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::readTransformationByTwoPoints(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelTransformByTwoPoints*>(comm);
        if (transform == nullptr) return false;
        double sPoint[3], ePoint[3];
        if (!readDoubleAttribute(h5Group, "SPoint", sPoint, 1, 3)) return false;
        transform->setStartPoint(sPoint[0], sPoint[1], sPoint[2]);
        if (!readDoubleAttribute(h5Group, "EPoint", ePoint, 1, 3)) return false;
        transform->setEndPoint(ePoint[0], ePoint[1], ePoint[2]);
        return readTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::writeTransformationByTwoPoints(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelTransformByTwoPoints*>(comm);
        if (transform == nullptr) return false;
        double sPoint[3], ePoint[3];
        auto sPointArray = transform->startPoint();
        sPoint[0] = sPointArray[0];
        sPoint[1] = sPointArray[1];
        sPoint[2] = sPointArray[2];
        writeDoubleAttribute(h5Group, "SPoint", sPoint, 1, 3);
        auto ePointArray = transform->endPoint();
        ePoint[0] = ePointArray[0];
        ePoint[1] = ePointArray[1];
        ePoint[2] = ePointArray[2];
        writeDoubleAttribute(h5Group, "EPoint", ePoint, 1, 3);
        return writeTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::readTransformationByDirAndDis(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelTransformByDirAndDis*>(comm);
        if (transform == nullptr) return false;
        double dirList[3];
        if (!readDoubleAttribute(h5Group, "Direction", dirList, 1, 3)) return false;
        transform->setDirection(dirList[0], dirList[1], dirList[2]);
        double dis = readDoubleAttribute(h5Group, "Distance");
        transform->setDistance(dis);
        return readTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::writeTransformationByDirAndDis(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelTransformByDirAndDis*>(comm);
        if (transform == nullptr) return false;
        double dirList[3];
        auto dir = transform->direction();
        dirList[0] = dir[0];
        dirList[1] = dir[1];
        dirList[2] = dir[2];
        writeDoubleAttribute(h5Group, "Direction", dirList, 1, 3);
        double dis = transform->distance();
        writeDoubleAttribute(h5Group, "Distance", &dis);
        return writeTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::readRotate(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelRotate*>(comm);
        if (transform == nullptr) return false;
        double sPoint[3], ePoint[3];
        if (!readDoubleAttribute(h5Group, "SPoint", sPoint, 1, 3)) return false;
        transform->setAxisStartPoint(sPoint[0], sPoint[1], sPoint[2]);
        if (!readDoubleAttribute(h5Group, "EPoint", ePoint, 1, 3)) return false;
        transform->setAxisEndPoint(ePoint[0], ePoint[1], ePoint[2]);

        double degree = readDoubleAttribute(h5Group, "Degree");
        transform->setDegree(degree);
        double radian = readDoubleAttribute(h5Group, "Radian");
        transform->setRadian(radian);
        return readTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::writeRotate(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelRotate*>(comm);
        if (transform == nullptr) return false;
        double sPoint[3], ePoint[3];
        auto sPointArray = transform->axisStartPoint();
        sPoint[0] = sPointArray[0];
        sPoint[1] = sPointArray[1];
        sPoint[2] = sPointArray[2];
        writeDoubleAttribute(h5Group, "SPoint", sPoint, 1, 3);
        auto ePointArray = transform->axisEndPoint();
        ePoint[0] = ePointArray[0];
        ePoint[1] = ePointArray[1];
        ePoint[2] = ePointArray[2];
        writeDoubleAttribute(h5Group, "EPoint", ePoint, 1, 3);
        double degree = transform->degree();
        writeDoubleAttribute(h5Group, "Degree", &degree);
        double radian = transform->radian();
        writeDoubleAttribute(h5Group, "Radian", &radian);
        return writeTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::readScale(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelScale*>(comm);
        if (transform == nullptr) return false;
        double factors[3], basePoint[3];
        if (!readDoubleAttribute(h5Group, "Factors", factors, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "BasePoint", basePoint, 1, 3)) return false;
        transform->setFactors(factors[0], factors[1], factors[2]);
        transform->setBasePoint(basePoint[0], basePoint[1], basePoint[2]);
        return readTransfromBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorTransform::writeScale(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto transform = dynamic_cast<Interface::FITKAbsGeoModelScale*>(comm);
        if (transform == nullptr) return false;
        double factors[3], basePoint[3];
        auto factorsArray = transform->factors();
        factors[0] = factorsArray[0];
        factors[1] = factorsArray[1];
        factors[2] = factorsArray[2];
        writeDoubleAttribute(h5Group, "Factors", factors, 1, 3);
        auto basePointArray = transform->basePoint();
        basePoint[0] = basePointArray[0];
        basePoint[1] = basePointArray[1];
        basePoint[2] = basePointArray[2];
        writeDoubleAttribute(h5Group, "BasePoint", basePoint, 1, 3);
        return writeTransfromBase(comm, h5Group);
    }

}   // namespace IO
