#include "FITKFlowOFHDF5AdaptorGeometryRefine.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionGeometryRefine.h"

#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"


#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorGeometryRefine::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorGeometry";
    }

    bool FITKFlowOFHDF5AdaptorGeometryRefine::adaptR()
    {
        _geoRefineData = dynamic_cast<Interface::FITKRegionGeometryRefine*>(_dataObj);
        if (!_reader || !_geoRefineData) return false;

        readDataObject(_geoRefineData, *_h5Group);

        int geoId = readIntAttribute(*_h5Group, "geometryId");
        _geoRefineData->setGeometryId(geoId);

        bool limitRefineMent = readBoolAttribute(*_h5Group, "limitRefineMent");
        _geoRefineData->setLimitRefinement(limitRefineMent);

        int refineModel = readIntAttribute(*_h5Group, "refineModel");
        _geoRefineData->setRefineModel(Interface::FITKRegionGeometryRefine::RefineModelType(refineModel));

        double distance = readDoubleAttribute(*_h5Group, "distance");
        _geoRefineData->setDistance(distance);

        int level = readIntAttribute(*_h5Group, "level");
        _geoRefineData->setLevel(level);

        int gapRefineModel = readIntAttribute(*_h5Group, "gapRefineModel");
        _geoRefineData->setGapRefineModel(Interface::FITKRegionGeometryRefine::GapModelType(gapRefineModel));

        int cellsInGapNum = readIntAttribute(*_h5Group, "cellsInGapNum");
        _geoRefineData->setCellsInGapNum(cellsInGapNum);

        int maxGapLevel = readIntAttribute(*_h5Group, "maxGapLevel");
        _geoRefineData->setMaxGapLevel(maxGapLevel);

        return true;
    }

    bool FITKFlowOFHDF5AdaptorGeometryRefine::adaptW()
    {
        _geoRefineData = dynamic_cast<Interface::FITKRegionGeometryRefine*>(_dataObj);
        if (!_writer || !_geoRefineData) return false;
        if (!_geoRefineData->getGeometryModel())return false;

        std::string name = createParentAttribute(_geoRefineData, *_h5Group);
        if (name.empty())return false;

        //创建组    
        H5::Group geoGroup = _h5Group->createGroup(name);
        writeDataObject(_geoRefineData, geoGroup);

        int geoId = _geoRefineData->getGeometryId();
        writeIntAttribute(geoGroup, "geometryId", &geoId);

        //写入七个参数属性
        bool limitRefineMent = _geoRefineData->getLimitRefineMent();
        writeBoolAttribute(geoGroup, "limitRefineMent", &limitRefineMent);

        int refineModel = _geoRefineData->getRefineModel();
        writeIntAttribute(geoGroup, "refineModel", &refineModel);

        double distance = _geoRefineData->getDistance();
        writeDoubleAttribute(geoGroup, "distance", &distance);

        int level = _geoRefineData->getLevel();
        writeIntAttribute(geoGroup, "level", &level);

        int gapRefineModel = _geoRefineData->getGapRefineModel();
        writeIntAttribute(geoGroup, "gapRefineModel", &gapRefineModel);

        int cellsInGapNum = _geoRefineData->getCellsInGapNum();
        int maxGapLevel = _geoRefineData->getMaxGapLevel();
        writeIntAttribute(geoGroup, "cellsInGapNum", &cellsInGapNum);
        writeIntAttribute(geoGroup, "maxGapLevel", &maxGapLevel);


        return true;
    }

}
