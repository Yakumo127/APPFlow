﻿/**
 * 
 * @file FITKAbstractQtXMLReader.h
 * @brief 利用Qt的XML解析器读取XML文件
 * @author libaojun (libaojunqd@foxmail.com)
 * @date 2024-10-11
 * 
 */
#ifndef _FITKABSTRACT_XML_QT_READER_H___
#define _FITKABSTRACT_XML_QT_READER_H___
 
#include "FITKAbstractIO.h"

class QDomDocument;
class QFile;


namespace Interface
{
    /**
     * @brief 利用Qt的XML解析器读取XML文件，抽象类
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-10-11
     */
    class FITKInterfaceIOAPI FITKAbstractQtXMLReader
        :public FITKAbstractIO
    {
    public:
       /**
        * @brief Construct a new FITKAbstractQtXMLReader object
        * @author libaojun (libaojunqd@foxmail.com)
        * @date 2024-10-11
        */
        explicit FITKAbstractQtXMLReader() = default;
        /**
         * @brief Destroy the FITKAbstractQtXMLReader object
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-10-11
         */
        virtual ~FITKAbstractQtXMLReader() = 0;
        /**
         * @brief 创建上下文，将文件与_document(QDomDocument)进行关联
         * @return true       创建成功
         * @return false      创建失败
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-10-11
         */
        virtual bool createContent();
        /**
         * @brief 关闭文件
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-10-11
         */
        virtual void closeFile();

    protected:
        /**
         * @brief qt的dom文档对象
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-10-11
         */
        QDomDocument* _document{};
        /**
         * @brief 文件对象
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-10-11
         */
        QFile* _file{};


    };
}


#endif
