#include "FITKInterfaceHDF5AdaptorOperGeometry.h"
//Geommtry
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoDelete.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoMultiDelete.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoOperBool.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperImprintSolid.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelImport.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelExport.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperCompound.h"

namespace IO
{
    // Reader.
   //@{

    QString FITKInterfaceHDF5AdaptorOperGeometry::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorOperGeometry";
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::adaptR()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;
        return readOperGeometry(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::adaptW()
    {
        auto comm = dynamic_cast<Interface::FITKAbsGeoCommand*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        return writeOperGeometry(comm, *_h5Group);
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        auto commType = comm->getGeometryCommandType();
        switch (commType)
        {
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTDelete:                return readOperGeometryDelete(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTMultiDelete:           return readOperGeometryMultiDelete(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTBool:                  return readOperGeometryBool(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTImprintSolid:          return readOperGeometryOperImprintSolid(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTImport:                return readOperGeometryOperImport(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTExport:                return readOperGeometryOperExport(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTCompoundAppendShape:
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTCompoundRemoveShape:   return readOperGeometryOperCompoundBase(comm, h5Group);
        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometry(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        if (comm == nullptr) return false;
        //获取命令类型
        auto commType = comm->getGeometryCommandType();
        switch (commType)
        {
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTDelete:                return writeOperGeometryDelete(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTMultiDelete:           return writeOperGeometryMultiDelete(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTBool:                  return writeOperGeometryBool(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTImprintSolid:          return writeOperGeometryOperImprintSolid(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTImport:                return writeOperGeometryOperImport(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTExport:                return writeOperGeometryOperExport(comm, h5Group);
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTCompoundAppendShape:
        case Interface::FITKGeoEnum::FITKGeometryComType::FGTCompoundRemoveShape:   return writeOperGeometryOperCompoundBase(comm, h5Group);
        default: return false;
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryDelete(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        Interface::FITKAbsGeoDelete* geoDelete = dynamic_cast<Interface::FITKAbsGeoDelete*>(comm);
        if (!geoDelete) return false;
        int deleteCommandID = readIntAttribute(h5Group, "DeleteCommandID");
        geoDelete->setDeleteCommandID(deleteCommandID);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryDelete(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group)
    {
        Interface::FITKAbsGeoDelete* geoDelete = dynamic_cast<Interface::FITKAbsGeoDelete*>(comm);
        if (!geoDelete) return false;
        int deleteCommandID = geoDelete->getDeleteCommandID();
        writeIntAttribute(h5Group, "DeleteCommandID", &deleteCommandID);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryMultiDelete(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoMultiDelete* geoDelete = dynamic_cast<Interface::FITKAbsGeoMultiDelete*>(comm);
        if (!geoDelete) return false;
        int deleteCmdIdCount = readIntAttribute(h5Group, "Count");
        int* deleteCommandIDs = new int[deleteCmdIdCount];

        if (!readIntAttribute(h5Group, "DeleteCommandIDs", deleteCommandIDs, 1, deleteCmdIdCount)) return false;
        QList<int> ids;
        for (int i = 0; i < deleteCmdIdCount; i++)
        {
            ids.append(deleteCommandIDs[i]);
        }
        geoDelete->setDeleteCommandIDs(ids);
        delete deleteCommandIDs;
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryMultiDelete(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoMultiDelete* geoDelete = dynamic_cast<Interface::FITKAbsGeoMultiDelete*>(comm);
        if (!geoDelete) return false;
        auto ids = geoDelete->getDeleteCommandIDs();
        int deleteCmdIdCount = ids.count();
        writeIntAttribute(h5Group, "Count", &deleteCmdIdCount);
        int* deleteCommandIDs = new int[deleteCmdIdCount];
        for (int i = 0; i < deleteCmdIdCount; i++)
        {
            deleteCommandIDs[i] = ids[i];
        }
        writeIntAttribute(h5Group, "DeleteCommandIDs", deleteCommandIDs, 1, deleteCmdIdCount);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryBool(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoOperBool* operBool = dynamic_cast<Interface::FITKAbsGeoOperBool*>(comm);
        if (!operBool) return false;

        int t = readIntAttribute(h5Group, "Type");
        operBool->setBoolOperType((Interface::FITKAbsGeoOperBool::GeoBoolOperType)t);

        int targetArray[3], toolArray[3];
        if (!readIntAttribute(h5Group, "Target", targetArray, 1, 3)) return false;
        Interface::VirtualShape vShapeTarget(targetArray[0], targetArray[1], targetArray[2]);
        operBool->setTarget(vShapeTarget);

        if (!readIntAttribute(h5Group, "ToolArray", toolArray, 1, 3)) return false;
        Interface::VirtualShape vShapeTool(toolArray[0], toolArray[1], toolArray[2]);
        operBool->setTool(vShapeTool);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryBool(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoOperBool* operBool = dynamic_cast<Interface::FITKAbsGeoOperBool*>(comm);
        if (!operBool) return false;

        int t = (int)operBool->getBoolOperType();
        writeIntAttribute(h5Group, "Type", &t);

        auto target = operBool->target();
        int targetArray[3]{ target.CmdId ,target.VirtualTopoId,target.VirtualTopoIndex };
        writeIntAttribute(h5Group, "Target", &targetArray, 1, 3);

        auto tool = operBool->tool();
        int toolArray[3]{ tool.CmdId ,tool.VirtualTopoId,tool.VirtualTopoIndex };
        writeIntAttribute(h5Group, "ToolArray", &toolArray, 1, 3);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryOperImprintSolid(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperImprintSolid* operImprintSolid = dynamic_cast<Interface::FITKAbsGeoModelOperImprintSolid*>(comm);
        if (!operImprintSolid) return false;

        int type = readIntAttribute(h5Group, "Type");
        operImprintSolid->setType((Interface::FITKAbsGeoModelOperImprintSolid::GeoSolidOperType)type);

        double tolerance = readDoubleAttribute(h5Group, "Tolerance");
        operImprintSolid->setTolerance(tolerance);

        int count = readIntAttribute(h5Group, "Count");

        int sourceSurfaceArray[3];
        for (int i = 0; i < count; i++)
        {
            if (!readIntAttribute(h5Group, std::to_string(i), sourceSurfaceArray, 1, 3)) return false;
            operImprintSolid->add(Interface::VirtualShape(sourceSurfaceArray[0], sourceSurfaceArray[1], sourceSurfaceArray[2]));
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryOperImprintSolid(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperImprintSolid* operImprintSolid = dynamic_cast<Interface::FITKAbsGeoModelOperImprintSolid*>(comm);
        if (!operImprintSolid) return false;

        int type = operImprintSolid->getType();
        writeIntAttribute(h5Group, "Type", &type);

        double tolerance = operImprintSolid->getTolerance();
        writeDoubleAttribute(h5Group, "Tolerance", &tolerance);

        auto shapes = operImprintSolid->getVShapes();
        int count = shapes.size();
        writeIntAttribute(h5Group, "Count", &count);

        for (int i = 0; i < count; i++)
        {
            int vShape[3]{ shapes[i].CmdId, shapes[i].VirtualTopoId };
            writeIntAttribute(h5Group, std::to_string(i), &vShape, 1, 3);
        }
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryOperImport(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelImport* gImport = dynamic_cast<Interface::FITKAbsGeoModelImport*>(comm);
        if (!gImport) return false;
        std::string fileName = readStrAttribute(h5Group, "FileName");
        gImport->setFileName(QString::fromStdString(fileName));
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryOperImport(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelImport* gImport = dynamic_cast<Interface::FITKAbsGeoModelImport*>(comm);
        if (!gImport) return false;
        QString fileName = gImport->getFileName();
        writeStrAttribute(h5Group, "FileName", fileName.toStdString());
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryOperExport(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelExport* gExport = dynamic_cast<Interface::FITKAbsGeoModelExport*>(comm);
        if (!gExport) return false;
        std::string fileName = readStrAttribute(h5Group, "FileName");
        gExport->setFileName(QString::fromStdString(fileName));
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryOperExport(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelExport* gExport = dynamic_cast<Interface::FITKAbsGeoModelExport*>(comm);
        if (!gExport) return false;
        QString fileName = gExport->getFileName();
        writeStrAttribute(h5Group, "FileName", fileName.toStdString());
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::readOperGeometryOperCompoundBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperCompound* operCompound = dynamic_cast<Interface::FITKAbsGeoModelOperCompound*>(comm);
        if (!operCompound) return false;

        int inputCmdArray[3], childCmdArray[3];
        if (!readIntAttribute(h5Group, "InputCmd", inputCmdArray, 1, 3)) return false;
        Interface::VirtualShape vShape(inputCmdArray[0], inputCmdArray[1], inputCmdArray[2]);
        operCompound->setInputCmdId(vShape);

        int count = readIntAttribute(h5Group, "Count");
        QList<Interface::VirtualShape> vShapeChildList;
        for (int i = 0; i < count; i++)
        {
            if (!readIntAttribute(h5Group, std::to_string(i), childCmdArray, 1, 3)) return false;

            Interface::VirtualShape vShapeChild(childCmdArray[0], childCmdArray[1], childCmdArray[2]);
            vShapeChildList.append(vShapeChild);
        }
        operCompound->setShapeCmdIds(vShapeChildList);
        return true;
    }

    bool FITKInterfaceHDF5AdaptorOperGeometry::writeOperGeometryOperCompoundBase(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)
    {
        Interface::FITKAbsGeoModelOperCompound* operCompound = dynamic_cast<Interface::FITKAbsGeoModelOperCompound*>(comm);
        if (!operCompound) return false;

        Interface::VirtualShape vShape = operCompound->getInputCmdId();
        int inputCmdArray[3]{ vShape.CmdId,vShape.VirtualTopoId, vShape.VirtualTopoIndex };
        writeIntAttribute(h5Group, "InputCmd", inputCmdArray, 1, 3);

        auto cmdIDs = operCompound->getShapeCmdIds();
        int count = cmdIDs.size();
        writeIntAttribute(h5Group, "Count", &count);
        for (int i = 0; i < count; i++)
        {
            auto cmdID = cmdIDs[i];
            int cmdIDArray[3]{ cmdID.CmdId, cmdID.VirtualTopoId,cmdID.VirtualTopoIndex };
            writeIntAttribute(h5Group, std::to_string(i), cmdIDArray, 1, 3);
        }
        return true;
    }

    //@}
}   // namespace IO
