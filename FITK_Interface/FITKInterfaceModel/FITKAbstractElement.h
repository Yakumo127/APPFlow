﻿/**
 *
 * @file FITKAbstractElement.h
 * @brief
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-28
 *
 */
#ifndef __FITABSTRACT_ELEMENT_H___
#define __FITABSTRACT_ELEMENT_H___

#include "FITKInterfaceModelAPI.h"
#include "FITKModelEnum.h"
#include "FITK_Kernel/FITKCore/FITKAbstractObject.hpp"
#include <QList>

namespace Interface
{
   /**
    * @brief 单元抽象类声明
    * @author LiBaojun (libaojunqd@foxmail.com)
    * @date 2024-02-28
    */
    class FITKInerfaceModelAPI FITKAbstractElement : public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief Construct a new FITKAbstractElement object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        FITKAbstractElement () = default;
        /**
         * @brief Destroy the FITKAbstractElement object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual ~FITKAbstractElement ();
       /**
        * @brief 获取单元类型
        * @return FITKEleType
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-02-28
        */
        virtual FITKModelEnum::FITKEleType getEleType() = 0;
        /**
         * @brief 获取单元节点数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int getNodeCount() = 0;
        /**
         * @brief 设置单元ID
         * @param[i]  id            单元ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void setEleID(const int id);
        /**
         * @brief 获取单元ID
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        int getEleID() const;
        /**
         * @brief 获取第index的节点ID，注意是ID不是节点列表的Index
         * @param[i]  index      节点索引，从0开始
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        int getNodeID(const int index) const;

        /**
         * @brief 获取节点ID的索引，不包含id，返回-1
         * @param[i]  id      节点id
         * @return int    索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        int getNodeIndex(const int id) const;
        /**
         * @brief 设置单元节点ID，注意是ID不是节点列表的Index
         * @param[i]  index          节点索引，从0开始
         * @param[i]  nodeID         节点ID 注意是ID不是节点列表的Index
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void setNodeID(const int index, int nodeID);
        /**
         * @brief 设置单元节点ID，注意是ID不是节点列表的Index
         * @param[i]  ids            节点ID顺序列表，长度必须与getNodeCount一致
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void setNodeID(const QList<int>& ids );
        /**
         * @brief 获取单元包含的面数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int getFaceCount() = 0 ;
        /**
         * @brief 获取单元维度
         * @return int  1维线单元 2维壳单元 3维体单元
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-09
         */
        virtual int getElementDim() = 0;
        /**
         * @brief 获取单元包含的边数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int getEdgeCount() = 0 ;
        /**
         * @brief 获取第index个面
         * @param[i]  index         面索引，从0开始
         * @return QList<int>       面的节点索引，其中的成员是指单元中的节点索引，其成员大小不超过getNodeCount
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual QList<int> getFace(const int index) = 0;
         /**
         * @brief 获取第index个边
         * @param[i]  index         边索引，从0开始
         * @return QList<int>       边的节点索引，其中的成员是指单元中的节点索引，其成员大小不超过getNodeCount
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual QList<int> getEdge(const int index) = 0;

        /**
         * @brief 单元反向
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        void reverse();
        /**
         * @brief 获取表面索引
         * @param[i]  face           组成表面的节点列表
         * @param[i]  normalSens     是否考虑方向
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-24
         */
        int getFaceIndex(const QList<int>& face, bool normalSens = false);

        /**
         * @brief 获取前一个节点
         * @param[i]  id        当前节点ID
         * @return int           前一个节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-11-11
         */
        int getPreviousNodeID(const int id);
        /**
         * @brief 获取后一个节点
         * @param[i]  id        当前节点ID
         * @return int           后一个节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date @date 2024-11-11
         */
        int getNextNodeID(const int id);
        /**
         * @brief 获取全部节点
         * @return QList<int>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date @date 2024-11-19
         */
        QList<int> getAllNodes();
        /**
       * @brief 替换节点ID
       * @return oldID 原先ID newID 替换后的ID 
       * @author LiBaojun (libaojunqd@foxmail.com)
       * @date 2025-03-03
       */
        void replaceNodeID(const int& oldID, const int& newID);
        /**
          * @brief 设置单元标记
          * @param[i] tag 标记值
          * @author LiBaojun (libaojunqd@foxmail.com)
          * @date 2025-03-28
          */
        void setTag(unsigned int tag);
        /**
          * @brief 获取单元标记
          * @return unsigned int 标记值
          * @date 2025-03-28
          */
        unsigned int getTag() const;

    private:
        /**
         * @brief 获取表面索引，方向敏感
         * @param[i]  face         组成表面的全部节点
         * @return int             面索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-24
         */
        int getFaceIndexNorSen (const QList<int>& face);
        /**
         * @brief 获取表面索引，方向不敏感
         * @param[i]  face         组成表面的全部节点
         * @return int             面索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-24
         */
        int getFaceIndexNorUnSen(const QList<int>& face);

    protected:
        /**
        * @brief 设置节点数量
        * @param[i]  c   节点数
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-02-28
        */
        virtual void setNodeCount(const int c);

    protected:
        /**
         * @brief 单元ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        int _eleID{ -1 };
        /**
         * @brief 单元拓扑，存储节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        QList<int> _elemenTopo{};
        /**
         * @brief 单元标记
         * @date 2025-03-28
         */
        unsigned int _tag{ 0 };
    };


}


#endif
