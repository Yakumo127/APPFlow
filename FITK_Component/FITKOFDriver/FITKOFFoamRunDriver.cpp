#include "FITKOFFoamRunDriver.h"

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

#include <QDebug>
namespace FoamDriver
{
    int FITKOFFoamRunDriver::getProgramType()
    {
        return 1;
    }

    QString FITKOFFoamRunDriver::getProgramName()
    {
        return "foamRun";
    }

    void FITKOFFoamRunDriver::start()
    {
        //输入参数判空
        if (!_inputInfo) return;

        // 获取foamRun启动参数
        QStringList foamRunArguments = _inputInfo->args();

        qDebug() << "foamRunArguments:" << foamRunArguments;

        // 获取监控的路径
        QStringList monitorPaths = _inputInfo->getMonitorPath();

        qDebug() << "monitorPaths:" << monitorPaths;

        QString foamRunCommond = "foamRun " + foamRunArguments.join(" ");

        qDebug() << "foamRunCommond:" << foamRunCommond;

        // 判断监控路径是否存在
        if (_commandRunner->isExistDictionary(monitorPaths))
        {
            // 执行命令
            connect(_commandRunner, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(threadFinishedSlot()), Qt::UniqueConnection);
            _commandRunner->setExecuteCommand(foamRunCommond);
            _commandRunner->push2ThreadPool();
        }

    }

    void FITKOFFoamRunDriver::stop()
    {
        _commandRunner->killProcess(_commandRunner->getID());
    }
}
