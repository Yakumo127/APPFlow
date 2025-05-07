#include "FITKOFFoamDictionaryDriver.h"

#include "FITK_Kernel/FITKAppFramework/FITKAbstractProgramDriver.h"
#include "FITK_Kernel/FITKAppFramework/FITKAbstractCommandRunner.h"

// QT
#include <QDebug>

namespace FoamDriver
{
    int FITKOFFoamDictionaryDriver::getProgramType()
    {
        return 1;
    }

    QString FITKOFFoamDictionaryDriver::getProgramName()
    {
        return "foamDictionary";
    }

    int FITKOFFoamDictionaryDriver::getSubdomainsNumber()
    {
        return _subdomains;
    }

    void FITKOFFoamDictionaryDriver::start()
    {
        //输入参数判空
        if (!_inputInfo) return;

        // 获取blockMesh启动参数
        QStringList foamDictionaryArguments = _inputInfo->args();

        qDebug() << "foamDictionaryArguments:" << foamDictionaryArguments;

        // 获取监控的路径
        QStringList monitorPaths = _inputInfo->getMonitorPath();

        qDebug() << "monitorPaths:" << monitorPaths;

        //foamDictionary -entry numberOfSubdomains -value system/decomposeParDict
        QString foamDictionaryCommond = "foamDictionary " + foamDictionaryArguments.join(" ");

        qDebug() << "foamDictionaryCommond:" << foamDictionaryCommond;

        // 判断监控路径是否存在
        if (_commandRunner->isExistDictionary(monitorPaths))
        {
            // 执行命令
            connect(_commandRunner, SIGNAL(taskFinishedSig(FITKThreadTask*)), this, SLOT(threadFinishedSlot()), Qt::UniqueConnection);
            _commandRunner->setExecuteCommand(foamDictionaryCommond);
            _commandRunner->push2ThreadPool();
        }
    }

    void FITKOFFoamDictionaryDriver::stop()
    {
        _commandRunner->killProcess(_commandRunner->getID());
    }

}
