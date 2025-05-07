#include "FITKInterfaceHDF5AdaptorBasicGeometryPoint.h"
//Geommtry
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelPoint.h"

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorBasicGeometryPoint::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorBasicGeometryPoint";
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readBasicGeometry(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeBasicGeometry(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometry(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        auto commType = comm->getGeometryCommandType();
        if (commType == Interface::FITKGeoEnum::FITKGeometryComType::FGTNone) return false;
        switch (commType)
        {
        case Interface::FITKGeoEnum::FGTPoint:                      return readBasicGeometryPointBase(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveEnd:                   return readBasicGeometryCurveEnd(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveEndDistance:           return readBasicGeometryCurveEndDistance(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveRadio:                 return readBasicGeometryCurveRadio(comm, h5Group);
        case Interface::FITKGeoEnum::FGTPointProjectionOnCurve:     return readBasicGeometryProjectionOnCurve(comm, h5Group);
        case Interface::FITKGeoEnum::FGTTwoCurveIntersectPoint:     return readBasicGeometryTwoCurveIntersection(comm, h5Group);
        case Interface::FITKGeoEnum::FGTPointProjectionOnSurface:   return readBasicGeometryPointProjectionOnSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveIntersectSurface:      return readBasicGeometryCurveIntersectionSurface(comm, h5Group);
        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometry(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        auto commType = comm->getGeometryCommandType();
        if (commType == Interface::FITKGeoEnum::FITKGeometryComType::FGTNone) return false;
        switch (commType)
        {
        case Interface::FITKGeoEnum::FGTPoint:                      return writeBasicGeometryPointBase(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveEnd:                   return writeBasicGeometryCurveEnd(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveEndDistance:           return writeBasicGeometryCurveEndDistance(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveRadio:                 return writeBasicGeometryCurveRadio(comm, h5Group);
        case Interface::FITKGeoEnum::FGTPointProjectionOnCurve:     return writeBasicGeometryProjectionOnCurve(comm, h5Group);
        case Interface::FITKGeoEnum::FGTTwoCurveIntersectPoint:     return writeBasicGeometryTwoCurveIntersection(comm, h5Group);
        case Interface::FITKGeoEnum::FGTPointProjectionOnSurface:   return writeBasicGeometryPointProjectionOnSurface(comm, h5Group);
        case Interface::FITKGeoEnum::FGTCurveIntersectSurface:      return writeBasicGeometryCurveIntersectionSurface(comm, h5Group);
        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryPointBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelPoint* point = dynamic_cast<Interface::FITKAbsGeoModelPoint*>(comm);
        if (point == nullptr) return false;
        QList<double> xyz;
        if (!readDoubleAttrbuteDataSet(h5Group, "Point", xyz, 1, 3)) return false;
        point->setCoord(xyz[0], xyz[1], xyz[2]);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryPointBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelPoint* point = dynamic_cast<Interface::FITKAbsGeoModelPoint*>(comm);
        if (point == nullptr) return false;
        double p[3]{ point->x(),point->y(), point->z() };
        writeDoubleAttribute(h5Group, "Point", &p, 1, 3);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryCurveEnd(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveEnd* curveEnd = dynamic_cast<Interface::FITKAbsGeoModelCurveEnd*>(comm);
        if (!curveEnd) return false;
        int sourceCurveArray[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurveArray, 1, 3)) return false;
        Interface::VirtualShape vShape(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]);
        curveEnd->setSourceCurve(vShape);
        bool useStartEnd = readBoolAttribute(h5Group, "UseStartEnd");
        curveEnd->setUseStartEnd(useStartEnd);
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryCurveEnd(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveEnd* curveEnd = dynamic_cast<Interface::FITKAbsGeoModelCurveEnd*>(comm);
        if (!curveEnd) return false;
        auto sourceCurve = curveEnd->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId,sourceCurve.VirtualTopoId,sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurveArray, 1, 3);
        bool useStartEnd = curveEnd->useStartEnd();
        writeBoolAttribute(h5Group, "UseStartEnd", &useStartEnd);

        return writeBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryCurveEndDistance(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveEndDistance* curveEnd = dynamic_cast<Interface::FITKAbsGeoModelCurveEndDistance*>(comm);
        if (!curveEnd) return false;
        int sourceCurveArray[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurveArray, 1, 3)) return false;
        Interface::VirtualShape vShape(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]);
        curveEnd->setSourceCurve(vShape);
        bool useStartEnd = readBoolAttribute(h5Group, "UseStartEnd");
        curveEnd->setUseStartEnd(useStartEnd);
        double distance = readDoubleAttribute(h5Group, "Distance");
        curveEnd->setDistance(distance);
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryCurveEndDistance(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveEndDistance* curveEnd = dynamic_cast<Interface::FITKAbsGeoModelCurveEndDistance*>(comm);
        if (!curveEnd) return false;
        auto sourceCurve = curveEnd->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId,sourceCurve.VirtualTopoId,sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurveArray, 1, 3);
        bool useStartEnd = curveEnd->useStartEnd();
        writeBoolAttribute(h5Group, "UseStartEnd", &useStartEnd);
        double distance = curveEnd->distance();
        writeDoubleAttribute(h5Group, "Distance", &distance);
        return writeBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryCurveRadio(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveRadio* curveRadio = dynamic_cast<Interface::FITKAbsGeoModelCurveRadio*>(comm);
        if (!curveRadio) return false;
        int sourceCurveArray[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurveArray, 1, 3)) return false;
        Interface::VirtualShape vShape(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]);
        curveRadio->setSourceCurve(vShape);
        double radio = readDoubleAttribute(h5Group, "Radio");
        curveRadio->setRadio(radio);
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryCurveRadio(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveRadio* curveRadio = dynamic_cast<Interface::FITKAbsGeoModelCurveRadio*>(comm);
        if (!curveRadio) return false;
        auto sourceCurve = curveRadio->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId,sourceCurve.VirtualTopoId,sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurveArray, 1, 3);
        double radio = curveRadio->radio();
        writeDoubleAttribute(h5Group, "Radio", &radio);
        return writeBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryProjectionOnCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelPointProjectionOnCurve* projectionOnCurve = dynamic_cast<Interface::FITKAbsGeoModelPointProjectionOnCurve*>(comm);
        if (!projectionOnCurve) return false;
        int sourcePointArray[3], sourceCurveArray[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourcePointArray, 1, 3)) return false;
        Interface::VirtualShape vShapePoint(sourcePointArray[0], sourcePointArray[1], sourcePointArray[2]);
        projectionOnCurve->setSourcePoint(vShapePoint);
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurveArray, 1, 3)) return false;
        Interface::VirtualShape vShapeCurve(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]);
        projectionOnCurve->setSourceCurve(vShapeCurve);
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryProjectionOnCurve(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelPointProjectionOnCurve* projectionOnCurve = dynamic_cast<Interface::FITKAbsGeoModelPointProjectionOnCurve*>(comm);
        if (!projectionOnCurve) return false;

        auto sourcePoint = projectionOnCurve->sourcePoint();
        int sourcePointArray[3]{ sourcePoint.CmdId,sourcePoint.VirtualTopoId,sourcePoint.VirtualTopoIndex };
        writeIntAttribute(h5Group, "sourcePoint", &sourcePointArray, 1, 3);
        auto sourceCurve = projectionOnCurve->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId,sourceCurve.VirtualTopoId,sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurveArray, 1, 3);
        return writeBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryTwoCurveIntersection(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelTwoCurveIntersection* twoCurveIntersection = dynamic_cast<Interface::FITKAbsGeoModelTwoCurveIntersection*>(comm);
        if (!twoCurveIntersection) return false;
        int sourceCurve1Array[3], sourceCurve2Array[3];
        if (!readIntAttribute(h5Group, "SourceCurve1", sourceCurve1Array, 1, 3)) return false;
        Interface::VirtualShape sourceCurve1(sourceCurve1Array[0], sourceCurve1Array[1], sourceCurve1Array[2]);

        if (!readIntAttribute(h5Group, "SourceCurve2", sourceCurve2Array, 1, 3)) return false;
        Interface::VirtualShape sourceCurve2(sourceCurve2Array[0], sourceCurve2Array[1], sourceCurve2Array[2]);
        twoCurveIntersection->setSourceCurve(sourceCurve1, sourceCurve2);

        //不需要处理交点
        //int count = readIntAttribute(h5Group, "Count");
        //double pArray[3];
        //for (int i = 0; i < count; i++)
        //{
        //    if (!readDoubleAttribute(h5Group, std::to_string(i), pArray, 1, 3)) return false;
        //
        //}
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryTwoCurveIntersection(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelTwoCurveIntersection* twoCurveIntersection = dynamic_cast<Interface::FITKAbsGeoModelTwoCurveIntersection*>(comm);
        if (!twoCurveIntersection) return false;

        auto sourceCurve1 = twoCurveIntersection->sourceCurve1();
        int sourceCurve1Array[3]{ sourceCurve1.CmdId,sourceCurve1.VirtualTopoId,sourceCurve1.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve1", &sourceCurve1Array, 1, 3);
        auto sourceCurve2 = twoCurveIntersection->sourceCurve2();
        int sourceCurve2Array[3]{ sourceCurve2.CmdId,sourceCurve2.VirtualTopoId,sourceCurve2.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve2", &sourceCurve2Array, 1, 3);
        auto points = twoCurveIntersection->getResultPoints();
        int count = points.size();
        writeIntAttribute(h5Group, "Count", &count);
        for (int i = 0; i < count; i++)
        {
            auto point = points[i];
            double pArray[3]{ point[0], point[1], point[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), &pArray, 1, 3);
        }
        return writeBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryPointProjectionOnSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelPointProjectionOnSurface* ppOnSurface = dynamic_cast<Interface::FITKAbsGeoModelPointProjectionOnSurface*>(comm);
        if (!ppOnSurface) return false;
        int sourcePointArray[3], sourceSurfaceArray[3];
        if (!readIntAttribute(h5Group, "SourcePoint", sourcePointArray, 1, 3)) return false;
        ppOnSurface->setSourcePoint(Interface::VirtualShape(sourcePointArray[0], sourcePointArray[1], sourcePointArray[2]));
        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3)) return false;
        ppOnSurface->setSourceSurface(Interface::VirtualShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]));
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryPointProjectionOnSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelPointProjectionOnSurface* ppOnSurface = dynamic_cast<Interface::FITKAbsGeoModelPointProjectionOnSurface*>(comm);
        if (!ppOnSurface) return false;
        auto sourcePoint = ppOnSurface->sourcePoint();
        int sourcePointArray[3]{ sourcePoint.CmdId,sourcePoint.VirtualTopoId, sourcePoint.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourcePoint", &sourcePointArray, 1, 3);
        auto sourceSurface = ppOnSurface->sourceSurface();
        int sourceSurfaceArray[3]{ sourceSurface.CmdId,sourceSurface.VirtualTopoId, sourceSurface.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", &sourceSurface, 1, 3);
        return writeBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::readBasicGeometryCurveIntersectionSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveIntersectionSurface* cIntersectionSurface = dynamic_cast<Interface::FITKAbsGeoModelCurveIntersectionSurface*>(comm);
        if (!cIntersectionSurface) return false;
        int sourceCurveArray[3], sourceSurfaceArray[3];
        if (!readIntAttribute(h5Group, "SourceCurve", sourceCurveArray, 1, 3)) return false;
        cIntersectionSurface->setSourceCurve(Interface::VirtualShape(sourceCurveArray[0], sourceCurveArray[1], sourceCurveArray[2]));
        if (!readIntAttribute(h5Group, "SourceSurface", sourceSurfaceArray, 1, 3)) return false;
        cIntersectionSurface->setSourceSurface(Interface::VirtualShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]));
        return readBasicGeometryPointBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryPoint::writeBasicGeometryCurveIntersectionSurface(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurveIntersectionSurface* cIntersectionSurface = dynamic_cast<Interface::FITKAbsGeoModelCurveIntersectionSurface*>(comm);
        if (!cIntersectionSurface) return false;
        auto sourceCurve = cIntersectionSurface->sourceCurve();
        int sourceCurveArray[3]{ sourceCurve.CmdId,sourceCurve.VirtualTopoId,sourceCurve.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceCurve", &sourceCurveArray, 1, 3);
        auto sourceSurface = cIntersectionSurface->sourceSurface();
        int sourceSurfaceArray[3]{ sourceSurface.CmdId,sourceSurface.VirtualTopoId, sourceSurface.VirtualTopoIndex };
        writeIntAttribute(h5Group, "SourceSurface", &sourceSurface, 1, 3);
        return writeBasicGeometryPointBase(comm, h5Group);
    }

    //@}
}   // namespace IO
