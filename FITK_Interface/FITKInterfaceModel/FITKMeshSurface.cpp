#include "FITKMeshSurface.h"
#include "FITKModelSet.h"
#include "FITKAbstractModel.h"
#include "FITK_Kernel/FITKCore/FITKDataRepo.h"


namespace Interface
{
    FITKMeshSurface::~FITKMeshSurface()
    {
    }

    FITKMeshSurface::MeshSurfaceType FITKMeshSurface::getMeshSurfaceType()
    {
        //错误值
        return FITKMeshSurface::SurNone;
    }
    bool FITKMeshSurface::isInternal() const
    {
        return _internal;
    }

    void FITKMeshSurface::isInternal(bool internal)
    {
        _internal = internal;
    }

    int FITKMeshSurface::getMeshSetCount() const
    {
        //集合长度
        return _modelSetIDs.size();
    }
    Interface::FITKModelSet* FITKMeshSurface::getMeshSetAt(const int index) const
    {
        //错误判断
        if (index < 0 || index >= _modelSetIDs.size()) return nullptr;
        const int id = _modelSetIDs.at(index).second;
        //类型转换
        return FITKDATAREPO->getTDataByID<Interface::FITKModelSet>(id);

    }

    FITKAbstractModel* FITKMeshSurface::getModelAt(const int index) const
    {
        if (index < 0 || index >= _modelSetIDs.size()) return nullptr;
        const int id = _modelSetIDs.at(index).first;
        //类型转换
        FITKAbstractModel* model = FITKDATAREPO->getTDataByID<Interface::FITKAbstractModel>(id);
        if (model == nullptr)
        {
            auto set = this->getMeshSetAt(index);
            if (set)
                model = set->getAbstractModel();
        }
        return model;
    }

    QList<Interface::SurfaceAbsSetInfo> FITKMeshSurface::getAbsoluteSetInfo()
    {
        return QList<Interface::SurfaceAbsSetInfo>();
    }

    int FITKMeshSurface::indexOf(int modelID, int setID)
    {
        QPair<int,int> p(modelID, setID);
        return _modelSetIDs.indexOf(p);

    }

}
