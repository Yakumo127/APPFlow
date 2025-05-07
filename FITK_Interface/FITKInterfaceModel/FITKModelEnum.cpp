﻿#include "FITKModelEnum.h"

namespace Interface
{
    FITKModelEnum::FITKMeshDim FITKModelEnum::GetElementDim(FITKModelEnum::FITKEleType eletype)
    {
        switch (eletype)
        {
            //线单元，一维单元
        case Interface::FITKModelEnum::Line2:
        case Interface::FITKModelEnum::Line3:
            return FITKModelEnum::FITKMeshDim::FMDimD1;
        //面单元，二维单元
        case Interface::FITKModelEnum::Tri3:
        case Interface::FITKModelEnum::Tri6:
        case Interface::FITKModelEnum::Quad4:
        case Interface::FITKModelEnum::Quad8:
            return FITKModelEnum::FITKMeshDim::FMDimD2;
        //体单元，三维单元
        case Interface::FITKModelEnum::Tet4:
        case Interface::FITKModelEnum::Tet10:
        case Interface::FITKModelEnum::Wedge6:
        case Interface::FITKModelEnum::Hex8:
        case Interface::FITKModelEnum::Hex20:
            return FITKModelEnum::FITKMeshDim::FMDimD3;
        default:
            break;
        }
        //默认返回无
        return FITKModelEnum::FITKMeshDim::FMDimNone;
    }

    bool FITKModelEnum::HasMeshDimFlag(const unsigned int flags, const FITKMeshDim& dim)
    {
        return (flags & dim) != 0;
    }
}


