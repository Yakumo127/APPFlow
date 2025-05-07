#include "FITKConsole.h"
#include "FITK_Kernel/FITKAppFramework/FITKSignalTransfer.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include <QAction>
#include <QDialog>
#include <QFile>
#include <QMenu>
#include <QMutex>
#include <QMutexLocker>
#include <QFileDialog>
#include <QTextStream>
#include <QContextMenuEvent>
#include <QDateTime>

namespace Comp
{
    //静态变量初始化
    QMutex FITKConsole::m_mutex;

    FITKConsole::FITKConsole(bool qtmessage, QWidget* parent)
        :QTextEdit(parent)
    {        
        //信号槽的方式显示信号连接
        if (FITKAPP != nullptr) {
            AppFrame::FITKSignalTransfer* SigTran = FITKAPP->getSignalTransfer();
            connect(SigTran, SIGNAL(outputMessageSig(int, QString)), this, SLOT(displayMessage(int, QString)));
        }

        //qt调试信息回调函数注册
        if(qtmessage)
            qInstallMessageHandler(FITKConsole::messageCallBack);

        this->setStyleSheet("font-size: 10pt;");
    }

    FITKConsole::~FITKConsole()
    {

    }

    void FITKConsole::displayMessage(MessageType type, const QString message)
    {
        //互斥锁添加
        QMutexLocker mutexLoc(&m_mutex);
        QString value = "";

        //获取当前时间
        QDateTime dateTime = QDateTime::currentDateTime();
        QString time = dateTime.toString("(hh:mm:ss)");

        //消息数据类型转换
        switch (type){
        case MessageType::Normal:value = QString("<font color=\"#3CB371\">[Normal]%1:%2</font>").arg(time).arg(message); break;
        case MessageType::Warning:value = QString("<font color = \"#FF9900\">[Warning]%1:%2</font>").arg(time).arg(message); break;
        case MessageType::Error:value = QString("<font color = \"#FF0000\">[Error]%1:%2</font>").arg(time).arg(message); break;
        case MessageType::Info:value = QString("%1").arg(message); break;
        default: break;
        }
        //消息体为空，不显示
        if (value.isEmpty())return;
        this->append(value);
    }

    void FITKConsole::displayMessage(int type, const QString message)
    {
        displayMessage(static_cast<MessageType>(type), message);
    }

    void FITKConsole::contextMenuEvent(QContextMenuEvent * event)
    {
        //控制台事件添加
        QMenu menu(this);

        QAction* clact = menu.addAction(tr("clear"));
        QAction* saveAct = menu.addAction(tr("Save"));
        connect(clact, SIGNAL(triggered()), this, SLOT(clear()));
        connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

        //事件位置添加
        menu.exec(event->globalPos());
    }

    void FITKConsole::messageCallBack(QtMsgType type, const QMessageLogContext & context, const QString & msg)
    {
        int mesType = 0;
        switch (type)
        {
        case QtDebugMsg: break;
        case QtInfoMsg:mesType = 1; break;
        case QtWarningMsg:mesType = 2; break;
        case QtCriticalMsg:
        case QtFatalMsg:mesType = 3; break;
        }
        //消息类型为空，不显示消息
        if (mesType == 0)return;

        //获取信号对象
        if (FITKAPP == nullptr) return;
        AppFrame::FITKSignalTransfer* SigTran = FITKAPP->getSignalTransfer();

        //发送消息
        if (SigTran == nullptr)return;
        emit SigTran->outputMessageSig(mesType, msg);
    }

    void FITKConsole::save()
    {
        //保存对话框
        QString filePath = QFileDialog::getSaveFileName(nullptr, tr("Save file"), "", "Text files (*.txt)");
        if (filePath.isEmpty())return;

        QString value =this->toPlainText();
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))return;
 
        QTextStream fileStream(&file);
        fileStream << value;
        file.close();
    }
}