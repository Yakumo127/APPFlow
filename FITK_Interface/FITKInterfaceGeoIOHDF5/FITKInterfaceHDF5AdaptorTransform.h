/*****************************************************************//**
 *
 * @file   FITKInterfaceHDF5AdaptorTransform.h
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
ForwardDeclarNS(Interface, FITKAbsGeoModelTransform);
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
    class FITKINTERFACEGEOIOHDF5API FITKInterfaceHDF5AdaptorTransform : public FITKAbstractHDF5Adaptor
    {
    public:
        /**
         * @brief Construct a new FITKInterfaceHDF5AdaptorTransform object
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        explicit FITKInterfaceHDF5AdaptorTransform() = default;
        virtual ~FITKInterfaceHDF5AdaptorTransform() = default;


        /**
         * @brief 获取适配器数据类型名
         * @return 适配器数据类型名
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        QString getAdaptorClass() override;

        /**
         * @brief 适配器读取
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool adaptR() override;

        /**
         * @brief 适配器写出
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool adaptW() override;

    protected:

        /**
         * @brief read
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool read(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool write(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read Base
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readTransfromBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write Base
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeTransfromBase(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read transformation
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readTransformation(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write transformation
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeTransformation(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read transformationByTwoPoints
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readTransformationByTwoPoints(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write transformationByTwoPoints
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeTransformationByTwoPoints(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read transformationByDirAndDis
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readTransformationByDirAndDis(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write transformationByDirAndDis
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeTransformationByDirAndDis(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read Rotate
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readRotate(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write Rotate
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeRotate(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief read Scale
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool readScale(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

        /**
         * @brief write Scale
         * @param agent agent
         * @param h5Group dataBlock
         * @return 状态 true成功， false失败
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-09-24
         */
        bool writeScale(Interface::FITKAbsGeoCommand* comm, H5::Group& h5Group);

    };

    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoTransformation, FITKInterfaceHDF5AdaptorTransform, 1)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelTransform, FITKInterfaceHDF5AdaptorTransform, 2)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelTransformByTwoPoints, FITKInterfaceHDF5AdaptorTransform, 3)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelTransformByDirAndDis, FITKInterfaceHDF5AdaptorTransform, 4)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRotate, FITKInterfaceHDF5AdaptorTransform, 5)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelScale, FITKInterfaceHDF5AdaptorTransform, 6)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelMirror, FITKInterfaceHDF5AdaptorTransform, 7)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelPattern, FITKInterfaceHDF5AdaptorTransform, 8)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelRectangularPattern, FITKInterfaceHDF5AdaptorTransform, 9)
    Register2FITKIOAdaptorFactory(HDF5, Interface::FITKAbsGeoModelCircularPattern, FITKInterfaceHDF5AdaptorTransform, 10)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTTransform, FITKInterfaceHDF5AdaptorTransform, 2)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTTransformByTwoPoints, FITKInterfaceHDF5AdaptorTransform, 3)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTTransformByDirAndDis, FITKInterfaceHDF5AdaptorTransform, 4)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTRotate, FITKInterfaceHDF5AdaptorTransform, 5)
    //Register2FITKIOAdaptorFactory(HDF5, Interface::FITKGeoEnum::FGTScale, FITKInterfaceHDF5AdaptorTransform, 6)

}


#endif
