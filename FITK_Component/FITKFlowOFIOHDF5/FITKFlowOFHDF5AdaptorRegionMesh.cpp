#include "FITKFlowOFHDF5AdaptorRegionMesh.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionMeshSize.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionMeshSizeBox.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionMeshSizeCylinder.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionMeshSizeSphere.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionMeshSizeGeom.h"


#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"


#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorRegionMesh::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorRegionMesh";
    }

    bool FITKFlowOFHDF5AdaptorRegionMesh::adaptR()
    {
        _regionMeshData = dynamic_cast<Interface::FITKAbstractRegionMeshSize*>(_dataObj);
        if (!_reader || !_regionMeshData) return false;
        bool isR = false;
        readNDataObject(_regionMeshData, *_h5Group);

        int type = _regionMeshData->getRegionType();
        if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RigonGeom)
            isR = this->regionGeometryR(*_h5Group);
        else if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RegionBox)
            isR = this->regionBoxR(*_h5Group);
        else if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RegionCylinder)
            isR = this->regionCylinderR(*_h5Group);
        else if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RegionSphere)
            isR = this->regionSphereR(*_h5Group);
        return isR;
    }

    bool FITKFlowOFHDF5AdaptorRegionMesh::adaptW()
    {
        _regionMeshData = dynamic_cast<Interface::FITKAbstractRegionMeshSize*>(_dataObj);
        if (!_writer || !_regionMeshData) return false;
        std::string name = createParentAttribute(_regionMeshData, *_h5Group);
        if (name.empty())
        {
            name = std::to_string(_regionMeshData->getDataObjectID());
            int numAttrCount = _h5Group->getNumAttrs();
            writeStrAttribute(*_h5Group, std::to_string(numAttrCount), name);
        }
        H5::Group h5Group = _h5Group->createGroup(name);
        bool isW = false;
        int type = _regionMeshData->getRegionType();
        writeIntAttribute(h5Group, "RegionType", &type);
        if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RigonGeom)
            isW = this->regionGeometryW(h5Group);
        else if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RegionBox)
            isW = this->regionBoxW(h5Group);
        else if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RegionCylinder)
            isW = this->regionCylinderW(h5Group);
        else if (type == Interface::FITKAbstractRegionMeshSize::RegionType::RegionSphere)
            isW = this->regionSphereW(h5Group);

        return isW;
    }


    bool FITKFlowOFHDF5AdaptorRegionMesh::regionGeometryW(H5::Group& h5Group)
    {
        Interface::FITKRegionMeshSizeGeom* geoRegion = dynamic_cast<Interface::FITKRegionMeshSizeGeom*>(_regionMeshData);
        if (!_writer || !geoRegion) return false;
        //几何id
        int geomId = geoRegion->getGeomID();
        writeIntAttribute(h5Group, "geomId", &geomId);
        //最值
        int min = int(geoRegion->getMinSize());
        int max = int(geoRegion->getMaxSize());
        writeIntAttribute(h5Group, "minValue", &min);
        writeIntAttribute(h5Group, "maxValue", &max);
        return true;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionGeometryR(H5::Group& h5Group)
    {
        Interface::FITKRegionMeshSizeGeom* geoRegion = dynamic_cast<Interface::FITKRegionMeshSizeGeom*>(_regionMeshData);
        if (!_reader || !geoRegion) return false;
        //几何Id
        int geomId = readIntAttribute(h5Group, "geomId");
        geoRegion->setGeomID(geomId);
        //最值
        int max = readIntAttribute(h5Group, "maxValue");
        int min = readIntAttribute(h5Group, "minValue");
        geoRegion->setMinSize(min);
        geoRegion->setMaxSize(max);
        return true;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionBoxW(H5::Group& h5Group)
    {
        Interface::FITKRegionMeshSizeBox* boxRegion = dynamic_cast<Interface::FITKRegionMeshSizeBox*>(_regionMeshData);
        if (!_writer || !boxRegion) return false;
        //第一点坐标
        double point1[3]{ 0 };
        boxRegion->getPoint1(point1);
        writeDoubleAttribute(h5Group, "point1", &point1, 1, 3);
        //长度
        double length[3]{ 0 };
        boxRegion->getLength(length);
        writeDoubleAttribute(h5Group, "length", &length, 1, 3);
        //离散数量
        int division1 = boxRegion->getDivision(0);
        int division2 = boxRegion->getDivision(1);
        int division3 = boxRegion->getDivision(2);
        writeIntAttribute(h5Group, "division1", &division1);
        writeIntAttribute(h5Group, "division2", &division2);
        writeIntAttribute(h5Group, "division3", &division3);
        //离散比例
        double grading1 = boxRegion->getGrading(0);
        double grading2 = boxRegion->getGrading(1);
        double grading3 = boxRegion->getGrading(2);
        writeDoubleAttribute(h5Group, "grading1", &grading1);
        writeDoubleAttribute(h5Group, "grading2", &grading2);
        writeDoubleAttribute(h5Group, "grading3", &grading3);
        //boundary
        for (int i = 0; i < 6; ++i)
        {
            int boundType = boxRegion->getBoundary(i);
            std::string faceName = boxRegion->getFaceName(i).toStdString();
            std::string boundTypeKey = (QString("boundType%1").arg(i)).toStdString();
            std::string faceNameKey = (QString("faceName%1").arg(i)).toStdString();
            writeIntAttribute(h5Group, boundTypeKey, &boundType);
            writeStrAttribute(h5Group, faceNameKey, faceName);
        }
        return true;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionBoxR(H5::Group& h5Group)
    {
        Interface::FITKRegionMeshSizeBox* boxRegion = dynamic_cast<Interface::FITKRegionMeshSizeBox*>(_regionMeshData);
        if (!_reader || !boxRegion) return false;
        //第一点坐标
        if (!h5Group.attrExists("point1"))return false;
        double point1[3] = { 0 };
        H5::Attribute att1 = h5Group.openAttribute("point1");
        att1.read(H5::PredType::NATIVE_DOUBLE, &point1);
        boxRegion->setPoint1(point1);
        //长度
        if (!h5Group.attrExists("length"))return false;
        double length[3] = { 0 };
        att1 = h5Group.openAttribute("length");
        att1.read(H5::PredType::NATIVE_DOUBLE, &length);
        boxRegion->setLength(length);
        //离散数量
        int division1 = readIntAttribute(h5Group, "division1");
        int division2 = readIntAttribute(h5Group, "division2");
        int division3 = readIntAttribute(h5Group, "division3");
        boxRegion->setDivision(0, division1);
        boxRegion->setDivision(1, division2);
        boxRegion->setDivision(2, division3);
        //离散比例
        double grading1 = readDoubleAttribute(h5Group, "grading1");
        double grading2 = readDoubleAttribute(h5Group, "grading2");
        double grading3 = readDoubleAttribute(h5Group, "grading3");
        boxRegion->setGrading(0, grading1);
        boxRegion->setGrading(1, grading2);
        boxRegion->setGrading(2, grading3);

        //boundary
        for (int i = 0; i < 6; ++i)
        {
            std::string boundTypeKey = (QString("boundType%1").arg(i)).toStdString();
            std::string faceNameKey = (QString("faceName%1").arg(i)).toStdString();
            int type = readIntAttribute(h5Group, boundTypeKey);
            std::string name = readStrAttribute(h5Group, faceNameKey);
            boxRegion->insertBoundary(i, Interface::FITKAbstractRegionMeshSize::BoundaryType(type));
            boxRegion->insertFaceName(i, QString::fromStdString(name));
        }

        return true;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionCylinderW(H5::Group& h5Group)
    {
        Interface::FITKRegionMeshSizeCylinder* cylinderRegion = dynamic_cast<Interface::FITKRegionMeshSizeCylinder*>(_regionMeshData);
        if (!_writer || !cylinderRegion) return false;
        //圆心坐标
        double location[3] = { 0,0,0 };
        cylinderRegion->getLocation(location);
        writeDoubleAttribute(h5Group, "location", &location, 1, 3);
        //轴线方向
        double direction[3] = { 0,0,0 };
        cylinderRegion->getDirection(direction);
        writeDoubleAttribute(h5Group, "direction", &direction, 1, 3);
        //半径
        double radius = cylinderRegion->getRadius();
        writeDoubleAttribute(h5Group, "radius", &radius);
        //长度
        double length = cylinderRegion->getLength();
        writeDoubleAttribute(h5Group, "length", &length);
        //半径因子
        double radiusFaction = cylinderRegion->getRadialFraction();
        writeDoubleAttribute(h5Group, "radiusFaction", &radiusFaction);
        //离散数量
        int division1 = cylinderRegion->getDivision(0);
        int division2 = cylinderRegion->getDivision(1);
        int division3 = cylinderRegion->getDivision(2);
        writeIntAttribute(h5Group, "division1", &division1);
        writeIntAttribute(h5Group, "division2", &division2);
        writeIntAttribute(h5Group, "division3", &division3);
        //离散比例
        double grading1 = cylinderRegion->getGrading(0);
        double grading2 = cylinderRegion->getGrading(1);
        double grading3 = cylinderRegion->getGrading(2);
        writeDoubleAttribute(h5Group, "grading1", &grading1);
        writeDoubleAttribute(h5Group, "grading2", &grading2);
        writeDoubleAttribute(h5Group, "grading3", &grading3);
        //boundary
        for (int i = 0; i < 3; ++i)
        {
            int boundType = cylinderRegion->getBoundary(i);
            std::string faceName = cylinderRegion->getFaceName(i).toStdString();
            std::string boundTypeKey = (QString("boundType%1").arg(i)).toStdString();
            std::string faceNameKey = (QString("faceName%1").arg(i)).toStdString();
            writeIntAttribute(h5Group, boundTypeKey, &boundType);
            writeStrAttribute(h5Group, faceNameKey, faceName);
        }

        return true;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionCylinderR(H5::Group& h5Group)
    {
        Interface::FITKRegionMeshSizeCylinder* cylinderRegion = dynamic_cast<Interface::FITKRegionMeshSizeCylinder*>(_regionMeshData);
        if (!_reader || !cylinderRegion) return false;
        //圆心坐标
        if (!h5Group.attrExists("location"))return false;
        double location[3] = { 0 };
        H5::Attribute att1 = h5Group.openAttribute("location");
        att1.read(H5::PredType::NATIVE_DOUBLE, &location);
        cylinderRegion->setLocation(location);
        //轴线方向
        if (!h5Group.attrExists("direction"))return false;
        double direction[3] = { 0 };
        att1 = h5Group.openAttribute("direction");
        att1.read(H5::PredType::NATIVE_DOUBLE, &direction);
        cylinderRegion->setDirection(direction);
        //半径
        double radius = readDoubleAttribute(h5Group, "radius");
        cylinderRegion->setRadius(radius);
        //长度
        double length = readDoubleAttribute(h5Group, "length");
        cylinderRegion->setLength(length);
        //半径因子
        double radiusFaction = readDoubleAttribute(h5Group, "radiusFaction");
        cylinderRegion->setRadialFraction(radiusFaction);
        //离散数量
        int division1 = readIntAttribute(h5Group, "division1");
        int division2 = readIntAttribute(h5Group, "division2");
        int division3 = readIntAttribute(h5Group, "division3");
        cylinderRegion->setDivision(0, division1);
        cylinderRegion->setDivision(1, division2);
        cylinderRegion->setDivision(2, division3);
        //离散比例
        double grading1 = readDoubleAttribute(h5Group, "grading1");
        double grading2 = readDoubleAttribute(h5Group, "grading2");
        double grading3 = readDoubleAttribute(h5Group, "grading3");
        cylinderRegion->setGrading(0, grading1);
        cylinderRegion->setGrading(1, grading2);
        cylinderRegion->setGrading(2, grading3);
        //boundary
        for (int i = 0; i < 3; ++i)
        {
            std::string boundTypeKey = (QString("boundType%1").arg(i)).toStdString();
            std::string faceNameKey = (QString("faceName%1").arg(i)).toStdString();
            int type = readIntAttribute(h5Group, boundTypeKey);
            std::string name = readStrAttribute(h5Group, faceNameKey);
            cylinderRegion->insertBoundary(i, Interface::FITKAbstractRegionMeshSize::BoundaryType(type));
            cylinderRegion->insertFaceName(i, QString::fromStdString(name));
        }
        return true;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionSphereW(H5::Group& h5Group)
    {
        if (!_writer || !_regionMeshData) return false;
        return false;
    }
    bool FITKFlowOFHDF5AdaptorRegionMesh::regionSphereR(H5::Group& h5Group)
    {
        return false;
    }
}
