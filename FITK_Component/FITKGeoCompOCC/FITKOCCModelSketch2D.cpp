#include "FITKOCCModelSketch2D.h"

// OCC
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopExp_Explorer.hxx>

namespace OCC
{
    FITKOCCModelSketch2D::FITKOCCModelSketch2D() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelSketch2D::update()
    {
        if (!_occShapeAgent)
        {
            return false;
        }

        // 初始化组合对象。
        BRep_Builder builder;
        TopoDS_Compound compound;
        builder.MakeCompound(compound);

        // 合并所有子数据。
        int nSubCmds = this->getDataCount();
        for (int i = 0; i < nSubCmds; i++)
        {
            Interface::FITKAbsGeoCommand* subModel = this->getDataByIndex(i);
            if (!subModel)
            {
                continue;
            }

            // 更新子数据。
            //subModel->update();

            // 获取形状代理器。
            FITKAbstractOCCModel* occSubModel = dynamic_cast<FITKAbstractOCCModel*>(subModel->getShapeAgent());
            if (!occSubModel)
            {
                continue;
            }

            // 获取OCC形状。
            TopoDS_Shape* subTopoShape = occSubModel->getShape();
            if (!subTopoShape)
            {
                continue;
            }

            // 检查形状数据。
            if (subTopoShape->IsNull())
            {
                continue;
            }

            // 组合形状。
            builder.Add(compound, *subTopoShape);
        }

        // 更新形状数据。
        if (nSubCmds == 0)
        {
            _occShapeAgent->updateShape(TopoDS_Shape());
        }
        else
        {
            _occShapeAgent->updateShape(compound);
        }

        return true;
    }

    bool FITKOCCModelSketch2D::isClosed()
    {
        BRepBuilderAPI_MakeWire mkWire;

        // 合并所有子数据。
        for (int i = 0; i < this->getDataCount(); i++)
        {
            Interface::FITKAbsGeoCommand* subModel = this->getDataByIndex(i);
            if (!subModel)
            {
                continue;
            }

            // 获取形状代理器。
            FITKAbstractOCCModel* occSubModel = dynamic_cast<FITKAbstractOCCModel*>(subModel->getShapeAgent());
            if (!occSubModel)
            {
                continue;
            }

            // 获取OCC形状。
            TopoDS_Shape* subTopoShape = occSubModel->getShape();
            if (!subTopoShape)
            {
                continue;
            }

            // 检查形状数据。
            if (subTopoShape->IsNull())
            {
                continue;
            }
            
            // 检查是否存在非线与线框数据。
            if (subTopoShape->ShapeType() != TopAbs_ShapeEnum::TopAbs_EDGE &&
                subTopoShape->ShapeType() != TopAbs_ShapeEnum::TopAbs_WIRE)
            {
                return false;
            }

            TopExp_Explorer exp(*subTopoShape, TopAbs_ShapeEnum::TopAbs_EDGE);
            while (exp.More())
            {
                TopoDS_Edge edge = TopoDS::Edge(exp.Current());
                if (edge.IsNull())
                {
                    return false;
                }

                // 组合形状。
                mkWire.Add(edge);

                exp.Next();
            }
        }
        
        const TopoDS_Shape & wire = mkWire.Shape();
        if (wire.IsNull() || !wire.Closed())
        {
            return false;
        }

        return true;
    }
}
