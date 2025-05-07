#include "FITKFlowOFHDF5AdaptorMesh.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredFluidMeshVTK.h"
#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredMeshVTK.h"

#include "FITK_Kernel/FITKCore/FITKVec3D.h"
#include "FITK_Interface/FITKInterfaceModel/FITKElementFactory.h"
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractElement.h"
#include "FITK_Interface/FITKInterfaceModel/FITKComponentManager.h"
#include "FITK_Interface/FITKInterfaceModel/FITKUnstructuredMesh.h"
#include "FITK_Interface/FITKInterfaceModel/FITKElementPolygon.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"

//数据层
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"

#include <array>
#include <QSet>
#include <QList>
#include <QMultiHash>

#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorMesh::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorMesh";
    }

    bool FITKFlowOFHDF5AdaptorMesh::adaptR()
    {
        _unstructuredMesh = dynamic_cast<Interface::FITKUnstructuredFluidMeshVTK*>(_dataObj);
        if (!_reader || !_unstructuredMesh) return false;
        if (!readNDataObject(_unstructuredMesh, *_h5Group)) return false;
        bool isR = true;

        isR &= fieldMeshR();
        isR &= boundaryMeshR();

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorMesh::adaptW()
    {
        _unstructuredMesh = dynamic_cast<Interface::FITKUnstructuredFluidMeshVTK*>(_dataObj);
        if (!_writer || !_unstructuredMesh) return false;
        if (!writeNDataObject(_unstructuredMesh, *_h5Group)) return false;
        bool isW = true;
        
        isW &= fieldMeshW();
        isW &= boundaryMeshW();

        return isW;
    }

    bool FITKFlowOFHDF5AdaptorMesh::fieldMeshW()
    {
        if (!_writer || !_unstructuredMesh)return false;
        H5::Group h5Group = _h5Group->createGroup("FieldMesh");
        Interface::FITKUnstructuredMeshVTK* fieldMesh = _unstructuredMesh->getFieldMesh();
        if (!fieldMesh)return false;
        writeNDataObject(fieldMesh, h5Group);
        H5::Group nodeH5Group = h5Group.createGroup("Node");
        writeNode(fieldMesh, nodeH5Group);
        H5::Group elementH5Group = h5Group.createGroup("Element");
        writeElement(fieldMesh, elementH5Group);
        return true;
    }
    bool FITKFlowOFHDF5AdaptorMesh::fieldMeshR()
    {
        if (!_reader || !_unstructuredMesh)return false;
        if (!_h5Group->nameExists("FieldMesh"))return false;
        Interface::FITKUnstructuredMeshVTK* fieldMesh = _unstructuredMesh->getFieldMesh();
        if (!fieldMesh)return false;
        H5::Group h5Group = _h5Group->openGroup("FieldMesh");
        readNDataObject(fieldMesh, h5Group);
        if (!h5Group.nameExists("Node")) return false;
        H5::Group nodeH5Group = h5Group.openGroup("Node");
        readNode(fieldMesh, nodeH5Group);
        if (!h5Group.nameExists("Element"))return false;
        H5::Group elementH5Group = h5Group.openGroup("Element");
        readElement(fieldMesh, elementH5Group);
        return true;
    }
    bool FITKFlowOFHDF5AdaptorMesh::boundaryMeshW()
    {
        if (!_writer || !_unstructuredMesh)return false;
        H5::Group h5Group = _h5Group->createGroup("BoundaryMesh");
        Interface::FITKBoundaryMeshVTKManager* boundaryMeshMgr = _unstructuredMesh->getBoundaryMeshManager();
        if (!boundaryMeshMgr)return false;
        int count = boundaryMeshMgr->getDataCount();
        writeIntAttribute(h5Group, "BoundaryMeshCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKBoundaryMeshVTK* boundaryMesh = boundaryMeshMgr->getDataByIndex(i);
            if (!boundaryMesh)continue;
            std::string name = std::to_string(i);
            H5::Group boundaryH5Group = h5Group.createGroup(name);
            writeNDataObject(boundaryMesh, boundaryH5Group);
            //写出用户信息
            int startFace = boundaryMesh->getUserDataT<int>(Core::FITKUserData::FITKUserRole);
            int nFaces = boundaryMesh->getUserDataT<int>(Core::FITKUserData::FITKUserRole + 1);
            writeIntAttribute(boundaryH5Group, "startFace", &startFace);
            writeIntAttribute(boundaryH5Group, "nFaces", &nFaces);
            H5::Group elementH5Group = boundaryH5Group.createGroup("Element");
            writeElement(boundaryMesh, elementH5Group);
        }

        return true;
    }
    bool FITKFlowOFHDF5AdaptorMesh::boundaryMeshR()
    {
        if (!_reader || !_unstructuredMesh)return false;
        if (!_h5Group->nameExists("BoundaryMesh"))return false;
        Interface::FITKBoundaryMeshVTKManager* boundaryMeshMgr = _unstructuredMesh->getBoundaryMeshManager();
        if (!boundaryMeshMgr)return false;
        H5::Group h5Group = _h5Group->openGroup("BoundaryMesh");
        int count = readIntAttribute(h5Group, "BoundaryMeshCount");
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.nameExists(name))continue;
            H5::Group boundaryH5Group = h5Group.openGroup(name);
            Interface::FITKBoundaryMeshVTK* boundaryMesh = new Interface::FITKBoundaryMeshVTK(_unstructuredMesh->getFieldMesh());
            readNDataObject(boundaryMesh, boundaryH5Group);
            int startFace = readIntAttribute(boundaryH5Group, "startFace");;
            int nFaces = readIntAttribute(boundaryH5Group, "nFaces");;
            boundaryMesh->setUserData(Core::FITKUserData::FITKUserRole, startFace);
            boundaryMesh->setUserData(Core::FITKUserData::FITKUserRole + 1, nFaces);
            if (!boundaryH5Group.nameExists("Element"))return false;
            H5::Group elementH5Group = boundaryH5Group.openGroup("Element");
            readElement(boundaryMesh, elementH5Group);
            boundaryMeshMgr->appendDataObj(boundaryMesh);
        }

        return true;
    }

    bool FITKFlowOFHDF5AdaptorMesh::readNode(Interface::FITKNodeList* mesh, H5::Group& h5Group)
    {
        if (mesh == nullptr) return false;

        //PointIDs
        if (!h5Group.nameExists("PointIDs")) return false;
        auto PointIDSet = h5Group.openDataSet("PointIDs");
        int n, m;
        //Points
        if (!getDataSetDim(h5Group, "Points", n, m)) return false;
        auto pointsSet = h5Group.openDataSet("Points");

        //点
        // 行数 // 列数
        hsize_t       dimPtData[2]{ n ,m };
        H5::DataSpace ptDataSpace(2, dimPtData);
        //点ID
        // 行数 // 列数
        hsize_t       dimPtIDData[2]{ n ,1 };
        H5::DataSpace ptIDDataSpace(2, dimPtIDData);

        //点数据
        hsize_t       dim3[] = { 3 };
        H5::DataSpace mspace3(1, dim3);
        //点ID数据
        hsize_t       dim1[] = { 1 };
        H5::DataSpace mspace1(1, dim1);

        //表格
        hsize_t       coordPtData[3][2];
        coordPtData[0][1] = 0;
        coordPtData[1][1] = 1;
        coordPtData[2][1] = 2;

        for (int i = 0; i < n; ++i)
        {
            coordPtData[0][0] = i;
            coordPtData[1][0] = i;
            coordPtData[2][0] = i;

            //点
            std::array< double, 3 >  point;
            ptDataSpace.selectElements(H5S_SELECT_SET, 3, (const hsize_t*)coordPtData);
            pointsSet.read(&point, H5::PredType::NATIVE_DOUBLE, mspace3, ptDataSpace);

            //点ID
            int pID;
            ptIDDataSpace.selectElements(H5S_SELECT_SET, 1, (const hsize_t*)coordPtData);
            PointIDSet.read(&pID, H5::PredType::NATIVE_INT, mspace1, ptIDDataSpace);
            mesh->addNode(pID, point[0], point[1], point[2]);
        }
        PointIDSet.close();
        pointsSet.close();
        return true;
    }

    bool FITKFlowOFHDF5AdaptorMesh::readElement(Interface::FITKElementList* mesh, H5::Group& h5Group)
    {
        if (mesh == nullptr) return false;
        //获取行列
        int n, m;
        if (!getDataSetDim(h5Group, "Element", n, m)) return false;
        hsize_t dimEleData[2]{ n ,m };
        //获取单元数据
        H5::DataSpace eleDataSpace(2, dimEleData);
        H5::DataSet eleDataSet = h5Group.openDataSet("Element");
        //循环类型
        // 对同类单元进行每行循环读取数据
        for (int i = 0; i < n; ++i)
        {
            // hyperslab的开始
            hsize_t start[2] = { i, 0 };
            // hyperslab的步长
            hsize_t stride[2] = { 1, m };
            hsize_t count[2] = { 1, 1 };
            // Block sizes
            hsize_t block[2] = { 1, m };
            eleDataSpace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            hsize_t dim[] = { m * 2 };

            H5::DataSpace mspace2(1, dim);
            hsize_t start2[1] = { 0 };
            hsize_t stride2[1] = { 1 };
            hsize_t count2[1] = { m };
            hsize_t block2[1] = { 1 };
            mspace2.selectHyperslab(H5S_SELECT_SET, count2, start2, stride2, block2);

            int* ptIDArray = new int[m];
            eleDataSet.read(ptIDArray, H5::PredType::NATIVE_INT, mspace2, eleDataSpace);
            QList<int> nodes;
            int eleNodeCount = ptIDArray[2];
            if (eleNodeCount + 3 > m)return false;
            for (int k = 0; k < eleNodeCount; ++k)
            {
                nodes.append(ptIDArray[k + 3]);
            }
            Interface::FITKAbstractElement* element = Interface::FITKElementFactory::createElement(Interface::FITKModelEnum::FITKEleType(ptIDArray[1]));
            if (!element) return false;
            //添加点与单元
            auto ele = dynamic_cast<Interface::FITKElementPolygon*>(element);
            if (ele)
                ele->setNodeCount(nodes.size());
            element->setEleID(ptIDArray[0]);
            element->setNodeID(nodes);
            mesh->appendElement(element);
            delete[] ptIDArray;
        }
        eleDataSet.close();
        return true;
    }


    bool FITKFlowOFHDF5AdaptorMesh::writeNode(Interface::FITKNodeList* mesh, H5::Group& h5Group)
    {
        if (mesh == nullptr) return false;
        // 写出节点函数主体
        int nodeCount = mesh->getNodeCount();
        //点
        // 行数 // 列数
        hsize_t       dimPtData[2]{ nodeCount ,3 };
        H5::DataSpace ptDataSpace(2, dimPtData);
        H5::DataSet   ptData = h5Group.createDataSet("Points", H5::PredType::NATIVE_DOUBLE, ptDataSpace);
        //点ID
        // 行数 // 列数
        hsize_t       dimPtIDData[2]{ nodeCount ,1 };
        H5::DataSpace ptIDDataSpace(2, dimPtIDData);
        H5::DataSet   ptIDData = h5Group.createDataSet("PointIDs", H5::PredType::NATIVE_ULLONG, ptIDDataSpace);

        // 写入点数据
        hsize_t       dim1[] = { 1 };
        H5::DataSpace mspace1(1, dim1);
        //写入点ID数据
        hsize_t       dim3[] = { 3 };
        H5::DataSpace mspace3(1, dim3);

        //表格
        hsize_t       coordPtData[3][2];
        coordPtData[0][1] = 0;
        coordPtData[1][1] = 1;
        coordPtData[2][1] = 2;
        for (int i = 0; i < dimPtData[0]; ++i)
        {
            coordPtData[0][0] = i;
            coordPtData[1][0] = i;
            coordPtData[2][0] = i;
            //点
            auto node = mesh->getNodeAt(i);
            if (!node)continue;
            const std::array< double, 3 > pt0{ node->x() ,node->y() ,node->z() };
            ptDataSpace.selectElements(H5S_SELECT_SET, 3, (const hsize_t*)coordPtData);
            ptData.write(&pt0, H5::PredType::NATIVE_DOUBLE, mspace3, ptDataSpace);
            //点ID
            int pID = node->getNodeID();
            ptIDDataSpace.selectElements(H5S_SELECT_SET, 1, (const hsize_t*)coordPtData);
            ptIDData.write(&pID, H5::PredType::NATIVE_INT, mspace1, ptIDDataSpace);
        }
        ptData.close();
        ptIDData.close();
        return true;
    }

    bool FITKFlowOFHDF5AdaptorMesh::writeElement(Interface::FITKElementList* mesh, H5::Group& h5Group)
    {
        if (mesh == nullptr) return false;
        // 写出单元函数主体
        int elemCount = mesh->getElementCount();
        int maxLength = 0;
        for (int i = 0; i < elemCount; ++i)
        {
            //单元
            auto ele = mesh->getElementAt(i);
            if (!ele)continue;
            int num = ele->getNodeCount();
            if (maxLength < num)
                maxLength = num;
        }
        int lineSize = maxLength + 3;
        hsize_t dimEleData[2]{ elemCount ,lineSize };

        H5::DataSpace eleDataSpace(2, dimEleData);
        H5::DataSet eleDataSet = h5Group.createDataSet("Element", H5::PredType::NATIVE_INT, eleDataSpace);
        // 对同类单元进行循环
        for (int i = 0; i < elemCount; ++i)
        {
            // hyperslab的开始
            hsize_t start[2] = { i, 0 };
            // hyperslab的步长
            hsize_t stride[2] = { 1, lineSize };
            hsize_t count[2] = { 1, 1 };
            // Block sizes
            hsize_t block[2] = { 1, lineSize };
            eleDataSpace.selectHyperslab(H5S_SELECT_SET, count, start, stride, block);
            hsize_t dim[] = { lineSize * 2 };

            H5::DataSpace mspace2(1, dim);
            hsize_t start2[1] = { 0 };
            hsize_t stride2[1] = { 1 };
            hsize_t count2[1] = { lineSize };
            hsize_t block2[1] = { 1 };
            mspace2.selectHyperslab(H5S_SELECT_SET, count2, start2, stride2, block2);
            //写入单元数据
            auto ele = mesh->getElementAt(i);
            if (!ele)continue;
            int eleNodeCount = ele->getNodeCount();
            int* ptIDArray = new int[lineSize];
            for (int k = 0; k < eleNodeCount; ++k)
                ptIDArray[k + 3] = ele->getNodeID(k);
            ptIDArray[0] = ele->getEleID();
            ptIDArray[1] = ele->getEleType();
            ptIDArray[2] = eleNodeCount;
            eleDataSet.write(ptIDArray, H5::PredType::NATIVE_INT, mspace2, eleDataSpace);
            delete[] ptIDArray;
        }
        eleDataSet.close();
        return true;
    }
}
