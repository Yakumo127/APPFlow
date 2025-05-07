#include "FITKOCCHDF5Writer.h"

//Kernel
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
//Geomerty
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorCommand.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorDatum.h"

#include "H5Cpp.h"
namespace IO
{

    void FITKOCCHDF5Writer::run()
    {
        *_resultMark = false;
        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_data);
        if (!commList || !_h5File) return;
        *_resultMark = true;
        *_resultMark &= writeInfo();
        *_resultMark &= writeVersion();
        *_resultMark &= writeCommDatas();
        *_resultMark &= writeDatumDatas();

        this->sendCalculateProgress(100);
    }

    void FITKOCCHDF5Writer::sendCalculateProgress(int Progress)
    {

    }

    void FITKOCCHDF5Writer::consoleMessage(int level, const QString &str)
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

    bool FITKOCCHDF5Writer::writeCommDatas()
    {
        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_data);
        if (!commList || !_h5File) return false;
        bool isW = true;
        H5::Group casesGroup = _h5File->createGroup("Geometry");
        int count = commList->getDataCount();
        for (int i = 0; i < count; i++)
        {
            Interface::FITKAbsGeoCommand* comm = commList->getDataByIndex(i);
            if (!comm) return false;

            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKInterfaceHDF5AdaptorCommand>("HDF5", "Interface::FITKAbsGeoCommand");
            if (adaptor == nullptr) return false;
            adaptor->setH5GroupData(casesGroup);
            adaptor->setDataObject(comm);
            adaptor->setFileWriter(this);
            bool w = adaptor->adaptW();
            if (!w) consoleMessage(3, QString("Write Command Errors, CaseName : %1").arg(comm->getDataObjectName()));
            isW &= w;
            delete adaptor;
        }

        //写出几何命令列表长度
        hsize_t       dim[2] = { 1, 1 };
        H5::DataSpace SpaceThree(2, dim);
        H5::Attribute transAttr = casesGroup.createAttribute("Count", H5::PredType::NATIVE_INT, SpaceThree);
        transAttr.write(H5::PredType::NATIVE_INT, &count);
        return isW;
    }

    bool FITKOCCHDF5Writer::writeDatumDatas()
    {
        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_data);
        if (!commList || !_h5File) return false;
        bool isW = true;
        H5::Group datumsGroup = _h5File->createGroup("Datums");
        auto datumList = commList->getDatumManager();

        int count = datumList->getDataCount();
        for (int i = 0; i < count; i++)
        {
            Interface::FITKAbsGeoDatum* datum = datumList->getDataByIndex(i);
            if (!datum) return false;

            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKInterfaceHDF5AdaptorDatum>("HDF5", "Interface::FITKAbsGeoDatum");
            if (adaptor == nullptr) return false;
            adaptor->setH5GroupData(datumsGroup);
            adaptor->setDataObject(datum);
            adaptor->setFileWriter(this);
            bool w = adaptor->adaptW();
            if (!w) consoleMessage(3, QString("Write Datum Errors, CaseName : %1").arg(datum->getDataObjectName()));
            isW &= w;
            delete adaptor;
        }

        //写出几何命令列表长度
        hsize_t       dim[2] = { 1, 1 };
        H5::DataSpace SpaceThree(2, dim);
        H5::Attribute transAttr = datumsGroup.createAttribute("Count", H5::PredType::NATIVE_INT, SpaceThree);
        transAttr.write(H5::PredType::NATIVE_INT, &count);
        return isW;
    }

    bool FITKOCCHDF5Writer::writeInfo()
    {
        H5::Group InfoGroup = _h5File->createGroup("Info");
        H5::DataSpace dataspace;
        H5::StrType   datatypeStr(H5::PredType::C_S1, H5T_VARIABLE);
        // 创建字符串类属性
        H5::Attribute desAttr = InfoGroup.createAttribute("SoftWareName", datatypeStr, dataspace);
        std::string softWareName = "CADOCCAPP";
        desAttr.write(datatypeStr, softWareName);
        return true;
    }

    bool FITKOCCHDF5Writer::writeVersion()
    {
        QString name = "Version";
        H5::Group versionGroup = _h5File->createGroup(name.toStdString());
        hsize_t       dim[2] = { 1, 1 };
        H5::DataSpace SpaceThree(2, dim);
        H5::Attribute transAttr = versionGroup.createAttribute(name.toStdString(), H5::PredType::NATIVE_DOUBLE, SpaceThree);
        transAttr.write(H5::PredType::NATIVE_DOUBLE, &_version);
        return true;
    }

    // Base.
    //@{


    //@}
}   // namespace IO
