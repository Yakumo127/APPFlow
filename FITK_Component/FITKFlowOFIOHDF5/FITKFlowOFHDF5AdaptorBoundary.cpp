#include "FITKFlowOFHDF5AdaptorBoundary.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"

#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFSolver.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundary.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundaryTypeManager.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundaryType.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsManager.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKFlowPhysicsHandlerFactory.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"

//数据层
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"



#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorBoundary::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorBoundary";
    }

    bool FITKFlowOFHDF5AdaptorBoundary::adaptR()
    {
        _boundary = dynamic_cast<Interface::FITKOFBoundary*>(_dataObj);
        if (!_reader || !_boundary) return false;
        if (!readNDataObject(_boundary, *_h5Group)) return false;
        bool isR = true;

        int meshBoundaryId = readIntAttribute(*_h5Group, "meshBoundaryId");
        _boundary->setMeshBoundaryID(meshBoundaryId);

        isR &= flowBoundaryR();
        isR &= turbulenceBoundaryR();
        isR &= phasesBoundaryR();

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorBoundary::adaptW()
    {
        _boundary = dynamic_cast<Interface::FITKOFBoundary*>(_dataObj);
        if (!_writer || !_boundary) return false;
        if (!writeNDataObject(_boundary, *_h5Group)) return false;
        bool isW = true;
        int meshBoundaryId = _boundary->getMeshBoundaryID();
        writeIntAttribute(*_h5Group, "meshBoundaryId", &meshBoundaryId);

        isW &= flowBoundaryW();
        isW &= turbulenceBoundaryW();
        isW &= phasesBoundaryW();

        return isW;
    }

    bool FITKFlowOFHDF5AdaptorBoundary::flowBoundaryW()
    {
        if (!_writer || !_boundary)return false;
        H5::Group h5Group = _h5Group->createGroup("Flow");
        int count = _boundary->getFlowCount();
        writeIntAttribute(h5Group, "FlowCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFAbsBoundaryType* boundaryT = _boundary->getFlowVBType(i);
            if (!boundaryT)continue;
            QString vname = _boundary->getFlowVariableName(i);
            std::string name = std::to_string(i);
            writeStrAttribute(h5Group, name, vname.toStdString());
            H5::Group boundaryH5Group = h5Group.createGroup(name);
            writeStrAttribute(boundaryH5Group, "boundaryTypeName", boundaryT->getDataObjectName().toStdString());
            writeNDataObject(boundaryT, boundaryH5Group);
            parameterToolW(boundaryH5Group, boundaryT->getBoundaryTypePara());
        }
        return true;
    }
    bool FITKFlowOFHDF5AdaptorBoundary::flowBoundaryR()
    {
        if (!_reader || !_boundary)return false;
        if (!_h5Group->nameExists("Flow"))return false;
        Interface::FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<Interface::FITKOFPhysicsData>();
        Interface::FITKOFPhysicsManager* physicsManager = Interface::FITKOFPhysicsManager::getInstance();
        if (!physicsData || !physicsManager)return false;
        Interface::FITKOFBoundaryTypeManager* boundaryTypeMgr = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeMgr)return false;
        //获取求解器
        Interface::FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return false;
        H5::Group h5Group = _h5Group->openGroup("Flow");
        int count = readIntAttribute(h5Group, "FlowCount");
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.attrExists(name))continue;
            QString vname = QString::fromStdString(readStrAttribute(h5Group, name));
            if (!h5Group.nameExists(name))return false;
            H5::Group boundaryH5Group = h5Group.openGroup(name);
            QString boundaryType = QString::fromStdString(readStrAttribute(boundaryH5Group, "boundaryTypeName"));
            //获取边界信息
            Interface::FITKOFBoundaryTypeInfo info = boundaryTypeMgr->getBoundaryTypeInfo(boundaryType, solver->getSolverType(), vname, _boundary->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())return false;
            Interface::FITKOFAbsBoundaryType* boundaryT = info._createFuns();
            if (!boundaryT)return false;
            readNDataObject(boundaryT, boundaryH5Group);
            parameterToolR(boundaryH5Group, boundaryT->getBoundaryTypePara());
            _boundary->setFlowBoundary(vname, boundaryT);
        }
        return true;
    }

    bool FITKFlowOFHDF5AdaptorBoundary::turbulenceBoundaryW()
    {
        if (!_writer || !_boundary)return false;
        H5::Group h5Group = _h5Group->createGroup("Turbulence");
        int count = _boundary->getTurbulenceCount();
        writeIntAttribute(h5Group, "TurbulenceCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFAbsBoundaryType* boundaryT = _boundary->getTurbulenceVBType(i);
            if (!boundaryT)continue;
            QString vname = _boundary->getTurbulenceVariableName(i);
            std::string name = std::to_string(i);
            writeStrAttribute(h5Group, name, vname.toStdString());
            H5::Group boundaryH5Group = h5Group.createGroup(name);
            writeStrAttribute(boundaryH5Group, "boundaryTypeName", boundaryT->getDataObjectName().toStdString());
            writeNDataObject(boundaryT, boundaryH5Group);
            parameterToolW(boundaryH5Group, boundaryT->getBoundaryTypePara());
        }
        return true;
    }
    bool FITKFlowOFHDF5AdaptorBoundary::turbulenceBoundaryR()
    {
        if (!_reader || !_boundary)return false;
        if (!_h5Group->nameExists("Turbulence"))return false;
        Interface::FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<Interface::FITKOFPhysicsData>();
        Interface::FITKOFPhysicsManager* physicsManager = Interface::FITKOFPhysicsManager::getInstance();
        if (!physicsData || !physicsManager)return false;
        Interface::FITKOFBoundaryTypeManager* boundaryTypeMgr = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeMgr)return false;
        //获取求解器
        Interface::FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return false;
        H5::Group h5Group = _h5Group->openGroup("Turbulence");
        int count = readIntAttribute(h5Group, "TurbulenceCount");
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.attrExists(name))continue;
            QString vname = QString::fromStdString(readStrAttribute(h5Group, name));
            if (!h5Group.nameExists(name))return false;
            H5::Group boundaryH5Group = h5Group.openGroup(name);
            QString boundaryType = QString::fromStdString(readStrAttribute(boundaryH5Group, "boundaryTypeName"));
            //获取边界信息
            Interface::FITKOFBoundaryTypeInfo info = boundaryTypeMgr->getBoundaryTypeInfo(boundaryType, solver->getSolverType(), vname, _boundary->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())return false;
            Interface::FITKOFAbsBoundaryType* boundaryT = info._createFuns();
            if (!boundaryT)return false;
            readNDataObject(boundaryT, boundaryH5Group);
            parameterToolR(boundaryH5Group, boundaryT->getBoundaryTypePara());
            _boundary->setTurbulenceBoundary(vname, boundaryT);
        }
        return true;
    }

    bool FITKFlowOFHDF5AdaptorBoundary::phasesBoundaryW()
    {
        if (!_writer || !_boundary)return false;
        H5::Group h5Group = _h5Group->createGroup("Phases");
        int count = _boundary->getPhasesCount();
        writeIntAttribute(h5Group, "PhasesCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFAbsBoundaryType* boundaryT = _boundary->getPhasesVBType(i);
            if (!boundaryT)continue;
            QString vname = _boundary->getPhasesVariableName(i);
            std::string name = std::to_string(i);
            writeStrAttribute(h5Group, name, vname.toStdString());
            H5::Group boundaryH5Group = h5Group.createGroup(name);
            writeStrAttribute(boundaryH5Group, "boundaryTypeName", boundaryT->getDataObjectName().toStdString());
            writeNDataObject(boundaryT, boundaryH5Group);
            parameterToolW(boundaryH5Group, boundaryT->getBoundaryTypePara());
        }
        return true;
    }
    bool FITKFlowOFHDF5AdaptorBoundary::phasesBoundaryR()
    {
        if (!_reader || !_boundary)return false;
        if (!_h5Group->nameExists("Phases"))return false;
        Interface::FITKOFPhysicsData* physicsData = FITKAPP->getGlobalData()->getPhysicsData<Interface::FITKOFPhysicsData>();
        Interface::FITKOFPhysicsManager* physicsManager = Interface::FITKOFPhysicsManager::getInstance();
        if (!physicsData || !physicsManager)return false;
        Interface::FITKOFBoundaryTypeManager* boundaryTypeMgr = physicsManager->getBoundaryTypeManager();
        if (!boundaryTypeMgr)return false;
        //获取求解器
        Interface::FITKAbstractOFSolver* solver = physicsData->getSolver();
        if (!solver)return false;
        H5::Group h5Group = _h5Group->openGroup("Phases");
        int count = readIntAttribute(h5Group, "PhasesCount");
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.attrExists(name))continue;
            QString vname = QString::fromStdString(readStrAttribute(h5Group, name));
            if (!h5Group.nameExists(name))return false;
            H5::Group boundaryH5Group = h5Group.openGroup(name);
            QString boundaryType = QString::fromStdString(readStrAttribute(boundaryH5Group, "boundaryTypeName"));
            //获取边界信息
            Interface::FITKOFBoundaryTypeInfo info = boundaryTypeMgr->getBoundaryTypeInfo(boundaryType, solver->getSolverType(), vname, _boundary->getBoundaryType());
            if (info._boundaryTypeName.isEmpty())return false;
            Interface::FITKOFAbsBoundaryType* boundaryT = info._createFuns();
            if (!boundaryT)return false;
            readNDataObject(boundaryT, boundaryH5Group);
            parameterToolR(boundaryH5Group, boundaryT->getBoundaryTypePara());
            _boundary->setPhasesBoundary(vname, boundaryT);
        }
        return true;
    }
}
