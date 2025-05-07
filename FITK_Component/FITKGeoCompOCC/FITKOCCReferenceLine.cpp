#include "FITKOCCReferenceLine.h"
#include <BRepBuilderAPI_MakeEdge.hxx>

namespace OCC {
    FITKOCCReferenceLine::FITKOCCReferenceLine() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }
    bool FITKOCCReferenceLine::update()
    {
        try
        {
            BRepBuilderAPI_MakeEdge edge(gp_Pnt(m_pos[0], m_pos[1], m_pos[2]), gp_Pnt(m_pos2[0], m_pos2[1], m_pos2[2]));
            _occShapeAgent->updateShape(edge);
            return true;
        }
        catch (...)
        {
            printLog(tr("Failed to make line."), 3);
            return false;
        }
    }

    Interface::FITKGeoEnum::FITKDatumType FITKOCCReferenceLine::getDatumType()
    {
        return Interface::FITKGeoEnum::FITKDatumType::FDTLine;
    }

}
