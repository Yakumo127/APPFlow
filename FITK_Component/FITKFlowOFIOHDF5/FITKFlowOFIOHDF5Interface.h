/**********************************************************************
 * @file   FITKFlowOFIOHDF5Interface.h
 * @brief  流体hdf5文件读写接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-07
 *********************************************************************/
#ifndef _FITKFLOWOFHDF5INTERFACE_H__
#define _FITKFLOWOFHDF5INTERFACE_H__

#include <QObject>
#include "FITKFlowOFIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponentInterface.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbstractIO);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, DataType);
ForwardDeclarNS(H5, H5File);

namespace IO
{
    /**
     * @brief  HDF5文件读写接口
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-09-07
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFIOHDF5Interface : public QObject, public AppFrame::FITKComponentInterface
    {

        Q_OBJECT

    public:
        using AppFrame::FITKComponentInterface::FITKComponentInterface;
        virtual ~FITKFlowOFIOHDF5Interface() = default;

        /**
         * @brief 设置文件名称
         * @param fileName 文件名称
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-04-10
         */
        void setFileName(const QString& fileName);

        /**
         * @brief 打开文件流
         * @param state 1 读取 2 写出
         * @return 是否打开成功
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-06-11
         */
        bool openFileStream(int state);

        /**
         * @brief 关闭文件流
         * @return 是否关闭成功
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-06-11
         */
        bool closeFileStream();

        /**
         * @brief 获取组件名称，不能重复  return "FITKFlowOFHDF5IO"
         * @return QString
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-10
         */
        virtual QString getComponentName() override;

        /**
         * @brief 执行读取或写出
         * @param indexPort  1：读取 2：写出
         * @return
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-04-10
         */
        virtual bool exec(const int indexPort) override;

        /**
         * @brief 获取是否执行成功标记
         * @return bool
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-04-10
         */
        bool isSuccess();

        /**
         * @brief 是否在执行中
         * @return true 执行中 false未在执行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-04-12
         */
        bool isRunning();
        /**
         * @brief 设置是否在独立的线程运行。默认true，为在独立线程执行
         * @param r 是否在独立线程运行
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-11
         */
        void setRunInThread(bool r = true);

        /**
         * @brief 读取 弃用
         * @return true 执行中 false未在执行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-04-12
         */
        bool read();

        /**
         * @brief 写出 弃用
         * @return true 执行中 false未在执行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-04-12
         */
        bool write();


    signals:
        /**
         * @brief 读取线程结束发送信号
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-10
         */
        void ioThreadFinishedSig();

    private slots:
        /**
         * @brief 读取线程结束处理槽函数
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-10
         */
        void ioThreadFinishedSlot();

    private:
        /**
         * @brief 文件名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-04-10
         */
        QString _fileName{};

        /**
         * @brief H5的文件指针
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-06-11
         */
        H5::H5File* _h5File{};

        /**
         * @brief 是否执行成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-27
         */
        bool _success{ false };
        /**
         * @brief 读取线程
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-27
         */
        Interface::FITKAbstractIO * _io = nullptr;

        /**
         * @brief 是否在线程运行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-27
         */
        bool _runInThread{ true };
    };
}


#endif
