﻿#include "FITKParamInt.h"

namespace Core
{
    FITKParamInt::FITKParamInt()
    {

    }

    FITKParamInt::~FITKParamInt()
    {

    }

    FITKAbstractEasyParam::FITKEasyParamType FITKParamInt::getParamType()
    {
        return FITKAbstractEasyParam::FITKEasyParamType::FEPInt;
    }

    void FITKParamInt::copyParaData(FITKAbstractEasyParam* data)
    {
        FITKAbstractEasyParam::copyParaData(data);

        //判断同一类型数据对象
        if (!data || data->getParamType() != this->getParamType())return;
        FITKParamInt* oldData = dynamic_cast<FITKParamInt*>(data);
        if (!oldData)return;
        //设置名称
        this->setDataObjectName(data->getDataObjectName());
        //拷贝参数
        this->_value = oldData->_value;
        this->_range[0] = oldData->_range[0];
        this->_range[1] = oldData->_range[1];
    }

    void FITKParamInt::setValue(int value)
    {
        if (value < _range[0] || value>_range[1])return;
        _value = value;
        emit sigDataChange();
    }

    int FITKParamInt::getValue()
    {
        return _value;
    }
    void FITKParamInt::setRange(int * range)
    {
        _range[0] = range[0];
        _range[1] = range[1];
    }

    void FITKParamInt::getRange(int * range)
    {
        range[0] = _range[0];
        range[1] = _range[1];
    }
}

