#include "FITKOCCModelPart.h"

// OCC
#include <TopoDS_Shape.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepBuilderAPI_Copy.hxx>

namespace OCC
{
    FITKOCCModelPart::FITKOCCModelPart() : OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    TopoDS_Shape* FITKOCCModelPart::getPartShape()
    {
        if (!_occShapeAgent)
        {
            return nullptr;
        }

        return _occShapeAgent->getShape();
    }

    TopoDS_Shape FITKOCCModelPart::getCopiedPartShape()
    {
        TopoDS_Shape* partShape = getPartShape();
        if (!partShape)
        {
            return TopoDS_Shape();
        }

        // 拷贝形状。
        BRepBuilderAPI_Copy copy(*partShape);
        return copy.Shape();
    }

    void FITKOCCModelPart::updatePartShape(TopoDS_Shape & shape, bool unite)
    {
        if (!_occShapeAgent)
        {
            return;
        }

        TopoDS_Shape* orgShape = _occShapeAgent->getShape();

        // 求和。
        if (unite && orgShape)
        {
            BRepAlgoAPI_Fuse fuse(shape, *orgShape);
            _occShapeAgent->updateShape(fuse.Shape());
        }
        // 替换形状。
        else
        {
            _occShapeAgent->updateShape(shape);
        }
    }

    bool FITKOCCModelPart::backtrackingShape()
    {
        // 获取最后一条几何命令的形状。
        Interface::FITKAbsGeoCommand* lastCmd = this->getDataByIndex(this->getDataCount() - 1);

        // 不存在命令则重置为空形状。
        if (!lastCmd)
        {
            _occShapeAgent->updateShape(TopoDS_Shape());
            return true;
        }

        // 否则取出当前最后命令维护的形状刷新拓扑。
        FITKAbstractOCCModel* occModel = lastCmd->getTShapeAgent<FITKAbstractOCCModel>();
        if (!occModel)
        {
            _occShapeAgent->updateShape(TopoDS_Shape());
            return true;
        }

        _occShapeAgent->updateShape(*occModel->getShape());
        return true;
    }

    bool FITKOCCModelPart::update()
    {
        if (!_occShapeAgent)
        {
            return false;
        }

        // 重构虚拓扑。
        _occShapeAgent->buildVirtualTopo();
        _occShapeAgent->triangulation();
        return true;
    }

    void FITKOCCModelPart::appendDataObj(Core::FITKAbstractDataObject* obj)
    {
        Interface::FITKAbsGeoCommand* subCmd = dynamic_cast<Interface::FITKAbsGeoCommand*>(obj);
        if (!subCmd)
        {
            return;
        }

        // 类型转换，获取子数据形状代理器。
        FITKAbstractOCCModel* shapeAgentNew = subCmd->getTShapeAgent<FITKAbstractOCCModel>();
        if (!shapeAgentNew)
        {
            return;
        }

        // 同步第一条子命令形状。
        if (this->getDataCount() == 0)
        {
            updatePartShape(*shapeAgentNew->getShape());
        }

        Interface::FITKAbsGeoPart::appendDataObj(subCmd);

        // 设置部件。
        shapeAgentNew->setPart(this);
    }
}