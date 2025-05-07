#include "FITKOFSnappyHexMeshDriver.h"

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

#include <QFile>
#include <QFileInfo>
#include <QDebug>

namespace FoamDriver
{
    int FITKOFSnappyHexMeshDriver::getProgramType()
    {
        return 1;
    }

    QString FITKOFSnappyHexMeshDriver::getProgramName()
    {
        return "snappyHexMesh";
    }

    void FITKOFSnappyHexMeshDriver::start()
    {
        //输入参数判空
        if (!_inputInfo) return;

        // 获取snappyHexMesh启动参数
        QStringList snappyHexMeshArguments = _inputInfo->args();

        qDebug() << "snappyHexMeshArguments:" << snappyHexMeshArguments;

        // 获取监控的路径
        QStringList monitorPaths = _inputInfo->getMonitorPath();

        qDebug() << "monitorPaths:" << monitorPaths;

        QString snappyHexMeshCommond = "snappyHexMesh " + snappyHexMeshArguments.join(" ");

        qDebug() << "snappyHexMeshCommond:" << snappyHexMeshCommond;

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

    void FITKOFSnappyHexMeshDriver::stop()
    {
        _commandRunner->killProcess(_commandRunner->getID());
    }
}
