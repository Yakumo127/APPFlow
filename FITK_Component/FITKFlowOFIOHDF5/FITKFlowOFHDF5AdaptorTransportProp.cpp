#include "FITKFlowOFHDF5AdaptorTransportProp.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFTransportProp.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFTransportModel.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKFlowPhysicsHandlerFactory.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITKFlowOFHDF5Reader.h"
#include "FITKFlowOFHDF5Writer.h"

//数据层
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"



#include <QDebug>
namespace IO
{
    QString FITKFlowOFHDF5AdaptorTransportProp::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorTransportProp";
    }

    bool FITKFlowOFHDF5AdaptorTransportProp::adaptR()
    {
        _transportProp = dynamic_cast<Interface::FITKOFTransportProp*>(_dataObj);
        if (!_reader || !_transportProp) return false;
        if (!readNDataObject(_transportProp, *_h5Group)) return false;
        bool isR = true;
        isR &= this->transportAdditionalDataR();

        isR &= this->phasesR();

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorTransportProp::adaptW()
    {
        _transportProp = dynamic_cast<Interface::FITKOFTransportProp*>(_dataObj);
        if (!_writer || !_transportProp) return false;
        if (!writeNDataObject(_transportProp, *_h5Group)) return false;
        bool isW = true;
        isW &= this->transportAdditionalDataW();

        isW &= this->phasesW();
        return true;
    }

    bool FITKFlowOFHDF5AdaptorTransportProp::transportAdditionalDataW()
    {
        if (!_writer || !_transportProp)return false;
        H5::Group h5Group = _h5Group->createGroup("TransportAdditionalData");
        //如果为空就证明没有数据
        Core::FITKParameter* additionalTran = _transportProp->getTransportAdditionalData();
        if (additionalTran)
            parameterToolW(h5Group, additionalTran);
        return true;
    }

    bool FITKFlowOFHDF5AdaptorTransportProp::transportAdditionalDataR()
    {
        if (!_reader || !_transportProp)return false;
        if (!_h5Group->nameExists("TransportAdditionalData"))return false;
        H5::Group h5Group = _h5Group->openGroup("TransportAdditionalData");
        if (h5Group.getNumAttrs() > 0)
        {
            Core::FITKParameter* additionalTran = new Core::FITKParameter;
            parameterToolR(h5Group, additionalTran);
            _transportProp->setTransportAdditionalData(additionalTran);
        }
        return true;
    }

    bool FITKFlowOFHDF5AdaptorTransportProp::phasesW()
    {
        if (!_writer || !_transportProp)return false;
        H5::Group h5Group = _h5Group->createGroup("Phases");
        int phaseCount = _transportProp->getPhasesCount();
        writeIntAttribute(h5Group, "PhaseCount", &phaseCount);
        for (int i = 0; i < phaseCount; ++i)
        {
            Interface::FITKOFTransportPhase* phase = _transportProp->getPhase(i);
            if (!phase)continue;
            std::string name = std::to_string(i);
            H5::Group phaseH5Group = h5Group.createGroup(name);
            //名称
            QString phaseName = phase->getPhaseName();
            writeStrAttribute(phaseH5Group, "PhaseName", phaseName.toStdString());
            //其他数据
            H5::Group addH5Group = phaseH5Group.createGroup("AdditionalData");
            Core::FITKParameter* additionData = phase->getPhaseAdditionalData();
            if (additionData) parameterToolW(addH5Group, additionData);
            //模式数据
            Interface::FITKAbsOFTransportModel* model = phase->getTransportModel();
            if (model)
            {
                writeStrAttribute(phaseH5Group, "ModelName", model->getDataObjectName().toStdString());
                H5::Group modelH5Group = phaseH5Group.createGroup("ModelData");
                writeNDataObject(model, modelH5Group);
                parameterToolW(modelH5Group, model->getTransportModelPara());
            }
        }
        return true;
    }

    bool FITKFlowOFHDF5AdaptorTransportProp::phasesR()
    {
        if (!_reader || !_transportProp)return false;
        if (!_h5Group->nameExists("Phases"))return false;
        Interface::FITKFlowPhysicsHandlerFactory* factoryData = FITKAPP->getComponents()->getComponentTByName<Interface::FITKFlowPhysicsHandlerFactory>("FITKFlowPhysicsHandlerFactory");
        if (!factoryData) return false;
        H5::Group h5Group = _h5Group->openGroup("Phases");
        int phaseCount = readIntAttribute(h5Group, "PhaseCount");
        if (_transportProp->getPhasesCount() != phaseCount) return false;
        for (int i = 0; i < phaseCount; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.nameExists(name))continue;
            Interface::FITKOFTransportPhase* phase = _transportProp->getPhase(i);
            if (!phase)return false;
            H5::Group phaseH5Group = h5Group.openGroup(name);
            //名称
            QString phaseName = QString::fromStdString(readStrAttribute(phaseH5Group, "PhaseName"));
            phase->setPhaseName(phaseName);
            //其他数据
            if (!phaseH5Group.nameExists("AdditionalData"))return false;
            H5::Group addH5Group = phaseH5Group.openGroup("AdditionalData");
            if (addH5Group.getNumAttrs() > 0)
            {
                Core::FITKParameter* additionData = new Core::FITKParameter;
                parameterToolR(addH5Group, additionData);
                phase->setPhaseAdditionalData(additionData);
            }
            //模式数据
            if (phaseH5Group.attrExists("ModelName"))
            {
                QString modelName = QString::fromStdString(readStrAttribute(phaseH5Group, "ModelName"));
                factoryData->setTransportModel(i, modelName);
                H5::Group modelH5Group = phaseH5Group.openGroup("ModelData");
                Interface::FITKAbsOFTransportModel* model = phase->getTransportModel();
                readNDataObject(model, modelH5Group);
                model->getTransportModelPara()->clear();
                parameterToolR(modelH5Group, model->getTransportModelPara());
            }
        }
        return true;
    }

}
