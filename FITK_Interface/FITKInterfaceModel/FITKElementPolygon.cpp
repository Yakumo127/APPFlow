#include "FITKElementPolygon.h"

namespace Interface
{
    FITKModelEnum::FITKEleType FITKElementPolygon::getEleType()
    {
        return FITKModelEnum::FITKEleType::Polygon;
    }

    void FITKElementPolygon::setNodeCount(const int c)
    {
        FITKAbstractElement::setNodeCount(c);
    }


    int FITKElementPolygon::getNodeCount()
    {
        return _elemenTopo.size();
    }

    int FITKElementPolygon::getFaceCount()
    {
        return 1;
    }

    int FITKElementPolygon::getElementDim()
    {
        return 2;
    }

    int FITKElementPolygon::getEdgeCount()
    {
        return _elemenTopo.size();
    }

    QList<int> FITKElementPolygon::getFace(const int index)
    {
        return _elemenTopo;
    }

    QList<int> FITKElementPolygon::getEdge(const int index)
    {
        const int np = _elemenTopo.size();
        QList<int> edge;
        edge << index % np << (index + 1) % np;
        return edge;
    }

}


