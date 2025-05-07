#include "FITKAbstractDict.h"
//命名空间
namespace DICT
{
    FITKAbstractDict::~FITKAbstractDict()
    {
    }
    
    FITKAbstractDict::DictType FITKAbstractDict::getDictType()
    {
        return FITKAbstractDict::DictType::DictNone;
    }
}
