#ifndef _FITK_EASY_PARAM_WIDGET_FACTORY_H___
#define _FITK_EASY_PARAM_WIDGET_FACTORY_H___

#include "FITKEasyParamAPI.h"
#include <QString>

class QWidget;

namespace Core
{
    class FITKAbstractEasyParamWidget;
    class FITKAbstractEasyParam;

    class FITKEasyParamAPI FITKEasyParamWidgetFactory
    {
    public:
        static QWidget* createWidget(FITKAbstractEasyParam* data, QWidget * parent = nullptr, QString name = "");

    private:
        FITKEasyParamWidgetFactory() = default;
        ~FITKEasyParamWidgetFactory() = default;
    };

 
}


#endif
