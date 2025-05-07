﻿/**
 *
 * @file FITKComponentManager.h
 * @brief 集合管理器类声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-03-17
 *
 */

#ifndef  ___FITKMODELSETCOMPOMNENTMANAGER_H____
#define  ___FITKMODELSETCOMPOMNENTMANAGER_H____

#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITKAbstractModelComponent.h"
#include "FITKModelSet.h"
#include "FITKMeshSurface.h"

namespace Interface
{
    /**
     * @brief 集合管理器
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-17
     */
    class FITKInerfaceModelAPI FITKComponentManager: public Core::FITKAbstractDataObject,
        public Core::FITKAbstractDataManager<FITKAbstractModelComponent>
    {
    public:
        /**
         * @brief Construct a new FITKModelSetManager object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        explicit FITKComponentManager() = default;
        /**
         * @brief Destroy the FITKModelSetManager object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        virtual ~FITKComponentManager() = default;
        /**
         * @brief 根据类型获取集合
         * @param[i]  t            集合类型
         * @return QList<FITKModelSet*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        QList<FITKModelSet*> getModelSet(FITKModelEnum::FITKModelSetType t);
        /**
         * @brief 根据类型获取不是内部集合的集合
         * @param[i]  t             集合类型
         * @return QList<FITKModelSet*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        QList<FITKModelSet*> getUnInternalModelSet(FITKModelEnum::FITKModelSetType t);
        /**
         * @brief 根据类型获取表面
         * @param[i]  t              类型
         * @return QList<FITKMeshSurface*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        QList<FITKMeshSurface*> getMeshSurface(MeshSurfaceType t);
        /**
         * @brief 根据类型获取不是内部表面的表面
         * @param[i]  t              类型
         * @return QList<FITKMeshSurface*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-17
         */
        QList<FITKMeshSurface*> getUnInternalMeshSurface(MeshSurfaceType t);
        /**
         * @brief 判断是否为集合类型
         * @param[i]  index         索引
         * @return true
         * @return false
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-27
         */
        bool isModelSet(int index) ;
        /**
         * @brief 获取第index个成员并转换为set类型
         * @param[i]  index          索引
         * @return FITKModelSet*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-27
         */
        FITKModelSet* getAsModelSet(int index);
        /**
         * @brief 获取第index个成员并转换为surface类型
         * @param[i]  index          索引
         * @return FITKModelSet*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-27
         */
        FITKMeshSurface* getAsMeshSurf(int index);
        /**
         * @brief 获取全部集合
         * @param[i] recur 是否递归
         * @return QList<FITKModelSet*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-27
         */
        QList<FITKModelSet*> getAllSet(bool recur = true );
        /**
         * @brief 获取全部表面
         * @return QList<FITKMeshSurface*>
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-27
         */
        QList<FITKMeshSurface*> getAllSurface() ;
        /**
         * @brief 追加对象
         * @param[i] obj          追加的数据对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-22
         */
        virtual void appendDataObj(FITKAbstractDataObject* item) override;

        /**
         * @brief 插入数据对象，索引越界追加，索引为负数插入到最前面
         * @param[i] index           插入的索引
         * @param[i] item            待插入的数据对象
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-22
         */
        virtual void insertDataObj(int index, FITKAbstractDataObject* item) override;
        /**
         * @brief 根据ID获取数据对象
         * @param[i] id              ID
         * @return FITKAbstractModelComponent*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-22
         */
        virtual FITKAbstractModelComponent* getDataByID(const int id) override;
        /**
        * @brief 根据绝对成员获取集合，不存在则创建新的集合
        * @param[i] t             集合类型
        * @param[i] member        成员
        * @return FITKModelSet*
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-05-29
        */
        virtual FITKModelSet* getModelSetByMember(FITKModelEnum::FITKModelSetType t,
            const int modelID, const QList<int>  &member);

        /**
        * @brief 获取只有一个点的集合
        * @param[i] modelID      模型id            
        * @param[i] memID        成员ID
        * @return FITKModelSet*
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-05-29
        */
        FITKModelSet* getSingleNodeSet(const int modelID, const int memID);
     private:
         /**
         * @brief 合并同名集合
         * @param[i] existSet        已经存在的集合
         * @param[i] item            新插入集合
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-22
         */
         void mergeSameNameSet(FITKModelSet* existSet, FITKModelSet* newSet);
    };

}

#endif
