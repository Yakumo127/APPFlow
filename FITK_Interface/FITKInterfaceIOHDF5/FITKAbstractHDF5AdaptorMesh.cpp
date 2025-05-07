#include "FITKAbstractHDF5AdaptorMesh.h"

namespace IO
{

    QString FITKAbstractHDF5AdaptorMesh::getAdaptorClass()
    {
        return QString();
    }

    bool FITKAbstractHDF5AdaptorMesh::adaptR()
    {
        return false;
    }

    bool FITKAbstractHDF5AdaptorMesh::adaptW()
    {
        return false;
    }

}
