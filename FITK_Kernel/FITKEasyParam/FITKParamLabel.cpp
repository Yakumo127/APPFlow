#include "FITKParamLabel.h"

namespace Core
{
    FITKParamLabel::FITKParamLabel()
    {

    }

    FITKParamLabel::~FITKParamLabel()
    {

    }

    FITKAbstractEasyParam::FITKEasyParamType FITKParamLabel::getParamType()
    {
        return FITKAbstractEasyParam::FITKEasyParamType::FEPLabel;
    }

    void FITKParamLabel::copyParaData(FITKAbstractEasyParam* data)
    {
        FITKAbstractEasyParam::copyParaData(data);

        //判断同一类型数据对象
        if (!data || data->getParamType() != this->getParamType())return;
        FITKParamLabel* oldData = dynamic_cast<FITKParamLabel*>(data);
        if (!oldData)return;
        //设置名称
        this->setDataObjectName(data->getDataObjectName());
        //拷贝参数
        this->_value = oldData->_value;
    }

    void FITKParamLabel::setValue(QStringList value)
    {
        _value = value;
        emit sigDataChange();
    }

    void FITKParamLabel::appendValue(QString value)
    {
        _value.append(value);
        emit sigDataChange();
    }

    bool FITKParamLabel::isExist(QString v)
    {
        return _value.contains(v);
    }

    QStringList FITKParamLabel::getValue()
    {
        return _value;
    }

}

