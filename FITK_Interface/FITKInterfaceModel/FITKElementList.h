/**
 *
 * @file FITKElementList.h
 * @brief  单元列表类声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-28
 *
 */
#ifndef __FITK_ELEMENTLIST_H__
#define __FITK_ELEMENTLIST_H__

#include "FITKInterfaceModelAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractObject.hpp"
#include <QList>
#include <QHash>
#include <QMap>
#include <QMutex>

namespace Interface
{
    class FITKAbstractElement;
     /**
      * @brief 单元列表类，存储网格单元
      * @author LiBaojun (libaojunqd@foxmail.com)
      * @date 2024-02-28
      */
    class  FITKInerfaceModelAPI FITKElementList //: public Core::FITKAbstractObject
    {
    public:
        /**
         * @brief Construct a new FITKElementList object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        explicit FITKElementList() = default;
        /**
         * @brief Destroy the FITKElementList object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual ~FITKElementList() = 0;
        /**
         * @brief 追加单元
         * @param[i]  element        单元指针
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual void appendElement(FITKAbstractElement* element);

        /**
         * @brief 根据索引获取单元ID
         * @param[i]  index         索引
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
         int getEleIDByIndex(const int index);
        /**
         * @brief 根据ID获取单元索引
         * @param[i]  id            单元ID
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
         int getEleIndexByID(const int id) const;


        /**
         * @brief 获取第index个单元
         * @param[i]  index         单元索引
         * @return FITKAbstractElement*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        FITKAbstractElement* getElementAt(const int index);
        /**
         * @brief 根据ID获取单元
         * @param[i]  id           单元ID
         * @return FITKAbstractElement*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        FITKAbstractElement* getElementByID(const int id);
        /**
         * @brief 获取单元数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        int getElementCount();
        /**
         * @brief 单元反向 
         * @param id 单元ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        virtual void reverseEleByID(const int id);
        /**
         * @brief 单元反向
         * @param index 单元索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-03
         */
        virtual void reverseEleByIndex(const int index);


        template<class T>
        /**
         * @brief 获取第index个单元，强制转换成T类型
         * @param[i]  index         单元索引
         * @return T*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        T* getTElementAt(const int index)
        {
            return dynamic_cast<T*>(this->getElementAt(index));
        }

        template<class T>
        /**
         * @brief 根据ID获取单元，并强制转化为T类型
         * @param[i]  id            单元id
         * @return T*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        T* getTElementByID(const int id)
        {
            return dynamic_cast<T*>(this->getElementAt(id));
        }
        /**
         * @brief 获取单元最大id
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-28
         */
        int getElementMaxID();
        /**
         * @brief 移除全部单元
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-28
         */
        void removeAllElement();

        /**
         * @brief   根据索引移除单元。
         * @param   index：网格单元索引
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-28
         */
        void removeElementAt(const int index);

        /**
         * @brief   根据ID移除单元。
         * @param   id：网格单元ID
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-28
         */
        void removeElementByID(const int id);

        /**
         * @brief 根据拓扑关系获取节点相邻的单元列表
         * @param[i] nodeID 节点ID
         * @return QList<FITKAbstractElement*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-28
         */
        QList<FITKAbstractElement*> getNeighborElement(const int nodeID);

        /**
       * @brief 获取全部使用的节点ID
       * @return QList<int>
       * @author LiBaojun (libaojunqd@foxmail.com)
       * @date 2024-11-19
       */
        virtual QList<int> getAllNodeIDs() const;

      /**
       * @brief 替换节点ID
       * @return QHash<int, int> & nodes  原先节点ID-替换后的节点ID
       * @author LiBaojun (libaojunqd@foxmail.com)
       * @date 2025-03-03
       */
        virtual void replaceNodesID(const QHash<int, int> & nodes);

    protected:
        /**
         * @brief   更新ID与索引映射关系。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-28
         */
        void updateElementIDIndexMap();

        /**
         * @brief   根据索引移除单元，不更新映射关系，需手动刷新ID与索引映射。
         * @param   index：网格单元索引
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-28
         */
        void fastRemoveElementAt(const int index);

        /**
         * @brief   根据ID移除单元，不更新映射关系，需手动刷新ID与索引映射。
         * @param   id：网格单元ID
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-28
         */
        void fastRemoveElementByID(const int id);

    protected:
        /**
         * @brief   线程锁。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-28
         */
        QMutex _mutex;

        /**
         * @brief 单元列表
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        QList<FITKAbstractElement*> _elementList{};
        /**
         * @brief 辅助存储，id与索引的映射关系
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        QMap <int, int> _idIndexMap{};
        /**
         * @brief 辅助存储， 最大单元ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-22
         */
        int _eleMaxID = 0;
    };
}

#endif //