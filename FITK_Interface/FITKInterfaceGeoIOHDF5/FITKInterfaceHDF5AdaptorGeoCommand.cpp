#include "FITKInterfaceHDF5AdaptorGeoCommand.h"

#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"

#include <QMetaEnum>
namespace IO
{
    // Base.
    //@{
    QString FITKInterfaceHDF5AdaptorGeoCommand::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorGeoCommand";
    }

    bool FITKInterfaceHDF5AdaptorGeoCommand::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readCommand(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorGeoCommand::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeCommand(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorGeoCommand::readCommand(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (!comm) return false;
        if (!readNDataObject(comm, h5Group)) return false;
        std::string str = readStrAttribute(h5Group, "CommandStatus");
        if (str.empty()) return false;

        QMetaEnum metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKGeoStatus>();
        Interface::FITKGeoEnum::FITKGeoStatus status = (Interface::FITKGeoEnum::FITKGeoStatus)metaEnum.keyToValue(str.c_str());
        comm->setCommandStatus(status);

        int modifiedCmdID = readIntAttribute(h5Group, "ModifiedCmdID");
        comm->setModifiedCmdID(modifiedCmdID);

        int referenceCmdCount = readIntAttribute(h5Group, "ReferenceCmdCount");
        //打开子节点
        if (!h5Group.nameExists("ReferenceCmdID")) return false;
        auto _h5ReferenceCmdIDGroup = h5Group.openGroup("ReferenceCmdID");

        if (!h5Group.nameExists("ReferenceCmdType")) return false;
        auto _h5ReferenceCmdTypeGroup = h5Group.openGroup("ReferenceCmdType");

        for (int i = 0; i < referenceCmdCount; i++)
        {
            int refID = readIntAttribute(_h5ReferenceCmdIDGroup, std::to_string(i));
            comm->addReferenceCmdID(refID);
        }

        bool reference = readBoolAttribute(h5Group, "EnableReferenceList");
        comm->enableReferenceList(reference);

        return readChildVirtualShape(comm, h5Group);
    }

    bool FITKInterfaceHDF5AdaptorGeoCommand::writeCommand(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        QMetaEnum metaEnum;
        if (!comm) return false;
        std::string groupName = createParentAttribute(comm, h5Group);
        if (groupName.empty())return false;
        _h5CreateGroup = h5Group.createGroup(groupName);
        bool isW = writeNDataObject(comm, _h5CreateGroup);

        metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKGeoStatus>();
        std::string str = metaEnum.valueToKey(comm->getCommandStatus());
        if (str.empty()) return false;
        writeStrAttribute(_h5CreateGroup, "CommandStatus", str);

        metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKGeometryComType>();
        str = metaEnum.valueToKey(comm->getGeometryCommandType());
        if (str.empty()) return false;
        writeStrAttribute(_h5CreateGroup, "GeometryCommandType", str);

        int modifiedCmdID = comm->getModifiedCmdID();
        writeIntAttribute(_h5CreateGroup, "ModifiedCmdID", &modifiedCmdID);

        int referenceCmdCount = comm->getReferenceCmdCount();
        writeIntAttribute(_h5CreateGroup, "ReferenceCmdCount", &referenceCmdCount);

        //创建子节点
        auto _h5ReferenceCmdIDGroup = _h5CreateGroup.createGroup("ReferenceCmdID");
        auto _h5ReferenceCmdTypeGroup = _h5CreateGroup.createGroup("ReferenceCmdType");

        for (int i = 0; i < referenceCmdCount; i++)
        {
            auto refComm = comm->getReferenceCmdByIndex(i);
            if (refComm == nullptr) return false; //判断异常
            int refID = refComm->getDataObjectID();
            writeIntAttribute(_h5ReferenceCmdIDGroup, std::to_string(i), &refID);
            //写出类型
            //metaEnum = QMetaEnum::fromType<Interface::FITKGeoEnum::FITKGeometryComType>();
            //str = metaEnum.valueToKey(refComm->getGeometryCommandType());
            //if (str.empty()) return false;        //判断异常
            //writeStrAttribute(_h5ReferenceCmdTypeGroup, "GeometryCommandType", str);
        }

        bool reference = comm->getEnableReferenceList();
        writeBoolAttribute(_h5CreateGroup, "EnableReferenceList", &reference);

        isW &= writeChildVirtualShape(comm, _h5CreateGroup);
        return isW;
    }

    bool FITKInterfaceHDF5AdaptorGeoCommand::readChildVirtualShape(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group, bool isSaveShape)
    {
        if (comm == nullptr) return false;
        auto agent = comm->getShapeAgent();
        if (agent == nullptr) return true;
        auto manager = agent->getVirtualTopoManager();
        if (manager == nullptr) return true;
        QMetaEnum m = QMetaEnum::fromType<Interface::FITKGeoEnum::VTopoShapeType>();
        int vTopoShapeTypeCount = m.keyCount();
        //实际存储类型
        int shapeTypeCount = 0;

        int dataObjectInfo[4];
        auto vTopoShapeManagerGroup = h5Group.openGroup("vTopoShapeManager");
        int virtualTopoManagerRootID = readIntAttribute(h5Group, "VirtualTopoManagerRootID");
        for (int i = vTopoShapeTypeCount - 1; i > 0; i--)
        {
            auto shapeManager = manager->getShapeVirtualTopoManager((Interface::FITKGeoEnum::VTopoShapeType)i);
            if (shapeManager == nullptr) return false;

            std::string vTopoTypeStr = readStrAttribute(vTopoShapeManagerGroup, std::to_string(i - 1));
            if (!vTopoShapeManagerGroup.nameExists(vTopoTypeStr)) continue;
            auto vTopoTypeGroup = vTopoShapeManagerGroup.openGroup(vTopoTypeStr);
            int count = readIntAttribute(vTopoTypeGroup, "Count");
            for (int j = 0; j < count; j++)
            {
                std::string attrObjectName = std::to_string(j) + "_DataObject";

                Interface::FITKAbsVirtualTopo* vt = new Interface::FITKAbsVirtualTopo();
                vt->setShapeType((Interface::FITKGeoEnum::VTopoShapeType)i);
                shapeManager->appendDataObj(vt);

                if (!readIntAttribute(vTopoTypeGroup, attrObjectName, dataObjectInfo, 1, 4))
                {
                    delete vt;
                    return false;
                }
                Core::FITKAbstractDataIDAlter dataIDAlter;
                dataIDAlter.modifyDataID(vt, dataObjectInfo[0]);
                vt->setParentDataID(dataObjectInfo[1]);
                vt->enable(dataObjectInfo[2]);
                vt->setIndexLabel(dataObjectInfo[3]);

                //设置根节点
                if (dataObjectInfo[0] == virtualTopoManagerRootID)
                {
                    manager->setRootObj(vt);
                }
            }
        }

        for (int i = vTopoShapeTypeCount - 1; i > 0; i--)
        {
            auto shapeManager = manager->getShapeVirtualTopoManager((Interface::FITKGeoEnum::VTopoShapeType)i);
            if (shapeManager == nullptr) return false;

            auto vTopoShapeManagerGroup = h5Group.openGroup("vTopoShapeManager");
            std::string vTopoTypeStr = readStrAttribute(vTopoShapeManagerGroup, std::to_string(i - 1));
            if (!vTopoShapeManagerGroup.nameExists(vTopoTypeStr)) continue;
            auto vTopoTypeGroup = vTopoShapeManagerGroup.openGroup(vTopoTypeStr);
            int typeCount = readIntAttribute(vTopoTypeGroup, "Count");
            for (int j = 0; j < typeCount; j++)
            {
                std::string attrObjectName = std::to_string(j) + "_DataObject";
                std::string attrChildVTopoName = std::to_string(j) + "_ChildVTopo";

                if (!readIntAttribute(vTopoTypeGroup, attrObjectName, dataObjectInfo, 1, 4)) return false;
                auto vTopo = shapeManager->getDataByID(dataObjectInfo[0]);
                if (vTopo == nullptr) return false;
                //添加对象
                int subTopoCount = readIntAttribute(vTopoTypeGroup, attrChildVTopoName);
                if (subTopoCount < 0) continue;
                int* subTopoIDs = new int[subTopoCount + 1];
                for (int k = 0; k < subTopoCount; k++)
                {
                    if (!readIntAttribute(vTopoTypeGroup, attrChildVTopoName, subTopoIDs, 1, subTopoCount + 1)) return false;
                    int vChildTopoID = subTopoIDs[k + 1];
                    auto subTopo = manager->findDownInternal(vChildTopoID, (Interface::FITKGeoEnum::VTopoShapeType)i);
                    if (subTopo == nullptr) return false;
                    vTopo->addSubTopo(subTopo);
                }
                delete[] subTopoIDs;
            }
        }

        //读取shape
        auto shapeGroup = h5Group.openGroup("Shape");
        if (!readVShape(comm, shapeGroup)) return false;
        return true;
    }

    bool FITKInterfaceHDF5AdaptorGeoCommand::writeChildVirtualShape(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group, bool isSaveShape)
    {
        auto agent = comm->getShapeAgent();
        if (agent == nullptr) return true;
        auto manager = agent->getVirtualTopoManager();
        if (manager == nullptr) return true;
        auto vTopoShapeManager = h5Group.createGroup("vTopoShapeManager");

        QMetaEnum m = QMetaEnum::fromType<Interface::FITKGeoEnum::VTopoShapeType>();
        int vTopoShapeTypeCount = m.keyCount();
        //实际存储类型
        int shapeTypeCount = 0;
        int dataObjectInfo[4];
        for (int i = 1; i < vTopoShapeTypeCount; i++)
        {
            auto shapeManager = manager->getShapeVirtualTopoManager((Interface::FITKGeoEnum::VTopoShapeType)i);
            if (shapeManager == nullptr) continue;
            shapeTypeCount++;
            std::string name = m.valueToKey(i);
            auto vTopoShapeTypeGroup = vTopoShapeManager.createGroup(name);
            int shapeManagerCount = shapeManager->getDataCount();
            writeIntAttribute(vTopoShapeTypeGroup, "Count", &shapeManagerCount);
            for (int j = 0; j < shapeManager->getDataCount(); j++)
            {
                std::string attrObjectName = std::to_string(j) + "_DataObject";
                std::string attrChildVTopoName = std::to_string(j) + "_ChildVTopo";
                //std::string attrParentVTopoName = std::to_string(j) + "_ParentVTopo";
                //写出每个节点的dataObject信息
                auto vTopo = shapeManager->getDataByIndex(j);
                int indexLabel = vTopo->getIndexLabel();

                //写出dataObject
                dataObjectInfo[0] = vTopo->getDataObjectID();
                dataObjectInfo[1] = vTopo->getParentDataID();
                dataObjectInfo[2] = vTopo->isEnable();
                dataObjectInfo[3] = indexLabel;
                writeIntAttribute(vTopoShapeTypeGroup, attrObjectName, dataObjectInfo, 1, 4);

                //int parentTopoCount = vTopo->getParentTopoCount();
                //int* parentTopoData = new int[parentTopoCount + 1];
                //for (int k = 0; k < parentTopoCount; k++)
                //{
                //    int vParentTopoID = vTopo->getParentTopo(k)->getDataObjectID();
                //    parentTopoData[k + 1] = vParentTopoID;
                //}
                ////write parent
                //if (parentTopoCount > 0)
                //{
                //    parentTopoData[0] = parentTopoCount;
                //    writeIntAttribute(vTopoShapeTypeGroup, attrParentVTopoName, parentTopoData, 1, parentTopoCount + 1);
                //}
                //delete[] parentTopoData;

                int subTopoCount = vTopo->getSubTopoCount();
                int* childTopoData = new int[subTopoCount + 1];
                for (int k = 0; k < subTopoCount; k++)
                {
                    int vChildTopoID = vTopo->getSubTopo(k)->getDataObjectID();
                    childTopoData[k + 1] = vChildTopoID;
                }
                if (subTopoCount > 0)
                {
                    childTopoData[0] = subTopoCount;
                    writeIntAttribute(vTopoShapeTypeGroup, attrChildVTopoName, childTopoData, 1, subTopoCount + 1);
                }
                delete[] childTopoData;
            }
            //存储名称的链表 用index作为属性名称添加
            int numAttrCount = vTopoShapeManager.getNumAttrs();
            writeStrAttribute(vTopoShapeManager, std::to_string(numAttrCount), name);
        }
        writeIntAttribute(vTopoShapeManager, "Count", &shapeTypeCount);

        //写出根节点ID
        if (manager->getRootObj() != nullptr)
        {
            int virtualTopoManagerRootID = manager->getRootObj()->getDataObjectID();
            writeIntAttribute(h5Group, "VirtualTopoManagerRootID", &virtualTopoManagerRootID);
        }
        //写出shape
        auto shapeGroup = h5Group.createGroup("Shape");
        if (!writeVShape(agent, shapeGroup)) return false;
        return true;
    }

    //@}
}   // namespace IO
