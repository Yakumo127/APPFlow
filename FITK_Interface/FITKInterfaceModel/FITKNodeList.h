/**
 *
 * @file FITKNodeList.h
 * @brief 节点列表声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-28
 *
 */
#ifndef __FITKNODELIST_H__
#define __FITKNODELIST_H__

#include "FITKInterfaceModelAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractObject.hpp"
#include <QList>
#include <QMap>
#include <QMutex>

namespace Core
{
    class FITKNode;
}

namespace Interface
{
    /**
     * @brief 节点列表
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-02-28
     */
    class FITKInerfaceModelAPI FITKNodeList //: public Core::FITKAbstractObject
    {
    public:
       /**
        * @brief Construct a new FITKNodeList object
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-02-28
        */
        explicit FITKNodeList() = default;
        /**
         * @brief Destroy the FITKNodeList object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual ~FITKNodeList();
        /**
         * @brief 追加节点
         * @param[i]  x              x坐标
         * @param[i]  y              y坐标
         * @param[i]  z              z坐标
         * @return int     节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual int addNode(const double x, const double y, const double z);
        /**
         * @brief 追加节点
         * @param[i]  id             节点ID
         * @param[i]  x              x坐标
         * @param[i]  y              y坐标
         * @param[i]  z              z坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual void addNode(const int id, const double x, const double y, const double z);
        /**
         * @brief 移除第index个节点，index从0开始
         * @param[i]  index          节点索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void removeNodeAt(const int index);
        /**
         * @brief 根据ID移除节点
         * @param[i]  id            节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void removeNodeByID(const int id);
        /**
         * @brief 获取节点数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        int getNodeCount();
        /**
         * @brief 获取第index个节点
         * @param[i]  index         节点索引
         * @return Core::FITKNode*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        Core::FITKNode* getNodeAt(const int index);
        /**
         * @brief 根据ID获取节点
         * @param[i]  id          节点ID
         * @return Core::FITKNode*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        Core::FITKNode* getNodeByID(const int id);
        /**
         * @brief 根据索引获取节点ID
         * @param[i]  index         索引
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
          int getNodeIDByIndex(const int index);
        /**
         * @brief 根据ID获取节点索引
         * @param[i]  id            节点ID
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
         int getNodeIndexByID(const int id);
        /**
         * @brief 获取节点最大id
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-28
         */
        int getNodeMaxID();
        /**
         * @brief 移除全部节点
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-28
         */
        void removeAllNode();

    protected:
        /**
         * @brief 更新ID与索引的映射，移除节点等过程调用
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-10-30
         */
        void updateNodeIDIndexMap();
        /**
         * @brief 移除第index个节点，index从0开始
         * @param[i]  index          节点索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void fastRemoveNodeAt(const int index);
        /**
         * @brief 根据ID移除节点
         * @param[i]  id            节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        void fastRemoveNodeByID(const int id);

    protected:
        /**
         * @brief 线程互斥锁
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        QMutex _mutex;
        /**
         * @brief 节点列表
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        QList<Core::FITKNode*> _nodeList{};
        /**
         * @brief 辅助存储， ID与index映射关系
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        QMap<int, int> _idIndexMap{};
        /**
         * @brief 辅助存储， 最大节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-22
         */
        int _nodeMaxID = 0;
    };
}



#endif // !__FITKNODELIST_H__
