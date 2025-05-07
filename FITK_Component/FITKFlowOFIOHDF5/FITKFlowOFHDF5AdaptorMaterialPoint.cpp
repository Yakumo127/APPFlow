#include "FITKFlowOFHDF5AdaptorMaterialPoint.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKZonePoints.h"


#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"


#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorMaterialPoint::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorMaterialPoint";
    }

    bool FITKFlowOFHDF5AdaptorMaterialPoint::adaptR()
    {
        _pointData = dynamic_cast<Interface::FITKZonePoint*>(_dataObj);
        if (!_reader || !_pointData) return false;
        
        if (!readDataObject(_pointData, *_h5Group))return false;
        if (!_h5Group->attrExists("coor"))return false;
        //坐标
        double coor[3] = { 0 };
        H5::Attribute att1 = _h5Group->openAttribute("coor");
        att1.read(H5::PredType::NATIVE_DOUBLE, &coor);
        _pointData->setCoor(coor[0], coor[1], coor[2]);
        return true;
    }

    bool FITKFlowOFHDF5AdaptorMaterialPoint::adaptW()
    {
        _pointData = dynamic_cast<Interface::FITKZonePoint*>(_dataObj);
        if (!_writer || !_pointData) return false;
        std::string name = createParentAttribute(_pointData, *_h5Group);
        if (name.empty())return false;
        //创建组
        H5::Group h5Group = _h5Group->createGroup(name);
        if (!writeDataObject(_pointData, h5Group)) return false;
        //坐标
        double coor[3]{ 0 };
        _pointData->getCoor(coor);
        this->writeDoubleAttribute(h5Group, "coor", &coor, 1, 3);
        return true;
    }

}
