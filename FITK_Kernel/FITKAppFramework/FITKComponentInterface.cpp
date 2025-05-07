﻿#include "FITKComponentInterface.h"

namespace AppFrame
{
    FITKComponentInterface::~FITKComponentInterface()
    {
        //析构，清理数据，会收内存
    }

    void FITKComponentInterface::init()
    {
        //注册接口等操作
    }

    QWidget* FITKComponentInterface::getWidget(const int indexPort)
    {
        //错误值
        return nullptr;
    }

    QString FITKComponentInterface::getComponentName()
    {
        //抽象类，错误值
        return QString();
    }

    bool FITKComponentInterface::exec(const int indexPort)
    {
        return false;
    }

    void FITKComponentInterface::setComponentObjName(const QString & name)
    {
        //名称
        _compObjName = name;
    }

    QString FITKComponentInterface::getComponentObjName() const
    {
        return _compObjName;
    }

    CallBackFuns FITKComponentInterface::getCallBackFuns(int key)
    {
        if (_callBackFuns.contains(key))
            return _callBackFuns[key];
        return nullptr;
    }

    void FITKComponentInterface::setCallBackFuns(int k, CallBackFuns f)
    {
        _callBackFuns.insert(k, f);
    }

    void FITKComponentInterface::removeCallBackFun(int k)
    {
        _callBackFuns.remove(k);
    }

    void FITKComponentInterface::setDataObject(const QString& name, Core::FITKAbstractDataObject* data)
    {
        _dataObjects[name] = data;
    }

    Core::FITKAbstractDataObject* FITKComponentInterface::getDataObject(const QString& name)
    {
        return _dataObjects.value(name);
    }

    void FITKComponentInterface::resetDataObjects()
    {
        _dataObjects.clear();
    }

}


