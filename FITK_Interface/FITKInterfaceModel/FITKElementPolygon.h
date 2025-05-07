/**
 *
 * @file FITKElementPolygon.h
 * @brief  多边形单元类型声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-08-02
 *
 */
#ifndef _FITKELEMENT_POLYGON__H___
#define _FITKELEMENT_POLYGON__H___
 
#include "FITKInterfaceModelAPI.h"
#include "FITKAbstractElement.h"


namespace Interface
{
    /**
    * @brief 多边形单元类型
    * @author LiBaojun (libaojunqd@foxmail.com)
    * @date 2024-08-02
    */
    class FITKInerfaceModelAPI FITKElementPolygon : public FITKAbstractElement
    {
    public:
        explicit FITKElementPolygon() = default;
        virtual ~FITKElementPolygon() = default;

        /**
        * @brief 获取单元类型
        * @return FITKEleType
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-02-28
        */
        virtual FITKModelEnum::FITKEleType getEleType() override;
        /**
        * @brief 设置节点数量
        * @param[i]  c   节点数
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-02-28
        */
        virtual void setNodeCount(const int c) override;
        /**
         * @brief 获取单元节点数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int getNodeCount() override;
        /**
         * @brief 获取单元包含的面数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int getFaceCount() override;
        /**
         * @brief 获取单元维度
         * @return int  1维线单元 2维壳单元 3维体单元
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-09
         */
        virtual int getElementDim() override;
        /**
         * @brief 获取单元包含的边数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int getEdgeCount() override;
        /**
         * @brief 获取第index个面
         * @param[i]  index         面索引，从0开始
         * @return QList<int>       面的节点索引，其中的成员是指单元中的节点索引，其成员大小不超过getNodeCount
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual QList<int> getFace(const int index) override;
        /**
        * @brief 获取第index个边
        * @param[i]  index         边索引，从0开始
        * @return QList<int>       边的节点索引，其中的成员是指单元中的节点索引，其成员大小不超过getNodeCount
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-02-28
        */
        virtual QList<int> getEdge(const int index) override;

    };
}


#endif
