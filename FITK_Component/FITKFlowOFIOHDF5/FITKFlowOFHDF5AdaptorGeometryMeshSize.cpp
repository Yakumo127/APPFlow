#include "FITKFlowOFHDF5AdaptorGeometryMeshSize.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKGeometryMeshSize.h"

#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"


#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorGeometryMeshSize::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorGeometryMeshSize";
    }

    bool FITKFlowOFHDF5AdaptorGeometryMeshSize::adaptR()
    {
        _geoMeshSizeData = dynamic_cast<Interface::FITKGeometryMeshSize*>(_dataObj);
        if (!_reader || !_geoMeshSizeData) return false;

        if (!readNDataObject(_geoMeshSizeData, *_h5Group))return false;
        //几何组件Id
        int componentId = readIntAttribute(*_h5Group, "geoComponentId");
        _geoMeshSizeData->setGeoGroupComponentId(componentId);
        //层数
        int layerNum = readIntAttribute(*_h5Group, "layerNumber");
        _geoMeshSizeData->setLayerNumber(layerNum);
        //膨胀率
        double expansionRatio = readDoubleAttribute(*_h5Group, "expansionRatio");
        _geoMeshSizeData->setExpansionRatio(expansionRatio);
        //层厚度
        double layerThickness = readDoubleAttribute(*_h5Group, "layerThickness");
        _geoMeshSizeData->setLayerThickness(layerThickness);
        return true;
    }

    bool FITKFlowOFHDF5AdaptorGeometryMeshSize::adaptW()
    {
        _geoMeshSizeData = dynamic_cast<Interface::FITKGeometryMeshSize*>(_dataObj);
        if (!_writer || !_geoMeshSizeData) return false;
        std::string name = _geoMeshSizeData->getDataObjectName().toStdString();
        int numAttrCount = _h5Group->getNumAttrs();
        writeStrAttribute(*_h5Group, std::to_string(numAttrCount), name);
        //创建组
        H5::Group h5Group = _h5Group->createGroup(name);
        if (!writeNDataObject(_geoMeshSizeData, h5Group)) return false;
        //几何组件Id
        int componentId = _geoMeshSizeData->getGeoGroupComponentId();
        writeIntAttribute(h5Group, "geoComponentId", &componentId);
        //层数
        int layerNum = _geoMeshSizeData->getLayerNumber();
        writeIntAttribute(h5Group, "layerNumber", &layerNum);
        //膨胀率
        double expansionRatio = _geoMeshSizeData->getExpansionRatio();
        writeDoubleAttribute(h5Group, "expansionRatio", &expansionRatio);
        //层厚度
        double layerThickness = _geoMeshSizeData->getLayerThickness();
        writeDoubleAttribute(h5Group, "layerThickness", &layerThickness);
        return true;
    }

}
