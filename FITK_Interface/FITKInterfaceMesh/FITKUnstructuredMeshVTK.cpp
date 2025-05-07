#include "FITKUnstructuredMeshVTK.h"
#include "FITKMeshFeatureVTK.h"
#include "FITKMeshVTKMap.h"
#include "FITK_Kernel/FITKCore/FITKVec3D.h"

// VTK
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkPoints.h>
#include <vtkPointData.h>
#include <vtkCellData.h>

// For VTK 7
//@{
#include <vtkSmartPointer.h>
#include <vtkIdList.h>
#include <vtkCell.h>
#include <vtkCellType.h>
//@}

#include "FITKInterfaceModel/FITKAbstractElement.h"
#include "FITKInterfaceModel/FITKElementFactory.h"
#include "FITKInterfaceModel/FITKElementHex.h"
#include "FITKInterfaceModel/FITKElementQuad.h"
#include "FITKInterfaceModel/FITKElementTet.h"
#include "FITKInterfaceModel/FITKElementTri.h"

#include <QHash>
#include <QColor>

namespace Interface
{


    FITKUnstructuredMeshVTK::FITKUnstructuredMeshVTK()
    {
        //创建VTK的网格对象
        _vtkDataSet = vtkUnstructuredGrid::New();
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        _vtkDataSet->SetPoints(points);

        _feature = new FITKMeshFeatureVTK(_vtkDataSet);
    }

    FITKUnstructuredMeshVTK::~FITKUnstructuredMeshVTK()
    {
        // 移除特征数据。
        //@{
        if (_feature)
        {
            delete _feature;
            _feature = nullptr;
        }
        //@}

        //内存回收
        if (_vtkDataSet != nullptr)
            _vtkDataSet->Delete();
    }

    FITKModelEnum::AbsModelType FITKUnstructuredMeshVTK::getAbsModelType()
    {
        return FITKModelEnum::AbsModelType::AMTunstructuredMeshvtk;
    }

    void FITKUnstructuredMeshVTK::update()
    {
        if (!_modified) return;

        _vtkDataSet->Modified();

        if (_feature)
            _feature->update();

        _modified = false;
    }

    const QList<int> FITKUnstructuredMeshVTK::getCellIndiceByDim(int dim)
    {
        QList<int> indice;
        if (dim < 0 || dim > 3)
        {
            return indice;
        }

        for (int i = 0 ; i < _elementList.count() ; i ++)
        {
            FITKAbstractElement* element = _elementList[i];
            if (dim == element->getElementDim())
            {
                indice.push_back(i);
            }
        }

        return indice;
    }

    int FITKUnstructuredMeshVTK::addNode(const double x, const double y, const double z)
    {
        //追加节点，vtk中的节点顺序与节点列表一致
        int id = FITKNodeList::addNode(x, y, z);

        vtkPoints* points = _vtkDataSet->GetPoints();
        if (points == nullptr) return -1;
        points->InsertNextPoint(x, y, z);
        _modified = true;

        return id;
    }


    void FITKUnstructuredMeshVTK::addNode(const int id, const double x, const double y, const double z)
    {
        //追加节点，vtk中的节点顺序与节点列表一致
        FITKNodeList::addNode(id, x, y, z);
        vtkPoints* points = _vtkDataSet->GetPoints();
        if (points == nullptr) return;
        points->InsertNextPoint(x, y, z);
        _modified = true;
    }

    void FITKUnstructuredMeshVTK::appendElement(FITKAbstractElement* element)
    {
        if (element == nullptr) return;
        Interface::FITKModelEnum::FITKEleType type = element->getEleType();
        if (!eleTypeHash.contains(type)) return;
        //追加到单元中
        FITKElementList::appendElement(element);

        int count = element->getNodeCount();
        vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
        for (int i = 0; i < count; ++i)
        {
            //查找节点索引
            const int nodeID = element->getNodeID(i);
            const int index = this->getNodeIndexByID(nodeID);
            idList->InsertNextId(index);
        }
        _vtkDataSet->InsertNextCell(eleTypeHash[type], idList);
        _modified = true;
    }

    bool FITKUnstructuredMeshVTK::writeToFile(const QString & file)
    {
        //写出文件
        vtkSmartPointer<vtkUnstructuredGridWriter> writer = vtkSmartPointer<vtkUnstructuredGridWriter>::New();
        writer->SetFileName(file.toStdString().c_str());
        writer->SetFileTypeToASCII();
        // writer->SetFileTypeToBinary();
        writer->SetInputData(_vtkDataSet);
        writer->Write();
        return true;
    }

    void FITKUnstructuredMeshVTK::reverseEleByID(const int id)
    {
        const int index = getEleIndexByID(id);
        this->reverseEleByIndex(index);
    }

    void FITKUnstructuredMeshVTK::reverseEleByIndex(const int index)
    {
        FITKUnstructuredMesh::reverseEleByIndex(index);

        auto cell = _vtkDataSet->GetCell(index);

        if (cell == nullptr) return;
        auto points = cell->GetPointIds();
        if (points == nullptr) return;
        //交换首尾节点编号
        const int np = points->GetNumberOfIds();

        vtkIdType* pts = new vtkIdType[np];

        for (int i = 0; i < np / 2; ++i)
        {
            int p1 = points->GetId(i);
            int p2 = points->GetId(np - 1 - i);

            pts[i] = p2;
            pts[np - 1 - i] = p1;
        }

        // 替换单元。
        _vtkDataSet->ReplaceCell(index, np, pts);

        // 已经过测试可删除。
        delete pts;

        _modified = true;
    }

    FITKMeshFeatureVTK* FITKUnstructuredMeshVTK::getMeshFeature()
    {
        return _feature;
    }

    vtkUnstructuredGrid* FITKUnstructuredMeshVTK::getGrid()
    {
        return _vtkDataSet;
    }

    bool FITKUnstructuredMeshVTK::getBounds(double bds6[6])
    {
        if (!_vtkDataSet)
        {
            return false;
        }

        if (_vtkDataSet->GetNumberOfCells() == 0 &&
            _vtkDataSet->GetNumberOfPoints() == 0)
        {
            return false;
        }

        double* bds = _vtkDataSet->GetBounds();
        for (int i = 0; i < 6; i++)
        {
            bds6[i] = bds[i];
        }

        return true;
    }

    int FITKUnstructuredMeshVTK::getNumberOfCells()
    {
        if (!_vtkDataSet)
            return 0;

        return _vtkDataSet->GetNumberOfCells();
    }

    void FITKUnstructuredMeshVTK::reConstructure()
    {
        // 重置网格数据，重新构建。
        _vtkDataSet->Reset();
        vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();
        _vtkDataSet->SetPoints(points);

        double pos3[3]{ 0., 0., 0. };
        for (Core::FITKNode* node : _nodeList)
        {
            node->getCoor(pos3);
            points->InsertNextPoint(pos3);
        }

        for (FITKAbstractElement* element : _elementList)
        {
            int count = element->getNodeCount();
            vtkSmartPointer<vtkIdList> idList = vtkSmartPointer<vtkIdList>::New();
            for (int i = 0; i < count; ++i)
            {
                //查找节点索引
                const int nodeID = element->getNodeID(i);
                const int index = this->getNodeIndexByID(nodeID);
                idList->InsertNextId(index);
            }

            Interface::FITKModelEnum::FITKEleType type = element->getEleType();
            _vtkDataSet->InsertNextCell(eleTypeHash[type], idList);
        }
    }


    void FITKUnstructuredMeshVTK::transformVTKMesh(vtkUnstructuredGrid* grid)
    {
        if (grid == nullptr) return;
        this->removeAllNode();
        this->removeAllElement();
        _vtkDataSet->DeepCopy(grid);
        //复制节点 
        const int npt = _vtkDataSet->GetNumberOfPoints();
        for (int i = 0; i < npt; ++i)
        {
            double coor[3] = { 0,0,0 };
            _vtkDataSet->GetPoint(i, coor);
            FITKNodeList::addNode(coor[0], coor[1], coor[2]);
        }
        //复制单元 
        const int ncell = _vtkDataSet->GetNumberOfCells();
        for (int i = 0; i < ncell; ++i)
        {
            vtkCell* cell = _vtkDataSet->GetCell(i);
            if (cell == nullptr) continue;
            int cT = cell->GetCellType();
            //查询单元类型
            Interface::FITKModelEnum::FITKEleType t = eleTypeHash.key(cT);
            FITKAbstractElement* ele = FITKElementFactory::createElement(t);
            if (ele == nullptr) continue;
            //单元节点
            QList<int> cellID{};
            const int ncellPt = cell->GetNumberOfPoints();
            for (int cpt = 0; cpt < ncellPt; ++cpt)
            {
                int nodeid = cell->GetPointId(cpt);
                cellID.append(nodeid + 1);
            }
            ele->setNodeID(cellID);
        }
    }

    void FITKUnstructuredMeshVTK::clearMesh()
    {
        this->removeAllNode();
        this->removeAllElement();

        _vtkDataSet->GetPoints()->Reset();

        int nPtArrs = _vtkDataSet->GetPointData()->GetNumberOfArrays();
        int nCellArrs = _vtkDataSet->GetCellData()->GetNumberOfArrays();

        // 移除节点数组。
        for (int i = nPtArrs - 1; i >= 0; i--)
        {
            _vtkDataSet->GetPointData()->RemoveArray(i);
        }

        // 移除单元数组。
        for (int i = nCellArrs - 1; i >= 0; i--)
        {
            _vtkDataSet->GetCellData()->RemoveArray(i);
        }

        _vtkDataSet->Reset();
    }

    void FITKUnstructuredMeshVTK::clearNativeMesh()
    {
        // 清空VTK数据。
        _vtkDataSet->GetPoints()->Reset();
        _vtkDataSet->Reset();

        int nPtArrs = _vtkDataSet->GetPointData()->GetNumberOfArrays();
        int nCellArrs = _vtkDataSet->GetCellData()->GetNumberOfArrays();

        // 移除节点数组。
        for (int i = nPtArrs - 1; i >= 0; i--)
        {
            _vtkDataSet->GetPointData()->RemoveArray(i);
        }

        // 移除单元数组。
        for (int i = nCellArrs - 1; i >= 0; i--)
        {
            _vtkDataSet->GetCellData()->RemoveArray(i);
        }

        // 移除抽象层网格数据。
        int nPoints = this->getNodeCount();
        int nEles = this->getElementCount();

        // 节点移除标记，按照节点ID最大值开出数组。
        QVector<bool> nodeFlags(nPoints);
        nodeFlags.fill(false);

        for (int i = nEles - 1; i >= 0; i--)
        {
            FITKAbstractElement* element = this->getElementAt(i);
            unsigned int eTag = element->getTag();
            if (eTag != 0)
            {
                int nEleNode = element->getNodeCount();
                for (int j = 0; j < nEleNode; j++)
                {
                    int nId = element->getNodeID(j);
                    int iNode = this->getNodeIndexByID(nId);
                    nodeFlags[iNode] = true;
                }

                this->fastRemoveElementAt(i);
            }
        }

        for (int i = nPoints - 1; i >= 0; i--)
        {
            if (!nodeFlags[i])
            {
                continue;
            }

            // 循环索引为节点索引。
            this->fastRemoveNodeAt(i);
        }

        // 重新构建ID索引映射。
        this->updateNodeIDIndexMap();
        this->updateElementIDIndexMap();

        // 重建VTK数据。
        reConstructure();
        update();
    }

    void FITKUnstructuredMeshVTK::replaceNodesID(const QHash<int, int> & nodes)
    {
        FITKElementList::replaceNodesID(nodes);
        //重置单元
        this->reConstructure();
        this->update();
    }

}
