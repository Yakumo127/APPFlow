#include "FITKExecProgramDriver.h"
#include "FITKAppFramework.h"
#include "FITKSignalTransfer.h"
#include <QProcess>

namespace AppFrame
{
    FITKExecProgramDriver::FITKExecProgramDriver()
    {
        //创建进程对象
        _process = new QProcess;
        // _process->setReadChannel(QProcess::StandardOutput);

        //消息输出
        connect(_process, &QProcess::readyRead, this, &FITKExecProgramDriver::sendMessageSlot);
    }

    FITKExecProgramDriver::~FITKExecProgramDriver()
    {
        //杀死进程
        if (!_process) return;
        disconnect(_process, &QProcess::readyRead, this, &FITKExecProgramDriver::sendMessageSlot);
        disconnect(_process, SIGNAL(finished(int)), this, SIGNAL(sig_Finish()));
        _process->kill();
        _process->waitForFinished();
       // 释放进程对象 
 //       delete _process;
 //       _process = nullptr;
    }

    void FITKExecProgramDriver::setExecProgram(const QString & program)
    {
        _program = program;
    }

    QString FITKExecProgramDriver::getExecProgram() const
    {
        return _program;
    }

    void FITKExecProgramDriver::setWorkingDirectory(const QString & path)
    {
        _workDir = path;
    }

    QString FITKExecProgramDriver::getWorkingDirectory() const
    {
        return _workDir;
    } 

    void FITKExecProgramDriver::start()
    {
        //启动进程
        if (_process == nullptr) return;
        QStringList args;
        if (_inputInfo != nullptr)
            args = _inputInfo->args();

        // 设置工作路径。
        if (!_workDir.isEmpty())
        {
            _process->setWorkingDirectory(_workDir);
        }
        //信号关联
        connect(_process, SIGNAL(finished(int)), this, SIGNAL(sig_Finish()));

        _process->start(_program, args);
    }

    void FITKExecProgramDriver::stop()
    {
        //终止进程
        if (_process == nullptr) return;
        _process->kill();
        _process->waitForFinished();
    }

    void FITKExecProgramDriver::enableSendMessage(bool s)
    {
        _sendMessage = s;
    }

    
    bool FITKExecProgramDriver::isSendMessage() const
    {
        return _sendMessage;
    }

    void FITKExecProgramDriver::sendMessageSlot()
    {
        //读取信息
        if (!_sendMessage ||  _process == nullptr) return;

        QString mess = _process->readAllStandardOutput();
        if (!mess.isEmpty())
        {
            this->sendMessage(0, mess);
        }

        QString err = _process->readAllStandardError();
        if (!err.isEmpty())
        {
            this->sendMessage(0, err);
        }
    }
}
