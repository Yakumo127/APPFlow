/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorSplitter.h
 * @brief  HDF5 Adaptor Command。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-24
 *
 *********************************************************************/
#ifndef __FITKABAQUSABAQUSWRITER_H__
#define __FITKABAQUSABAQUSWRITER_H__

#include "FITKInterfaceGeoIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorCommand.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoSplitter);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Command
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-24
    */
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorSplitter : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorSplitter object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        explicit FITKInterfaceHDF5AdaptorSplitter() = default;
        virtual ~FITKInterfaceHDF5AdaptorSplitter() = default;


        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool adaptW() override;

    protected:

        /**
         * @brief read
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool read(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool write(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read Base
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readSplitterBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write Base
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeSplitterBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read CurveSplitter
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readCurveSplitter(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write CurveSplitter
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeCurveSplitter(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read SurfaceSplitter
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readSurfaceSplitter(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write SurfaceSplitter
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeSurfaceSplitter(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read SolidSplitter
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readSolidSplitter(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write SolidSplitter
         * @param agent agent
         * @param h5Group dataBlock
         * @return status
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeSolidSplitter(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoSplitter, FITKInterfaceHDF5AdaptorSplitter, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoCurveSplitter, FITKInterfaceHDF5AdaptorSplitter, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoSurfaceSplitter, FITKInterfaceHDF5AdaptorSplitter, 3)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTCurveSplitter, FITKInterfaceHDF5AdaptorSplitter, 2)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTSurfaceSplitter, FITKInterfaceHDF5AdaptorSplitter, 3)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTSolidSplitter, FITKInterfaceHDF5AdaptorSplitter, 4)
}


#endif
