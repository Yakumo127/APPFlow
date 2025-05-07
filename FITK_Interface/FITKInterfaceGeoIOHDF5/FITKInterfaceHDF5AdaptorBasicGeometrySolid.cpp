#include "FITKInterfaceHDF5AdaptorBasicGeometrySolid.h"
//Geommtry
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelBox.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSphere.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelCylinder.h"

namespace IO
{
    // Reader.
   //@{

    bool FITKInterfaceHDF5AdaptorBasicGeometrySolid::readOperGeometrySolidBox(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBox* box = dynamic_cast<Interface::FITKAbsGeoModelBox*>(comm);
        if (box == nullptr) return false;
        double p1[3], length[3];
        if (!readDoubleAttribute(h5Group, "Point", p1, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "Length", length, 1, 3))return false;
        box->setPoint1(p1);
        box->setLength(length);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometrySolid::writeOperGeometrySolidBox(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelBox* box = dynamic_cast<Interface::FITKAbsGeoModelBox*>(comm);
        if (box == nullptr) return false;
        double p1[3], length[3];
        box->getPoint1(p1);
        box->getLength(length);
        writeDoubleAttribute(h5Group, "Point", &p1, 1, 3);
        writeDoubleAttribute(h5Group, "Length", &length, 1, 3);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometrySolid::readOperGeometrySolidSphere(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSphere* sphere = dynamic_cast<Interface::FITKAbsGeoModelSphere*>(comm);
        if (sphere == nullptr) return false;
        double location[3];
        if (!readDoubleAttribute(h5Group, "Location", location, 1, 3)) return false;
        double radius = readDoubleAttribute(h5Group, "Radius");
        sphere->setLocation(location);
        sphere->setRadius(radius);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometrySolid::writeOperGeometrySolidSphere(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelSphere* sphere = dynamic_cast<Interface::FITKAbsGeoModelSphere*>(comm);
        if (sphere == nullptr) return false;
        double location[3];
        sphere->getLocation(location);
        double radius = sphere->getRadius();
        writeDoubleAttribute(h5Group, "Location", &location, 1, 3);
        writeDoubleAttribute(h5Group, "Radius", &radius);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometrySolid::readOperGeometrySolidCylinder(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCylinder* cylinder = dynamic_cast<Interface::FITKAbsGeoModelCylinder*>(comm);
        if (cylinder == nullptr) return false;
        double location[3], direction[3];
        if (!readDoubleAttribute(h5Group, "Location", location, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "Direction", direction, 1, 3)) return false;
        double radius = readDoubleAttribute(h5Group, "Radius");
        double length = readDoubleAttribute(h5Group, "Length");
        cylinder->setLocation(location);
        cylinder->setDirection(direction);
        cylinder->setRadius(radius);
        cylinder->setLength(length);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBasicGeometrySolid::writeOperGeometrySolidCylinder(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelCylinder* cylinder = dynamic_cast<Interface::FITKAbsGeoModelCylinder*>(comm);
        if (cylinder == nullptr) return false;
        double location[3], direction[3];
        cylinder->getLocation(location);
        cylinder->getDirection(direction);
        double radius = cylinder->getRadius();
        double length = cylinder->getLength();
        writeDoubleAttribute(h5Group, "Location", &location, 1, 3);
        writeDoubleAttribute(h5Group, "Direction", &direction, 1, 3);
        writeDoubleAttribute(h5Group, "Radius", &radius);
        writeDoubleAttribute(h5Group, "Length", &length);
        return true;
    }


    //@}
}   // namespace IO
