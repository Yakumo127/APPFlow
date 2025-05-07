#include "FITKInterfaceHDF5AdaptorSurface.h"

#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"

#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"

#include "FITK_Interface/FITKInterfaceModel/FITKModelSet.h"
#include "FITK_Interface/FITKInterfaceModel/FITKMeshSurface.h"
#include "FITK_Interface/FITKInterfaceModel/FITKMeshSurfaceNode.h"
#include "FITK_Interface/FITKInterfaceModel/FITKMeshSurfaceElement.h"

#include "FITK_Interface/FITKInterfaceModel/FITKAssembly.h"
#include "FITK_Interface/FITKInterfaceModel/FITKAbstractModel.h"

namespace IO
{
    QString FITKInterfaceHDF5AdaptorSurface::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorSurface";
    }

    bool FITKInterfaceHDF5AdaptorSurface::adaptR()
    {
        Interface::FITKMeshSurface* surfaceData = dynamic_cast<Interface::FITKMeshSurface*>(_dataObj);
        if (!surfaceData || !_reader || !_h5Group) return false;
        bool isR = true;
        isR &= surfR(surfaceData, *_h5Group);
        return isR;
    }

    bool FITKInterfaceHDF5AdaptorSurface::adaptW()
    {
        Interface::FITKMeshSurface* surfaceData = dynamic_cast<Interface::FITKMeshSurface*>(_dataObj);
        if (!surfaceData || !_writer || !_h5Group) return false;
        bool isW = true;
        isW &= surfW(surfaceData, *_h5Group);
        return isW;
    }

    bool FITKInterfaceHDF5AdaptorSurface::surfR(Interface::FITKMeshSurface * surfaceData, H5::Group & h5Group)
    {
        if (surfaceData == nullptr) return false;
        bool isR = readNDataObject(surfaceData, h5Group);

        bool isInternal = readBoolAttribute(h5Group, "isInternal");
        surfaceData->isInternal(isInternal);

        if (!h5Group.nameExists("SetIDList")) return false;
        if (!h5Group.nameExists("SetModelID")) return false;

        //写出类型
        auto surfType = surfaceData->getMeshSurfaceType();

        if (surfType == Interface::MeshSurfaceType::SurNode)
        {
            isR &= nodeTypeR(surfaceData, h5Group);
        }
        else if (surfType == Interface::MeshSurfaceType::SurEle)
        {
            isR &= elementTypeR(surfaceData, h5Group);
        }
        else
            return false;

        return isR;
    }

    bool FITKInterfaceHDF5AdaptorSurface::elementTypeR(Interface::FITKMeshSurface* surfaceData, H5::Group& h5Group)
    {
        Interface::FITKMeshSurfaceElement* abaSurfaceData = dynamic_cast<Interface::FITKMeshSurfaceElement*>(surfaceData);
        if (!abaSurfaceData) return false;
        if (!h5Group.nameExists("SurfaceIndex")) return false;

        QList<int> setIdList;
        QList<int> SetModelIDList;
        QList<int> surfaceIndex;
        readIntDataSet(h5Group, "SetIDList", setIdList);
        readIntDataSet(h5Group, "SetModelID", SetModelIDList);
        readIntDataSet(h5Group, "SurfaceIndex", surfaceIndex);

        for (int i = 0; i < surfaceIndex.size(); i++)
        {
            abaSurfaceData->addMeshSet(SetModelIDList[i], setIdList[i], surfaceIndex[i]);
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorSurface::nodeTypeR(Interface::FITKMeshSurface* surfaceData, H5::Group& h5Group)
    {
        Interface::FITKMeshSurfaceNode* abaSurfaceData = dynamic_cast<Interface::FITKMeshSurfaceNode*>(surfaceData);
        if (!abaSurfaceData) return false;
        if (!h5Group.nameExists("Weights"))return false;

        QList<int> setIdList;
        QList<int> SetModelIDList;
        QList<double> Weights;
        readIntDataSet(h5Group, "SetIDList", setIdList);
        readIntDataSet(h5Group, "SetModelID", SetModelIDList);
        readDoubleDataSet(h5Group, "Weights", Weights);

        for (int i = 0; i < setIdList.size(); i++)
        {
            abaSurfaceData->addMeshSet(SetModelIDList[i], setIdList[i], Weights[i]);
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorSurface::surfW(Interface::FITKMeshSurface* surfaceData, H5::Group& h5Group)
    {
        if (surfaceData == nullptr) return false;
        bool isW = true;

        std::string groupName = createParentAttribute(surfaceData, h5Group);
        if (groupName.empty())return false;

        //创建表面的数据块
        H5::Group surfGroup = h5Group.createGroup(groupName);
        isW &= writeNDataObject(surfaceData, surfGroup);

        bool isInternal = surfaceData->isInternal();
        writeBoolAttribute(surfGroup, "isInternal", &isInternal);

        //写出类型
        auto surfType = surfaceData->getMeshSurfaceType();

        //枚举转换字符
        Core::FITKEnumTransfer<Interface::FITKMeshSurface::MeshSurfaceType> fitkSurfTypeTrafer;
        bool isValid = false;
        //写出类型
        QString TypeStr = fitkSurfTypeTrafer.toString(surfType, isValid);
        if (!isValid) return false;
        writeStrAttribute(surfGroup, "Type", TypeStr.toStdString());

        if (surfType == Interface::MeshSurfaceType::SurNode)
        {
            isW &= nodeTypeW(surfaceData, surfGroup);
        }
        else if (surfType == Interface::MeshSurfaceType::SurEle)
        {
            isW &= elementTypeW(surfaceData, surfGroup);
        }
        else
            return false;

        //写出引用的setID
        QList<int> setIDList;
        for (int i = 0; i < surfaceData->getMeshSetCount(); ++i)
        {
            auto set = surfaceData->getMeshSetAt(i);
            if (!set) return false;
            setIDList.append(set->getDataObjectID());
        }
        writeIntDataSet(surfGroup, "SetIDList", setIDList);

        //写出引用的SetParentID
        QList<int> setParentIDList;
        for (int i = 0; i < surfaceData->getMeshSetCount(); ++i)
        {
            auto model = surfaceData->getModelAt(i);
            setParentIDList.append(model->getDataObjectID());
        }
        writeIntDataSet(surfGroup, "SetModelID", setParentIDList);

        //写出唯一类型
        writeStrAttribute(surfGroup, "UniqueType", "Surface");
        return true;
    }

    bool FITKInterfaceHDF5AdaptorSurface::nodeTypeW(Interface::FITKMeshSurface* surfaceData, H5::Group & h5Group)
    {
        Interface::FITKMeshSurfaceNode* abaSurfaceData = dynamic_cast<Interface::FITKMeshSurfaceNode*>(surfaceData);
        if (!abaSurfaceData) return false;
        int count = abaSurfaceData->getMeshSetCount();
        QList<double> weights;

        for (int i = 0; i < count; ++i)
        {
            //获取权重
            double value = abaSurfaceData->getValueAt(i);
            weights.append(value);
        }
        //写出权重
        writeDoubleDataSet(h5Group, "Weights", weights);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorSurface::elementTypeW(Interface::FITKMeshSurface* surfaceData, H5::Group & h5Group)
    {
        Interface::FITKMeshSurfaceElement* abaSurfaceData = dynamic_cast<Interface::FITKMeshSurfaceElement*>(surfaceData);
        if (!abaSurfaceData) return false;
        int count = surfaceData->getMeshSetCount();
        QList<int> polygonIndexList;

        for (int i = 0; i < count; i++)
        {
            //获取面的索引
            int polygonIndex = abaSurfaceData->getSurfaceIndexAt(i);
            polygonIndexList.append(polygonIndex);
        }
        //写出SurfaceIndex
        writeIntDataSet(h5Group, "SurfaceIndex", polygonIndexList);
        return true;
    }

}


