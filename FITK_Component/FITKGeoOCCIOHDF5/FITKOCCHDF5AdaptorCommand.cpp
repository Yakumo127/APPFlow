#include "FITKOCCHDF5AdaptorCommand.h"
#include "FITKOCCShapeIO.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorOperGeometry.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorBasicGeometryPoint.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorBasicGeometryCurve.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorBasicGeometryFace.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorBasicGeometrySolid.h"


#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
// OCC
#include <TopoDS_Shape.hxx>

//Component
#include "FITK_Component/FITKGeoCompOCC/FITKAbstractOCCModel.h"

//Geommtry
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelBox.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelSphere.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelCylinder.h"


namespace IO
{
    bool FITKOCCHDF5AdaptorCommand::readVShape(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        if (comm == nullptr) return false;
        auto occShape = dynamic_cast<OCC::FITKAbstractOCCModel*>(comm->getShapeAgent());
        if (occShape == nullptr) return false;

        uint len = readIntAttribute(h5Group, "Len");
        char* data = new char[len];
        if (!readCharDataSet(h5Group, "Shape", data, len)) return false;
        if (!FITKOCCIOTool::SetDataToCommand(comm, len, data)) return false;
        delete[] data;
        return true;
    }
    bool FITKOCCHDF5AdaptorCommand::writeVShape(Interface::FITKAbsGeoShapeAgent * agent, H5::Group & h5Group)
    {
        auto occShape = dynamic_cast<OCC::FITKAbstractOCCModel*>(agent);
        if (occShape == nullptr) return false;
        uint len = -1;
        char* data;
        if (!FITKOCCIOTool::ShapeToData(occShape->getShape(), len, data)) return false;
        writeCharDataSet(h5Group, "Shape", data, len);
        writeIntAttribute(h5Group, "Len", &len);
        delete[] data;
        return true;
    }
}   // namespace IO
