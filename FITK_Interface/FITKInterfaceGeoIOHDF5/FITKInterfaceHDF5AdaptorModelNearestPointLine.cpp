/*****************************************************************//**
 * @file    FITKInterfaceHDF5AdaptorNearestPointLine.cpp
 * @brief   HDF5 Adaptor Nearest Point Line Implementation
 * @date    2025-03-27
 * @author  libaojun
 *********************************************************************/

#include "FITKInterfaceHDF5AdaptorModelNearestPointLine.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelNearestPointLine.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"

namespace IO
{
    QString FITKInterfaceHDF5AdaptorNearestPointLine::getAdaptorClass()
    {
        return "OCC::FITKOCCNearestPointLine";
    }

    bool FITKInterfaceHDF5AdaptorNearestPointLine::adaptR()
    {
        // 错误判断
        Interface::FITKAbsGeoModelNearestPointLine* comm = dynamic_cast<Interface::FITKAbsGeoModelNearestPointLine*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;

        // 读取 Point
        double point[3];
        this->readDoubleAttribute(*_h5Group, "Point", point, 1, 3);
        comm->setPoint(point);

        // 读取 NearestPoint
        double nearestPoint[3];
        this->readDoubleAttribute(*_h5Group, "NearestPoint", nearestPoint, 1, 3);
        comm->setNearestPoint(nearestPoint);

        // 读取 Shape
        int shapeArray[3];
        this->readIntAttribute(*_h5Group, "Shape", shapeArray, 1, 3);
        Interface::VirtualShape shape(shapeArray[0], shapeArray[1], shapeArray[2]);
        comm->setShape(shape);

        // 读取 ShapeType
        bool ok = false;
        std::string sShapeType = this->readStrAttribute(*_h5Group, "ShapeType");
        Interface::FITKAbsGeoModelNearestPointLine::ShapeType shapeType =
            Core::FITKEnumTransfer<Interface::FITKAbsGeoModelNearestPointLine::ShapeType>().
            fromString(QString::fromStdString(sShapeType), ok);
        if (!ok) return false;
        comm->setShapeType(shapeType);

        return true;
    }

    bool FITKInterfaceHDF5AdaptorNearestPointLine::adaptW()
    {
        // 错误判断
        Interface::FITKAbsGeoModelNearestPointLine* comm = dynamic_cast<Interface::FITKAbsGeoModelNearestPointLine*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;

        // 写入 Point
        double point[3];
        comm->getPoint(point);
        this->writeDoubleAttribute(*_h5Group, "Point", point, 1, 3);

        // 写入 NearestPoint
        double nearestPoint[3];
        comm->getNearestPoint(nearestPoint);
        this->writeDoubleAttribute(*_h5Group, "NearestPoint", nearestPoint, 1, 3);

        // 写入 Shape
        Interface::VirtualShape shape = comm->getShape();
        int shapeArray[3] = { shape.CmdId, shape.VirtualTopoId, shape.VirtualTopoIndex };
        this->writeIntAttribute(*_h5Group, "Shape", shapeArray, 1, 3);

        // 写入 ShapeType
        bool ok = false;
        Interface::FITKAbsGeoModelNearestPointLine::ShapeType shapeType = comm->getShapeType();
        QString sShapeType =
            Core::FITKEnumTransfer<Interface::FITKAbsGeoModelNearestPointLine::ShapeType>().
            toString(shapeType, ok);
        if (!ok) return false;
        this->writeStrAttribute(*_h5Group, "ShapeType", sShapeType.toStdString());

        return true;
    }
}


