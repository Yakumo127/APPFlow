#include "FITKWidgetDouble.h"
#include "FITKAbstractEasyParam.h"
#include "FITKParamDouble.h"

namespace Core
{
    FITKWidgetDouble::FITKWidgetDouble(FITKAbstractEasyParam * data, QWidget * parent):
        FITKWidgetSciNotation(parent)
    {
        _value = dynamic_cast<FITKParamDouble*>(data);
        init();
    }

    FITKWidgetDouble::~FITKWidgetDouble()
    {

    }

    void FITKWidgetDouble::init()
    {
        if (_value == nullptr)return;
        double value = _value->getValue();
        double range[2] = { 0,0 };
        _value->getRange(range);
        this->setRange(range);
        this->setCurrentValidValue(value);

        connect(this, SIGNAL(dataChanged()), this, SLOT(slotDataChangeFinished()));
    }

    void FITKWidgetDouble::wheelEvent(QWheelEvent * event)
    {
        Q_UNUSED(event);
    }

    void FITKWidgetDouble::slotDataChangeFinished()
    {
        if (_value == nullptr)return;

        double value = 0.0;
        getCurrentValidValue(value);
        _value->setValue(value);
    }
}
