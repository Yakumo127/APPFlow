/*****************************************************************//**
 *
 * @file   FITKOCCHDF5AdaptorDatum.h
 * @brief  基准几何适配器。
 * @author fulipeng (flipengqd@yeah.net)
 * @date   2024-09-09
 *
 *********************************************************************/
#ifndef __FITKABAQUSABAQUSWRITER_H__
#define __FITKABAQUSABAQUSWRITER_H__

#include "FITKGeoOCCIOHDF5API.h"
#include "FITK_Kernel/FITKCore/FITKCoreMacros.h"
#include "FITK_Kernel/FITKAdaptor/FITKIOAdaptorFactory.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKInterfaceHDF5AdaptorDatum.h"

ForwardDeclarNS(Core, FITKAbstractDataObject);
ForwardDeclarNS(Interface, FITKAbsGeoCommand);
ForwardDeclarNS(Interface, FITKAbsGeoDatum);
ForwardDeclarNS(Interface, FITKAbsGeoReferencePlane);
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
    class FITKGEOOCCIOHDF5API FITKOCCHDF5AdaptorDatum : public FITKInterfaceHDF5AdaptorDatum
    {
    public:
        /**
         * @brief Construct a new FITKOCCHDF5AdaptorDatum object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-09
         */
        explicit FITKOCCHDF5AdaptorDatum() = default;
        virtual ~FITKOCCHDF5AdaptorDatum() = default;

        /**
         * @brief   get adapter data type name
         * @return  adapter data type name
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-14
         */
        QString getAdaptorClass() override;

        /**
         * @brief   read adaptor
         * @return  status
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-14
         */
        bool adaptR() override;

        /**
         * @brief   write adaptor
         * @return  status
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-09-14
         */
        bool adaptW() override;


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

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoDatum, FITKOCCHDF5AdaptorDatum, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoReferencePlane, FITKOCCHDF5AdaptorDatum, 2)

}


#endif
