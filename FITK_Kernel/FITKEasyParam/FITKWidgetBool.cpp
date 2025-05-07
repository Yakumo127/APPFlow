#include "FITKWidgetBool.h"

#include "FITKAbstractEasyParam.h"
#include "FITKParamBool.h"

namespace Core
{
    FITKWidgetBool::FITKWidgetBool(FITKAbstractEasyParam * data, QWidget * parent) :
        QCheckBox(parent)
    {
        _value = dynamic_cast<FITKParamBool*>(data);
        init();
        connect(this, SIGNAL(stateChanged(int)), this, SLOT(slotDataChange()));
    }

    FITKWidgetBool::~FITKWidgetBool()
    {

    }

    void FITKWidgetBool::init()
    {
        if (_value == nullptr)return;
        setChecked(_value->getValue());
    }

    void FITKWidgetBool::slotDataChange()
    {
        if (_value == nullptr)return;
        _value->setValue(isChecked());
    }
}

