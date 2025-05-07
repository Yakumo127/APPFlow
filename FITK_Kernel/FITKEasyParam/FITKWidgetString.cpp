#include "FITKWidgetString.h"
#include "FITKAbstractEasyParam.h"
#include "FITKParamString.h"

namespace Core
{
    FITKWidgetString::FITKWidgetString(FITKAbstractEasyParam * data, QWidget * parent) :
        QLineEdit(parent)
    {
        _value = dynamic_cast<FITKParamString*>(data);
        init();
        connect(this, SIGNAL(textChanged(QString)), this, SLOT(slotDataChange()));
    }

    FITKWidgetString::~FITKWidgetString()
    {

    }

    void FITKWidgetString::init()
    {
        if (_value == nullptr)return;
        QString value = _value->getValue();

        this->setText(value);
    }

    void FITKWidgetString::slotDataChange()
    {
        if (_value == nullptr)return;
        _value->setValue(text());
    }
}

