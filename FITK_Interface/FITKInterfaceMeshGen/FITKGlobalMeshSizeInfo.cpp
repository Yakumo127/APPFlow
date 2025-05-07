﻿#include "FITKGlobalMeshSizeInfo.h"

namespace Interface
{
    FITKGlobalMeshSizeInfo::FITKGlobalMeshSizeInfo()
    {

    }

    void FITKGlobalMeshSizeInfo::setGlobalSize(const double s)
    {
        //错误判断
        if (s < 0) return;
        //赋值
        _globalSize = s;
    }


    double FITKGlobalMeshSizeInfo::getGlobalSize() const
    {
        return _globalSize;
    }

    void FITKGlobalMeshSizeInfo::setMinSize(const double s)
    {
        _minSize = s;
    }

    double FITKGlobalMeshSizeInfo::getMinSize() const
    {
        return  _minSize;
    }

    void FITKGlobalMeshSizeInfo::setMaxSize(const double s)
    {
        _maxSize = s;
    }

    double FITKGlobalMeshSizeInfo::getMaxSize() const
    {
        return _maxSize;
    }

    void FITKGlobalMeshSizeInfo::setSizeFactor(const double f)
    {
        _sizeFactor = f;
    }

    double FITKGlobalMeshSizeInfo::getSizeFactor() const
    {
        return _sizeFactor;
    }

}


