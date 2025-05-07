/**********************************************************************
 * @file   FITKOFInitialDirWriter.h
 * @brief  初始值 0文件夹写出
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-29
 *********************************************************************/
#ifndef __FITKFLOWOFINITIALDIRWRITER_H__
#define __FITKFLOWOFINITIALDIRWRITER_H__

#include "FITKOFDictWriterAPI.h"
#include "FITKOFAbstractDictWriter.h"

namespace Interface 
{
    class FITKOFAbsBoundaryType;
    class FITKOFBoundary;
}

namespace DICT
{
    class FITKDictVector;
    class FITKDictArray;
    class FITKDictGroup;
}

namespace Core
{
    class FITKAbstractEasyParam;
}

namespace IO
{
    class FITKOFChangeDictionaryDictW;
    /**
     * @brief ControlMeshDict 文件写出器
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date 2024-07-15
     */
    class FITKOFInitialDirWriter : public FITKOFAbstractDictWriter
    {
    public:
        explicit FITKOFInitialDirWriter();
        virtual ~FITKOFInitialDirWriter();

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
        void dictObjectFoamFile(QString vName);

        bool initialFileWrite(QString vName, Core::FITKAbstractEasyParam* vPara);

        bool dimensionsW(QString vName);

    private:
        /**
         * @brief 文件名
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        QString m_fileName{};
        /**
         * @brief  边界写出的工具
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-30
         */
        FITKOFChangeDictionaryDictW* m_boundaryTool;
    };
}



#endif
