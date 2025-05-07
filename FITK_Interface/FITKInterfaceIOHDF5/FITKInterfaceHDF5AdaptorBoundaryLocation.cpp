#include "FITKInterfaceHDF5AdaptorBoundaryLocation.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfacePhysics/FITKBoundaryLocation.h"

namespace IO
{
    QString FITKInterfaceHDF5AdaptorBoundaryLocation::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorBoundaryLocation";
    }

    bool FITKInterfaceHDF5AdaptorBoundaryLocation::adaptR()
    {
        auto bc = dynamic_cast<Interface::FITKBoundaryLocation*>(_dataObj);
        if (!_reader || !_h5Group || !bc) return false;
        bool isR = true;
        isR &= readBoundaryLocation(bc, *_h5Group);
        return isR;
    }

    bool FITKInterfaceHDF5AdaptorBoundaryLocation::adaptW()
    {
        auto bc = dynamic_cast<Interface::FITKBoundaryLocation*>(_dataObj);
        if (!_writer || !_h5Group || !bc) return false;
        bool isW = true;
        isW &= writeBoundaryLocation(bc, *_h5Group);
        return isW;
    }

    bool FITKInterfaceHDF5AdaptorBoundaryLocation::readBoundaryLocation(Interface::FITKBoundaryLocation * bc, H5::Group & h5Group)
    {
        if (!bc) return false;
        if (!readNDataObject(bc, h5Group)) return false;
        if (!h5Group.attrExists("ModelID")) return false;
        if (!h5Group.attrExists("ComponentID")) return false;
        int modelID = readIntAttribute(h5Group, "ModelID");
        int componentID = readIntAttribute(h5Group, "ComponentID");
        bc->setModel(modelID);
        bc->setComponent(componentID);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorBoundaryLocation::writeBoundaryLocation(Interface::FITKBoundaryLocation * bc, H5::Group & h5Group)
    {
        if (!bc) return false;
        int modelID = bc->getModelID();
        writeIntAttribute(h5Group, "ModelID", &modelID);
        int componentID = bc->getComponentID();
        writeIntAttribute(h5Group, "ComponentID", &componentID);
        return writeNDataObject(bc, h5Group);
    }


}


