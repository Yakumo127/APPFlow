﻿#include "FITKWidgetSciNotation.h"

#include <QTimer>
#include <QHelpEvent>
#include <QToolTip>
#include <QMessageBox>

namespace Core
{
    FITKWidgetSciNotation::FITKWidgetSciNotation(QWidget* parent) :
        QLineEdit(parent) 
    {
        setAttribute(Qt::WA_AlwaysShowToolTips);
        //文本编辑控件编辑完成信号连接
        connect(this, SIGNAL(editingFinished()), this, SLOT(slot_textChanged()));

        connect(this, &FITKWidgetSciNotation::textEdited, this, &FITKWidgetSciNotation::slot_textEdited);
        connect(this, &FITKWidgetSciNotation::textChanged, this, &FITKWidgetSciNotation::slot_textEdited);
    }

    FITKWidgetSciNotation::~FITKWidgetSciNotation()
    {

    }

    void FITKWidgetSciNotation::setValue(double val)
    {
        // 保存数值。
        _value = val;
        _currentValidText = QString::number(_value);

        // 更新文本。
        disconnect(this, &FITKWidgetSciNotation::textChanged, this, &FITKWidgetSciNotation::slot_textEdited);
        setText(QString("%1").arg(val));
        connect(this, &FITKWidgetSciNotation::textChanged, this, &FITKWidgetSciNotation::slot_textEdited);
    }

    double FITKWidgetSciNotation::value()
    {
        return _value;
    }

    void FITKWidgetSciNotation::setRange(double* range)
    {
        _range[0] = range[0];
        _range[1] = range[1];
    }

    bool FITKWidgetSciNotation::isValidText(QString message, double & value)
    {
        bool result = {};
        //判断是否为空
        if (message.isEmpty())return false;

        //获取第一个字符串
        QString firstChart = message.mid(0, 1);
        
        //判断数据是否为负数，qstring::toDouble不支持负数
        if (firstChart == "-"){
            QString stringData = message.remove(0, 1);
            stringData.toDouble(&result);
            if (result == true){
                double doubleData = stringData.toDouble();
                //数据取反
                value = doubleData * (-1);
                return true;
            }
            else{
                return false;
            }
        }
        else{
            message.toDouble(&result);
            if (result == true){
                value = message.toDouble(&result);
                return true;
            }
            else{
                return false;
            }
        }
    }

    QString FITKWidgetSciNotation::getCurrentValidText()
    {
        return _currentValidText;
    }

    bool FITKWidgetSciNotation::getCurrentValidValue(double & value)
    {
        return isValidText(_currentValidText, value);
    }

    void FITKWidgetSciNotation::setCurrentValidValue(double value)
    {
        _currentValidText = QString::number(value);
        setText(_currentValidText);
    }

    void FITKWidgetSciNotation::slot_textChanged()
    {
        bool result = true;
        double value;
        //判断文本是否是有效的科学计数法
        result = isValidText(this->text(), value);
        if (result == true){
            //判断数据是否超出范围
            if (value < _range[0] || value>_range[1]) {
                QMessageBox::warning(this, "Warning", QString("Value Range:%1-%2").arg(_range[0]).arg(_range[1]));
                this->setText(_currentValidText);
                return;
            }
            _currentValidText = this->text();
            emit dataChanged();
        }
        else{
            this->setText(_currentValidText);
        }
    }

    void FITKWidgetSciNotation::slot_textEdited(const QString & text)
    {
        _value = text.toDouble();
    }
}
