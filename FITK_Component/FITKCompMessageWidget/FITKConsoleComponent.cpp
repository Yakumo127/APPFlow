﻿#include "FITKConsoleComponent.h"
#include "FITKConsole.h"

namespace Comp
{
    ConsoleComponent::ConsoleComponent(QWidget* parent)
    {
        _parent = parent;
    }

    ConsoleComponent::~ConsoleComponent()
    {
        //释放内存
        QList<FITKConsole*> ws = m_widgetHash.values();
        for (FITKConsole* w : ws)
        {
            if (w)
            {
                delete w;
            }
        }

        m_widgetHash.clear();
    }

    void ConsoleComponent::takeoverQtMessage(bool takeover /*= true*/)
    {
        //接管qt输出
        _takeoverQt = takeover;
    }

    QWidget * ConsoleComponent::getWidget(const int indexPort)
    {
        // 判断索引异常。
        if (indexPort < 0)
        {
            return nullptr;
        }

        if (!m_widgetHash.contains(indexPort))
        {
            FITKConsole* w = new FITKConsole(_takeoverQt, _parent);
            m_widgetHash.insert(indexPort, w);
            connect(w, &QWidget::destroyed, this, [&] 
            { 
                int port = m_widgetHash.key(w);
                m_widgetHash.remove(port);
            });
        }

        return m_widgetHash[indexPort];
    }

    QString ConsoleComponent::getComponentName()
    {
        //自定义组件名称
        return "MessageConsole";
    }
}