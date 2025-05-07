/*****************************************************************//**
 *
 * @file   FITKOCCHDF5AdaptorCommand.h
 * @brief  普通几何的HDF5适配器。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef __FITKABAQUSABAQUSWRITER_H__
#define __FITKABAQUSABAQUSWRITER_H__

#include "FITKGeoOCCIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorCommand.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoDelete);
ForwardDeclarNS(H5, H5File);
ForwardDeclarNS(H5, Group);
ForwardDeclarNS(H5, H5Object);
ForwardDeclarNS(H5, DataType);

namespace IO
{
    /**
    * @brief HDF5 Adaptor Command
    * @author fulipeng (fulipengqd@yeah.net)
    * @date 2024-09-09
    */
    class FITKGEOOCCIOHDF5API FITKOCCHDF5AdaptorCommand : public FITKInterfaceHDF5AdaptorCommand
    {
    public:
        /**
         * @brief Construct a new FITKOCCHDF5AdaptorCommand object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        explicit FITKOCCHDF5AdaptorCommand() = default;
        virtual ~FITKOCCHDF5AdaptorCommand() = default;

    protected:

        /**
         * @brief   read Virtual Shape
         * @param   agent agent
         * @param   h5Group dataBlock
         * @return  status
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        virtual bool readVShape(Interface::FITKAbsGeoCommand * comm, H5::Group & h5Group)  override;

        /**
         * @brief   write Virtual Shape
         * @param   agent agent
         * @param   h5Group dataBlock
         * @return  status
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-10
         */
        virtual bool writeVShape(Interface::FITKAbsGeoShapeAgent* agent, H5::Group & h5Group)  override;
    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoCommand, FITKOCCHDF5AdaptorCommand, 1)

}


#endif
