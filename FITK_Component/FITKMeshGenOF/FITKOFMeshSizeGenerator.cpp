#include "FITKOFMeshSizeGenerator.h"

namespace OF
{
    Interface::FITKGlobalMeshSizeInfo* FITKOFMeshSizeGenerator::generateGlobalMeshSizeInfo()
    {
        //默认使用父类函数
        return Interface::FITKAbstractMeshSizeInfoGenerator::generateGlobalMeshSizeInfo();
    }
    Interface::FITKAbstractRegionMeshSize* FITKOFMeshSizeGenerator::createRegionMeshSize(Interface::FITKAbstractRegionMeshSize::RegionType t)
    {
        //默认使用父类函数
        return Interface::FITKAbstractMeshSizeInfoGenerator::createRegionMeshSize(t);
    }
}




