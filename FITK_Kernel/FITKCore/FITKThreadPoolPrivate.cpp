#include "FITKThreadPoolPrivate.h"
#include "FITKThreadTask.h"
#include "FITK_Kernel/FITKAppFramework/FITKSignalTransfer.h"

namespace Core
{
    //
    FITKThreadPoolPrivate::~FITKThreadPoolPrivate()
    {
    }

    void FITKThreadPoolPrivate::addTask(FITKThreadTask* task)
    {
        if (task == nullptr) return;

        //关联进度信号
        if (_sigTransfer)
            connect(task, SIGNAL(sendProcessSig(QObject*, int)), _sigTransfer, SIGNAL(sendProcessSig(QObject*,int)));

        //追加到列表
        _taskList.append(task);
        //线程池启动任务
        _threadPool.start(task);
    }

    int FITKThreadPoolPrivate::taskCount()
    {
        return _taskList.size();
    }

    void FITKThreadPoolPrivate::waitForFinished()
    {
        //等待线程池全部结束
        _threadPool.waitForDone();
    }

    void FITKThreadPoolPrivate::setSignalTransfer(AppFrame::FITKSignalTransfer* sigTransfer)
    {
        _sigTransfer = sigTransfer;
    }

    bool FITKThreadPoolPrivate::isContains(FITKThreadTask* task)
    {
        return _taskList.contains(task);
    }

    void FITKThreadPoolPrivate::removeTask(FITKThreadTask* task)
    {
        if (task == nullptr) return;
        //从列表移除
        _taskList.removeOne(task);
    }

}