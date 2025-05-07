/**
 *
 * @file FITKUnstructuredMesh.h
 * @brief 非结构网格声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-03-07
 *
 */
#ifndef __FITKABSTRUCTUNSTRUCTED_MESH_H__
#define __FITKABSTRUCTUNSTRUCTED_MESH_H__

#include "FITKInterfaceModelAPI.h"
#include "FITKNodeList.h"
#include "FITKElementList.h"
#include "FITKAbstractMesh.h"

namespace Interface
{
    /**
     * @brief 非结构化网格
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-07
     */
    class FITKInerfaceModelAPI FITKUnstructuredMesh
        : public FITKAbstractMesh, public FITKNodeList, public FITKElementList
    {
    public:
        /**
         * @brief Construct a new FITKUnstructuredMesh object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-07
         */
        explicit FITKUnstructuredMesh();
        /**
         * @brief Destroy the FITKUnstructuredMesh object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-07
         */
        virtual ~FITKUnstructuredMesh();
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
         * @brief 获取网格维度
         * @return FITKModelEnum::FITKMeshDim
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        virtual FITKModelEnum::FITKMeshDim getMeshDim() override;
         /**
         * @brief 通过位运算获取网格维度
         * @return unsigned int 返回网格维度的位表示，参考 FITKModelEnum::FITKMeshDim 
         * @author LiBaojun
         * @date 2025-04-11
         */
        unsigned int getMeshDimBit() override;

        
        /**
         * @brief 评判网格质量
         * @param[i] eleIndex 单元索引
         * @return FITKElemntQuality
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-06-23
         */
        FITKElemntQuality checkElementQuality(const int eleIndex);

        /**
         * @brief 获取单元方向，支持线单元与壳单元
         * @param[o] dir 单元方向
         * @param[i] id  单元ID
         * @return bool 是否获取成功
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-09
         */
        bool getElementDirection(double* dir , const int id);


    private:
        /**
         * @brief 计算边的长度
         * @param[i] edge 边的节点ID
         * @return double
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-06-23
         */
        double calMeshEdgeLength(const QList<int> & edge);
        /**
         * @brief 获取线单元方向
         * @param[o] dir 单元方向
         * @param[i] ele  单元对象
         * @return bool 是否获取成功
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-09
         */
        bool getLineEleDirection(double* dir, FITKAbstractElement* ele);
        /**
         * @brief 获取壳单元方向
         * @param[o] dir 单元方向
         * @param[i] ele  单元对象指针
         * @return bool 是否获取成功
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-09
         */
        bool getShellEleDirection(double* dir, FITKAbstractElement* ele);


    };
}



#endif
