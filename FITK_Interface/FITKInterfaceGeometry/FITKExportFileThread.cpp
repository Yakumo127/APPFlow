#include "FITKExportFileThread.h"

// App
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"

// Geometry
#include "FITKGeoInterfaceFactory.h"
#include "FITKGeoCommandList.h"
#include "FITKAbsGeoModelExport.h"

namespace Interface
{
    void FITKExportFileThread::run()
    {
        m_newIds.clear();
        // Check the file path.
        if (m_filePath.isEmpty())
        {
            m_isRunning = false;
            AppFrame::FITKMessageError(tr("Invalid geometry file path!"));
            emit sig_readFinished(false);
            return;
        }

        // Check the geometry component.
        Interface::FITKGeoCommandList* geoList = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();
        Interface::FITKInterfaceGeometryFactory* geoFac = Interface::FITKInterfaceGeometryFactory::getInstance();
        if (!geoFac || !geoList)
        {
            m_isRunning = false;
            AppFrame::FITKMessageError(tr("Invalid geometry component!"));
            emit sig_readFinished(false);
            return;
        }

        // Create the reader.
        Interface::FITKAbsGeoModelExport* exportCmd = geoFac->createCommandT<Interface::FITKAbsGeoModelExport>(m_ioType);
        if (!exportCmd)
        {
            m_isRunning = false;
            AppFrame::FITKMessageError(tr("Non-supported writeing method!"));
            emit sig_readFinished(false);
            return;
        }
        m_isRunning = true;
        emit sendProcessSig(this, -1);
        exportCmd->setFileName(m_filePath);
        bool flag = exportCmd->update();
        if (!flag)
        {
            m_isRunning = false;
            AppFrame::FITKMessageError(tr("Failed writeing geometry from %1.").arg(m_filePath));
            emit sig_readFinished(false);
        }
        else
        {
            // Save the ids.
            m_newIds = exportCmd->getCreatedCommandIds();
            AppFrame::FITKMessageNormal(tr("write geometry from %1.").arg(m_filePath));
            emit sig_readFinished(true);
        }

        // Clear cache.
        m_filePath.clear();
        emit sendProcessSig(this, 100);
        m_isRunning = false;
    }

    void FITKExportFileThread::setFilePath(QString filePath)
    {
        m_filePath = filePath;
    }

    void FITKExportFileThread::setImportedMethod(Interface::FITKGeoEnum::FITKGeometryComType type)
    {
        switch (type)
        {
        case Interface::FITKGeoEnum::FGTExportPart:
            m_ioType = type;
            return;
        default:
            return;
        }
    }

    const QList<int> & FITKExportFileThread::newCmdIds()
    {
        return m_newIds;
    }

    bool FITKExportFileThread::isRunning()
    {
        return m_isRunning;
    }
}