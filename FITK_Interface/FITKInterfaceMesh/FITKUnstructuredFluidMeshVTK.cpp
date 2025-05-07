#include "FITKUnstructuredFluidMeshVTK.h"
#include "FITKUnstructuredMeshVTK.h"
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractElement.h"
#include "FITKMeshVTKMap.h"
#include <vtkUnstructuredGrid.h>

namespace Interface
{
    FITKUnstructuredFluidMeshVTK::FITKUnstructuredFluidMeshVTK()
    {
        //对象创建
        _fieldMesh = new FITKUnstructuredMeshVTK;
        _boundaryMeshManager = new FITKBoundaryMeshVTKManager;
    }

    FITKUnstructuredFluidMeshVTK::~FITKUnstructuredFluidMeshVTK()
    {
        //释放对象
        if (_fieldMesh) delete _fieldMesh;
        if (_boundaryMeshManager) delete _boundaryMeshManager;
    }

    FITKUnstructuredMeshVTK* FITKUnstructuredFluidMeshVTK::getFieldMesh()
    {
        return _fieldMesh;
    }

    FITKBoundaryMeshVTKManager* FITKUnstructuredFluidMeshVTK::getBoundaryMeshManager()
    {
        return _boundaryMeshManager;
    }



    void FITKUnstructuredFluidMeshVTK::clearMesh()
    {
        if (_boundaryMeshManager)
            _boundaryMeshManager->clear();
        if (_fieldMesh)
            _fieldMesh->clearMesh();
    }

    FITKBoundaryMeshVTK::FITKBoundaryMeshVTK(FITKUnstructuredMeshVTK* fieldmesh)
        :_fieldMesh(fieldmesh)
    {
        //获取节点
        _vtkDataSet = vtkUnstructuredGrid::New();
        if (_fieldMesh == nullptr) return;
        vtkUnstructuredGrid* fg = _fieldMesh->getGrid();
        if (fg == nullptr) return;
        //节点共用
        _vtkDataSet->SetPoints(fg->GetPoints());
    }

    void FITKBoundaryMeshVTK::appendElement(FITKAbstractElement* element)
    {
        if (element == nullptr || _fieldMesh == nullptr) return;
        Interface::FITKModelEnum::FITKEleType type = element->getEleType();
        if (!eleTypeHash.contains(type)) return;
        //追加到单元中
        FITKElementList::appendElement(element);

        int count = element->getNodeCount();
        vtkIdList* idList = vtkIdList::New();
        for (int i = 0; i < count; ++i)
        {
            //查找节点索引
            const int nodeID = element->getNodeID(i);
            const int index = _fieldMesh->getNodeIndexByID(nodeID);
            idList->InsertNextId(index);
        }
        _vtkDataSet->InsertNextCell(eleTypeHash[type], idList);
    }

    vtkUnstructuredGrid* FITKBoundaryMeshVTK::getGrid()
    {
        return _vtkDataSet;
    }

    FITKBoundaryMeshVTK::~FITKBoundaryMeshVTK()
    {
        if (_vtkDataSet != nullptr) _vtkDataSet->Delete();
    }

}


