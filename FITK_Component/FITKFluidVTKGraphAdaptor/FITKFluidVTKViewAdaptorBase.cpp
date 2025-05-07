#include "FITKFluidVTKViewAdaptorBase.h"

// Graph and data
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITKFluidVTKGraphObject3D.h"

namespace Exchange
{
    void FITKFluidVTKViewAdaptorBase::setDataObject(Core::FITKAbstractDataObject* data)
    {
        if (data && data != _dataObj)
        {
            m_needUpdate = true;
        }

        Adaptor::FITKAbstractViewAdaptor::setDataObject(data);
    }

    void FITKFluidVTKViewAdaptorBase::setDetails(QVariant details)
    {
        // Set the details information for exchanging data.
        m_details = details;
    }

    Exchange::FITKFluidVTKGraphObject3D* FITKFluidVTKViewAdaptorBase::getOutputData()
    {
        // The data exchanged to the output
        return m_outputData;
    }

    bool FITKFluidVTKViewAdaptorBase::update()
    {
        // override in subclass
        return true;
    }
}   // namespace Exchange
