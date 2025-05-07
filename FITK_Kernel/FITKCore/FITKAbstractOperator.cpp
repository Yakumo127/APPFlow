﻿#include "FITKAbstractOperator.h"
#include "FITKScriptTextRepo.h"

namespace Core
{
    FITKAbstractOperator::~FITKAbstractOperator()
    {
        //对象被释放，发送信号，让管理器等移除该对象
        emit operatorDestoryedSig(this);
    }

    void FITKAbstractOperator::setEmitter(QObject* obj)
    {
        //触发器记录
        _emitter = obj;
    }

    void FITKAbstractOperator::setArgs(const QString& argName, QVariant arg)
    {
        //如果已经存在则直接覆盖
        _operArgs.insert(argName, arg);
    }

    bool FITKAbstractOperator::hasArgs(const QString& argName)
    {
        return _operArgs.contains(argName);
    }

    void FITKAbstractOperator::clearArgs()
    {
        //指针类型存放在QVarient中不会被delete
        _operArgs.clear();
    }

    void FITKAbstractOperator::saveScript(const QStringList& script)
    {
        FITKScriptTextRepo::getInstance()->appendScript(script);
    }

    void FITKAbstractOperator::saveScript(const QString& script)
    {
        FITKScriptTextRepo::getInstance()->appendScript(script);
    }


}

