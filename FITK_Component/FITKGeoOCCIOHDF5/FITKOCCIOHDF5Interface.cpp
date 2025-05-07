#include "FITKOCCIOHDF5Interface.h"
#include "FITKOCCHDF5Reader.h"
#include "FITKOCCHDF5Writer.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorCommand.h"

#include "H5Cpp.h"

#define HDF5VERSION 0.1

namespace IO
{
    void FITKOCCIOHDF5Interface::setFileName(const QString& fileName)
    {
        _fileName = fileName;
    }

    QString FITKOCCIOHDF5Interface::getComponentName()
    {
        //返回类型名
        return "FITKOCCHDF5IO";
    }

    bool FITKOCCIOHDF5Interface::openFileStream(int state)
    {
        try
        {
            if (state == 1)
                _h5File = new H5::H5File(_fileName.toStdString().c_str(), H5F_ACC_RDWR);
            else if (state == 2)
                _h5File = new H5::H5File(_fileName.toStdString().c_str(), H5F_ACC_TRUNC);
        }
        catch (const H5::FileIException& ex)
        {
            AppFrame::FITKMessageError(QString("HDF5 File I/O Error: %1").arg(ex.getCDetailMsg()));
        }

        if (_fileName.isEmpty() || !_h5File) return false;
        return true;
    }

    bool FITKOCCIOHDF5Interface::closeFileStream()
    {
        if (_h5File != nullptr)
        {
            _h5File->close();
            delete _h5File;
            _h5File = nullptr;
            return true;
        }
        return false;
    }

    void FITKOCCIOHDF5Interface::setDataObject(Core::FITKAbstractDataObject* dataObject)
    {
        _dataObject = dataObject;
    }

    bool FITKOCCIOHDF5Interface::exec(const int indexPort)
    {
        if (_io) return false;
        //打开文件异常时，直接退出并返回结束信号
        if (!openFileStream(indexPort))
        {
            ioThreadFinishedSlot();
            return false;
        }

        //临时代码 后续重写
        auto commList = dynamic_cast<Interface::FITKGeoCommandList*>(_dataObject);
        if (commList == nullptr) return false;
        if (indexPort == 1)
        {
            FITKOCCHDF5Reader* tempIo = new FITKOCCHDF5Reader();

            //commList->clear();
            //重置仓库数据
            FITKAPP->resetDataObjects();
            tempIo->setH5Root(_h5File);
            tempIo->setVersion(HDF5VERSION);
            _io = tempIo;
        }
        else if (indexPort == 2)
        {
            FITKOCCHDF5Writer* tempIo = new FITKOCCHDF5Writer();
            tempIo->setH5Root(_h5File);
            tempIo->setVersion(HDF5VERSION);
            _io = tempIo;
        }
        if (_io == nullptr) return false;

        connect(_io, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(ioThreadFinishedSlot()));
        //临时代码
        _io->setFileName(_fileName);
        _io->setDataObject(commList);
        _io->setResultMark(&_success);
        //在线程运行，提交到线程池
        if (_runInThread)
            _io->push2ThreadPool();
        else
        {
            _io->run();
            //不在线程运行，执行完读写之后直接触发结束信号
            emit ioThreadFinishedSig();
            closeFileStream();
        }
        return true;
    }

    bool FITKOCCIOHDF5Interface::read()
    {
        return false;
    }

    bool FITKOCCIOHDF5Interface::write()
    {
        //Interface::FITKGeoCommandList* comList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();
        //if (comList == nullptr) return false;
        //auto redoList = comList->getRedoList();
        //if (redoList == nullptr) return false;
        //int count = redoList->getDataCount();
        //for (int i = 0; i < count; i++)
        //{
        //    Interface::FITKAbsGeoCommand* comm = redoList->getDataByIndex(i);
        //    if (comm == nullptr) return false;
        //
        //    FITKInterfaceHDF5AdaptorCommand* adaptor = FITKIOADAPTORFACTORY->createT<FITKInterfaceHDF5AdaptorCommand>("HDF5", comm);
        //    if (!adaptor) return false;
        //}



        return false;
    }

    bool FITKOCCIOHDF5Interface::isSuccess()
    {
        return _success;
    }

    bool FITKOCCIOHDF5Interface::isRunning()
    {
        return  _io != nullptr;
    }

    void FITKOCCIOHDF5Interface::setRunInThread(bool r /*= true*/)
    {
        _runInThread = r;
    }

    void FITKOCCIOHDF5Interface::ioThreadFinishedSlot()
    {
        emit this->ioThreadFinishedSig();
        closeFileStream();
        _io = nullptr;
    }
}



