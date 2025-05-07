#include "FITKOFInputInfo.h"

namespace FoamDriver
{
    void FITKOFInputInfo::setArgs(const QStringList &args)
    {
        //设置参数列表
        _args = args;
    }

    QStringList FITKOFInputInfo::args()
    {
        //获取参数列表
        return _args;
    }

    void FITKOFInputInfo::setMonitorPath(QStringList & monitorpath)
    {
        //设置监控目录
        _monitorPaths = monitorpath;
    }

    QStringList FITKOFInputInfo::getMonitorPath()
    {
        //获取监控目录
        return _monitorPaths;
    }

    void FITKOFInputInfo::setMonitorFiles(QStringList & monitorFiles)
    {
        //设置监控文件列表
        _monitorFiles = monitorFiles;
    }

    QStringList FITKOFInputInfo::getMonitorFiles()
    {
        //获取监控文件列表
        return _monitorFiles;
    }
}
