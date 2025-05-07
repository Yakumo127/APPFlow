#include "FITKWidgetVBox.h"
#include "ui_FITKWidgetVBox.h"

#include <QRadioButton>

namespace Core
{
    FITKWidgetVBox::FITKWidgetVBox(QList<QWidget*> widgetList, QWidget * parent) :
        QWidget(parent), _subWidgets(widgetList)
    {
        _ui = new Ui::FITKWidgetVBox();
        _ui->setupUi(this);

        for (int i = 0; i < widgetList.size(); i++) {
            auto w = widgetList[i];
            if (w == nullptr)continue;
            _ui->verticalLayout->addWidget(w);
        }
    }

    FITKWidgetVBox::~FITKWidgetVBox()
    {
        if (_ui)delete _ui;
    }

    void FITKWidgetVBox::setSubWidgetEnable(bool enable, bool isFirst)
    {
        for (int i = 0; i < _subWidgets.size(); i++) {
            auto w = _subWidgets[i];
            if (w == nullptr)continue;
            if (i == 0 && isFirst == true) {
                continue;
            }
            w->setEnabled(enable);
        }
    }

    QList<QWidget*> FITKWidgetVBox::getSubWidget()
    {
        return _subWidgets;
    }
}

