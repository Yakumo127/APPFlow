﻿#include "FITKWidgetComBox.h"
#include "FITKAbstractEasyParamWidget.h"
#include "FITKAbstractEasyParam.h"
#include "FITKParamCombox.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"


#include <QTableWidget>

namespace Core
{
    FITKWidgetComBox::FITKWidgetComBox(FITKAbstractEasyParam * data, QWidget * parent):
        QComboBox(parent)
    {
        _value = dynamic_cast<FITKParamCombox*>(data);
        init();
        connect(this, SIGNAL(activated(int)), this, SLOT(slotDataChange()));
    }

    FITKWidgetComBox::~FITKWidgetComBox()
    {

    }

    void FITKWidgetComBox::init()
    {
        if (_value == nullptr)return;
        QStringList value = _value->getValue();
        int index = _value->getIndex();
        addItems(value);
        setCurrentIndex(index);
    }

    void FITKWidgetComBox::wheelEvent(QWheelEvent * event)
    {
        Q_UNUSED(event);
    }

    void FITKWidgetComBox::slotDataChange()
    {
        if (_value == nullptr)return;
        _value->setIndex(currentIndex());
    }
}
