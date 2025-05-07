#include "FITKInterfaceHDF5AdaptorBasicGeometryCurve.h"
//Interface
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelCurve.h"


namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorBasicGeometryCurve::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorBasicGeometryCurve";
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryCurveBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurve* curveBase = dynamic_cast<Interface::FITKAbsGeoModelCurve*>(comm);
        if (!curveBase) return false;

        double originArray[3], xDirectionList[3], yDirectionList[3], zDirectionList[3];
        if (!readDoubleAttribute(h5Group, "Origin", originArray, 1, 3)) return false;
        curveBase->setOrigin(originArray[0], originArray[1], originArray[2]);

        //类内计算X 不需要设置
        //if (!readDoubleAttribute(h5Group, "XDirection", xDirectionList, 1, 3)) return false;
        //curveBase->setXDirection(xDirectionList[0], xDirectionList[1], xDirectionList[2]);

        if (!readDoubleAttribute(h5Group, "YDirection", yDirectionList, 1, 3)) return false;
        curveBase->setYDirection(yDirectionList[0], yDirectionList[1], yDirectionList[2]);

        if (!readDoubleAttribute(h5Group, "ZDirection", zDirectionList, 1, 3)) return false;
        curveBase->setZDirection(zDirectionList[0], zDirectionList[1], zDirectionList[2]);

        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryCurveBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCurve* curveBase = dynamic_cast<Interface::FITKAbsGeoModelCurve*>(comm);
        if (!curveBase) return false;
        auto origin = curveBase->origin();
        double originList[3]{ origin[0],origin[1],origin[2] };
        writeDoubleAttribute(h5Group, "Origin", originList, 1, 3);
        auto xDirection = curveBase->xDirection();
        double xDirectionList[3]{ xDirection[0],xDirection[1],xDirection[2] };
        writeDoubleAttribute(h5Group, "XDirection", xDirectionList, 1, 3);
        auto yDirection = curveBase->yDirection();
        double yDirectionList[3]{ yDirection[0],yDirection[1],yDirection[2] };
        writeDoubleAttribute(h5Group, "YDirection", yDirectionList, 1, 3);
        auto zDirection = curveBase->zDirection();
        double zDirectionList[3]{ zDirection[0],zDirection[1],zDirection[2] };
        writeDoubleAttribute(h5Group, "ZDirection", zDirectionList, 1, 3);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryCurveConicBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryCurveConicBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelLine* line = dynamic_cast<Interface::FITKAbsGeoModelLine*>(comm);
        if (!line) return false;
        double dirList[3];
        if (!readDoubleAttribute(h5Group, "Dir", dirList, 1, 3)) return false;
        line->setDir(dirList[0], dirList[1], dirList[2]);
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryLine(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelLine* line = dynamic_cast<Interface::FITKAbsGeoModelLine*>(comm);
        if (!line) return false;
        auto dir = line->dir();
        double dirList[3]{ dir[0],dir[1],dir[2] };
        writeDoubleAttribute(h5Group, "Dir", dirList, 1, 3);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometrySegment(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSegment* segment = dynamic_cast<Interface::FITKAbsGeoModelSegment*>(comm);
        if (!segment) return false;
        double sPointList[3], ePointList[3];
        if (!readDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3)) return false;
        segment->setStartPoint(sPointList[0], sPointList[1], sPointList[2]);

        if (!readDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3)) return false;
        segment->setEndPoint(ePointList[0], ePointList[1], ePointList[2]);
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometrySegment(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSegment* segment = dynamic_cast<Interface::FITKAbsGeoModelSegment*>(comm);
        if (!segment) return false;
        auto sPoint = segment->startPoint();
        double sPointList[3]{ sPoint[0],sPoint[1],sPoint[2] };
        writeDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3);

        auto ePoint = segment->endPoint();
        double ePointList[3]{ ePoint[0],ePoint[1],ePoint[2] };
        writeDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3);
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryWire(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelWire* wire = dynamic_cast<Interface::FITKAbsGeoModelWire*>(comm);
        if (!wire) return false;
        double p[3];
        int count = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < count; i++)
        {
            if (!readDoubleAttribute(h5Group, std::to_string(i), p, 1, 3)) return false;
            wire->addPoint(p[0], p[1], p[2]);
        }
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryWire(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelWire* wire = dynamic_cast<Interface::FITKAbsGeoModelWire*>(comm);
        if (!wire) return false;
        int count = wire->count();
        writeIntAttribute(h5Group, "Count", &count);
        for (int i = 0; i < count; i++)
        {
            auto stdDoubleArray = wire->point(i);
            double p[3]{ stdDoubleArray[0], stdDoubleArray[1], stdDoubleArray[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), p, 1, 3);
        }
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryConic(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryConic(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryCircle(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCircle* circle = dynamic_cast<Interface::FITKAbsGeoModelCircle*>(comm);
        if (!circle) return false;
        double radius = readDoubleAttribute(h5Group, "Radius");
        circle->setRadius(radius);
        return readBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryCircle(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCircle* circle = dynamic_cast<Interface::FITKAbsGeoModelCircle*>(comm);
        if (!circle) return false;
        double radius = circle->radius();
        writeDoubleAttribute(h5Group, "Radius", &radius);
        return writeBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryCircleArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCircleArc* circleArc = dynamic_cast<Interface::FITKAbsGeoModelCircleArc*>(comm);
        if (!circleArc) return false;
        double sPointList[3], ePointList[3];
        if (!readDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3)) return false;
        circleArc->setStartPoint(sPointList[0], sPointList[1], sPointList[2]);

        if (!readDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3)) return false;
        circleArc->setEndPoint(ePointList[0], ePointList[1], ePointList[2]);
        return readBasicGeometryCircle(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryCircleArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCircleArc* circleArc = dynamic_cast<Interface::FITKAbsGeoModelCircleArc*>(comm);
        if (!circleArc) return false;
        auto sPoint = circleArc->startPoint();
        double sPointList[3]{ sPoint[0],sPoint[1],sPoint[2] };
        writeDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3);

        auto ePoint = circleArc->endPoint();
        double ePointList[3]{ ePoint[0],ePoint[1],ePoint[2] };
        writeDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3);
        return writeBasicGeometryCircle(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryThreePointsCircle(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsCircle* threePointsCircle = dynamic_cast<Interface::FITKAbsGeoModelThreePointsCircle*>(comm);
        if (!threePointsCircle) return false;
        const int pointCount = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < pointCount; i++)
        {
            double pointList[3];
            if (!readDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3)) return false;
            threePointsCircle->setPoint(i, pointList[0], pointList[1], pointList[2]);
        }
        return readBasicGeometryCircle(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryThreePointsCircle(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsCircle* threePointsCircle = dynamic_cast<Interface::FITKAbsGeoModelThreePointsCircle*>(comm);
        if (!threePointsCircle) return false;
        const int pointCount = 3;
        writeIntAttribute(h5Group, "Count", &pointCount);
        for (int i = 0; i < pointCount; i++)
        {
            auto point = threePointsCircle->point(i);
            double pointList[3]{ point[0],point[1],point[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3);
        }
        return writeBasicGeometryCircle(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryEllipse(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelEllipse* ellipse = dynamic_cast<Interface::FITKAbsGeoModelEllipse*>(comm);
        if (!ellipse) return false;
        double majorRadius = readDoubleAttribute(h5Group, "MajorRadius");
        ellipse->setMajorRadius(majorRadius);
        double minorRadius = readDoubleAttribute(h5Group, "MinorRadius");
        ellipse->setMinorRadius(minorRadius);
        return readBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryEllipse(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelEllipse* ellipse = dynamic_cast<Interface::FITKAbsGeoModelEllipse*>(comm);
        if (!ellipse) return false;
        double majorRadius = ellipse->majorRadius();
        writeDoubleAttribute(h5Group, "MajorRadius", &majorRadius);
        double minorRadius = ellipse->minorRadius();
        writeDoubleAttribute(h5Group, "MinorRadius", &minorRadius);
        return  writeBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryEllipseArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelEllipseArc* ellipseArc = dynamic_cast<Interface::FITKAbsGeoModelEllipseArc*>(comm);
        if (!ellipseArc) return false;
        double sPointList[3], ePointList[3];
        if (!readDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3)) return false;
        ellipseArc->setStartPoint(sPointList[0], sPointList[1], sPointList[2]);

        if (!readDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3)) return false;
        ellipseArc->setStartPoint(ePointList[0], ePointList[1], ePointList[2]);

        return readBasicGeometryEllipse(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryEllipseArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelEllipseArc* ellipseArc = dynamic_cast<Interface::FITKAbsGeoModelEllipseArc*>(comm);
        if (!ellipseArc) return false;
        auto sPoint = ellipseArc->startPoint();
        double sPointList[3]{ sPoint[0],sPoint[1],sPoint[2] };
        writeDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3);

        auto ePoint = ellipseArc->endPoint();
        double ePointList[3]{ ePoint[0],ePoint[1],ePoint[2] };
        writeDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3);
        return writeBasicGeometryEllipse(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryThreePointsEllipse(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsEllipse* tpEllipse = dynamic_cast<Interface::FITKAbsGeoModelThreePointsEllipse*>(comm);
        if (!tpEllipse) return false;
        double majorPointList[3], minorPointList[3];
        if (!readDoubleAttribute(h5Group, "MajorPoint", majorPointList, 1, 3)) return false;
        tpEllipse->setMajorPoint(majorPointList[0], majorPointList[1], majorPointList[2]);
        if (!readDoubleAttribute(h5Group, "MinorPoint", minorPointList, 1, 3)) return false;
        tpEllipse->setMinorPoint(minorPointList[0], minorPointList[1], minorPointList[2]);
        return readBasicGeometryConic(comm, h5Group);
        //return readBasicGeometryEllipse(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryThreePointsEllipse(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsEllipse* tpEllipse = dynamic_cast<Interface::FITKAbsGeoModelThreePointsEllipse*>(comm);
        if (!tpEllipse) return false;
        auto majorPoint = tpEllipse->majorPoint();
        double majorPointList[3]{ majorPoint[0],majorPoint[1],majorPoint[2] };
        writeDoubleAttribute(h5Group, "MajorPoint", majorPointList, 1, 3);

        auto minorPoint = tpEllipse->minorPoint();
        double minorPointList[3]{ minorPoint[0],minorPoint[1],minorPoint[2] };
        writeDoubleAttribute(h5Group, "MinorPoint", minorPointList, 1, 3);
        return writeBasicGeometryConic(comm, h5Group);
        //return writeBasicGeometryEllipse(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryHyperbola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelHyperbola* hyperbola = dynamic_cast<Interface::FITKAbsGeoModelHyperbola*>(comm);
        if (!hyperbola) return false;
        double majorRadius = readDoubleAttribute(h5Group, "MajorRadius");
        hyperbola->setMajorRadius(majorRadius);
        double minorRadius = readDoubleAttribute(h5Group, "MinorRadius");
        hyperbola->setMinorRadius(minorRadius);
        return readBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryHyperbola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelHyperbola* hyperbola = dynamic_cast<Interface::FITKAbsGeoModelHyperbola*>(comm);
        if (!hyperbola) return false;
        double majorRadius = hyperbola->majorRadius();
        writeDoubleAttribute(h5Group, "MajorRadius", &majorRadius);
        double minorRadius = hyperbola->minorRadius();
        writeDoubleAttribute(h5Group, "MinorRadius", &minorRadius);
        return writeBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryThreePointsHyperbola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsHyperbola* tpHyperbola = dynamic_cast<Interface::FITKAbsGeoModelThreePointsHyperbola*>(comm);
        if (!tpHyperbola) return false;
        double majorPointList[3], minorPointList[3];
        if (!readDoubleAttribute(h5Group, "MajorPoint", majorPointList, 1, 3)) return false;
        tpHyperbola->setMajorPoint(majorPointList[0], majorPointList[1], majorPointList[2]);

        if (!readDoubleAttribute(h5Group, "MinorPoint", minorPointList, 1, 3)) return false;
        tpHyperbola->setMinorPoint(minorPointList[0], minorPointList[1], minorPointList[2]);
        return readBasicGeometryHyperbola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryThreePointsHyperbola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsHyperbola* tpHyperbola = dynamic_cast<Interface::FITKAbsGeoModelThreePointsHyperbola*>(comm);
        if (!tpHyperbola) return false;
        auto majorPoint = tpHyperbola->majorPoint();
        double majorPointList[3]{ majorPoint[0],majorPoint[1],majorPoint[2] };
        writeDoubleAttribute(h5Group, "MajorPoint", majorPointList, 1, 3);

        auto minorPoint = tpHyperbola->minorPoint();
        double minorPointList[3]{ minorPoint[0],minorPoint[1],minorPoint[2] };
        writeDoubleAttribute(h5Group, "MinorPoint", minorPointList, 1, 3);
        return writeBasicGeometryHyperbola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryHyperbolaArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelHyperbolaArc* hyperbolaArc = dynamic_cast<Interface::FITKAbsGeoModelHyperbolaArc*>(comm);
        if (!hyperbolaArc) return false;
        double sPointList[3], ePointList[3];
        if (!readDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3)) return false;
        hyperbolaArc->setStartPoint(sPointList[0], sPointList[1], sPointList[2]);

        if (!readDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3)) return false;
        hyperbolaArc->setStartPoint(ePointList[0], ePointList[1], ePointList[2]);
        return readBasicGeometryHyperbola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryHyperbolaArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelHyperbolaArc* hyperbolaArc = dynamic_cast<Interface::FITKAbsGeoModelHyperbolaArc*>(comm);
        if (!hyperbolaArc) return false;
        auto sPoint = hyperbolaArc->startPoint();
        double sPointList[3]{ sPoint[0],sPoint[1],sPoint[2] };
        writeDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3);

        auto ePoint = hyperbolaArc->endPoint();
        double ePointList[3]{ ePoint[0],ePoint[1],ePoint[2] };
        writeDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3);
        return writeBasicGeometryHyperbola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryParabola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelParabola* parabola = dynamic_cast<Interface::FITKAbsGeoModelParabola*>(comm);
        if (!parabola) return false;
        double focalLength = readDoubleAttribute(h5Group, "FocalLength");
        parabola->setFocalLength(focalLength);
        return readBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryParabola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelParabola* parabola = dynamic_cast<Interface::FITKAbsGeoModelParabola*>(comm);
        if (!parabola) return false;
        double focalLength = parabola->focalLength();
        writeDoubleAttribute(h5Group, "FocalLength", &focalLength);
        return writeBasicGeometryConic(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryThreePointsParabola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsParabola* tpParabola = dynamic_cast<Interface::FITKAbsGeoModelThreePointsParabola*>(comm);
        if (!tpParabola) return false;
        double pointList[3];
        const int pointCount = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < pointCount; i++)
        {
            if (!readDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3)) return false;
            tpParabola->setPoint(i, pointList[0], pointList[1], pointList[2]);
        }
        return readBasicGeometryParabola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryThreePointsParabola(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelThreePointsParabola* tpParabola = dynamic_cast<Interface::FITKAbsGeoModelThreePointsParabola*>(comm);
        if (!tpParabola) return false;
        const int pointCount = 3;
        writeIntAttribute(h5Group, "Count", &pointCount);
        for (int i = 0; i < pointCount; i++)
        {
            auto point = tpParabola->point(i);
            double pointList[3]{ point[0],point[1],point[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3);
        }
        return writeBasicGeometryParabola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryParabolaArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelParabolaArc* parabolaArc = dynamic_cast<Interface::FITKAbsGeoModelParabolaArc*>(comm);
        if (!parabolaArc) return false;
        double sPointList[3], ePointList[3];
        if (!readDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3)) return false;
        parabolaArc->setStartPoint(sPointList[0], sPointList[1], sPointList[2]);

        if (!readDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3)) return false;
        parabolaArc->setEndPoint(ePointList[0], ePointList[1], ePointList[2]);
        return readBasicGeometryParabola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryParabolaArc(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelParabolaArc* parabolaArc = dynamic_cast<Interface::FITKAbsGeoModelParabolaArc*>(comm);
        if (!parabolaArc) return false;
        auto sPoint = parabolaArc->startPoint();
        double sPointList[3]{ sPoint[0],sPoint[1],sPoint[2] };
        writeDoubleAttribute(h5Group, "StartPoint", sPointList, 1, 3);

        auto ePoint = parabolaArc->endPoint();
        double ePointList[3]{ ePoint[0],ePoint[1],ePoint[2] };
        writeDoubleAttribute(h5Group, "EndPoint", ePointList, 1, 3);
        return writeBasicGeometryParabola(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryBeizeByControlPoints(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBeizeByControlPoints* beizeByControlPoints = dynamic_cast<Interface::FITKAbsGeoModelBeizeByControlPoints*>(comm);
        if (!beizeByControlPoints) return false;
        double pointList[3];
        int count = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < count; i++)
        {
            if (!readDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3)) return false;
            beizeByControlPoints->addControlPoint(pointList[0], pointList[1], pointList[2]);
        }
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryBeizeByControlPoints(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBeizeByControlPoints* beizeByControlPoints = dynamic_cast<Interface::FITKAbsGeoModelBeizeByControlPoints*>(comm);
        if (!beizeByControlPoints) return false;
        auto points = beizeByControlPoints->controlPoints();
        int count = points.size();
        writeIntAttribute(h5Group, "Count", &count);
        for (int i = 0; i < count; i++)
        {
            auto point = points[i];
            double pointList[3]{ point[0],point[1],point[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3);
        }
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::readBasicGeometryBsplineByThroughPoints(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBsplineByThroughPoints* bspByThroughPoints = dynamic_cast<Interface::FITKAbsGeoModelBsplineByThroughPoints*>(comm);
        if (!bspByThroughPoints) return false;
        double pointList[3];
        int count = readIntAttribute(h5Group, "Count");
        for (int i = 0; i < count; i++)
        {
            if (!readDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3)) return false;
            bspByThroughPoints->addThroughPoint(pointList[0], pointList[1], pointList[2]);
        }

        QList<Interface::VirtualShape> throughPointShapes;
        int ThroughPointShapesCount = readIntAttribute(h5Group, "ThroughPointShapesCount");
        for (int i = 0; i < ThroughPointShapesCount; i++)
        {
            double ThroughPointShapeArray[3];
            if (!readDoubleAttribute(h5Group, "ThroughPointShapes" + std::to_string(i), ThroughPointShapeArray, 1, 3)) return false;
            throughPointShapes.append(Interface::VirtualShape(ThroughPointShapeArray[0], ThroughPointShapeArray[1], ThroughPointShapeArray[2]));
        }
        bspByThroughPoints->setThroughPointShapes(throughPointShapes);
        return readBasicGeometryCurveBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometryCurve::writeBasicGeometryBsplineByThroughPoints(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBsplineByThroughPoints* bspByThroughPoints = dynamic_cast<Interface::FITKAbsGeoModelBsplineByThroughPoints*>(comm);
        if (!bspByThroughPoints) return false;
        auto points = bspByThroughPoints->throughPoints();
        int count = points.size();
        writeIntAttribute(h5Group, "Count", &count);
        for (int i = 0; i < count; i++)
        {
            auto point = points[i];
            double pointList[3]{ point[0],point[1],point[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), pointList, 1, 3);
        }

        QList<Interface::VirtualShape> throughPointShapes = bspByThroughPoints->throughPointShapes();
        int ThroughPointShapesCount = throughPointShapes.size();
        writeIntAttribute(h5Group, "ThroughPointShapesCount", &ThroughPointShapesCount);
        for (int i = 0; i < ThroughPointShapesCount; i++)
        {
            auto vShape = throughPointShapes[i];
            double ThroughPointShapeArray[3]{ vShape.CmdId,vShape.VirtualTopoId,vShape.VirtualTopoIndex };
            writeDoubleAttribute(h5Group, "ThroughPointShapes" + std::to_string(i), ThroughPointShapeArray, 1, 3);
        }
        return writeBasicGeometryCurveBase(comm, h5Group);
    }

    //@}
}   // namespace IO
