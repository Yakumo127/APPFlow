#include "FITKAbsGeoModelOperFace.h"

#include "FITK_Kernel/FITKCore/FITKDataRepo.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
namespace Interface
{
    void FITKAbsGeoModelOperFace::add(VirtualShape geoCommandShape)
    {
        m_tempVShapes.append(geoCommandShape);
    }

    void FITKAbsGeoModelOperFace::add(QList<VirtualShape> geoCommandShapes)
    {
        m_tempVShapes.append(geoCommandShapes);
    }

    void FITKAbsGeoModelOperFace::set(VirtualShape geoCommandShape)
    {
        m_tempVShapes.clear();
        m_tempVShapes.append(geoCommandShape);
    }

    void FITKAbsGeoModelOperFace::set(QList<VirtualShape> geoCommandShapes)
    {
        m_tempVShapes = geoCommandShapes;
    }


    void FITKAbsGeoModelOperFace::remove(int index)
    {
        m_tempVShapes.removeAt(index);
    }

    void FITKAbsGeoModelOperFace::clear()
    {
        m_tempVShapes.clear();
    }

    void FITKAbsGeoModelOperFace::setType(GeoFaceOperType t)
    {
        _faceOperType = t;
    }

    FITKAbsGeoModelOperFace::GeoFaceOperType FITKAbsGeoModelOperFace::getType()
    {
        return _faceOperType;
    }

    QList<VirtualShape> FITKAbsGeoModelOperFace::getVShapes()
    {
        return m_tempVShapes;
    }

    QList<int> FITKAbsGeoModelOperFace::getModelOperFacesID()
    {
        QList<int> _geoCommands;

        for (int i = 0; i < m_tempVShapes.size(); i++)
        {
            _geoCommands.append(m_tempVShapes[i].CmdId);
        }
        return _geoCommands;
    }

    void FITKAbsGeoModelOperFace::setTolerance(double tolerance)
    {
        _tolerance = tolerance;
    }

    double FITKAbsGeoModelOperFace::getTolerance()
    {
        return _tolerance;
    }


    Interface::FITKAbsVirtualTopo* FITKAbsGeoModelOperFace::getRefModelVirtualTopo(Interface::FITKGeoEnum::VTopoShapeType shapeType, int m_solidCmdId, int virtualTopoId)
    {
        //数据获取
        Interface::FITKAbsGeoCommand* comm = FITKDATAREPO->getTDataByID<Interface::FITKAbsGeoCommand>(m_solidCmdId);
        if (comm == nullptr) return nullptr;
        auto sVirtualTopoManager = comm->getShapeVirtualTopoManager(shapeType);
        if (!sVirtualTopoManager) return nullptr;
        Interface::FITKAbsVirtualTopo* faceVirtualShape = sVirtualTopoManager->getDataByID(virtualTopoId);
        return faceVirtualShape;
    }

    //移除面
    //{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelOperFaceRemoveFace::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTRemoveFace;
    }
    //}

    //延申面
    //{

    void FITKAbsGeoModelOperFaceExtendFace::setEdges(QList<VirtualShape> edges)
    {
        _tempEdgeShapes = edges;
    }

    QList<VirtualShape> FITKAbsGeoModelOperFaceExtendFace::getEdges()
    {
        return _tempEdgeShapes;
    }

    void FITKAbsGeoModelOperFaceExtendFace::setFaces(QList<VirtualShape> face)
    {
        m_tempVShapes = face;
    }

    QList<VirtualShape> FITKAbsGeoModelOperFaceExtendFace::getFaces()
    {
        return m_tempVShapes;
    }

    void FITKAbsGeoModelOperFaceExtendFace::setTagFaces(QList<VirtualShape> faces)
    {
        _tempTagFaceShapes = faces;
    }

    QList<VirtualShape> FITKAbsGeoModelOperFaceExtendFace::getTagFaces()
    {
        return _tempTagFaceShapes;
    }

    void FITKAbsGeoModelOperFaceExtendFace::setDistance(double dis)
    {
        _distance = dis;
    }

    double FITKAbsGeoModelOperFaceExtendFace::getDistance()
    {
        return _distance;
    }

    void FITKAbsGeoModelOperFaceExtendFace::setTrim(bool isTrim)
    {
        _trim = isTrim;
    }

    bool FITKAbsGeoModelOperFaceExtendFace::getTrim()
    {
        return _trim;
    }

    void FITKAbsGeoModelOperFaceExtendFace::setSpecifyMode(SpecifyModel sm)
    {
        _selectedMode.first = sm;
    }

    void FITKAbsGeoModelOperFaceExtendFace::setMethodModel(MethodModel mm)
    {
        _selectedMode.second = mm;
    }

    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelOperFaceExtendFace::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTExtendFace;
    }
    //}

    //修复面
    //{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelOperFaceRepairFaces::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTRepairFace;
    }
    //}

    //填补缝隙
    //{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelOperFaceFillGaps::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTFillGapsFace;
    }
    //}

    //填补孔洞
    //{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelOperFaceFillHoles::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTFillHolesFace;
    }
    //}

    //删除悬浮边
    //{
    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelOperFaceDeleteFloatingEdge::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTDeleteFloatingEdge;
    }

    void FITKAbsGeoModelOperFaceDeleteFloatingEdge::setMFace(VirtualShape vface)
    {
        m_face = vface;
    }
    VirtualShape FITKAbsGeoModelOperFaceDeleteFloatingEdge::getMFace()
    {
        return m_face;
    }
    //}
}