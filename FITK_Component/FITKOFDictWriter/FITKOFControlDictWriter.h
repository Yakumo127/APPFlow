﻿/**
 * @file   FITKOFControlDictWriter.h
 * @brief ControlDict写出接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date 2024-07-24
 */
#ifndef __FITKFLOWOFCONTROLWRITER_H__
#define __FITKFLOWOFCONTROLWRITER_H__

#include "FITKOFDictWriterAPI.h"
#include "FITKOFAbstractDictWriter.h"

namespace Interface
{
    class FITKAbstractRegionMeshSize;
    class FITKAbstractOFSolver;
}

namespace DICT
{
    class FITKDictVector;
    class FITKDictArray;
}

namespace IO
{
    /**
     * @brief ControlMeshDict 文件写出器
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date 2024-07-15
     */
    class FITKOFControlDictWriter : public FITKOFAbstractDictWriter
    {
    public:
        explicit FITKOFControlDictWriter();
        virtual ~FITKOFControlDictWriter();

        /**
         * @brief 设置文件路径
         * @param[i] filePath
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        void setFilePath(const QString& filePath) override;
        /**
         * @brief 重写run函数
         * @return 状态 true:成功 false:失败
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-15
         */
        bool run() override;
        /**
         * @brief 获取文件
         * @return QString
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        QString getFileName() override;

    private:
        /**
         * @brief 设置字典里的FoamFile
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        void dictObjectFoamFile();

        bool controlDictW();

        bool writeDefaultControl();

    private:
        /**
         * @brief 文件名
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        QString m_fileName{};
    };
}



#endif
