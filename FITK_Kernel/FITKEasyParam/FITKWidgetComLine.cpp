#include "FITKWidgetComLine.h"
#include "ui_FITKWidgetComLine.h"
#include "FITKAbstractEasyParam.h"
#include "FITKEasyParamWidgetFactory.h"

#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QLabel>
#include <QToolBox>

namespace Core
{
    FITKWidgetComLine::FITKWidgetComLine(FITKAbstractEasyParam* data, QWidget * parent) :
        QWidget(parent), _data(data)
    {
        _ui = new Ui::FITKWidgetComLine();
        _ui->setupUi(this);

        init();
    }

    FITKWidgetComLine::~FITKWidgetComLine()
    {
        if (_ui)delete _ui;
    }

    void FITKWidgetComLine::init()
    {
        if (_data == nullptr)return;
        QLabel* label = new QLabel(this);
        label->setText(_data->getDataObjectName());
        int width = this->width();
        label->setMinimumWidth(width*0.4);
        label->setMaximumWidth(width*0.4);
        _ui->horizontalLayout->addWidget(label);

        QWidget* widget = FITKEasyParamWidgetFactory::createWidget(_data, this);
        if (widget == nullptr)return;
        _ui->horizontalLayout->addWidget(widget);
    }

    QToolBox * FITKWidgetComLine::CreateToolBox(QWidget * parent)
    {
        QToolBox* toolBox = new QToolBox(parent);
        toolBox->setStyleSheet(
            "QToolBox::tab {"
            "    background-color: #d3d3d3;" /* 淡浅灰色背景 */
            "}"
            "QToolBox::tab:selected {"
            "    background-color: #a9a9a9;" /* 选中时的背景色，稍深的灰色 */
            "}"
        );

        return toolBox;
    }

    FITKAbstractEasyParam * FITKWidgetComLine::getData()
    {
        return _data;
    }
}

