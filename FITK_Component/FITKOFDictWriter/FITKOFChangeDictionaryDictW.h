/**********************************************************************
 * @file   FITKOFChangeDictionaryDictW.h
 * @brief  边界数据写出接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-28
 *********************************************************************/
#ifndef __FITKFLOWOFCHANGEDICTIONARYDICTWRITER_H__
#define __FITKFLOWOFCHANGEDICTIONARYDICTWRITER_H__

#include "FITKOFDictWriterAPI.h"
#include "FITKOFAbstractDictWriter.h"

namespace Interface 
{
    class FITKAbstractParameter;
    class FITKOFBoundary;
    class FITKOFAbsBoundaryType;
    class FITKOFInitialConditions;
    class FITKOFBoundaryManager;
    class FITKAbstractOFSolver;
}

namespace DICT
{
    class FITKDictVector;
    class FITKDictArray;
    class FITKDictGroup;
}

namespace IO
{
    /**
     * @brief ControlMeshDict 文件写出器
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date 2024-07-15
     */
    class FITKOFChangeDictionaryDictW : public FITKOFAbstractDictWriter
    {
    public:
        explicit FITKOFChangeDictionaryDictW();
        virtual ~FITKOFChangeDictionaryDictW();

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

        bool paraBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* boundaryG, QString nameV);

    private:
        /**
         * @brief 设置字典里的FoamFile
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        void dictObjectFoamFile();
        /**
         * @brief    写出字典文件
         * @return   bool
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-28
         */
        bool changeDictBoundaryFieldW();

        bool boundaryFieldW(QString boundMeshName, QString nameV, Interface::FITKOFAbsBoundaryType* boundPara);

        bool paraZeroGradientBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraFixedFluxPressureBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraFixedValueBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraStandardWallFunctionBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraVLowReWallFunctionBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraNoSlipBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraTurbulentIntensityInletBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraTurbulentMixingLengthInletBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraTotalPressureBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraPressureIOVelocityBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraSurNorFixedValueBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraSymmetryBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraOutletPhaseMeanVelocityBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraInletOutletBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);
        bool paraVariableHeightBTyW(Interface::FITKOFAbsBoundaryType* boundPara, DICT::FITKDictGroup* group, QString vName);

        QString getInitialBasicParaValue(QString vName);

    private:
        /**
         * @brief 文件名
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-19
         */
        QString m_fileName{};
        /**
         * @brief  init边界数据对象
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-03
         */
        Interface::FITKOFInitialConditions* _initialCond{};
        /**
         * @brief  边界管理器
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-03
         */
        Interface::FITKOFBoundaryManager* _boundaryMgr{};
        /**
         * @brief  求解器数据
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-05
         */
        Interface::FITKAbstractOFSolver* _solver{};
    };
}



#endif
