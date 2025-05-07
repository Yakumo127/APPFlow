#include "FITKAbsGeomTools.h"

#include "FITKGeoInterfaceFactory.h"

// Global data
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"

// Data
#include "FITK_Kernel/FITKCore/FITKVec3DAlg.h"

namespace Interface
{
    // 点查询。
    //@{
    FITKAbstractGeomPointTool* FITKAbstractGeomPointTool::createTool()
    {
        //获取注册的工具生成器
        FITKAbstractGeomToolsCreator* c = Interface::FITKInterfaceGeometryFactory::getInstance()->getGeomToolsCreator();
        if (c == nullptr) return nullptr;
        //创建工具
        return c->createPointTool();
    }

    bool FITKAbstractGeomPointTool::getXYZByID(const int & id, double* oXyz, int iModelId)
    {
        // Cast the data.
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getXYZ(vTopo, oXyz, iModelId);
    }
    //@}

    // 线查询。
    //@{
    FITKAbstractGeomEdgeTool* FITKAbstractGeomEdgeTool::createTool()
    {
        //获取注册的工具生成器
        FITKAbstractGeomToolsCreator* c = Interface::FITKInterfaceGeometryFactory::getInstance()->getGeomToolsCreator();
        if (c == nullptr) return nullptr;
        //创建工具
        return c->createEdgeTool();
    }

    bool FITKAbstractGeomEdgeTool::getStartPointDirectionByID(const int & id, double* oPos, double* oDir, int iModelId)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getStartPointDirection(vTopo, oPos, oDir, iModelId);
    }

    bool FITKAbstractGeomEdgeTool::getEndPointDirectionByID(const int & id, double* oPos, double* oDir, int iModelId)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getEndPointDirection(vTopo, oPos, oDir, iModelId);
    }

    bool FITKAbstractGeomEdgeTool::getDirectionByID(const int & id, double* oPos, double* oDir, double iU, int iModelId)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getDirection(vTopo, oPos, oDir, iU, iModelId);
    }

    bool FITKAbstractGeomEdgeTool::isLineByID(const int & id)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->isLine(vTopo);
    }

    bool FITKAbstractGeomEdgeTool::getLengthByID(const int & id, double & len)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getLength(vTopo, len);
    }

    bool FITKAbstractGeomEdgeTool::getMidPointByID(const int & id, double * oPos, int iModelId)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getMidPoint(vTopo, oPos, iModelId);
    }

    bool FITKAbstractGeomEdgeTool::getFeaturePointsByID(const int & id, QList<QList<double>> & oPoses, int iModelId)
    {
        // 调用虚拓扑对象接口。
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getFeaturePoints(vTopo, oPoses, iModelId);
    }
    //@}

    // 面查询。
    //@{
    FITKAbstractGeomFaceTool* FITKAbstractGeomFaceTool::createTool()
    {
        //获取注册的工具生成器
        FITKAbstractGeomToolsCreator* c = Interface::FITKInterfaceGeometryFactory::getInstance()->getGeomToolsCreator();
        if (c == nullptr) return nullptr;
        //创建工具
        return c->createFaceTool();
    }

    bool FITKAbstractGeomFaceTool::getPlaneByID(const int & id, double* oPos, double* oNormal, double* oUp, int iModelId)
    {
        // Cast the data.
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getPlane(vTopo, oPos, oNormal, oUp, iModelId);
    }

    bool FITKAbstractGeomFaceTool::getNormalByID(const int & id, double* iPos, double* oNormal, int iModelId)
    {
        // Cast the data.
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->getNormal(vTopo, iPos, oNormal, iModelId);
    }

    bool FITKAbstractGeomFaceTool::isPlaneByID(const int & id)
    {
        // Cast the data.
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(id);
        return this->isPlane(vTopo);
    }
    //@}

    // 通用查询。
    //@{
    FITKAbstractGeomCommonTool* FITKAbstractGeomCommonTool::createTool()
    {
        //获取注册的工具生成器
        FITKAbstractGeomToolsCreator* c = Interface::FITKInterfaceGeometryFactory::getInstance()->getGeomToolsCreator();
        if (c == nullptr) return nullptr;
        //创建工具
        return c->createCommonTool();
    }

    bool FITKAbstractGeomCommonTool::getDistanceByTopoIDs(const int vTopoId_1, const int vTopoId_2, double & oDist, double oPos_1[3], double oPos_2[3])
    {
        // Cast the data.
        Interface::FITKAbsVirtualTopo* vTopo_1 = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(vTopoId_1);
        Interface::FITKAbsVirtualTopo* vTopo_2 = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(vTopoId_2);
        return this->getDistanceByTopos(vTopo_1, vTopo_2, oDist, oPos_1, oPos_2);
    }

    bool FITKAbstractGeomCommonTool::getDistanceByTopoIDAndPos(const int vTopoId, double iPos3[3], double & oDist, double oPos[3])
    {
        // Cast the data.
        Interface::FITKAbsVirtualTopo* vTopo = FITKDATAREPO->getTDataByID<Interface::FITKAbsVirtualTopo>(vTopoId);
        return this->getDistanceByTopoAndPos(vTopo, iPos3, oDist, oPos);
    }
    //@}

    // 特征查询。
    //@{
    FITKAbstractGeomFeatureTool* FITKAbstractGeomFeatureTool::createTool()
    {
        //获取注册的工具生成器
        FITKAbstractGeomToolsCreator* c = Interface::FITKInterfaceGeometryFactory::getInstance()->getGeomToolsCreator();
        if (c == nullptr) return nullptr;
        //创建工具
        return c->createFeatureTool();
    }
    //@}

    FITKAbstractGeomToolsCreator::~FITKAbstractGeomToolsCreator()
    {
    }

    FITKAbstractGeomPointTool* FITKAbstractGeomToolsCreator::createPointTool()
    {
        //错误值
        return nullptr;
    }

    FITKAbstractGeomEdgeTool* FITKAbstractGeomToolsCreator::createEdgeTool()
    {
        //错误值
        return nullptr;
    }

    FITKAbstractGeomFaceTool* FITKAbstractGeomToolsCreator::createFaceTool()
    {
        //错误值
        return nullptr;
    }
    Interface::FITKAbstractGeomCommonTool* FITKAbstractGeomToolsCreator::createCommonTool()
    {
        //错误值
        return nullptr;
    }
    Interface::FITKAbstractGeomFeatureTool * FITKAbstractGeomToolsCreator::createFeatureTool()
    {
        //错误值
        return nullptr;
    }
}
