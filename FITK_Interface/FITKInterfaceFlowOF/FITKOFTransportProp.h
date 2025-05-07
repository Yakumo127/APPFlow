#ifndef _FITK_OF_TRANSPORT_PROP__H___
#define _FITK_OF_TRANSPORT_PROP__H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"


namespace Core
{
    class FITKParameter;
}

namespace Interface
{
    class FITKAbsOFTransportModel;

    class FITKInterfaceFlowOFAPI FITKOFTransportPhase
    {
    public:
        explicit FITKOFTransportPhase();
        virtual ~FITKOFTransportPhase();

        QString getPhaseName();
        Core::FITKParameter* getPhaseAdditionalData();
        FITKAbsOFTransportModel* getTransportModel();


        void setPhaseName(QString name);
        void setPhaseAdditionalData(Core::FITKParameter* data);
        void setTransportModel(FITKAbsOFTransportModel* modelData);

    private:
        QString _name{};
        Core::FITKParameter* _additional{};
        FITKAbsOFTransportModel* _transportModel{};
    };

    class FITKInterfaceFlowOFAPI FITKOFTransportProp : public Core::FITKAbstractNDataObject
    {
        Q_OBJECT
            FITKCLASS(Interface, FITKOFTransportProp);
    public:
        explicit FITKOFTransportProp();
        virtual ~FITKOFTransportProp();

        int getPhasesCount();
        FITKOFTransportPhase* getPhase(int index);
        Core::FITKParameter* getTransportAdditionalData();

        void appendPhase(FITKOFTransportPhase* phase);
        void setTransportAdditionalData(Core::FITKParameter* tranAddData);

    protected:
    private:
        Core::FITKParameter* _additionalTrans{};
        QList<FITKOFTransportPhase*> _phases{};
    };
}


#endif
