#include "FITKFlowOFIOHDF5Interface.h"
#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"

#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"

#include "H5Cpp.h"

#define HDF5VERSION 0.2

namespace IO
{
    void FITKFlowOFIOHDF5Interface::setFileName(const QString& fileName)
    {
        _fileName = fileName;
    }

    QString FITKFlowOFIOHDF5Interface::getComponentName()
    {
        //返回类型名
        return "FITKFlowOFHDF5IO";
    }

    bool FITKFlowOFIOHDF5Interface::openFileStream(int state)
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

    bool FITKFlowOFIOHDF5Interface::closeFileStream()
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

    bool FITKFlowOFIOHDF5Interface::exec(const int indexPort)
    {
        //打开文件异常时，直接退出并返回结束信号
        if (!openFileStream(indexPort))
        {
            ioThreadFinishedSlot();
            return false;
        }

        //临时代码 后续重写
        if (indexPort == 1)
        {
            FITKFlowOFHDF5Reader* tempIo = new FITKFlowOFHDF5Reader();
            tempIo->setH5Root(_h5File);
            tempIo->setVersion(HDF5VERSION);
            _io = tempIo;
        }
        else if (indexPort == 2)
        {
            FITKFlowOFHDF5Writer* tempIo = new FITKFlowOFHDF5Writer();
            tempIo->setH5Root(_h5File);
            tempIo->setVersion(HDF5VERSION);
            _io = tempIo;
        }
        if (_io == nullptr) return false;

        connect(_io, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(ioThreadFinishedSlot()));
        //临时代码
        _io->setFileName(_fileName);

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

    bool FITKFlowOFIOHDF5Interface::read()
    {
        //遍历所有case
        //for (int i = 0; i < _caseManager->getDataCount(); ++i)
        //{
        //    FITKAbaqusHDF5Reader* tempIo = new FITKAbaqusHDF5Reader();
        //    tempIo->setFileName(_fileName);
        //    _io = tempIo;
        //    connect(_io, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(ioThreadFinishedSlot()));
        //    AbaqusData::FITKDataCase* dataObject = _caseManager->getDataByIndex(i);
        //    _io->setDataObject(dataObject);
        //    _io->setResultMark(&_success);
        //
        //    if (_runInThread)
        //        _io->push2ThreadPool();
        //    else
        //    {
        //        _io->run();
        //        //不在线程运行，执行完读写之后直接触发结束信号
        //        emit ioThreadFinishedSig();
        //    }
        //}
        return true;


    }

    bool FITKFlowOFIOHDF5Interface::write()
    {
        //if (!_caseManager || !_jobManager) return false;
        //for (int i = 0; i < _caseManager->getDataCount(); ++i)
        //{
        //    FITKAbaqusHDF5Writer* tempIo = new FITKAbaqusHDF5Writer();
        //    tempIo->setFileName(_fileName);
        //    _io = tempIo;
        //    connect(_io, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(ioThreadFinishedSlot()));
        //    AbaqusData::FITKDataCase* dataObject = _caseManager->getDataByIndex(i);
        //    _io->setDataObject(dataObject);
        //    _io->setResultMark(&_success);
        //
        //    if (_runInThread)
        //        _io->push2ThreadPool();
        //    else
        //    {
        //        _io->run();
        //        //不在线程运行，执行完读写之后直接触发结束信号
        //        emit ioThreadFinishedSig();
        //    }
        //}
        return true;
    }

    bool FITKFlowOFIOHDF5Interface::isSuccess()
    {
        return _success;
    }

    bool FITKFlowOFIOHDF5Interface::isRunning()
    {
        return  _io != nullptr;
    }

    void FITKFlowOFIOHDF5Interface::setRunInThread(bool r /*= true*/)
    {
        _runInThread = r;
    }

    void FITKFlowOFIOHDF5Interface::ioThreadFinishedSlot()
    {
        emit this->ioThreadFinishedSig();
        closeFileStream();
        _io = nullptr;
    }
}