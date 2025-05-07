#include "FITKAbsVirtualTopo.h"

namespace Interface
{

    FITKAbsVirtualTopo::FITKAbsVirtualTopo(FITKGeoEnum::VTopoShapeType type)
        :_topoShapeType(type)
    {
    }

    FITKAbsVirtualTopo::~FITKAbsVirtualTopo()
    {
        //清空子对象
        this->clearSubTopo();
        if (_shape) delete _shape;
        _shape = nullptr;
    }

    FITKGeoEnum::VTopoShapeType FITKAbsVirtualTopo::getShapeType() const
    {
        //获取拓扑类型
        return _topoShapeType;
    }

    void FITKAbsVirtualTopo::setShapeType(FITKGeoEnum::VTopoShapeType s)
    {
        _topoShapeType = s;
    }

    void FITKAbsVirtualTopo::addSubTopo(FITKAbsVirtualTopo* subTopo)
    {
        //添加子对象，已经包含的不再添加
        if (_subTopo.contains(subTopo)) return;
        _subTopo.append(subTopo);
        subTopo->addParentTopo(this);
    }

    void FITKAbsVirtualTopo::addParentTopo(FITKAbsVirtualTopo* pTopo)
    {
        if (nullptr == pTopo || _parents.contains(pTopo)) return;
        return _parents.append(pTopo);
    }

    int FITKAbsVirtualTopo::getSubTopoCount()
    {
        return _subTopo.count();
    }

    FITKAbsVirtualTopo* FITKAbsVirtualTopo::getSubTopo(const int index)
    {
        //数组是否越界判断
        if (index < 0 || index >= _subTopo.count()) return nullptr;
        return _subTopo[index];
    }

    int FITKAbsVirtualTopo::getParentTopoCount()
    {
        return _parents.count();
    }

    FITKAbsVirtualTopo* FITKAbsVirtualTopo::getParentTopo(const int index)
    {
        //数组是否越界判断
        if (index < 0 || index >= _parents.count()) return nullptr;
        return _parents[index];
    }

    FITKAbsVirtualTopo* FITKAbsVirtualTopo::getRootTopo()
    {
        FITKAbsVirtualTopo* rootTopo = getParentTopo(0);
        do
        {
            auto tempRootTopo = rootTopo->getParentTopo(0);
            if (!tempRootTopo) return rootTopo;
            rootTopo = tempRootTopo;

        } while (rootTopo != nullptr);

        return rootTopo;
    }

    void FITKAbsVirtualTopo::clearSubTopo()
    {
        //      const int n = _subTopo.size();
        //      for (int i = 0; i<n; ++i)
        //      {
        //          FITKAbsVirtualTopo* t = _subTopo.at(i);
        //          delete t;
        //      }
        _subTopo.clear();
    }

    void FITKAbsVirtualTopo::setShape(FITKAbsVirtualTopoShape* shape)
    {
        _shape = shape;
    }

    FITKAbsVirtualTopoShape* FITKAbsVirtualTopo::getShape()
    {
        return _shape;
    }

    void FITKAbsVirtualTopo::setIndexLabel(const int index)
    {
        _indexLabel = index;
    }


    int FITKAbsVirtualTopo::getIndexLabel() const
    {
        return _indexLabel;
    }

    FITKAbsVirtualTopoShape::~FITKAbsVirtualTopoShape()
    {

    }

}



