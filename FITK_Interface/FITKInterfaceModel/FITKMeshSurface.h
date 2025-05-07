/**
 *
 * @file FITKMeshSurface.h
 * @brief  网格表面类声明，基于elementset表示
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-03-26
 *
 */
#ifndef __FITKMESH__SURFACE_H___
#define __FITKMESH__SURFACE_H___

#include "FITK_Interface/FITKInterfaceModel/FITKAbstractModelComponent.h"
#include <QList>
#include <QPair>

namespace Interface
{
    class FITKAbstractModel;
    class FITKModelSet;

    //表面的几何信息，复合集合展开并过滤，仅包含最底层
    struct SurfaceAbsSetInfo
    {
        FITKAbstractModel* _model{};
        FITKModelSet* _set{};
        //面索引，单元表面特有
        int _surfaceIndex{ -1 };
        //点权重，节点表面特有
        double _nodeWidght{ 0 };
    };

    /**
     * @brief 表面类型
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-26
     */
    enum MeshSurfaceType
    {
        SurNone,  ///< 错误值
        SurEle,   ///< 单元表面
        SurNode,  ///< 节点表面
    };

    class FITKModelSet;
    /**
     * @brief 网格表面类，基于set的表示
     * @author  LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-26
     */
    class FITKInerfaceModelAPI FITKMeshSurface : public FITKAbstractModelComponent
    {
        Q_OBJECT
        FITKCLASS(Interface, FITKMeshSurface);
    public:
        /**
     * @brief 表面类型
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-26
     */
        enum MeshSurfaceType
        {
            SurNone,  ///< 错误值
            SurEle,   ///< 单元表面
            SurNode,  ///< 节点表面
        };
        Q_ENUM(MeshSurfaceType);
    public:
        /**
         * @brief Construct a new FITKMeshSurface object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        explicit FITKMeshSurface() = default;
        /**
         * @brief Destroy the FITKMeshSurface object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        virtual ~FITKMeshSurface() = 0;

        /**
         * @brief 获取表面类型
         * @return MeshSurfaceType
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        virtual MeshSurfaceType getMeshSurfaceType() = 0;
        /**
         * @brief 是否为内部面
         * @return true
         * @return false
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        bool isInternal() const;
        /**
         * @brief 设置是否为内部面
         * @param[i]  internal       是否内部面
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        void isInternal(bool internal);
        /**
         * @brief 获取包含集合的数量
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        int getMeshSetCount() const;
        /**
         * @brief 获取第index个集合
         * @param[i]  index         索引
         * @return FITKModelSet*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        FITKModelSet* getMeshSetAt(const int index) const;
        /**
         * @brief 获取第index个集合属于的模型，part instance assembly等
         * @param[i]  index         索引
         * @return FITKModelSet*
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        FITKAbstractModel* getModelAt(const int index) const;
        
        /**
        * @brief 获取集合信息，将复合集合拆分，返回值不会包含复合集合
        * @return QList<SurfaceAbsSetInfo>
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-03-26
        */
        virtual QList<SurfaceAbsSetInfo> getAbsoluteSetInfo();

    protected:
        /**
         * @brief 集合的索引
         * @param[i]  modelID        模型id
         * @param[i]  setID          集合ID
         * @return int               索引
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-04-18
         */
        int indexOf(int modelID, int setID);

    protected:
        /**
         * @brief 是否内部表面
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        bool _internal{ false };
        /**
         * @brief 集合ID, 第一个值为model，可以是instace等，第二值为集合id
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-03-26
         */
        QList<QPair<int, int>> _modelSetIDs{};

    };
}


#endif
