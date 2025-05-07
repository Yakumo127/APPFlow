﻿#include "FITKImportFileThread.h"

// App
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"

// Geometry
#include "FITKGeoInterfaceFactory.h"
#include "FITKGeoCommandList.h"
#include "FITKAbsGeoImportBase.h"

namespace Interface
{
    void FITKImportFileThread::run()
    {
        m_isRunning = true;

        emit sendProcessSig(this, -1);

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
        Interface::FITKAbsGeoImportBase* importCmd = geoFac->createCommandT<Interface::FITKAbsGeoImportBase>
            (m_ioType);
        if (!importCmd)
        {
            m_isRunning = false;
            AppFrame::FITKMessageError(tr("Non-supported reading method!"));
            emit sig_readFinished(false);
            return;
        }

        importCmd->setFileName(m_filePath);
        
        bool flag = importCmd->update();
        if (!flag)
        {
            m_isRunning = false;
            AppFrame::FITKMessageError(tr("Failed reading geometry from %1.").arg(m_filePath));
            emit sig_readFinished(false);
            return;
        }

        // Save the ids.
        m_newIds = importCmd->getCreatedCommandIds();

        AppFrame::FITKMessageNormal(tr("Read geometry from %1.").arg(m_filePath));

        // Clear cache.
        m_filePath.clear();

        emit sig_readFinished(true);

        emit sendProcessSig(this, 100);

        m_isRunning = false;
    }

    void FITKImportFileThread::setFilePath(QString filePath)
    {
        m_filePath = filePath;
    }

    void FITKImportFileThread::setImportedMethod(Interface::FITKGeoEnum::FITKGeometryComType type)
    {
        switch (type)
        {
        case Interface::FITKGeoEnum::FGTImport:
        case Interface::FITKGeoEnum::FGTImportMergePart:
        // case Interface::FITKGeoEnum::FGTImportSplitPart:
        case Interface::FITKGeoEnum::FGTImportFlattenAssembly:
        // case Interface::FITKGeoEnum::FGTImportSplitAssembly:
        // case Interface::FITKGeoEnum::FGTImportPart:
            m_ioType = type;
            return;
        default:
            return;
        }
    }

    const QList<int> & FITKImportFileThread::newCmdIds()
    {
        return m_newIds;
    }

    bool FITKImportFileThread::isRunning()
    {
        return m_isRunning;
    }
}