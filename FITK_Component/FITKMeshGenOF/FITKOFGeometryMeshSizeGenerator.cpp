#include "FITKOFGeometryMeshSizeGenerator.h"

namespace OF
{
    Interface::FITKGeometryMeshSize* FITKOFGeometryMeshSizeGenerator::createGeometryMeshSize()
    {
        //默认使用父类函数
        return Interface::FITKAbstractGeometryMeshSizeGenerator::createGeometryMeshSize();
    }
}




