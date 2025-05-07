#include "FITKInterfaceHDF5AdaptorSplitter.h"
#include "FITKInterfaceHDF5AdaptorOperGeometry.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometryCurve.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometryFace.h"
#include "FITKInterfaceHDF5AdaptorBasicGeometrySolid.h"

//Geommtry
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoSplitter.h"

namespace IO
{
    QString FITKInterfaceHDF5AdaptorSplitter::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorSplitter";
    }

    bool FITKInterfaceHDF5AdaptorSplitter::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return read(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return write(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::read(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (!comm) return false;
        auto t = comm->getGeometryCommandType();
        switch (t)
        {
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTCurveSplitter:         return readCurveSplitter(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTSurfaceSplitter:       return readSurfaceSplitter(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTSolidSplitter:         return readSolidSplitter(comm, h5Group);
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorSplitter::write(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (!comm) return false;
        auto t = comm->getGeometryCommandType();
        switch (t)
        {
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTCurveSplitter:         return writeCurveSplitter(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTSurfaceSplitter:       return writeSurfaceSplitter(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTSolidSplitter:         return writeSolidSplitter(comm, h5Group);
        }
        return false;
    }

    bool FITKInterfaceHDF5AdaptorSplitter::readSplitterBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoSplitter*>(comm);
        if (splitter == nullptr) return false;
        int sShape[3], tShape[3];
        double toolPoint[3];
        if (!readIntAttribute(h5Group, "SourceShape", sShape, 1, 3)) return false;
        if (!readIntAttribute(h5Group, "ToolShape", tShape, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "ToolPoint", toolPoint, 1, 3)) return false;

        splitter->setSourceShape(Interface::VirtualShape(sShape[0], sShape[1], sShape[2]));
        splitter->setToolShape(Interface::VirtualShape(tShape[0], tShape[1], tShape[2]));
        std::array<double, 3> toolPointArray{ toolPoint[0],toolPoint[1],toolPoint[2] };
        splitter->setToolPoint(toolPointArray);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorSplitter::writeSplitterBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoSplitter*>(comm);
        if (splitter == nullptr) return false;
        int sShape[3]{ splitter->sourceShape().CmdId,splitter->sourceShape().VirtualTopoId,splitter->sourceShape().VirtualTopoIndex };
        int tShape[3]{ splitter->toolShape().CmdId,splitter->toolShape().VirtualTopoId,splitter->toolShape().VirtualTopoIndex };
        double toolPoint[3]{ splitter->toolPoint()[0],splitter->toolPoint()[1] ,splitter->toolPoint()[2] };

        writeIntAttribute(h5Group, "SourceShape", sShape, 1, 3);
        writeIntAttribute(h5Group, "ToolShape", tShape, 1, 3);
        writeDoubleAttribute(h5Group, "ToolPoint", toolPoint, 1, 3);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorSplitter::readCurveSplitter(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoCurveSplitter*>(comm);
        if (splitter == nullptr) return false;
        double pArray[3];
        if (!readDoubleAttribute(h5Group, "Point", pArray, 1, 3)) return false;
        splitter->setPoint(pArray[0], pArray[1], pArray[2]);
        return readSplitterBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::writeCurveSplitter(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoCurveSplitter*>(comm);
        if (splitter == nullptr) return false;
        auto point = splitter->point();
        double pArray[3]{ point[0], point[1], point[2] };
        writeDoubleAttribute(h5Group, "Point", &pArray, 1, 3);
        return writeSplitterBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::readSurfaceSplitter(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoSurfaceSplitter*>(comm);
        if (splitter == nullptr) return false;
        return readSplitterBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::writeSurfaceSplitter(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoSurfaceSplitter*>(comm);
        if (splitter == nullptr) return false;
        return writeSplitterBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::readSolidSplitter(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoSolidSplitter*>(comm);
        if (splitter == nullptr) return false;
        return readSplitterBase(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSplitter::writeSolidSplitter(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        auto splitter = dynamic_cast<Interface::FITKAbsGeoSolidSplitter*>(comm);
        if (splitter == nullptr) return false;
        return writeSplitterBase(comm, h5Group);
    }


}   // namespace IO
