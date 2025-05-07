﻿/**
 *
 * @file FITKAbstractModel.h
 * @brief 模型抽象类声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-27
 *
 */
#ifndef __FITKABSTRACTMODEL_H__
#define __FITKABSTRACTMODEL_H__

#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITKInterfaceModelAPI.h"
#include "FITKModelEnum.h"

namespace Interface
{
    class FITKComponentManager;
    /**
     * @brief  模型抽象类，派生出网格类型 几何类型 装配实例
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-02-27
     */
    class FITKInerfaceModelAPI FITKAbstractModel : public Core::FITKAbstractNDataObject
    {
    public:
        /**
         * @brief Construct a new FITKAbstractModel object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        explicit FITKAbstractModel() = default;
        /**
         * @brief Destroy the FITKAbstractModel object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual ~FITKAbstractModel() = 0;

        /**
         * @brief 获取模型类型
         * @return AbsModelType
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual FITKModelEnum::AbsModelType getAbsModelType() = 0;

        /**
         * @brief 获取集合/表面管理器
         * @return Interface::FITKModelSetManager*
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        virtual FITKComponentManager* getComponentManager();
        /**
         * @brief 写出模型到文件
         * @param[i]  file           文件绝对路径（包含文件名）
         * @return true   写出成功
         * @return false  写出失败
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual bool writeToFile(const QString & file);

        /**
         * @brief 获取模型维度
         * @return FITKModelDim
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual FITKModelEnum::FITKModelDim getModelDim();
        /**
         * @brief 获取点坐标
         * @param[i]  pointID  点ID
         * @param[o]  coor 节点坐标
         * @param[i]  modelIndex 模型索引，用于复合模型（一个模型包含多个子模型）  
         * @return  bool 是否获取成功
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-19
         */
        virtual bool getPointCoor(int pointID, double* coor, int modelIndex = 0);

        /**
         * @brief   坐标变换。[虚函数]
         * @param   iPos：输入坐标
         * @param   oPos：输出坐标
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-23
         */
        virtual void transformPoint(double* iPos, double* oPos);

        /**
         * @brief   方向变换。[虚函数]
         * @param   iDir：输入方向
         * @param   oDir：输出方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-12-23
         */
        virtual void transformDirection(double* iDir, double* oDir);

    public:
        /**
        * @brief 数组拷贝
        * @param[i]  from 原始数组
        * @param[i]  to 目标数组
        * @param[i]  dim 数组长度
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-04-19
        */
        static void CopyArray(double* from, double* to, int dim);
    };
}




#endif
