#include "FITKFlowOFHDF5AdaptorTurbulence.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFTurbulence.h"

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
    QString FITKFlowOFHDF5AdaptorTurbulence::getAdaptorClass()
    {
        return "FITKFlowOFHDF5AdaptorTurbulence";
    }

    bool FITKFlowOFHDF5AdaptorTurbulence::adaptR()
    {
        _turbulence = dynamic_cast<Interface::FITKAbstractOFTurbulence*>(_dataObj);
        if (!_reader || !_turbulence) return false;
        if (!readNDataObject(_turbulence, *_h5Group)) return false;
        bool isR = true;

        isR &= turbulenceParaR();
        isR &= deltaR();

        return isR;
    }

    bool FITKFlowOFHDF5AdaptorTurbulence::adaptW()
    {
        _turbulence = dynamic_cast<Interface::FITKAbstractOFTurbulence*>(_dataObj);
        if (!_writer || !_turbulence) return false;
        if (!writeNDataObject(_turbulence, *_h5Group)) return false;
        bool isW = true;
        //写出湍流类型
        std::string turbulenceType = _turbulence->getDataObjectName().toStdString();
        writeStrAttribute(*_h5Group, "turbulenceType", turbulenceType);

        isW &= turbulenceParaW();
        isW &= deltaW();

        return isW;
    }

    bool FITKFlowOFHDF5AdaptorTurbulence::turbulenceParaW()
    {
        if (!_writer || !_turbulence)return false;
        H5::Group h5Group = _h5Group->createGroup("TurbulencePara");
        if (_turbulence->getTurbulenceParams())
            parameterToolW(h5Group, _turbulence->getTurbulenceParams());
        return true;
    }
    bool FITKFlowOFHDF5AdaptorTurbulence::turbulenceParaR()
    {
        if (!_reader || !_turbulence)return false;
        if (!_h5Group->nameExists("TurbulencePara"))return false;
        H5::Group h5Group = _h5Group->openGroup("TurbulencePara");
        if (h5Group.getNumAttrs() > 0)
        {
            Core::FITKParameter* turbPara = _turbulence->getTurbulenceParams();
            if (!turbPara) return false;
            turbPara->clear();
            parameterToolR(h5Group, turbPara);
        }
        return true;
    }
    bool FITKFlowOFHDF5AdaptorTurbulence::deltaW()
    {
        if (!_writer || !_turbulence)return false;
        H5::Group h5Group = _h5Group->createGroup("Delta");
        if (_turbulence->getDeltaParams())
            parameterToolW(h5Group, _turbulence->getDeltaParams());
        return true;
    }
    bool FITKFlowOFHDF5AdaptorTurbulence::deltaR()
    {
        if (!_reader || !_turbulence)return false;
        if (!_h5Group->nameExists("Delta"))return false;
        H5::Group h5Group = _h5Group->openGroup("Delta");
        if (h5Group.getNumAttrs() > 0)
        {
            Core::FITKParameter* delta = _turbulence->getDeltaParams();
            if (!delta) return false;
            delta->clear();
            parameterToolR(h5Group, delta);
        }
        return true;
    }
}
