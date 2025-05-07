#include "FITKInterfaceHDF5AdaptorDatum.h"

#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoReferencePlane.h"

#include <QMetaEnum>
namespace IO
{
    // Base.
    //@{
    QString FITKInterfaceHDF5AdaptorDatum::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorDatum";
    }

    bool FITKInterfaceHDF5AdaptorDatum::adaptR()
    {
        //父类 读取
        if (!FITKInterfaceHDF5AdaptorGeoCommand::adaptR()) return false;
        auto comm = dynamic_cast<Interface::FITKAbsGeoDatum*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        if (!readDatum(comm, *_h5Group)) return false;
        return true;
    }

    bool FITKInterfaceHDF5AdaptorDatum::adaptW()
    {
        //父类 写出
        if (!FITKInterfaceHDF5AdaptorGeoCommand::adaptW()) return false;
        auto comm = dynamic_cast<Interface::FITKAbsGeoDatum*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        if (!writeDatum(comm, _h5CreateGroup)) return false;
        return true;
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatum(Interface::FITKAbsGeoDatum* datum, H5::Group& h5Group)
    {
        if (!datum) return false;

        auto t = datum->getDatumType();
        switch (t)
        {
        case Interface::FITKGeoEnum::FITKDatumType::FDTPoint:               return readDatumPoint(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTLine:                return readDatumLine(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTPlane:               return readDatumPlane(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTOffsetPlane:         return readDatumOffsetPlane(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTThreePointsPlane:    return readDatumThreePointsPlane(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTEquationPlane:       return readDatumEquationPlane(datum, h5Group);
        default: return false;
        }

        return true;
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatum(Interface::FITKAbsGeoDatum* datum, H5::Group& h5Group)
    {
        if (!datum) return false;
        std::string groupName = createParentAttribute(datum, h5Group);
        if (groupName.empty())return false;

        auto t = datum->getDatumType();

        //Object Type
        QMetaEnum metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKDatumType>();
        std::string strDatumType = metaEnum.valueToKey(t);
        if (strDatumType.empty()) return false;
        writeStrAttribute(h5Group, "Type", strDatumType);

        switch (t)
        {
        case Interface::FITKGeoEnum::FITKDatumType::FDTPoint:               return writeDatumPoint(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTLine:                return writeDatumLine(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTPlane:               return writeDatumPlane(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTOffsetPlane:         return writeDatumOffsetPlane(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTThreePointsPlane:    return writeDatumThreePointsPlane(datum, h5Group);
        case Interface::FITKGeoEnum::FITKDatumType::FDTEquationPlane:       return writeDatumEquationPlane(datum, h5Group);
        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumBase(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        if (!datum) return false;
        double position[3];
        if (!readDoubleAttribute(h5Group, "Position", position, 1, 3)) return false;
        datum->setPosition(position);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumBase(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        if (!datum) return false;
        double position[3];
        datum->getPosition(position);
        writeDoubleAttribute(h5Group, "Position", position, 1, 3);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumPoint(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto dPoint = dynamic_cast<Interface::FITKAbsGeoDatumPoint*>(datum);
        if (!dPoint) return false;
        return readDatumBase(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumPoint(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto dPoint = dynamic_cast<Interface::FITKAbsGeoDatumPoint*>(datum);
        if (!dPoint) return false;
        return writeDatumBase(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumLine(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto dLine = dynamic_cast<Interface::FITKAbsGeoDatumLine*>(datum);
        if (!dLine) return false;

        double pos1[3], pos2[3];
        if (!readDoubleAttribute(h5Group, "Position1", pos1, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "Position2", pos2, 1, 3)) return false;
        dLine->setFiniteLine(pos1, pos2);
        return readDatumBase(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumLine(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto dLine = dynamic_cast<Interface::FITKAbsGeoDatumLine*>(datum);
        if (!dLine) return false;

        double pos1[3], pos2[3];
        dLine->getFiniteLine(pos1, pos2);
        writeDoubleAttribute(h5Group, "Position1", pos1, 1, 3);
        writeDoubleAttribute(h5Group, "Position2", pos2, 1, 3);

        return writeDatumBase(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto dPlane = dynamic_cast<Interface::FITKAbsGeoDatumPlane*>(datum);
        if (!dPlane) return false;
        double pos[3], normal[3], up[3];
        if (!readDoubleAttribute(h5Group, "Position1", pos, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "Normal", normal, 1, 3)) return false;
        if (!readDoubleAttribute(h5Group, "Up", up, 1, 3)) return false;
        dPlane->setPlane(pos, normal, up);
        return readDatumBase(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto dPlane = dynamic_cast<Interface::FITKAbsGeoDatumPlane*>(datum);
        if (!dPlane) return false;
        double pos[3], normal[3], up[3];
        dPlane->getPlane(pos, normal, up);
        writeDoubleAttribute(h5Group, "Position1", pos, 1, 3);
        writeDoubleAttribute(h5Group, "Normal", normal, 1, 3);
        writeDoubleAttribute(h5Group, "Up", up, 1, 3);

        return writeDatumBase(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumOffsetPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto oPlane = dynamic_cast<Interface::FITKAbsGeoReferenceOffsetPlane*>(datum);
        if (!oPlane) return false;
        Interface::VirtualShape sObject;
        sObject.CmdId = readIntAttribute(h5Group, "CmdId");
        sObject.VirtualTopoId = readIntAttribute(h5Group, "VirtualTopoId");
        sObject.VirtualTopoIndex = readIntAttribute(h5Group, "VirtualTopoIndex");

        oPlane->setSourceSurface(sObject);
        double offset = readDoubleAttribute(h5Group, "Offset");
        oPlane->setOffset(offset);

        return readDatumPlane(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumOffsetPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto oPlane = dynamic_cast<Interface::FITKAbsGeoReferenceOffsetPlane*>(datum);
        if (!oPlane) return false;

        Interface::VirtualShape sObject = oPlane->sourceSurface();
        int cmdId = sObject.CmdId;
        writeIntAttribute(h5Group, "CmdId", &cmdId);
        int virtualTopoId = sObject.VirtualTopoId;
        writeIntAttribute(h5Group, "VirtualTopoId", &virtualTopoId);
        int virtualTopoIndex = sObject.VirtualTopoIndex;
        writeIntAttribute(h5Group, "VirtualTopoIndex", &virtualTopoIndex);
        double offset = oPlane->offset();
        writeDoubleAttribute(h5Group, "Offset", &offset);

        return writeDatumPlane(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumThreePointsPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto tpPlane = dynamic_cast<Interface::FITKAbsGeoReferenceThreePointsPlane*>(datum);
        if (!tpPlane) return false;
        for (int i = 0; i < 3; i++)
        {
            double P_i[3];
            if (!readDoubleAttribute(h5Group, std::to_string(i), P_i, 1, 3)) return false;
            tpPlane->setPoint(i, P_i[0], P_i[1], P_i[2]);
        }
        return readDatumPlane(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumThreePointsPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto tpPlane = dynamic_cast<Interface::FITKAbsGeoReferenceThreePointsPlane*>(datum);
        if (!tpPlane) return false;
        for (int i = 0; i < 3; i++)
        {
            auto point = tpPlane->point(i);
            double P_i[3]{ point[0],point[1],point[2] };
            writeDoubleAttribute(h5Group, std::to_string(i), P_i, 1, 3);
        }
        return writeDatumPlane(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::readDatumEquationPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto grePlane = dynamic_cast<Interface::FITKAbsGeoReferenceEquationPlane*>(datum);
        if (!grePlane) return false;

        double a = readDoubleAttribute(h5Group, "A");
        double b = readDoubleAttribute(h5Group, "B");
        double c = readDoubleAttribute(h5Group, "C");
        double d = readDoubleAttribute(h5Group, "D");
        grePlane->setA(a);
        grePlane->setB(b);
        grePlane->setC(c);
        grePlane->setD(d);
        return readDatumPlane(datum, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorDatum::writeDatumEquationPlane(Interface::FITKAbsGeoDatum * datum, H5::Group & h5Group)
    {
        auto grePlane = dynamic_cast<Interface::FITKAbsGeoReferenceEquationPlane*>(datum);
        if (!grePlane) return false;

        double a = grePlane->a();
        writeDoubleAttribute(h5Group, "A", &a);
        double b = grePlane->b();
        writeDoubleAttribute(h5Group, "B", &b);
        double c = grePlane->c();
        writeDoubleAttribute(h5Group, "C", &c);
        double d = grePlane->d();
        writeDoubleAttribute(h5Group, "D", &d);

        return writeDatumPlane(datum, h5Group);
    }
    //@}
}   // namespace IO
