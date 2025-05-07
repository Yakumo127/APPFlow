#include "FITKOFCreatePatchDriver.h"

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>

namespace FoamDriver
{
    int FITKOFCreatePatchDriver::getProgramType()
    {
        return 1;
    }

    QString FITKOFCreatePatchDriver::getProgramName()
    {
        return "createPatch";
    }

    void FITKOFCreatePatchDriver::start()
    {
        //输入参数判空
        if (!_inputInfo) return;

        // 获取createPatch启动参数
        QStringList createPatchArguments = _inputInfo->args();

        qDebug() << "createPatchArguments:" << createPatchArguments;

        // 获取监控的路径
        QStringList monitorPaths = _inputInfo->getMonitorPath();

        qDebug() << "monitorPaths:" << monitorPaths;

        QString snappyHexMeshCommond = "createPatch " + createPatchArguments.join(" ");

        qDebug() << "createPatchCommond:" << snappyHexMeshCommond;

        // 判断监控路径是否存在
        int indexError = -1;
        if (!_commandRunner->isExistDictionary(monitorPaths, indexError))
        {
            QString str;
            if (indexError != -1)
                str = QString("Not Exist Dictionary Path : %1").arg(monitorPaths[indexError]);
            sendMessage(3, str);
        }

        // 执行命令
        connect(_commandRunner, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(threadFinishedSlot()), Qt::UniqueConnection);
        _commandRunner->setExecuteCommand(snappyHexMeshCommond);
        _commandRunner->push2ThreadPool();

    }

    void FITKOFCreatePatchDriver::stop()
    {
        _commandRunner->killProcess(_commandRunner->getID());
    }
}
