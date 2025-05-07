#include "FITKInterfaceHDF5AdaptorSketchGeometry.h"
#include "FITKInterfaceHDF5AdaptorCommand.h"

//Interface
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoSketch2D.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"

#include <QMetaEnum>

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorSketchGeometry::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorSketchGeometry";
    }

    bool FITKInterfaceHDF5AdaptorSketchGeometry::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readSketchGeometry(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSketchGeometry::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeSketchGeometry(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorSketchGeometry::readSketchGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        Interface::FITKAbsGeoSketch2D* sk = dynamic_cast<Interface::FITKAbsGeoSketch2D*>(comm);
        if (sk == nullptr) return false;
        //获取命令类型
        auto commType = sk->getGeometryCommandType();
        if (commType != Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D) return false;

        double pos[3], normal[3], up[3];

        if (!readDoubleAttribute(h5Group, "Position", pos, 1, 3)) return false;
        sk->setPosition(pos);

        if (!readDoubleAttribute(h5Group, "Normal", normal, 1, 3)) return false;
        sk->setNormal(normal);

        if (!readDoubleAttribute(h5Group, "Up", up, 1, 3)) return false;
        sk->setUp(up);

        bool isR = true;
        auto childsGroup = h5Group.openGroup("Childs");
        int count = readIntAttribute(childsGroup, "Count");

        std::string geoName;
        H5::StrType datatype(H5::PredType::C_S1, H5T_VARIABLE);

        for (int i = 0; i < count; i++)
        {
            //根据索引映射读取几何名称
            auto geoNameAttribute = childsGroup.openAttribute(std::to_string(i));
            geoNameAttribute.read(datatype, geoName);
            auto childGroup = childsGroup.openGroup(geoName);

            //获取几何命令类型
            auto geoTypeAttribute = childGroup.openAttribute("GeometryCommandType");
            std::string geoType;
            geoTypeAttribute.read(datatype, geoType);
            if (geoType.empty())return false;
            //实例几何命令类型
            auto geo = getGeoCommand(QString::fromStdString(geoType));
            if (geo == nullptr) return false;
            sk->appendDataObj(geo);
            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKInterfaceHDF5AdaptorCommand>("HDF5", "Interface::FITKAbsGeoCommand");
            if (adaptor == nullptr) return false;
            adaptor->setH5GroupData(childGroup);
            adaptor->setDataObject(geo);
            adaptor->setFileReader(_reader);
            bool r = adaptor->adaptR();
            isR &= r;
            delete adaptor;
        }
        return isR;
    }

    bool FITKInterfaceHDF5AdaptorSketchGeometry::writeSketchGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        Interface::FITKAbsGeoSketch2D* sk = dynamic_cast<Interface::FITKAbsGeoSketch2D*>(comm);
        if (sk == nullptr) return false;
        //获取命令类型
        auto commType = sk->getGeometryCommandType();
        if (commType != Interface::FITKGeoEnum::FITKGeometryComType::FGTSketch2D) return false;

        double pos[3], normal[3], up[3];
        sk->getPosition(pos);
        writeDoubleAttribute(h5Group, "Position", pos, 1, 3);

        sk->getNormal(normal);
        writeDoubleAttribute(h5Group, "Normal", normal, 1, 3);

        sk->getUp(up);
        writeDoubleAttribute(h5Group, "Up", up, 1, 3);

        auto childGroup = h5Group.createGroup("Childs");
        bool isW = true;
        int count = sk->getDataCount();
        for (int i = 0; i < count; i++)
        {
            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKInterfaceHDF5AdaptorCommand>("HDF5", "Interface::FITKAbsGeoCommand");
            if (adaptor == nullptr) return false;
            adaptor->setH5GroupData(childGroup);
            adaptor->setDataObject(sk->getDataByIndex(i));
            adaptor->setFileWriter(_writer);
            bool w = adaptor->adaptW();
            isW &= w;
            delete adaptor;
        }
        writeIntAttribute(childGroup, "Count", &count);
        return isW;
    }


    Core::FITKAbstractNDataObject* FITKInterfaceHDF5AdaptorSketchGeometry::getGeoCommand(QString enumName)
    {
        if (enumName.isEmpty()) return nullptr;
        auto metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKGeometryComType>();
        int valueID = metaEnum.keyToValue(enumName.toLocal8Bit());
        if (valueID < 0) return nullptr;

        Interface::FITKInterfaceGeometryFactory* fac = Interface::FITKInterfaceGeometryFactory::getInstance();
        if (!fac) return nullptr;

        return fac->createCommand((Interface::FITKGeoEnum::FITKGeometryComType)valueID);
    }
    //@}
}   // namespace IO
