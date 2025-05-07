#ifndef _FITK_GEO_MODELCOMMAND_EXPORT__H___
#define _FITK_GEO_MODELCOMMAND_EXPORT__H___
 
#include "FITKInterfaceGeometryAPI.h"
#include "FITKAbsGeoCommand.h"
#include <QString>

namespace Interface
{
    class FITKInterfaceGeometryAPI FITKAbsGeoModelExportCommonds :
        public  FITKAbsGeoCommand
    {
        FITKCLASS(Interface, FITKAbsGeoModelExportCommonds);
    public:

        explicit FITKAbsGeoModelExportCommonds() = default;
        virtual ~FITKAbsGeoModelExportCommonds() = default;

        /**
         * @brief   设置文件名称
         * @param   fileName：文件名称
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        void setFileName(const QString& fileName);

        /**
         * @brief   获取文件名称
         * @return  FITKGeoEnum::FITKGeometryComType
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        QString getFileName() const;

        /**
         * @brief   设置导出的命令ID
         * @param   fileName：文件名称
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        void setExportCommandIDs(QList<int> ids);

        /**
         * @brief   获取导出的命令ID
         * @return  FITKGeoEnum::FITKGeometryComType
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        QList<int> getExportCommandIDs() const;

        /**
         * @brief   获取几何命令类型
         * @return  FITKGeoEnum::FITKGeometryComType
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;


    protected:
        /**
         * @brief   导出的文件名
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        QString _exportFileName{};

        /**
         * @brief   导出的命令ID列表
         * @author  fulipeng (flipengqd@yeah.net)
         * @date    2025-01-17
         */
        QList<int> commandIDs{};

    };
}

#endif
