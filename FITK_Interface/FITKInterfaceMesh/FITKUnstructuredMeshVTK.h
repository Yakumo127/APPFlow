﻿/**
 *
 * @file FITKUnstructuredMeshVTK.h
 * @brief 非结构网格的vtk实现声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-28
 *
 */
#ifndef _FITKUNSTRUCTUREDMESH_VTK_H__
#define _FITKUNSTRUCTUREDMESH_VTK_H__

#include "FITK_Interface/FITKInterfaceModel/FITKUnstructuredMesh.h"
#include "FITKInterfaceMeshAPI.h"

 //class QColor;

class vtkUnstructuredGrid;
class vtkPoints;

namespace Interface
{
    class FITKMeshFeatureVTK;

    /**
     * @brief 非结构化网格vtk实现
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-02-28
     */
    class FITKInterfaceMeshAPI FITKUnstructuredMeshVTK : public FITKUnstructuredMesh
    {
        //        FITKSafeDownCastA(FITKUnstructuredMeshVTK, Core::FITKAbstractDataObject);

    public:
        explicit FITKUnstructuredMeshVTK();
        virtual ~FITKUnstructuredMeshVTK();

        /**
         * @brief 获取模型类型
         * @return AbsModelType
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual FITKModelEnum::AbsModelType getAbsModelType() override;
        /**
         * @brief 更新数据
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        virtual void update() override;

        /**
         * @brief   根据给定维度获取网格单元索引。
         * @param   dim：单元维度
         * @return  单元索引列表
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-10
         */
        const QList<int> getCellIndiceByDim(int dim);

        /**
         * @brief 追加节点
         * @param[i]  x              x坐标
         * @param[i]  y              y坐标
         * @param[i]  z              z坐标
         * @return int     节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int addNode(const double x, const double y, const double z) override;
        /**
         * @brief 追加节点
         * @param[i]  id             节点ID
         * @param[i]  x              x坐标
         * @param[i]  y              y坐标
         * @param[i]  z              z坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual void addNode(const int id, const double x, const double y, const double z) override;

        /**
         * @brief 追加单元
         * @param[i]  element        单元指针
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual void appendElement(FITKAbstractElement* element) override;
        /**
         * @brief 写出模型到文件
         * @param[i]  file           文件绝对路径（包含文件名）
         * @return true   写出成功
         * @return false  写出失败
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual bool writeToFile(const QString & file) override;

        /**
         * @brief 单元反向
         * @param id 单元ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        virtual void reverseEleByID(const int id) override;
        /**
         * @brief 单元反向
         * @param index 单元索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        virtual void reverseEleByIndex(const int index) override;

        /**
         * @brief 获取网格特征
         * @return FITKMeshFeatureVTK*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-22
         */
        FITKMeshFeatureVTK* getMeshFeature();

        /**
         * @brief       获取原始模型网格。
         * @return      模型数据集
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-04-03
         */
        vtkUnstructuredGrid* getGrid();

        /**
         * @brief       获取网格包围盒。
         * @param[out]  bds6：包围盒
         * @return      是否存在有效包围盒
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-04-08
         */
        bool getBounds(double bds6[6]);

        /**
         * @brief       获取当前生效网格数据的单元数量。
         * @return      单元数量
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-04-07
         */
        int getNumberOfCells();

        /**
         * @brief       重新构建网格，刷新单元拓扑。
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2024-04-08
         */
        void reConstructure();
        /**
         * @brief 从vtk数据集转换
         * @param[i] grid  vtk数据集
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        void transformVTKMesh(vtkUnstructuredGrid* grid);

        /**
         * @brief 清空网格
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-26
         */
        void clearMesh();

        /**
         * @brief       清空关联网格。（存在几何映射关系）
         * @author      ChengHaotian (yeguangbaozi@foxmail.com)
         * @date        2025-03-28
         */
        void clearNativeMesh();

        /**
       * @brief 替换节点ID
       * @return QHash<int, int> & nodes  原先节点ID-替换后的节点ID
       * @author LiBaojun (libaojunqd@foxmail.com)
       * @date 2025-03-03
       */
        virtual void replaceNodesID(const QHash<int, int> & nodes) override;

    private:
        /**
         * @brief VTK表示的网格
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-08
         */
        vtkUnstructuredGrid* _vtkDataSet{};
        /**
         * @brief 节点列表
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-08
         */
         //        vtkPoints* _vtkPoints{};

        /**
         * @brief 模型特征
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-21
         */
        FITKMeshFeatureVTK* _feature{};

        /**
         * @brief 数据被修改
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        bool _modified{ false };

    };
}



#endif
