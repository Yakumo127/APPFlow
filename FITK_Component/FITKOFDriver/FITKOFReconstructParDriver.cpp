#include "FITKOFReconstructParDriver.h"

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>

namespace FoamDriver
{

    int FITKOFReconstructParDriver::getProgramType()
    {
        return 1;
    }

    QString FITKOFReconstructParDriver::getProgramName()
    {
        return "reconstructPar";
    }

    void FITKOFReconstructParDriver::start()
    {
        //输入参数判空
        if (!_inputInfo) return;

        // 获取blockMesh启动参数
        QStringList reconstructParArguments = _inputInfo->args();

        qDebug() << "reconstructPar:" << reconstructParArguments;

        // 获取监控的路径
        QStringList monitorPaths = _inputInfo->getMonitorPath();

        qDebug() << "monitorPaths:" << monitorPaths;

        QString reconstructParCommond = "reconstructPar " + reconstructParArguments.join(" ");

        qDebug() << "reconstructParCommond:" << reconstructParCommond;

        // 判断监控路径是否存在
        if (_commandRunner->isExistDictionary(monitorPaths))
        {
            // 执行命令
            connect(_commandRunner, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(threadFinishedSlot()), Qt::UniqueConnection);
            _commandRunner->setExecuteCommand(reconstructParCommond);
            _commandRunner->push2ThreadPool();
        }
    }

    void FITKOFReconstructParDriver::stop()
    {
        _commandRunner->killProcess(_commandRunner->getID());
    }
}

