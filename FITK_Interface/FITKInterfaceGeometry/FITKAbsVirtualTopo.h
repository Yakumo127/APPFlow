/**
 * 
 * @file FITKAbsVirtualTopo.h
 * @brief 几何虚拟拓扑接口
 * @author libaojun (libaojunqd@foxmail.com)
 * @date 2024-08-09
 * 
 */
#ifndef _FITK_ABS_VIRTUAL_TOPO_H___
#define _FITK_ABS_VIRTUAL_TOPO_H___

#include "FITKInterfaceGeometryAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITKGeoEnum.h"
#include <QMutex>

namespace Interface
{
    /**
     * @brief 几何形状代理
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-08-09
     */
    class FITKInterfaceGeometryAPI FITKAbsVirtualTopoShape
    {
    public:
        explicit FITKAbsVirtualTopoShape() = default;
        virtual ~FITKAbsVirtualTopoShape() = 0;
        /**
         * @brief 是否为同一个形状
         * @param[i] 是同一个形状
         * @return true 
         * @return false 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        virtual bool isSameShape( void* ) = 0;
    };
    /**
     * @brief 几何虚拓扑对象
     * @author libaojun (libaojunqd@foxmail.com)
     * @date 2024-08-09
     */
    class FITKInterfaceGeometryAPI FITKAbsVirtualTopo : public Core::FITKAbstractDataObject
    {
        FITKCLASS(Interface, FITKAbsVirtualTopo);
        friend FITKAbsVirtualTopo;
        Q_OBJECT
    public:
        /**
         * @brief Construct a new FITKAbsVirtualTopo object
         * @param[i]  type           类型
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        explicit FITKAbsVirtualTopo(FITKGeoEnum::VTopoShapeType type = FITKGeoEnum::VSNone);
        /**
         * @brief 析构，不会释放子拓扑内存
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        virtual ~FITKAbsVirtualTopo();
        /**
         * @brief 获取类型
         * @return VTopoShapeType 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        FITKGeoEnum::VTopoShapeType getShapeType()const;
        /**
         * @brief 设置类型
         * @param[i]  s           类型
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */ 
        void setShapeType(FITKGeoEnum::VTopoShapeType s);
        /**
         * @brief 添加子拓扑
         * @param[i]  subTopo           子拓扑
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        void addSubTopo(FITKAbsVirtualTopo* subTopo);
        
        /**
         * @brief 获取子拓扑数量
         * @return int 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        int getSubTopoCount();
        /**
         * @brief 获取子拓扑
         * @param[i]  index          索引
         * @return FITKAbsVirtualTopo* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        FITKAbsVirtualTopo* getSubTopo(const int index);

        /**
         * @brief 获取父拓扑数量
         * @return int
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        int getParentTopoCount();
        /**
         * @brief 获取父拓扑
         * @param[i]  index          索引
         * @return FITKAbsVirtualTopo*
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        FITKAbsVirtualTopo* getParentTopo(const int index);

        /**
         * @brief 获取根拓扑
         * @return FITKAbsVirtualTopo*
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-08-09
         */
        FITKAbsVirtualTopo* getRootTopo();

        template<class T>
        /**
         * @brief 获取子拓扑，并强制转换类型
         * @param[i]  index       索引
         * @return T* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        T* getTSubTopo(const int index)
        {
            return dynamic_cast<T*>(this->getSubTopo(index));
        }
        /**
         * @brief 清空子拓扑， 不会清理内存
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        void clearSubTopo();
        /**
         * @brief 设置形状
         * @param[i]  shape          形状
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        void setShape(FITKAbsVirtualTopoShape* shape);
        /**
         * @brief 获取形状
         * @return FITKAbsVirtualTopoShape* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        FITKAbsVirtualTopoShape* getShape();

        template<class T>
        /**
         * @brief 获取形状，并强制转换类型
         * @return T* 
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        T* getShapeT()
        {
            return dynamic_cast<T*>(_shape);
        }
        /**
         * @brief 设置索引标记
         * @param[i] index  索引
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-27
         */
        void setIndexLabel(const int index);
        /**
         * @brief 获取索引标记
         * @return int
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-27
         */
        int getIndexLabel() const;

    private:
        /**
        * @brief 添加父对象
        * @param[i]  pTopo       父对象
        * @author libaojun (libaojunqd@foxmail.com)
        * @date 2024-08-09
        */
        void addParentTopo(FITKAbsVirtualTopo* pTopo);

    private:
        /**
         * @brief 父对象
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        QList<FITKAbsVirtualTopo*> _parents{};
        /**
         * @brief 形状类型
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        FITKGeoEnum::VTopoShapeType _topoShapeType{ FITKGeoEnum::VSNone };
        /**
         * @brief 形状
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */ 
        FITKAbsVirtualTopoShape* _shape{};
        /**
         * @brief 子拓扑
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-09
         */
        QList<FITKAbsVirtualTopo*> _subTopo{};
        /**
         * @brief 索引标记
         * @author libaojun (libaojunqd@foxmail.com)
         * @date 2024-08-27
         */
        int _indexLabel{ -1 };
    };

}


#endif
