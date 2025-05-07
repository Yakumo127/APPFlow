﻿#include "FITKOFFVSolutionWriter.h"
#include "FITKDictObject.h"
#include "FITKDictArray.h"
#include "FITKDictGroup.h"
#include "FITKDictVector.h"
#include "FITKDictValue.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFSolution.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFSolutionSolver.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamRadioGroup.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamBool.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamCombox.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDouble.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamInt.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamString.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFSolver.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFOperatingConditions.h"

#include <QFileInfo>
#include <QtMath>
//命名空间
namespace IO
{
    FITKOFFVSolutionWriter::FITKOFFVSolutionWriter()
    {
    }
    FITKOFFVSolutionWriter::~FITKOFFVSolutionWriter()
    {
    }

    void FITKOFFVSolutionWriter::setFilePath(const QString& filePath)
    {
        FITKOFAbstractDictWriter::setFilePath(filePath);
        QFileInfo fileInfo(filePath);
        //判断是否是路径
        if (!fileInfo.isDir())return;
        m_fileName = QString("%1/system/fvSolution").arg(filePath);
    }

    bool FITKOFFVSolutionWriter::run()
    {
        //判断文件是否存在
        if (m_fileName.isEmpty())return false;
        //获取字典工程
        this->openDictObject();
        if (!m_objectDict)return false;
        //写出FoamFile
        this->dictObjectFoamFile();
        //设置写出的网格区域数据
        bool Ok = this->fvSolutionWrite();
        //写出字典文件
        if (Ok)
            Ok = this->writeDictFile();

        //关闭字典工程
        this->closeDictObject();
        return Ok;
    }

    QString FITKOFFVSolutionWriter::getFileName()
    {
        return m_fileName;
    }

    void FITKOFFVSolutionWriter::dictObjectFoamFile()
    {
        if (!m_objectDict)return;
        //FoamFile
        DICT::FITKDictGroup* group = new DICT::FITKDictGroup;
        group->append("version", 2.0);
        group->append("format", "ascii");
        group->append("class", "dictionary");
        group->append("location", "\"system\"");
        group->append("object", "fvSolution");
        m_objectDict->append("FoamFile", group);
    }

    bool FITKOFFVSolutionWriter::writeEmptySolution()
    {
        if (!m_objectDict) return false;
        DICT::FITKDictGroup* solvers = new DICT::FITKDictGroup;
        m_objectDict->append("solvers", solvers);
        return true;
    }

    bool FITKOFFVSolutionWriter::fvSolutionWrite()
    {
        if (!m_objectDict) return false;
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取求解器
        Interface::FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver) return this->writeEmptySolution();
        bool isFinal = false;
        Interface::FITKOFSolverTypeEnum::FITKOFSolverType solverType = solver->getSolverType();
        if (solverType == Interface::FITKOFSolverTypeEnum::FITKOFSolverType::INTER)
            isFinal = true;
        //获取离散数据
        Interface::FITKOFSolution* solutionData = physicsData->getSolution();
        if (!solutionData) return false;
        //写出代数方程组求解设置
        DICT::FITKDictGroup* solvers = new DICT::FITKDictGroup;
        m_objectDict->append("solvers", solvers);
        //代数方程变量
        int count = solutionData->getSolversCount();
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFAlgebraicEquationsPara* solutionSolver = solutionData->getSolverVariablePara(i);
            if (!solutionData)continue;
            QString name = solutionSolver->getVariableName();
            if (name == "alpha")
                name = "\"alpha.*\"";
            DICT::FITKDictGroup* variable = new DICT::FITKDictGroup;
            solvers->append(name, variable);
            DICT::FITKDictGroup* variableFinal = nullptr;
            if (isFinal && !name.contains("\""))
            {
                variableFinal = new DICT::FITKDictGroup;
                solvers->append(name + "Final", variableFinal);
            }
            this->writeAdditionalPara(solutionSolver->getSolverAdditionalPara(), variable);
            if (variableFinal) this->writeAdditionalPara(solutionSolver->getSolverAdditionalPara(), variableFinal);

            Interface::FITKOFAbsSolutionSolver* solverV = solutionSolver->getSolutionSolver();
            if (!solverV)continue;
            QString solverSolutionName = solverV->getDataObjectName();
            if (solverSolutionName == "GAMG")
            {
                this->writeGAMGSolverVariable(solverV, variable);
                if (variableFinal) this->writeGAMGSolverVariable(solverV, variableFinal);
            }
            else if (solverSolutionName == "PCG")
            {
                this->writePCGSolverVariable(solverV, variable);
                if (variableFinal) this->writePCGSolverVariable(solverV, variableFinal);
            }
            else if (solverSolutionName == "Smooth Solver")
            {
                this->writeSmoothSolverSolverVariable(solverV, variable);
                if (variableFinal) this->writeSmoothSolverSolverVariable(solverV, variableFinal);
            }  
            else if (solverSolutionName == "PBiCG Stabilized")
            {
                this->writePBiCGStabilizedSolverVariable(solverV, variable);
                if (variableFinal) this->writePBiCGStabilizedSolverVariable(solverV, variableFinal);
            }
            else if (solverSolutionName == "PBiCG")
            {
                this->writePBiCGSolverVariable(solverV, variable);
                if (variableFinal) this->writePBiCGSolverVariable(solverV, variableFinal);
            }
            if (variableFinal && !variableFinal->value("minIter")) variableFinal->append("minIter", 1);
        }
        //写出算法设置
        QString solverSpeN = solutionData->getSolverSpeciallyDataName();
        if (solverSpeN == "SIMPLE")
            this->arithmeticSIMPLEW(solutionData);
        else if (solverSpeN == "PIMPLE")
            this->arithmeticPIMPLEW(solutionData);
        //写出relaxation
        DICT::FITKDictGroup* relaxation = new DICT::FITKDictGroup;
        m_objectDict->append("relaxationFactors", relaxation);
        Core::FITKParameter* relaxationData = solutionData->getRelaxation();
        if (!relaxationData) return false;
        count = relaxationData->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKParamDouble* paraData = dynamic_cast<Core::FITKParamDouble*>(relaxationData->getDataByIndex(i));
            if (!paraData)continue;
            relaxation->append(paraData->getDataObjectName(), paraData->getValue());
        }
        return true;
    }

    bool FITKOFFVSolutionWriter::writeAdditionalPara(Core::FITKParameter* additionalPara, DICT::FITKDictGroup* group)
    {
        if (!additionalPara || !group)return false;
        int count = additionalPara->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKAbstractEasyParam* paraData = additionalPara->getDataByIndex(i);
            if (!paraData)continue;
            QString key = this->getAdditionalParaKey(paraData->getDataObjectName());
            Core::FITKAbstractEasyParam::FITKEasyParamType type = paraData->getParamType();
            if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPBool)
            {
                Core::FITKParamBool* p = dynamic_cast<Core::FITKParamBool*>(paraData);
                if (!p)continue;
                group->append(key, p->getValue());
            }
            else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDouble)
            {
                Core::FITKParamDouble* p = dynamic_cast<Core::FITKParamDouble*>(paraData);
                if (!p)continue;
                group->append(key, p->getValue());
            }
            else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPInt)
            {
                Core::FITKParamInt* p = dynamic_cast<Core::FITKParamInt*>(paraData);
                if (!p)continue;
                group->append(key, p->getValue());
            }
            else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPString)
            {
                Core::FITKParamString* p = dynamic_cast<Core::FITKParamString*>(paraData);
                if (!p)continue;
                group->append(key, p->getValue());
            }
        }
        return true;
    }

    QString FITKOFFVSolutionWriter::getAdditionalParaKey(QString name)
    {
        if (name == "Alpha Sub-Cycles")
            return "nAlphaSubCycles";
        else if (name == "Correctors")
            return "nAlphaCorr";
        else if (name == "MULES Corrector")
            return "MULESCorr";
        else if (name == "Apply Previous Corrector")
            return "alphaApplyPrevCorr";
        else if (name == "Limiter Iterations")
            return "nLimiterIter";
        else if (name == "Calpha")
            return "cAlpha";
        else if (name == "ICalpha")
            return "icAlpha";
        return name;
    }

    bool FITKOFFVSolutionWriter::writeGAMGSolverVariable(Interface::FITKOFAbsSolutionSolver* solverV, DICT::FITKDictGroup* group)
    {
        if (!solverV || !group)return false;
        Core::FITKParameter* solverSolutionParams = solverV->getSolverSolutionPara();
        if (!solverSolutionParams)return false;
        group->append("solver", "GAMG");
        bool ok = false;
        QString smoother = solverSolutionParams->getComboxCurrentParaByName("Smoother", ok);
        if (smoother == "Gauss-Seidel")
            smoother = "GaussSeidel";
        else if (smoother == "DIC")
            smoother = "DIC";
        else if (smoother == "DIC & Gauss-Seidel")
            smoother = "DICGaussSeidel";
        group->append("smoother", smoother);
        if (!ok) return false;
        group->append("relTol", solverSolutionParams->getDoubleParaByName("Relative Tolerance", ok));
        if (!ok) return false;
        group->append("cacheAgglomeration", solverSolutionParams->getBoolParaByName("Cache Agglomeration", ok));
        if (!ok) return false;
        group->append("nFinestSweeps", solverSolutionParams->getIntParaByName("Finest Sweeps", ok));
        if (!ok) return false;
        group->append("nPreSweeps", solverSolutionParams->getIntParaByName("Pre Sweeps", ok));
        if (!ok) return false;
        group->append("maxIter", solverSolutionParams->getIntParaByName("Max Iterations", ok));
        if (!ok) return false;
        group->append("nPostSweeps", solverSolutionParams->getIntParaByName("Post Sweeps", ok));
        if (!ok) return false;
        QString agglomerator = solverSolutionParams->getComboxCurrentParaByName("Agglomerator", ok);
        if (!ok) return false;
        if (agglomerator == "Face Area Pair")
            agglomerator = "faceAreaPair";
        else if (agglomerator == "Algebraic Pair")
            agglomerator = "algebraicPair";
        group->append("agglomerator", agglomerator);
        if (!ok) return false;
        group->append("nCellsInCoarsestLevel", solverSolutionParams->getIntParaByName("Cells In Coarsest Level", ok));
        if (!ok) return false;
        group->append("tolerance", solverSolutionParams->getDoubleParaByName("Tolerance", ok));
        if (!ok) return false;
        group->append("mergeLevels", solverSolutionParams->getIntParaByName("Merge Levels", ok));
        if (!ok) return false;
        return true;
    }

    bool FITKOFFVSolutionWriter::writePCGSolverVariable(Interface::FITKOFAbsSolutionSolver* solverV, DICT::FITKDictGroup* group)
    {
        if (!solverV || !group)return false;
        Core::FITKParameter* solverSolutionParams = solverV->getSolverSolutionPara();
        if (!solverSolutionParams)return false;
        group->append("solver", "PCG");
        bool ok = false;
        group->append("relTol", solverSolutionParams->getDoubleParaByName("Relative Tolerance", ok));
        if (!ok) return false;
        QString preconditioner = solverSolutionParams->getComboxCurrentParaByName("Preconditioner", ok);
        if (preconditioner == "DIC")
            preconditioner = "GaussSeidel";
        else if (preconditioner == "Fast DIC")
            preconditioner = "FDIC";
        else if (preconditioner == "Diagonal")
            preconditioner = "diagonal";
        else if (preconditioner == "none")
            preconditioner = "none";
        group->append("preconditioner", preconditioner);
        if (!ok) return false;
        group->append("tolerance", solverSolutionParams->getDoubleParaByName("Tolerance", ok));
        if (!ok) return false;
        group->append("maxIter", solverSolutionParams->getIntParaByName("Max Iterations", ok));
        if (!ok) return false;
        return true;
    }

    bool FITKOFFVSolutionWriter::writeSmoothSolverSolverVariable(Interface::FITKOFAbsSolutionSolver* solverV, DICT::FITKDictGroup* group)
    {
        if (!solverV || !group)return false;
        Core::FITKParameter* solverSolutionParams = solverV->getSolverSolutionPara();
        if (!solverSolutionParams)return false;
        group->append("solver", "smoothSolver");
        bool ok = false;
        QString smoother = solverSolutionParams->getComboxCurrentParaByName("Smoother", ok);
        if (smoother == "Gauss-Seidel")
            smoother = "GaussSeidel";
        else if (smoother == "DIC")
            smoother = "DIC";
        else if (smoother == "DIC & Gauss-Seidel")
            smoother = "DICGaussSeidel";
        group->append("smoother", smoother);
        if (!ok) return false;
        group->append("nSweeps", solverSolutionParams->getIntParaByName("Sweeps", ok));
        if (!ok) return false;
        group->append("relTol", solverSolutionParams->getDoubleParaByName("Relative Tolerance", ok));
        if (!ok) return false;
        group->append("tolerance", solverSolutionParams->getDoubleParaByName("Tolerance", ok));
        if (!ok) return false;
        group->append("maxIter", solverSolutionParams->getIntParaByName("Max Iterations", ok));
        if (!ok) return false;
        return true;
    }

    bool FITKOFFVSolutionWriter::writePBiCGStabilizedSolverVariable(Interface::FITKOFAbsSolutionSolver* solverV, DICT::FITKDictGroup* group)
    {
        if (!solverV || !group)return false;
        Core::FITKParameter* solverSolutionParams = solverV->getSolverSolutionPara();
        if (!solverSolutionParams)return false;
        group->append("solver", "PBiCGStab");
        bool ok = false;
        group->append("relTol", solverSolutionParams->getDoubleParaByName("Relative Tolerance", ok));
        if (!ok) return false;
        QString preconditioner = solverSolutionParams->getComboxCurrentParaByName("Preconditioner", ok);
        if (preconditioner == "DIC")
            preconditioner = "GaussSeidel";
        else if (preconditioner == "Diagonal")
            preconditioner = "diagonal";
        else if (preconditioner == "none")
            preconditioner = "none";
        group->append("preconditioner", preconditioner);
        if (!ok) return false;
        group->append("tolerance", solverSolutionParams->getDoubleParaByName("Tolerance", ok));
        if (!ok) return false;
        group->append("maxIter", solverSolutionParams->getIntParaByName("Max Iterations", ok));
        if (!ok) return false;
        return true;
    }

    bool FITKOFFVSolutionWriter::writePBiCGSolverVariable(Interface::FITKOFAbsSolutionSolver* solverV, DICT::FITKDictGroup* group)
    {
        if (!solverV || !group)return false;
        Core::FITKParameter* solverSolutionParams = solverV->getSolverSolutionPara();
        if (!solverSolutionParams)return false;
        group->append("solver", "PBiCG");
        bool ok = false;
        group->append("relTol", solverSolutionParams->getDoubleParaByName("Relative Tolerance", ok));
        if (!ok) return false;
        QString preconditioner = solverSolutionParams->getComboxCurrentParaByName("Preconditioner", ok);
        if (preconditioner == "DIC")
            preconditioner = "GaussSeidel";
        else if (preconditioner == "Diagonal")
            preconditioner = "diagonal";
        else if (preconditioner == "none")
            preconditioner = "none";
        group->append("preconditioner", preconditioner);
        if (!ok) return false;
        group->append("tolerance", solverSolutionParams->getDoubleParaByName("Tolerance", ok));
        if (!ok) return false;
        group->append("maxIter", solverSolutionParams->getIntParaByName("Max Iterations", ok));
        if (!ok) return false;
        return true;
    }

    bool FITKOFFVSolutionWriter::arithmeticSIMPLEW(Interface::FITKOFSolution* solutionData)
    {
        if (!m_objectDict || !solutionData)return false;
        Core::FITKParameter* arithmetic = solutionData->getSolverSpeciallyDataPara();
        if (!arithmetic)return false;
        //写出SIMPLE算法设置
        DICT::FITKDictGroup* simple = new DICT::FITKDictGroup;
        m_objectDict->append("SIMPLE", simple);
        bool ok = false;
        bool consistent = arithmetic->getBoolParaByName("Consistent", ok);
        if (ok) simple->append("consistent", consistent);
        int nOCorr = arithmetic->getIntParaByName("Non-Orthogonal Correctors", ok);
        if (ok) simple->append("nNonOrthogonalCorrectors", nOCorr);
        //residualControl
        DICT::FITKDictGroup* residual = new DICT::FITKDictGroup;
        simple->append("residualControl", residual);
        int count = solutionData->getResidualsCount();
        for (int i = 0; i < count; ++i)
        {
            QString name = solutionData->getResidualVariableName(i);
            Core::FITKParameter* residualPara = solutionData->getResidualVariablePara(i);
            if (!residualPara)continue;
            double value = residualPara->getDoubleParaByName(name, ok);
            residual->append(name, value);
        }
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取作用条件
        Interface::FITKOFOperatingConditions* opera = physicsData->getOperatingConditions();
        Core::FITKParamRadioGroup* location = nullptr;
        Core::FITKParameter* subLocation = nullptr;
        if (opera && opera->getReferencePressure())
        {
            Core::FITKParameter* pre = opera->getReferencePressure();
            location = dynamic_cast<Core::FITKParamRadioGroup*>(pre->getDataByName("location"));
            if (location) subLocation = location->getSubValuePara();
        }
        if (location && subLocation)
        {
            Core::FITKRadioGroupValue radioG = location->getCurrentRadioGroupValue();
            if (radioG._name == "Cell" && radioG._value)
                simple->append("pRefCell", radioG._value->getDoubleParaByName("Cell", ok));
            else if (radioG._name == "Point" && radioG._value)
            {
                int count = radioG._value->getDataCount();
                QStringList valueList;
                for (int i = 0; i < count; ++i)
                {
                    Core::FITKParamDouble* p = dynamic_cast<Core::FITKParamDouble*>(radioG._value->getDataByIndex(i));
                    if (!p) continue;
                    valueList.append(QString::number(p->getValue()));
                }
                simple->append("pRefPoint", QString("(%1)").arg(valueList.join(' ')));
            }
            simple->append("Value", subLocation->getDoubleParaByName("Value", ok));
        }
        
        return true;
    }

    bool FITKOFFVSolutionWriter::arithmeticPIMPLEW(Interface::FITKOFSolution* solutionData)
    {
        if (!m_objectDict || !solutionData)return false;
        Core::FITKParameter* arithmetic = solutionData->getSolverSpeciallyDataPara();
        if (!arithmetic)return false;
        //写出SIMPLE算法设置
        DICT::FITKDictGroup* simple = new DICT::FITKDictGroup;
        m_objectDict->append("PIMPLE", simple);
        int count = arithmetic->getDataCount();
        for (int i = 0; i < count; ++i)
        {
            Core::FITKAbstractEasyParam* paraData = arithmetic->getDataByIndex(i);
            if (!paraData)continue;
            QString key = this->getArithmeticParaKey(paraData->getDataObjectName());
            Core::FITKAbstractEasyParam::FITKEasyParamType type = paraData->getParamType();
            if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPBool)
            {
                Core::FITKParamBool* p = dynamic_cast<Core::FITKParamBool*>(paraData);
                if (!p)continue;
                simple->append(key, p->getValue());
            }
            else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDouble)
            {
                Core::FITKParamDouble* p = dynamic_cast<Core::FITKParamDouble*>(paraData);
                if (!p)continue;
                simple->append(key, p->getValue());
            }
            else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPInt)
            {
                Core::FITKParamInt* p = dynamic_cast<Core::FITKParamInt*>(paraData);
                if (!p)continue;
                simple->append(key, p->getValue());
            }
            else if (type == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPString)
            {
                Core::FITKParamString* p = dynamic_cast<Core::FITKParamString*>(paraData);
                if (!p)continue;
                simple->append(key, p->getValue());
            }
        }
        //residualControl
        DICT::FITKDictGroup* residual = new DICT::FITKDictGroup;
        simple->append("residualControl", residual);
        count = solutionData->getResidualsCount();
        for (int i = 0; i < count; ++i)
        {
            QString name = solutionData->getResidualVariableName(i);
            Core::FITKParameter* residualPara = solutionData->getResidualVariablePara(i);
            if (!residualPara)continue;
            bool ok = false;
            double value = residualPara->getDoubleParaByName(name, ok);
            residual->append(name, value);
        }
        bool ok = false;
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取作用条件
        Interface::FITKOFOperatingConditions* opera = physicsData->getOperatingConditions();
        Core::FITKParamRadioGroup* location = nullptr;
        Core::FITKParameter* subLocation = nullptr;
        if (opera && opera->getReferencePressure())
        {
            Core::FITKParameter* pre = opera->getReferencePressure();
            location = dynamic_cast<Core::FITKParamRadioGroup*>(pre->getDataByName("location"));
            if(location) subLocation = location->getSubValuePara();
        }
        if (location && subLocation)
        {
            Core::FITKRadioGroupValue radioG = location->getCurrentRadioGroupValue();
            if (radioG._name == "Cell" && radioG._value)
                simple->append("pRefCell", radioG._value->getDoubleParaByName("Cell", ok));
            else if (radioG._name == "Point" && radioG._value)
            {
                int count = radioG._value->getDataCount();
                QStringList valueList;
                for (int i = 0; i < count; ++i)
                {
                    Core::FITKParamDouble* p = dynamic_cast<Core::FITKParamDouble*>(radioG._value->getDataByIndex(i));
                    if (!p) continue;
                    valueList.append(QString::number(p->getValue()));
                }
                simple->append("pRefPoint", QString("(%1)").arg(valueList.join(' ')));
            }
            simple->append("Value", subLocation->getDoubleParaByName("Value", ok));
        }
        return true;
    }

    QString FITKOFFVSolutionWriter::getArithmeticParaKey(QString name)
    {
        if (name == "Correctors")
            return "nCorrectors";
        else if (name == "Non-Orthogonal Correctors")
            return "nNonOrthogonalCorrectors";
        else if (name == "Momentum Predictor")
            return "momentumPredictor";
        else if (name == "Correct Phi")
            return "correctPhi";
        else if (name == "Mesh Outer Correctors")
            return "moveMeshOuterCorrectors";
        else if (name == "Check Mesh Co")
            return "checkMeshCourantNo";
        else if (name == "Outer Correctors")
            return "nOuterCorrectors";
        return name;
    }
}



