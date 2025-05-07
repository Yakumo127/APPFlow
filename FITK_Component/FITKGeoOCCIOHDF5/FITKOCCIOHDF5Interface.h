/*****************************************************************//**
 *
 * @file   FITKOCCIOHDF5Interface.h
 * @brief  HDF5文件读写接口
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef  _FITKOCCIOHDF5Interface_H__
#define  _FITKOCCIOHDF5Interface_H__

#include <QObject>
#include "FITKGeoOCCIOHDF5API.h"
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
     * @brief HDF5文件读取接口
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-03-12
     */
    class FITKGEOOCCIOHDF5API FITKOCCIOHDF5Interface : public QObject, public AppFrame::FITKComponentInterface
    {
        Q_OBJECT
    public:
        FITKOCCIOHDF5Interface() = default;
        virtual ~FITKOCCIOHDF5Interface() = default;

        /**
         * @brief 设置文件名称
         * @param fileName 文件名称
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void setFileName(const QString& fileName);

        /**
         * @brief 打开文件流
         * @param state 1 读取 2 写出
         * @return 是否打开成功
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool openFileStream(int state);

        /**
         * @brief 关闭文件流
         * @return 是否关闭成功
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool closeFileStream();

        /**
         * @brief 获取组件名称，不能重复  return "FITKAbaqusHDF5IO"
         * @return QString
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        virtual QString getComponentName() override;

        /**
         * @brief 文件读写时的数据对象
         * @param dataObject 数据对象
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void setDataObject(Core::FITKAbstractDataObject* dataObject);

        /**
         * @brief 执行读取或写出
         * @param indexPort  1：读取 2：写出
         * @return
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        virtual bool exec(const int indexPort) override;

        /**
         * @brief 获取是否执行成功标记
         * @return bool
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool isSuccess();

        /**
         * @brief 是否在执行中
         * @return true 执行中 false未在执行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool isRunning();
        /**
         * @brief 设置是否在独立的线程运行。默认true，为在独立线程执行
         * @param r 是否在独立线程运行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void setRunInThread(bool r = true);

        /**
         * @brief 读取 弃用
         * @return true 执行中 false未在执行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool read();

        /**
         * @brief 写出 弃用
         * @return true 执行中 false未在执行
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool write();


    signals:
        /**
         * @brief 读取线程结束发送信号
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void ioThreadFinishedSig();

    private slots:
        /**
         * @brief 读取线程结束处理槽函数
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void ioThreadFinishedSlot();

    private:
        /**
         * @brief 文件名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        QString _fileName{};

        /**
         * @brief H5的文件指针
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        H5::H5File* _h5File{};

        /**
         * @brief 数据对象
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        Core::FITKAbstractDataObject* _dataObject{};

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

#endif // 
