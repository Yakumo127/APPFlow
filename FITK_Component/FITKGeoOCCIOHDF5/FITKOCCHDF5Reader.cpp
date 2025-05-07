#include "FITKOCCHDF5Reader.h"
#include "FITKOCCHDF5AdaptorCommand.h"
//Kernel
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
//Geomerty
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"


#include <QMetaEnum>

namespace IO
{

    void FITKOCCHDF5Reader::run()
    {
        *_resultMark = false;

        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_data);
        if (!commList || !_h5File) return;
        if (!readInfo()) return;
        *_resultMark = true;
        *_resultMark &= readVersion();
        *_resultMark &= readCommDatas();
        *_resultMark &= readDatumDatas();
    }

    void FITKOCCHDF5Reader::consoleMessage(int level, const QString &str)
    {
        qDebug() << str;
        //判断消息等级
        switch (level)
        {
        case 1:AppFrame::FITKMessageNormal(str); break;
        case 2: AppFrame::FITKMessageWarning(str); break;
        case 3:AppFrame::FITKMessageError(str); break;
        default: AppFrame::FITKMessageError(str); break;
        }
    }


    bool FITKOCCHDF5Reader::readCommDatas()
    {
        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_data);
        if (!commList || !_h5File) return false;
        bool isW = true;
        // create cases group
        H5::Group casesGroup = _h5File->openGroup("Geometry");

        //获取几何命令长度
        if (!casesGroup.attrExists("Count")) return true;
        H5::Attribute att = casesGroup.openAttribute("Count");
        int count = 0;
        att.read(H5::PredType::NATIVE_INT, &count);

        for (int i = 0; i < count; i++)
        {
            //根据索引映射读取几何名称
            auto geoNameAttribute = casesGroup.openAttribute(std::to_string(i));
            std::string geoName;
            H5::StrType datatype(H5::PredType::C_S1, H5T_VARIABLE);
            geoNameAttribute.read(datatype, geoName);

            if (!casesGroup.nameExists(geoName))
            {
                consoleMessage(3, QString("Read Geo Error, CaseName : %1").arg(QString::fromStdString(geoName)));
                return false;
            }
            auto geoGroup = casesGroup.openGroup(geoName);
            //获取几何命令类型
            auto geoTypeAttribute = geoGroup.openAttribute("GeometryCommandType");
            std::string geoType;
            geoTypeAttribute.read(datatype, geoType);
            if (geoType.empty())return false;
            //实例几何命令类型
            auto geo = getGeoCommand(QString::fromStdString(geoType));
            Interface::FITKAbsGeoCommand* comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(geo);
            if (!comm) return false;
            commList->appendDataObj(comm);
            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKOCCHDF5AdaptorCommand>("HDF5", "Interface::FITKAbsGeoCommand");
            if (adaptor == nullptr)
            {
                delete comm;
                return false;
            }
            adaptor->setH5GroupData(geoGroup);
            adaptor->setDataObject(comm);
            adaptor->setFileReader(this);
            bool w = adaptor->adaptR();
            if (!w) consoleMessage(3, QString("Read Command Errors, Command : %1").arg(comm->getDataObjectName()));
            isW &= w;
            delete adaptor;
        }
        return isW;
    }

    bool FITKOCCHDF5Reader::readDatumDatas()
    {
        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_data);
        if (!commList || !_h5File) return false;
        bool isW = true;

        auto datumList = commList->getDatumManager();

        // create cases group
        H5::Group casesGroup = _h5File->openGroup("Datums");

        //获取几何命令长度
        if (!casesGroup.attrExists("Count")) return true;
        H5::Attribute att = casesGroup.openAttribute("Count");
        int count = 0;
        att.read(H5::PredType::NATIVE_INT, &count);

        for (int i = 0; i < count; i++)
        {
            //根据索引映射读取几何名称
            auto geoNameAttribute = casesGroup.openAttribute(std::to_string(i));
            std::string geoName;
            H5::StrType datatype(H5::PredType::C_S1, H5T_VARIABLE);
            geoNameAttribute.read(datatype, geoName);

            if (!casesGroup.nameExists(geoName))
            {
                consoleMessage(3, QString("Read GeoDatum Error, CaseName : %1").arg(QString::fromStdString(geoName)));
                return false;
            }
            auto geoGroup = casesGroup.openGroup(geoName);
            //获取几何命令类型
            auto geoTypeAttribute = geoGroup.openAttribute("Type");
            std::string geoType;
            geoTypeAttribute.read(datatype, geoType);
            if (geoType.empty())return false;
            //实例几何命令类型
            auto geo = getGeoDatum(QString::fromStdString(geoType));
            Core::FITKAbstractNDataObject* geoData = dynamic_cast<Core::FITKAbstractNDataObject*>(geo);
            if (!geoData) return false;
            datumList->appendDataObj(geoData);
            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKAbstractHDF5Adaptor>("HDF5", "Interface::FITKAbsGeoDatum");
            if (adaptor == nullptr)
            {
                delete geoData;
                return false;
            }
            adaptor->setH5GroupData(geoGroup);
            adaptor->setDataObject(geoData);
            adaptor->setFileReader(this);
            bool w = adaptor->adaptR();
            if (!w) consoleMessage(3, QString("Read GeoDatum Errors, Command : %1").arg(QString::fromStdString(geoName)));
            isW &= w;
            delete adaptor;
        }
        return isW;
    }

    bool FITKOCCHDF5Reader::readInfo()
    {
        // 校验信息
        if (!_h5File->nameExists("Info")) return false;
        H5::Group infoGroup = _h5File->openGroup("Info");
        H5::StrType datatype(H5::PredType::C_S1, H5T_VARIABLE);
        H5::Attribute att = infoGroup.openAttribute("SoftWareName");
        std::string str{};
        att.read(datatype, str);
        bool flag = str == "CADOCCAPP";
        if(!flag)
            consoleMessage(3, "Error! Software Information Does Not Match HDF5 Information!");
        return flag;
    }

    bool FITKOCCHDF5Reader::readVersion()
    {
        //写出HDF5管理功能版本号
        std::string name = "Version";
        if (!_h5File->nameExists(name)) return false;
        H5::Group versionGroup = _h5File->openGroup(name);
        if (!versionGroup.attrExists(name)) return false;
        auto attrVersion = versionGroup.openAttribute(name);
        double version = -1;
        attrVersion.read(H5::PredType::NATIVE_DOUBLE, &version);
        consoleMessage(1, QString("HDF5 SoftWare Version : %1, HDF5 File Version : %2").arg(_version).arg(version));
        if (version > _version)
        {
            consoleMessage(2, "Read Error, File Version Mismatch.");
            return false;
        }
        return true;
    }

    Core::FITKAbstractNDataObject* FITKOCCHDF5Reader::getGeoCommand(QString enumName)
    {
        if (enumName.isEmpty()) return nullptr;
        auto metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKGeometryComType>();
        int valueID = metaEnum.keyToValue(enumName.toLocal8Bit());
        if (valueID < 0) return nullptr;

        Interface::FITKInterfaceGeometryFactory* fac = Interface::FITKInterfaceGeometryFactory::getInstance();
        if (!fac) return nullptr;

        return fac->createCommand((Interface::FITKGeoEnum::FITKGeometryComType)valueID);
    }

    Core::FITKAbstractNDataObject* FITKOCCHDF5Reader::getGeoDatum(QString enumName)
    {
        if (enumName.isEmpty()) return nullptr;
        auto metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKDatumType>();
        int valueID = metaEnum.keyToValue(enumName.toLocal8Bit());
        if (valueID < 0) return nullptr;

        Interface::FITKInterfaceGeometryFactory* fac = Interface::FITKInterfaceGeometryFactory::getInstance();
        if (!fac) return nullptr;

        return fac->createDatum((Interface::FITKGeoEnum::FITKDatumType)valueID);
    }
    //@}
}   // namespace IO
