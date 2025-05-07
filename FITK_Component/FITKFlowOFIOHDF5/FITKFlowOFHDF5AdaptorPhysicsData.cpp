#include "FITKFlowOFHDF5AdaptorPhysicsData.h"
#include "FITKFlowOFHDF5AdaptorTurbulence.h"
#include "FITKFlowOFHDF5AdaptorTransportProp.h"
#include "FITKFlowOFHDF5AdaptorDiscretization.h"
#include "FITKFlowOFHDF5AdaptorSolution.h"
#include "FITKFlowOFHDF5AdaptorInitialCondition.h"
#include "FITKFlowOFHDF5AdaptorRunControl.h"
#include "FITKFlowOFHDF5AdaptorBoundary.h"
#include "FITKFlowOFHDF5AdaptorOperatingCond.h"

#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFSolver.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFTurbulence.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFTransportProp.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFDiscretization.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundary.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFSolution.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFInitialConditions.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFRunControl.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFOperatingConditions.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKFlowPhysicsHandlerFactory.h"

//求解器
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFSolverSIMPLE.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFSolverInter.h"

#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"


#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorPhysicsData::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorPhysicsData";
    }

    bool FITKFlowOFHDF5AdaptorPhysicsData::adaptR()
    {
        _physicsData = dynamic_cast<Interface::FITKOFPhysicsData*>(_dataObj);
        if (!_reader || !_physicsData) return false;
        if (!readDataObject(_physicsData, *_h5Group))return false;
        //是否启用湍流数据
        bool enableTurb = readBoolAttribute(*_h5Group, "enableTurb");
        _physicsData->setEnableTurbulenceEqu(enableTurb);

        bool isR = true;
        //必须先求解器后湍流
        isR &= this->physicsSolverR();
        isR &= this->physicsTurbulenceR();

        isR &= this->physicsTransportPropR();
        isR &= this->physicsDiscretizationR();
        isR &= this->physicsSolutionR();
        isR &= this->physicsInitialConditionsR();
        isR &= this->physicsBoundaryR();
        isR &= this->physicsRunControlR();
        isR &= this->physicsOperatingConditionsR();

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorPhysicsData::adaptW()
    {
        _physicsData = dynamic_cast<Interface::FITKOFPhysicsData*>(_dataObj);
        if (!_writer || !_physicsData) return false;
        bool isW = true;
        if (!writeDataObject(_physicsData, *_h5Group))return false;
        //是否启用湍流数据
        bool enableTurb = _physicsData->isEnableTurbulenceEqu();
        writeBoolAttribute(*_h5Group, "enableTurb", &enableTurb);
        //写出湍流数据
        if (_physicsData->getSolver())
            isW &= this->physicsSolverW();
        if (_physicsData->getTurbulence())
            isW &= this->physicsTurbulenceW();
        if (_physicsData->getTransportProp())
            isW &= this->physicsTransportPropW();
        if (_physicsData->getDiscretization())
            isW &= this->physicsDiscretizationW();
        if (_physicsData->getSolution())
            isW &= this->physicsSolutionW();
        if (_physicsData->getInitialConditions())
            isW &= this->physicsInitialConditionsW();
        if (_physicsData->getBoundaryManager())
            isW &= this->physicsBoundaryW();
        if (_physicsData->getRunControl())
            isW &= this->physicsRunControlW();
        if (_physicsData->getOperatingConditions())
            isW &= this->physicsOperatingConditionsW();

        return isW;
    }

    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsSolverW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("Solver");
        Interface::FITKAbstractOFSolver* solverData = _physicsData->getSolver();
        if (!solverData)return false;
        if (!writeNDataObject(solverData, h5Group)) return false;
        std::string solverName = solverData->getDataObjectName().toStdString();
        if (solverName.empty())return false;
        writeStrAttribute(h5Group, "solverName", solverName);
        return true;
    }

    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsSolverR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("Solver"))return true;
        H5::Group h5Group = _h5Group->openGroup("Solver");
        Interface::FITKFlowPhysicsHandlerFactory* factoryData = FITKAPP->getComponents()->getComponentTByName<Interface::FITKFlowPhysicsHandlerFactory>("FITKFlowPhysicsHandlerFactory");
        if (!factoryData) return false;
        std::string solverName = readStrAttribute(h5Group, "solverName");
        factoryData->setSolver(QString::fromStdString(solverName));
        Interface::FITKAbstractOFSolver* solverData = _physicsData->getSolver();
        if (!solverData)return false;
        if (!readDataObject(solverData, h5Group))return false;
        return true;
    }

    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsTurbulenceW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("Turbulence");
        Interface::FITKAbstractOFTurbulence* turbulence = _physicsData->getTurbulence();
        if (!turbulence)return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorTurbulence>("HDF5", "Interface::FITKAbstractOFTurbulence");
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(turbulence);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write Turbulence Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsTurbulenceR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("Turbulence"))return true;
        H5::Group h5Group = _h5Group->openGroup("Turbulence");
        Interface::FITKFlowPhysicsHandlerFactory* factoryData = FITKAPP->getComponents()->getComponentTByName<Interface::FITKFlowPhysicsHandlerFactory>("FITKFlowPhysicsHandlerFactory");
        if (!factoryData) return false;
        std::string turbulenceType = readStrAttribute(h5Group, "turbulenceType");
        factoryData->setTurbence(QString::fromStdString(turbulenceType));
        Interface::FITKAbstractOFTurbulence* turbulence = _physicsData->getTurbulence();
        if (!turbulence)return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorTurbulence>("HDF5", "Interface::FITKAbstractOFTurbulence");
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(turbulence);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Reader Turbulence Errors ! "));
        delete adaptor;
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsTransportPropW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("TransportProp");
        Interface::FITKOFTransportProp* transportProp = _physicsData->getTransportProp();
        if (!transportProp) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorTransportProp>("HDF5", transportProp);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(transportProp);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write transportProp Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsTransportPropR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("TransportProp")) return true;
        H5::Group h5Group = _h5Group->openGroup("TransportProp");
        Interface::FITKOFTransportProp* transportProp = _physicsData->getTransportProp();
        if (!transportProp) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorTransportProp>("HDF5", transportProp);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(transportProp);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Read transportProp Errors ! "));
        delete adaptor;
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsDiscretizationW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("Discretization");
        Interface::FITKOFDiscretization* discretization = _physicsData->getDiscretization();
        if (!discretization) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorDiscretization>("HDF5", discretization);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(discretization);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write Discretization Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsDiscretizationR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("Discretization")) return true;
        H5::Group h5Group = _h5Group->openGroup("Discretization");
        Interface::FITKOFDiscretization* discretization = _physicsData->getDiscretization();
        if (!discretization) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorDiscretization>("HDF5", discretization);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(discretization);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Read Discretization Errors ! "));
        delete adaptor;
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsSolutionW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("Solution");
        Interface::FITKOFSolution* solution = _physicsData->getSolution();
        if (!solution) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorSolution>("HDF5", solution);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(solution);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write Solution Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsSolutionR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("Solution")) return true;
        H5::Group h5Group = _h5Group->openGroup("Solution");
        Interface::FITKOFSolution* solution = _physicsData->getSolution();
        if (!solution) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorSolution>("HDF5", solution);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(solution);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Read Solution Errors ! "));
        delete adaptor;
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsInitialConditionsW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("InitialConditions");
        Interface::FITKOFInitialConditions* initialCond = _physicsData->getInitialConditions();
        if (!initialCond) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorInitialCondition>("HDF5", initialCond);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(initialCond);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write InitialCondition Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsInitialConditionsR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("InitialConditions")) return true;
        H5::Group h5Group = _h5Group->openGroup("InitialConditions");
        Interface::FITKOFInitialConditions* initialCond = _physicsData->getInitialConditions();
        if (!initialCond) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorInitialCondition>("HDF5", initialCond);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(initialCond);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Read InitialCondition Errors ! "));
        delete adaptor;
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsBoundaryW()
    {
        if (!_physicsData || !_writer)return false;
        bool isW = true;
        H5::Group h5Group = _h5Group->createGroup("Bounadry");
        Interface::FITKOFBoundaryManager* boundaryMgr = _physicsData->getBoundaryManager();
        if (!boundaryMgr)return false;
        int count = boundaryMgr->getDataCount();
        writeIntAttribute(h5Group, "BoundaryCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKOFBoundary* boundary = boundaryMgr->getDataByIndex(i);
            if (!boundary) continue;
            std::string name = std::to_string(i);
            H5::Group boundaryH5Group = h5Group.createGroup(name);
            int boundaryType = boundary->getBoundaryType();
            writeIntAttribute(h5Group, name, &boundaryType);
            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorBoundary>("HDF5", boundary);
            if (adaptor == nullptr) return false;
            adaptor->setH5GroupData(boundaryH5Group);
            adaptor->setDataObject(boundary);
            adaptor->setFileWriter(_writer);
            bool w = adaptor->adaptW();
            if (!w) consoleMessage(3, QString("Write boundary Errors : %1 ! ").arg(boundary->getDataObjectName()));
            delete adaptor;
            isW &= w;
        }
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsBoundaryR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("Bounadry")) return true;
        Interface::FITKFlowPhysicsHandlerFactory* factoryData = FITKAPP->getComponents()->getComponentTByName<Interface::FITKFlowPhysicsHandlerFactory>("FITKFlowPhysicsHandlerFactory");
        if (!factoryData) return false;
        bool isR = true;
        H5::Group h5Group = _h5Group->openGroup("Bounadry");
        Interface::FITKOFBoundaryManager* boundaryMgr = _physicsData->getBoundaryManager();
        if (!boundaryMgr) return false;
        boundaryMgr->clear();
        int count = readIntAttribute(h5Group, "BoundaryCount");
        for (int i = 0; i < count; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.nameExists(name))continue;
            H5::Group boundaryH5Group = h5Group.openGroup(name);
            int boundaryType = readIntAttribute(h5Group, name);
            Interface::FITKOFBoundary* boundary = new Interface::FITKOFBoundary(Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType(boundaryType));
            boundaryMgr->appendDataObj(boundary);
            auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorBoundary>("HDF5", boundary);
            if (adaptor == nullptr) return false;
            adaptor->setH5GroupData(boundaryH5Group);
            adaptor->setDataObject(boundary);
            adaptor->setFileReader(_reader);
            bool r = adaptor->adaptR();
            if (!r) consoleMessage(3, QString("Read boundary Errors : %1 ! ").arg(boundary->getDataObjectName()));
            delete adaptor;
            isR &= r;
        }
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsRunControlW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("RunControl");
        Interface::FITKOFRunControl* runControl = _physicsData->getRunControl();
        if (!runControl) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorRunControl>("HDF5", runControl);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(runControl);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write RunControl Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsRunControlR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("RunControl")) return true;
        H5::Group h5Group = _h5Group->openGroup("RunControl");
        Interface::FITKOFRunControl* runControl = _physicsData->getRunControl();
        if (!runControl) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorRunControl>("HDF5", runControl);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(runControl);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Read RunControl Errors ! "));
        delete adaptor;
        return isR;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsOperatingConditionsW()
    {
        if (!_physicsData || !_writer)return false;
        H5::Group h5Group = _h5Group->createGroup("OperatingConditions");
        Interface::FITKOFOperatingConditions* operatingCond = _physicsData->getOperatingConditions();
        if (!operatingCond) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorOperatingCond>("HDF5", operatingCond);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(operatingCond);
        adaptor->setFileWriter(_writer);
        bool isW = adaptor->adaptW();
        if (!isW) consoleMessage(3, QString("Write OperatingCondition Errors ! "));
        delete adaptor;
        return isW;
    }
    bool FITKFlowOFHDF5AdaptorPhysicsData::physicsOperatingConditionsR()
    {
        if (!_physicsData || !_reader)return false;
        if (!_h5Group->nameExists("OperatingConditions")) return true;
        H5::Group h5Group = _h5Group->openGroup("OperatingConditions");
        Interface::FITKOFOperatingConditions* operatingCond = _physicsData->getOperatingConditions();
        if (!operatingCond) return false;
        auto adaptor = FITKIOADAPTORFACTORY->createT<FITKFlowOFHDF5AdaptorOperatingCond>("HDF5", operatingCond);
        if (adaptor == nullptr) return false;
        adaptor->setH5GroupData(h5Group);
        adaptor->setDataObject(operatingCond);
        adaptor->setFileReader(_reader);
        bool isR = adaptor->adaptR();
        if (!isR) consoleMessage(3, QString("Read OperatingCondition Errors ! "));
        delete adaptor;
        return isR;
    }

}
