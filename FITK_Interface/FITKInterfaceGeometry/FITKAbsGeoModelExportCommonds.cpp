#include "FITKAbsGeoModelExportCommonds.h"

namespace Interface
{
    void FITKAbsGeoModelExportCommonds::setFileName(const QString& fileName)
    {
        _exportFileName = fileName;
    }

    QString FITKAbsGeoModelExportCommonds::getFileName() const
    {
        return _exportFileName;
    }

    void FITKAbsGeoModelExportCommonds::setExportCommandIDs(QList<int> ids)
    {
        commandIDs = ids;
    }

    QList<int> FITKAbsGeoModelExportCommonds::getExportCommandIDs() const
    {
        return commandIDs;
    }

    FITKGeoEnum::FITKGeometryComType FITKAbsGeoModelExportCommonds::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTExportCommands;
    }

}