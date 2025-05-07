/**********************************************************************
 * @file   FITKFlowOFHDF5AbstractAdaptor.h
 * @brief  抽象的HDF5文件读写适配器
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-09-07
 *********************************************************************/
#ifndef _FITKFLOWOFHDTF5ABSTRACTADAPTOR_H__
#define _FITKFLOWOFHDTF5ABSTRACTADAPTOR_H__

#include "FITKFlowOFIOHDF5API.h"
#include "FITK_Kernel/FITKAdaptor/FITKAbstractIOAdaptor.h"
#include "FITK_Interface/FITKInterfaceGeoIOHDF5/FITKAbstractHDF5Adaptor.h"

ForwardDeclarNS(H5, Group)

namespace Core
{
    class FITKAbstractNDataObject;
    class FITKParameter;
    class FITKParamBool;
    class FITKParamInt;
    class FITKParamDouble;
    class FITKParamString;
    class FITKParamBoolGroup;
    class FITKParamCombox;
    class FITKParamDoubleList;
    class FITKParamRadioGroup;
    class FITKParamLabel;
}

namespace IO
{
    class FITKAbstractHDF5Reader;
    class FITKAbstractHDF5Writer;
    /**
     * @brief 抽象的HDF5文件读写适配器
     * @author fulipeng (fulipengqd@yeah.net)
     * @date 2024-03-15
     */
    class FITKFLOWOFIOHDF5API FITKFlowOFHDF5AbstractAdaptor : public FITKAbstractHDF5Adaptor
    {
        FITKCLASS(IO, FITKFlowOFHDF5AbstractAdaptor);

    public:
        explicit FITKFlowOFHDF5AbstractAdaptor() = default;
        ~FITKFlowOFHDF5AbstractAdaptor();

        /**
         * @brief 输出消息
         * @param errorLevel等级
         * @param str 输出内容
         * @author fulipeng (fulipengqd@yeah.net)
         * @date 2024-03-15
         */
        void consoleMessage(int errorLevel, QString str);

    protected:

        bool parameterToolW(H5::Group& h5Group, Core::FITKParameter* paraData);

        bool parameterBoolW(H5::Group& h5Group, Core::FITKParamBool* paraBool);

        bool parameterComboxW(H5::Group& h5Group, Core::FITKParamCombox* paraCombox);

        bool parameterDoubleW(H5::Group& h5Group, Core::FITKParamDouble* paraDouble);

        bool parameterIntW(H5::Group& h5Group, Core::FITKParamInt* paraInt);

        bool parameterLabelW(H5::Group& h5Group, Core::FITKParamLabel* paraLabel);

        bool parameterStringW(H5::Group& h5Group, Core::FITKParamString* paraString);

        bool parameterRadioGroupW(H5::Group& h5Group, Core::FITKParamRadioGroup* paraRadioGroup);

        bool parameterDoubleListW(H5::Group& h5Group, Core::FITKParamDoubleList* paraDoubleList);

        bool parameterBoolGroupW(H5::Group& h5Group, Core::FITKParamBoolGroup* paraBoolGroup);


        bool parameterToolR(H5::Group& h5Group, Core::FITKParameter* paraData);

        bool parameterBoolR(H5::Group& h5Group, Core::FITKParamBool* paraBool);

        bool parameterComboxR(H5::Group& h5Group, Core::FITKParamCombox* paraCombox);

        bool parameterDoubleR(H5::Group& h5Group, Core::FITKParamDouble* paraDouble);

        bool parameterIntR(H5::Group& h5Group, Core::FITKParamInt* paraInt);

        bool parameterLabelR(H5::Group& h5Group, Core::FITKParamLabel* paraLabel);

        bool parameterStringR(H5::Group& h5Group, Core::FITKParamString* paraString);

        bool parameterRadioGroupR(H5::Group& h5Group, Core::FITKParamRadioGroup* paraRadioGroup);

        bool parameterDoubleListR(H5::Group& h5Group, Core::FITKParamDoubleList* paraDoubleList);

        bool parameterBoolGroupR(H5::Group& h5Group, Core::FITKParamBoolGroup* paraBoolGroup);
    };
}


#endif
