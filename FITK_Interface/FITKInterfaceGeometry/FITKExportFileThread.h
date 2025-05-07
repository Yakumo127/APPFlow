﻿/*****************************************************************//**
 * @file    FITKExportFileThread.h
 * @brief   File IO thread class for exoprting geometry.
 *
 * @author  fulipeng (flipengqd@yeah.net)
 * @date    2025-01-16
 *********************************************************************/

#ifndef __FITKEXPORTFILETHREAD_H__
#define __FITKEXPORTFILETHREAD_H__
#include "FITKInterfaceGeometryAPI.h"
#include "FITKGeoEnum.h"
#include "FITK_Kernel/FITKCore/FITKThreadTask.h"
#include <QList>

namespace Interface
{
    /**
     * @brief   File IO thread class for exoprting geometry.
     * @author  fulipeng (flipengqd@yeah.net)
     * @date    2025-01-16
     */
    class FITKInterfaceGeometryAPI FITKExportFileThread : public Core::FITKThreadTask
    {
        Q_OBJECT
    public:
        /**
         * @brief   Constructor.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        explicit FITKExportFileThread() = default;

        /**
         * @brief   Destructor.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        virtual ~FITKExportFileThread() = default;

        /**
         * @brief   The task execute function.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        virtual void run() override;

        /**
         * @brief   Set the geometry file path.
         * @param   filePath: The geometry file path
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        void setFilePath(QString filePath);

        /**
         * @brief   Set the imported method.
         * @param   type: The import command type
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        void setImportedMethod(Interface::FITKGeoEnum::FITKGeometryComType type);

        /**
         * @brief   Get the ids of the writer geometry command.
         * @return  The id list[const][quote]
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        const QList<int> & newCmdIds();

        /**
         * @brief   Get the running state of the task.
         * @return  Is the task running
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        bool isRunning();

    signals:
        /**
         * @brief   Signal - For IO thread finish.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        void sig_readFinished(bool status);

    protected:
        /**
         * @brief   The geometry file path.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        QString m_filePath;

        /**
         * @brief   The imported method.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        Interface::FITKGeoEnum::FITKGeometryComType m_ioType = 
            Interface::FITKGeoEnum::FITKGeometryComType::FGTExportPart;

        /**
         * @brief   The new command ids.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        QList<int> m_newIds;

        /**
         * @brief   The running state of the task.
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-16
         */
        bool m_isRunning = false;

    };
}

#endif // !__FITKExportFileThread_H__
