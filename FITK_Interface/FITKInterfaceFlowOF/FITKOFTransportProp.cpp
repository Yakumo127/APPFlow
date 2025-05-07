#include "FITKOFTransportProp.h"
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITKOFTransportModel.h"

namespace Interface
{
    FITKOFTransportPhase::FITKOFTransportPhase()
    {

    }

    FITKOFTransportPhase::~FITKOFTransportPhase()
    {
        if (_additional) delete _additional;
        if (_transportModel) delete _transportModel;
    }

    QString FITKOFTransportPhase::getPhaseName()
    {
        return _name;
    }

    Core::FITKParameter* FITKOFTransportPhase::getPhaseAdditionalData()
    {
        return _additional;
    }

    FITKAbsOFTransportModel* FITKOFTransportPhase::getTransportModel()
    {
        return _transportModel;
    }

    void FITKOFTransportPhase::setPhaseName(QString name)
    {
        _name = name;
    }

    void FITKOFTransportPhase::setPhaseAdditionalData(Core::FITKParameter* data)
    {
        if (_additional != data && _additional) delete _additional;
        _additional = data;
    }

    void FITKOFTransportPhase::setTransportModel(FITKAbsOFTransportModel* modelData)
    {
        if (_transportModel != modelData && _transportModel) delete _transportModel;
        _transportModel = modelData;
    }

    FITKOFTransportProp::FITKOFTransportProp()
    {
        _additionalTrans = new Core::FITKParameter;
    }

    FITKOFTransportProp::~FITKOFTransportProp()
    {
        if (_additionalTrans) delete _additionalTrans;
        for (FITKOFTransportPhase* phase : _phases)
            if (phase) delete phase;
    }

    int FITKOFTransportProp::getPhasesCount()
    {
        return _phases.size();
    }

    FITKOFTransportPhase* FITKOFTransportProp::getPhase(int index)
    {
        if (index < 0 || index >= _phases.size())return nullptr;
        return _phases.at(index);
    }

    Core::FITKParameter* FITKOFTransportProp::getTransportAdditionalData()
    {
        return _additionalTrans;
    }

    void FITKOFTransportProp::appendPhase(FITKOFTransportPhase* phase)
    {
        if (!phase)return;
        _phases.append(phase);
    }

    void FITKOFTransportProp::setTransportAdditionalData(Core::FITKParameter* tranAddData)
    {
        if (_additionalTrans != tranAddData && _additionalTrans) delete _additionalTrans;
        _additionalTrans = tranAddData;
    }
}
