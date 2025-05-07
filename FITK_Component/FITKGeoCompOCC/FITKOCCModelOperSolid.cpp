#include "FITKOCCModelOperSolid.h"

// OCC base
#include <TopoDS.hxx>
#include <TopoDS_Solid.hxx>

// 倒角/倒圆
#include <BRepFilletAPI_MakeChamfer.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>

// 特征移除。（填补孔洞/移除倒角/移除倒圆）
#include <BRepAlgoAPI_Defeaturing.hxx>

// App
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

// Geometry
#include "FITKOCCVirtualTopoCreator.h"
#include <FITK_Interface/FITKInterfaceGeometry/FITKGeoEnum.h>
#include <FITK_Interface/FITKInterfaceGeometry/FITKVirtualTopoManager.h>
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoInterfaceFactory.h"

namespace OCC
{
    // 倒角。
    //@{
    FITKOCCModelChamferSolid::FITKOCCModelChamferSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelChamferSolid::update()
    {
        Interface::FITKGeoCommandList* geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        // 获取被倒角的体模型。
        Interface::FITKAbsGeoCommand* cmd = geoCmdList->getDataByID(m_solidCmdId);
        if (!cmd)
        {
            printLog(tr("Invalid input model !"), 3);
            return false;
        }

        // 旧版本对单独体进行操作。
        //@{
        // 获取体形状。
        //@{
        //OCC::FITKOCCTopoShape* vOCCShapeSolid = cmd->getShapeT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSSolid, m_solidVirtualId);
        //if (!vOCCShapeSolid)
        //{
        //    return false;
        //}

        //TopoDS_Solid topoSolid = TopoDS::Solid(vOCCShapeSolid->getTopoShape());
        //if (topoSolid.IsNull())
        //{
        //    return false;
        //}
        //@}
        //@}

        // 新版本对整个模型进行操作。
        //@{
        TopoDS_Shape* shape{ nullptr };
        OCC::FITKAbstractOCCModel* occModel = cmd->getTShapeAgent<OCC::FITKAbstractOCCModel>();
        if (occModel)
        {
            shape = occModel->getShape();
        }
        //@}

        if (!shape)
        {
            return false;
        }

        if (m_dist <= 0)
        {
            return false;
        }

        // 异常处理。
        try
        {
            // 创建倒角。
            //@{
            BRepFilletAPI_MakeChamfer mkChamfer(*shape);

            for (const Interface::VirtualShape & vEdge : m_edgeVirtualTopos)
            {
                OCC::FITKOCCTopoShape* vOCCShapeEdge = cmd->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, vEdge.VirtualTopoIndex);
                if (!vOCCShapeEdge)
                {
                    continue;
                }

                TopoDS_Edge topoEdge = TopoDS::Edge(vOCCShapeEdge->getTopoShape());
                if (topoEdge.IsNull())
                {
                    return false;
                }

                mkChamfer.Add(m_dist, topoEdge);
            }
            //@}

            mkChamfer.Build();
            if (!mkChamfer.IsDone())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            const TopoDS_Shape & output= mkChamfer.Shape();
            if (output.IsNull())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            // 更新形状。
            _occShapeAgent->updateShape(output);
        }
        catch (...)
        {
            printLog(tr("Invalid parameters !"), 3);
            return false;
        }

        return true;
    }
    //@}

    // 倒圆。
    //@{
    FITKOCCModelFilletSolid::FITKOCCModelFilletSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelFilletSolid::update()
    {
        Interface::FITKGeoCommandList* geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        // 获取被倒圆的体模型。
        Interface::FITKAbsGeoCommand* cmd = geoCmdList->getDataByID(m_solidCmdId);
        if (!cmd)
        {
            printLog(tr("Invalid input model !"), 3);
            return false;
        }

        // 新版本对整个模型进行操作。
        //@{
        TopoDS_Shape* shape{ nullptr };
        OCC::FITKAbstractOCCModel* occModel = cmd->getTShapeAgent<OCC::FITKAbstractOCCModel>();
        if (occModel)
        {
            shape = occModel->getShape();
        }
        //@}

        if (m_radius <= 0)
        {
            return false;
        }

        // 异常处理。
        try
        {
            // 创建倒圆。
            //@{
            BRepFilletAPI_MakeFillet mkFillet(*shape);

            for (const Interface::VirtualShape & vEdge : m_edgeVirtualTopos)
            {
                OCC::FITKOCCTopoShape* vOCCShapeEdge = cmd->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSEdge, vEdge.VirtualTopoIndex);
                if (!vOCCShapeEdge)
                {
                    continue;
                }

                TopoDS_Edge topoEdge = TopoDS::Edge(vOCCShapeEdge->getTopoShape());
                if (topoEdge.IsNull())
                {
                    return false;
                }

                mkFillet.Add(m_radius, topoEdge);
            }
            //@}

            mkFillet.Build();
            if (!mkFillet.IsDone())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            const TopoDS_Shape & output = mkFillet.Shape();
            if (output.IsNull())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            // 更新形状。
            _occShapeAgent->updateShape(output);
        }
        catch (...)
        {
            printLog(tr("Invalid parameters !"), 3);
            return false;
        }

        return true;
    }
    //@}

    // 移除特征。
    //@{
    bool FITKOCCDefeatureTool::Defeature(int cmdId, QList<int> faceIndice, TopoDS_Shape & outputShape)
    {
        Interface::FITKGeoCommandList* geoCmdList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();

        // 获取被移除特征的体模型。
        Interface::FITKAbsGeoCommand* cmd = geoCmdList->getDataByID(cmdId);
        if (!cmd)
        {
            return false;
        }

        // 新版本对整个模型进行操作。
        //@{
        TopoDS_Shape* shape{ nullptr };
        OCC::FITKAbstractOCCModel* occModel = cmd->getTShapeAgent<OCC::FITKAbstractOCCModel>();
        if (occModel)
        {
            shape = occModel->getShape();
        }
        //@}

        // 获取面形状。
        //@{
        TopTools_ListOfShape topoFaces;
        for (const int & vFaceIndex : faceIndice)
        {
            OCC::FITKOCCTopoShape* vOCCShapeFace = cmd->getShapeTopoByIndexT<OCC::FITKOCCTopoShape>(Interface::FITKGeoEnum::VTopoShapeType::VSFace, vFaceIndex);
            if (!vOCCShapeFace)
            {
                return false;
            }

            TopoDS_Face topoFace = TopoDS::Face(vOCCShapeFace->getTopoShape());
            if (topoFace.IsNull())
            {
                return false;
            }

            topoFaces.Append(topoFace);
        }
        //@}

        // 移除特征。
        //@{
        try
        {
            BRepAlgoAPI_Defeaturing mkFillHole;
            mkFillHole.SetRunParallel(true);
            mkFillHole.SetToFillHistory(false);
            mkFillHole.SetShape(*shape);
            mkFillHole.AddFacesToRemove(topoFaces);
            mkFillHole.Build();

            if (!mkFillHole.IsDone())
            {
                return false;
            }

            outputShape = mkFillHole.Shape();
        }
        catch (...)
        {
            return false;
        }
        //@}

        return true;
    }
    //@}

    // 移除特征。
    //@{
    FITKOCCModelDefeatureSolid::FITKOCCModelDefeatureSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelDefeatureSolid::update()
    {
        QList<int> faceIndice;
        for (const Interface::VirtualShape & vFace : m_faceVirtualTopos)
        {
            faceIndice.push_back(vFace.VirtualTopoIndex);
        }

        // 移除特征。
        TopoDS_Shape outputShape;
        bool flag = FITKOCCDefeatureTool::Defeature(m_solidCmdId, faceIndice, outputShape);
        if (!flag)
        {
            printLog(tr("Invalid feature !"), 3);
            return false;
        }

        // 更新形状。
        _occShapeAgent->updateShape(outputShape);

        return true;
    }
    //@}

    // 移除倒角。
    //@{
    FITKOCCModelRemoveChamferSolid::FITKOCCModelRemoveChamferSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelRemoveChamferSolid::update()
    {
        QList<int> faceIndice;
        for (const Interface::VirtualShape & vFace : m_faceVirtualTopos)
        {
            faceIndice.push_back(vFace.VirtualTopoIndex);
        }

        // 移除特征。
        TopoDS_Shape outputShape;
        bool flag = FITKOCCDefeatureTool::Defeature(m_solidCmdId, faceIndice, outputShape);
        if (!flag)
        {
            printLog(tr("Invalid feature !"), 3);
            return false;
        }

        // 更新形状。
        _occShapeAgent->updateShape(outputShape);

        return true;
    }
    //@}

    // 移除倒圆。
    //@{
    FITKOCCModelRemoveFilletSolid::FITKOCCModelRemoveFilletSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelRemoveFilletSolid::update()
    {
        QList<int> faceIndice;
        for (const Interface::VirtualShape & vFace : m_faceVirtualTopos)
        {
            faceIndice.push_back(vFace.VirtualTopoIndex);
        }

        // 移除特征。
        TopoDS_Shape outputShape;
        bool flag = FITKOCCDefeatureTool::Defeature(m_solidCmdId, faceIndice, outputShape);
        if (!flag)
        {
            printLog(tr("Invalid feature !"), 3);
            return false;
        }

        // 更新形状。
        _occShapeAgent->updateShape(outputShape);

        return true;
    }
    //@}

    // 填补孔洞。
    //@{
    FITKOCCModelFillHoleSolid::FITKOCCModelFillHoleSolid() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelFillHoleSolid::update()
    {
        QList<int> faceIndice;
        for (const Interface::VirtualShape & vFace : m_faceVirtualTopos)
        {
            faceIndice.push_back(vFace.VirtualTopoIndex);
        }

        // 移除特征。
        TopoDS_Shape outputShape;
        bool flag = FITKOCCDefeatureTool::Defeature(m_solidCmdId, faceIndice, outputShape);
        if (!flag)
        {
            printLog(tr("Invalid feature !"), 3);
            return false;
        }

        // 更新形状。
        _occShapeAgent->updateShape(outputShape);

        return true;
    }
    //@}
}
