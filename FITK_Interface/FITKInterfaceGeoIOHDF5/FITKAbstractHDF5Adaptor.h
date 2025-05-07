/**
 *
 * @file   FITKAbstractHDF5Adaptor.h
 * @brief  抽象的HDF5文件读写适配器
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 */
#ifndef _FITKABSTRACTHDF5ADAPTOR_H__
#define _FITKABSTRACTHDF5ADAPTOR_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKAbstractIOAdaptor.h"
#include "H5Cpp.h"

namespace Core
{
    class FITKAbstractNDataObject;
}

ForwardDeclarNS(Interface, FITKAbsGeoCommand);

namespace IO
{
    class FITKAbstractHDF5Reader;
    class FITKAbstractHDF5Writer;

    /**
     * @brief 抽象的HDF5文件读写适配器
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-09-09
     */
    class FITKINTERFACEGEOIOHDF5API FITKAbstractHDF5Adaptor : public Adaptor::FITKAbstractIOAdaptor
    {
        FITKCLASS(IO, FITKAbstractHDF5Adaptor);

    public:
        explicit FITKAbstractHDF5Adaptor() = default;
        virtual ~FITKAbstractHDF5Adaptor() = 0;

        /**
         * @brief 设置INP文件读取器
         * @param reader INP读取类
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void setFileReader(FITKAbstractHDF5Reader* reader);

        /**
         * @brief 设置INP文件写出器
         * @param writer INP写出类
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void setFileWriter(FITKAbstractHDF5Writer* writer);

        /**
         * @brief 设置H5GroupData
         * @param h5Group
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void setH5GroupData(H5::Group& h5Group);

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool adaptW() override;

        /**
         * @brief 读取几何适配器
         * @return Status true and false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readGeometryAdaptor(Core::FITKAbstractNDataObject* comm, H5::Group & h5Group, QString adaptorName);

        /**
         * @brief 写出几何适配器
         * @return Status true and false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool writeGeometryAdaptor(Core::FITKAbstractNDataObject* comm, H5::Group & h5Group, QString adaptorName);

        /**
         * @brief 读取字符串型属性
         * @return true，读取成功；false，读取失败。
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param str 读到的字符串
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readStrAttribute(H5::Group& h5group, std::string name, std::string& str);
        /**
         * @brief 读取字符串型属性
         * @return 读到的字符串
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        std::string readStrAttribute(H5::H5Object& h5group, std::string name, bool* b = nullptr);
        /**
         * @brief 读取指定类型属性
         * @return true，读取成功；false，读取失败。
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param type 属性类型
         * @param buf 属性变量指针
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readAttribute(H5::H5Object& h5group, std::string name, const H5::DataType& type, void* buf);
        /**
         * @brief 读取bool类型属性
         * @return 读取到的bool值
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readBoolAttribute(H5::H5Object& h5group, std::string name, bool* b = nullptr);

        /**
         * @brief 读取双精度浮点类型属性
         * @return 读取到的双精度浮点数
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        double readDoubleAttribute(H5::H5Object& h5group, std::string name, bool* b = nullptr);

        /**
         * @brief 读取双精度浮点类型链表数据
         * @return 读取到的双精度浮点数
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readDoubleDataSet(H5::Group& h5group, std::string name, QList<double>& buff, int n = 1, int m = 1, bool* b = nullptr);


        /**
         * @brief 读取双精度浮点类型链表属性
         * @return 读取到的双精度浮点数
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readDoubleAttribute(H5::Group& h5group, std::string name, double* buff, int n = 1, int m = 1, bool* b = nullptr);

        /**
         * @brief 读取双精度浮点类型链表属性
         * @return 读取到的双精度浮点数
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readDoubleAttrbuteDataSet(H5::Group& h5group, std::string name, QList<double>& buff, int n = 1, int m = 1, bool* b = nullptr);


        /**
         * @brief 读取整数类型属性
         * @return 成功标记
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readIntVectorAttribute(H5::Group& h5group, std::string name, void* buff);
        /**
         * @brief 读取整数类型属性
         * @return 读取到的整数
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        int readIntAttribute(H5::H5Object& h5group, std::string name, bool* b = nullptr);

        /**
         * @brief 读取整数类型属性
         * @return 读取到的整数
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param b 成功标记
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readIntAttribute(H5::H5Object& h5group, std::string name, int* buff, int n, int m);

        /**
         * @brief 获取属性的行列数
         * @return true，读取成功；false，读取失败。
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param n 属性行数
         * @param m 属性列数
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool getAttributeDim(H5::Group& h5group, std::string name, int& n, int& m);

        /**
         * @brief 获取数据集的行列数
         * @return true，读取成功；false，读取失败。
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param n 属性行数
         * @param m 属性列数
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool getDataSetDim(H5::Group& h5group, std::string name, int& n, int& m);

        /**
         * @brief 读取字符串序列
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param rtStrs 读取到的字符串序列
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void readStrDataSet(H5::Group& h5group, std::string name, std::vector< std::string >& rtStrs);

        /**
         * @brief 读取字符串序列
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param rtStrs 读取到的字符串序列
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void readStrDataSet(H5::Group& h5group, std::string name, QList<QString>& rtStrs);

        /**
         * @brief 读取int序列
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param data 读取到的数据链表
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void readIntDataSet(H5::H5Object& h5group, std::string name, QList< int >& data);

        /**
         * @brief 读取Char *序列
         * @param h5group 要读取的group
         * @param name 属性名称
         * @param data 读取到的数据链表
         * @param len  读取长度
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        bool readCharDataSet(H5::H5Object& h5group, std::string name, char* &data, int len);

        /**
         * @brief 向h5group中写入属性
         * @param h5group，要写入的group；name，属性名称；type，属性类型；buf，数据指针；n，m，属性的2维尺寸。
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        void writeAttribute(H5::H5Object& h5group, std::string name, const H5::DataType& type, const void* buf, int n = 1, int m = 1);
        void writeStrAttribute(H5::H5Object& h5group, std::string name, std::string data);
        void writeBoolAttribute(H5::H5Object& h5group, std::string name, const void* buf, int n = 1, int m = 1);
        void writeDoubleAttribute(H5::H5Object& h5group, std::string name, const void* buf, int n = 1, int m = 1);
        void writeDoubleAttributeDataset(H5::H5Object& h5group, std::string name, QList<double>& buf, int n = 1, int m = 1);
        void writeIntAttribute(H5::H5Object& h5group, std::string name, const void* buf, int n = 1, int m = 1);
        void writeStrDataSet(H5::H5Object& h5group, std::string name, std::vector< std::string > data);
        void writeStrDataSet(H5::H5Object& h5group, std::string name, const QList< QString >& data);
        void writeCharDataSet(H5::H5Object& h5group, std::string name, char* &data, int len);
        void writeIntDataSet(H5::H5Object& h5group, std::string name, const QList< int >& data);
        void writeDoubleDataSet(H5::H5Object& h5group, std::string name, const QList< double >& data);


    protected:

#ifdef QT_DEBUG
        std::string createParentAttribute(Core::FITKAbstractNDataObject* obj, H5::H5Object & h5Object);
#endif
        std::string createParentAttribute(Core::FITKAbstractDataObject* obj, H5::H5Object & h5Object);

        /**
         * @brief 读取NDataObject信息
         * @param obj:写出对象
         * @return
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-06-04
         */
        bool readNDataObject(Core::FITKAbstractNDataObject* obj, H5::H5Object & h5Object);

        /**
         * @brief 读取NDataObject信息
         * @param obj:写出对象
         * @return
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-06-04
         */
        bool readDataObject(Core::FITKAbstractDataObject* obj, H5::H5Object & h5Object);

        /**
         * @brief 写出NDataObject信息
         * @param obj:写出对象
         * @return
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-31
         */
        bool writeNDataObject(Core::FITKAbstractNDataObject* obj, H5::H5Object & h5Object);

        /**
         * @brief 写出NDataObject信息
         * @param obj:写出对象
         * @return
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-05-31
         */
        bool writeDataObject(Core::FITKAbstractDataObject* obj, H5::H5Object & h5Object);

    protected:

        /**
         * @brief INP文件读取器
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        FITKAbstractHDF5Reader* _reader{};

        /**
         * @brief INP文件写出器
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        FITKAbstractHDF5Writer* _writer{};

        /**
         * @brief H5Group
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        H5::Group* _h5Group{};

        /**
         * @brief _h5Group下创建的第一个Group
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        H5::Group _h5CreateGroup;
    };
}


#endif
