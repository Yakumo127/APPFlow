#include "FITKMeshFeatureVTK.h"

// VTK
#include <vtkPolyData.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkAlgorithmOutput.h>
#include <vtkIdFilter.h>
#include <vtkPassThrough.h>

// 过滤器
#include "FITK_Interface/FITKVTKAlgorithm/FITKSurfaceFilter.h"
#include "FITK_Interface/FITKVTKAlgorithm/FITKShellFeatureEdges.h"
#include "FITK_Interface/FITKVTKAlgorithm/FITKPolyDataNormals.h"
#include "FITK_Interface/FITKVTKAlgorithm/FITKHighOrderCellFilter.h"

namespace Interface
{
    const char* FITKMeshFeatureVTK::GetPointIdArrayName()
    {
        return "PointIds";
    }

    const char* FITKMeshFeatureVTK::GetCellIdArrayName()
    {
        return "CellIds";
    }

    const char* FITKMeshFeatureVTK::GetFeatEdgeOriginalIdArrayName()
    {
        return "OriIds";
    }

    FITKMeshFeatureVTK::FITKMeshFeatureVTK(vtkDataSet* dataSet)
    {
        //  初始化管线。
        initialize();

        _passThrough->SetInputData(dataSet);
    }

    FITKMeshFeatureVTK::FITKMeshFeatureVTK(vtkAlgorithmOutput* connection)
    {
        //  初始化管线。
        initialize();

        _passThrough->SetInputConnection(connection);
    }

    FITKMeshFeatureVTK::~FITKMeshFeatureVTK()
    {
        // 手动删除所有过滤器。
        //@{
        deleteVtkObj(_highOrderFilter);
        deleteVtkObj(_normalFilter);
        deleteVtkObj(_featureEdgeFilter);
        deleteVtkObj(_edgeFilter);
        deleteVtkObj(_surfaceFilter);
        deleteVtkObj(_idFilter);
        deleteVtkObj(_passThrough);
        //@}
    }

    void FITKMeshFeatureVTK::initialize()
    {
        // 初始化。
        //@{
        // 输入传递过滤器。
        _passThrough = vtkPassThrough::New();

        // 添加单元与节点ID。
        _idFilter = vtkIdFilter::New();
        _idFilter->SetInputConnection(_passThrough->GetOutputPort());
        _idFilter->SetCellIds(true);
        _idFilter->SetPointIds(true);
        _idFilter->SetPointIdsArrayName(GetPointIdArrayName());
        _idFilter->SetCellIdsArrayName(GetCellIdArrayName());
        _idFilter->SetFieldData(true);

        // 提取表面数据过滤器。
        _surfaceFilter = FITKSurfaceFilter::New();
        _surfaceFilter->SetInputConnection(_idFilter->GetOutputPort());

        // 保存单元与原数据拓扑对应关系必须设置为true。
        _surfaceFilter->SetPassThroughPointIds(true);

        // 处理高阶单元数据时必须设置为true。
        _surfaceFilter->SetPassThroughCellIds(true);

        // 高阶单元划分级为0才能正常显示。
        _surfaceFilter->SetNonlinearSubdivisionLevel(0);

        // 法向提取过滤器。
        _normalFilter = FITKPolyDataNormals::New();
        _normalFilter->SetInputConnection(_surfaceFilter->GetOutputPort());
        _normalFilter->SetComputeCellNormals(true);
        _normalFilter->SetComputePointNormals(false);

        // 特征边提取过滤器。
        _featureEdgeFilter = FITKShellFeatureEdges::New();
        _featureEdgeFilter->SetInputConnection(_surfaceFilter->GetOutputPort());
        _featureEdgeFilter->BoundaryEdgesOn();
        _featureEdgeFilter->FeatureEdgesOn();

        // 网格边提取过滤器。
        _edgeFilter = FITKShellFeatureEdges::New();
        _edgeFilter->SetInputConnection(_surfaceFilter->GetOutputPort());
        _edgeFilter->BoundaryEdgesOff();
        _edgeFilter->FeatureEdgesOff();
        _edgeFilter->NonManifoldEdgesOn();
        _edgeFilter->ManifoldEdgesOn();

        // 处理高阶单元过滤器。
        _highOrderFilter = FITKHighOrderCellFilter::New();

        // 需要用到提取表面时生成的原始单元id数据，
        // 默认array名称为表面提取生成的默认名称vtkOriginalCellIds。
        _highOrderFilter->SetInputConnection(_surfaceFilter->GetOutputPort());
        //@}
    }

    void FITKMeshFeatureVTK::update()
    {        
        // 更新数据，提取表面用来提取法向与特征边等。
        //@{
        if (_dataSet)
        {
            _passThrough->SetInputData(_dataSet);
        }

        if (_connection)
        {
            _passThrough->SetInputConnection(_connection);
        }

        _passThrough->Update();
        _idFilter->Update();
        _surfaceFilter->Update();
        //@}

        // 更新法线、特征边。
        //@{
        _normalFilter->Update();
        _featureEdgeFilter->Update();
        //@}|

        // 处理高阶单元，此处生成的为实际可视化的表面数据。
        //@{
        _highOrderFilter->Update();
        //@}

        if (_dataSet)
        {
            _dataSet->Modified();
        }

        if (_connection)
        {
            _connection->Modified();
        }
    }

    void FITKMeshFeatureVTK::reset(vtkDataSet* dataSet)
    {
        _dataSet = dataSet;
        _connection = nullptr;
        _idFilter->SetInputData(_dataSet);

        update();
    }

    void FITKMeshFeatureVTK::reset(vtkAlgorithmOutput* connection)
    {
        _dataSet = nullptr;
        _connection = connection;
        _idFilter->SetInputConnection(_connection);

        update();
    }

    void FITKMeshFeatureVTK::setCellAndPointIdsEnable(bool pointIdsOn, bool cellIdsOn)
    {
        if (!_idFilter)
        {
            return;
        }

        _idFilter->SetPointIds(pointIdsOn);
        _idFilter->SetCellIds(cellIdsOn);
    }

    vtkPassThrough* FITKMeshFeatureVTK::getMeshPassThrough()
    {
        return _passThrough;
    }

    vtkIdFilter* FITKMeshFeatureVTK::getIdFilter()
    {
        return _idFilter;
    }

    FITKSurfaceFilter* FITKMeshFeatureVTK::getSurfaceFilter()
    {
        return _surfaceFilter;
    }

    FITKShellFeatureEdges* FITKMeshFeatureVTK::getFeatureEdgeFilter()
    {
        return _featureEdgeFilter;
    }

    FITKShellFeatureEdges* FITKMeshFeatureVTK::getShellEdgeFilter()
    {
        return _edgeFilter;
    }

    FITKHighOrderCellFilter* FITKMeshFeatureVTK::getHighOrderFilter()
    {
        return _highOrderFilter;
    }

    FITKPolyDataNormals* FITKMeshFeatureVTK::getNormalsFilter()
    {
        return _normalFilter;
    }

    vtkPolyData* FITKMeshFeatureVTK::getFeatureMesh(int type)
    {
        // 1 - 表面 2 - 法向 3 - 特征边 4 - 网格边
        switch (type)
        {
        case 1: 
            _highOrderFilter->Update();
            return _highOrderFilter->GetOutput();
        case 2: 
            _normalFilter->Update();
            return _normalFilter->GetOutput();
        case 3: 
            _featureEdgeFilter->Update();
            return _featureEdgeFilter->GetOutput();
        case 4:
            _edgeFilter->Update();
            return _edgeFilter->GetOutput();
        default: return nullptr;
        }

        return nullptr;
    }

    vtkDataArray* FITKMeshFeatureVTK::getCellNormals()
    {
        vtkPolyData* normalMesh = getFeatureMesh(2);
        if (!normalMesh)
        {
            return nullptr;
        }
            
        vtkCellData* cellData = normalMesh->GetCellData();
        if (!cellData)
        {
            return nullptr;
        }

        return cellData->GetNormals();
    }
}
