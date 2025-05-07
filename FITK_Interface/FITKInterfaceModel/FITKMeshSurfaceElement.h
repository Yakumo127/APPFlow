﻿/**
 *
 * @file FITKMeshSurface.h
 * @brief  网格表面类声明，基于elementset表示
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-03-26
 *
 */
#ifndef __FITKMESH__SURFACE_ELEMENT_H___
#define __FITKMESH__SURFACE_ELEMENT_H___

#include "FITKMeshSurface.h"

namespace Interface
{



    /**
     * @brief 网格单元表面类，基于set的表示
     * @author  LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-26
     */
    class FITKInerfaceModelAPI FITKMeshSurfaceElement : public FITKMeshSurface
    {
        FITKCLASS(Interface, FITKMeshSurfaceElement);
    public:
        /**
         * @brief Construct a new FITKMeshSurface object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        explicit FITKMeshSurfaceElement() = default;
        /**
         * @brief Destroy the FITKMeshSurface object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        virtual ~FITKMeshSurfaceElement() = default;

        /**
         * @brief 获取表面类型
         * @return MeshSurfaceType
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        FITKMeshSurface::MeshSurfaceType getMeshSurfaceType() override;

        /**
         * @brief 追加表面
         * @param[i]  modelID        set的父对象id，可以是装配、部件 装配实例
         * @param[i]  setID          集合ID
         * @param[i]  surfIndex      表面索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        void addMeshSet(int modelID, int setID, int surfIndex);
        /**
         * @brief 追加表面
         * @param[i]  model          set的父对象，可以是装配、部件 装配实例
         * @param[i]  set            集合
         * @param[i]  surfIndex      面索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        void addMeshSet(FITKAbstractModel* model, FITKModelSet* set, int surfIndex);
        /**
         * @brief  清除表面集合.
         * @author YanZhiHui(chanyuantiandao@126.com)
         * @date   2024-11-14
         */
        void clearMeshSet();

        /**
         * @brief 获取第index个面的索引
         * @param[i]  index          索引
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        int getSurfaceIndexAt(const int index) const;

        /**
         * @brief 设置第index个面的索引
         * @param[i] index        集合索引
         * @param[i]  surfIndex          面索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-20
         */
        void setSurfaceIndex(const int index, const int surfIndex);


        /**
        * @brief 获取集合信息，将复合集合拆分，返回值不会包含复合集合
        * @return QList<SurfaceAbsSetInfo>
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-03-26
        */
        virtual QList<SurfaceAbsSetInfo> getAbsoluteSetInfo() override;
    protected:

        /**
         * @brief 面索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        QList<int> _surfIndex{};
    };
}


#endif
