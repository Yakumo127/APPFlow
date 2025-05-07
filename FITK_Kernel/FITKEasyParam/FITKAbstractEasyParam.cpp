#include "FITKAbstractEasyParam.h"

namespace Core 
{
    FITKAbstractEasyParam::~FITKAbstractEasyParam()
    {
        _data.clear();
    }

    FITKAbstractEasyParam::FITKEasyParamType Core::FITKAbstractEasyParam::getParamType()
    {
        return  Core::FITKAbstractEasyParam::FITKEasyParamType::FEPNone;
    }

    void FITKAbstractEasyParam::copyParaData(FITKAbstractEasyParam * data)
    {
        if (data == nullptr)return;
        QList<QString> title = data->getDataTitle();
        for (QString t : title) {
            QVariant value = data->getData(t);
            this->setData(value, t);
        }
    }

    QVariant FITKAbstractEasyParam::getData(QString title)
    {
        return _data.value(title);
    }

    void FITKAbstractEasyParam::setData(QVariant data, QString title)
    {
        _data.insert(title, data);
    }

    QList<QString> FITKAbstractEasyParam::getDataTitle()
    {
        return _data.keys();
    }
}