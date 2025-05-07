/**
 * @file   FITKAbsGeoModelPartitionSolid.h
 * @brief  实体分块
 * @author YanZhiHui (chanyuantiandao@126.com)
 * @date   2025-04-23
 */
#ifndef  FITKABSGEOMODELPARTITIONSOLID_H
#define  FITKABSGEOMODELPARTITIONSOLID_H

#include "FITKInterfaceGeometryAPI.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include <QVector>
#include <array>

namespace Interface
{
    /**
     * @brief  实体分块.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2025-04-23
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelPartitionSolidWithDatumPlane :
        public FITKAbsGeoCommand
    {
        FITKCLASS(Interface, FITKAbsGeoModelPartitionSolidWithDatumPlane);
    public:
        FITKAbsGeoModelPartitionSolidWithDatumPlane() = default;
        ~FITKAbsGeoModelPartitionSolidWithDatumPlane() override = default;
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;
    };

}

#endif // !FITKABSGEOMODELPARTITIONSOLID_H
