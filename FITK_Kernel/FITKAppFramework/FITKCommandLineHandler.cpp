#include "FITKCommandLineHandler.h"
#include <QCoreApplication>


namespace AppFrame
{
    FITKCommandLineHandler::FITKCommandLineHandler()
    {
        //获取全部参数
        _args = QCoreApplication::instance()->arguments();
    }

    void FITKCommandLineHandler::exec()
    {
    }

    bool FITKCommandLineHandler::isNoGUI()
    {
        //遍历全部的参数
        for (QString s : _args)
        {
            //移除-号
            if (s.remove("-").toLower() == "nogui")
                return true;
        }
        return false;
    }

    QString FITKCommandLineHandler::argValue(const int index)
    {
        //错误值返回空值
        if (index < 0 || index >= _args.size())
            return QString();
        return _args.value(index);
    }

    bool FITKCommandLineHandler::containsValue(QString v)
    {
        //遍历全部的参数
        for (QString s : _args)
        {
            if (s.toLower() == v.toLower())
                return true;
        }
        return false;
    }

}



