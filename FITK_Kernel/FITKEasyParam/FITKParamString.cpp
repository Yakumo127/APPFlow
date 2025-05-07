﻿#include "FITKParamString.h"

namespace Core
{
    FITKParamString::FITKParamString()
    {

    }

    FITKParamString::~FITKParamString()
    {

    }

    FITKAbstractEasyParam::FITKEasyParamType FITKParamString::getParamType()
    {
        return FITKAbstractEasyParam::FITKEasyParamType::FEPString;
    }

    void FITKParamString::copyParaData(FITKAbstractEasyParam* data)
    {
        FITKAbstractEasyParam::copyParaData(data);
        //判断同一类型数据对象
        if (!data || data->getParamType() != this->getParamType())return;
        FITKParamString* oldData = dynamic_cast<FITKParamString*>(data);
        if (!oldData)return;
        //设置名称
        this->setDataObjectName(data->getDataObjectName());
        //拷贝参数
        this->_value = oldData->_value;
    }

    void FITKParamString::setValue(QString value)
    {
        _value = value;
        emit sigDataChange();
    }

    QString FITKParamString::getValue()
    {
        return _value;
    }
}

