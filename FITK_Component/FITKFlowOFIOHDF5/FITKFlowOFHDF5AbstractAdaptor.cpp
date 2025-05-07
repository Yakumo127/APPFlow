#include "FITKFlowOFHDF5AbstractAdaptor.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"

#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"
#include <typeinfo>

//数据层
#include "FITK_Kernel/FITKEasyParam/FITKParameter.h"
#include "FITK_Kernel/FITKEasyParam/FITKAbstractEasyParam.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamBool.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamInt.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDouble.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamString.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamBoolGroup.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamCombox.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamDoubleList.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamRadioGroup.h"
#include "FITK_Kernel/FITKEasyParam/FITKParamLabel.h"
//命名空间
namespace IO
{
    FITKFlowOFHDF5AbstractAdaptor::~FITKFlowOFHDF5AbstractAdaptor()
    {

    }

    void FITKFlowOFHDF5AbstractAdaptor::consoleMessage(int errorLevel, QString str)
    {
        //判断是读取还是写出
        QString isState = errorLevel ? "True" : "False";
        if (_reader)
        {
            _reader->consoleMessage(errorLevel, str + isState);
        }
        else if(_writer)
        {
            _writer->consoleMessage(errorLevel, str + isState);
        }
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterToolW(H5::Group& h5Group, Core::FITKParameter* paraData)
    {
        if (!paraData)return false;
        int count = paraData->getDataCount();
        writeIntAttribute(h5Group, "paraCount", &count);
        for (int i = 0; i < count; ++i)
        {
            Core::FITKAbstractEasyParam* para = paraData->getDataByIndex(i);
            if (!para)continue;
            int paraType = para->getParamType();
            std::string name = std::to_string(i);
            writeIntAttribute(h5Group, name, &paraType);
            //设置参数
            H5::Group childH5Group = h5Group.createGroup(name);
            writeNDataObject(para, childH5Group);
            if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPBool)
            {
                Core::FITKParamBool* paraBool = dynamic_cast<Core::FITKParamBool*>(para);
                if (!paraBool) return false;
                this->parameterBoolW(childH5Group, paraBool);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPCombox)
            {
                Core::FITKParamCombox* paraCombox = dynamic_cast<Core::FITKParamCombox*>(para);
                if (!paraCombox) return false;
                this->parameterComboxW(childH5Group, paraCombox);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDouble)
            {
                Core::FITKParamDouble* paraDouble = dynamic_cast<Core::FITKParamDouble*>(para);
                if (!paraDouble) return false;
                this->parameterDoubleW(childH5Group, paraDouble);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPInt)
            {
                Core::FITKParamInt* paraInt = dynamic_cast<Core::FITKParamInt*>(para);
                if (!paraInt) return false;
                this->parameterIntW(childH5Group, paraInt);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPLabel)
            {
                Core::FITKParamLabel* paraLabel = dynamic_cast<Core::FITKParamLabel*>(para);
                if (!paraLabel) return false;
                this->parameterLabelW(childH5Group, paraLabel);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPString)
            {
                Core::FITKParamString* paraString = dynamic_cast<Core::FITKParamString*>(para);
                if (!paraString) return false;
                this->parameterStringW(childH5Group, paraString);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPRadioGroup)
            {
                Core::FITKParamRadioGroup* paraRadioGroup = dynamic_cast<Core::FITKParamRadioGroup*>(para);
                if (!paraRadioGroup) return false;
                this->parameterRadioGroupW(childH5Group, paraRadioGroup);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDoubleList)
            {
                Core::FITKParamDoubleList* paraDoubleList = dynamic_cast<Core::FITKParamDoubleList*>(para);
                if (!paraDoubleList) return false;
                this->parameterDoubleListW(childH5Group, paraDoubleList);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPBoolGroup)
            {
                Core::FITKParamBoolGroup* paraBoolGroup = dynamic_cast<Core::FITKParamBoolGroup*>(para);
                if (!paraBoolGroup) return false;
                this->parameterBoolGroupW(childH5Group, paraBoolGroup);
            }
        }
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterBoolW(H5::Group& h5Group, Core::FITKParamBool* paraBool)
    {
        if (!paraBool) return false;
        bool value = paraBool->getValue();
        writeBoolAttribute(h5Group, "Value", &value);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterComboxW(H5::Group& h5Group, Core::FITKParamCombox* paraCombox)
    {
        if (!paraCombox) return false;
        std::string value = paraCombox->getValue().join(';').toStdString();
        int currentIndex = paraCombox->getIndex();
        writeIntAttribute(h5Group, "CurrentIndex", &currentIndex);
        writeStrAttribute(h5Group, "Value", value);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterDoubleW(H5::Group& h5Group, Core::FITKParamDouble* paraDouble)
    {
        if (!paraDouble) return false;
        double value = paraDouble->getValue();
        double range[2] = { 0 };
        paraDouble->getRange(range);
        writeDoubleAttribute(h5Group, "Value", &value);
        writeDoubleAttribute(h5Group, "Range", range, 1, 2);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterIntW(H5::Group& h5Group, Core::FITKParamInt* paraInt)
    {
        if (!paraInt) return false;
        int value = paraInt->getValue();
        int range[2] = { 0 };
        paraInt->getRange(range);
        writeIntAttribute(h5Group, "Value", &value);
        writeIntAttribute(h5Group, "Range", range, 1, 2);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterLabelW(H5::Group& h5Group, Core::FITKParamLabel* paraLabel)
    {
        if (!paraLabel) return false;
        std::string value = paraLabel->getValue().join(';').toStdString();
        writeStrAttribute(h5Group, "Value", value);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterStringW(H5::Group& h5Group, Core::FITKParamString* paraString)
    {
        if (!paraString) return false;
        std::string value = paraString->getValue().toStdString();
        writeStrAttribute(h5Group, "Value", value);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterRadioGroupW(H5::Group& h5Group, Core::FITKParamRadioGroup* paraRadioGroup)
    {
        if (!paraRadioGroup) return false;
        H5::Group subGroupH5 = h5Group.createGroup("SubValue");
        //共有数据
        Core::FITKParameter* subValue = paraRadioGroup->getSubValuePara();
        if (subValue) parameterToolW(subGroupH5, subValue);
        //数据组
        H5::Group radioGroupH5 = h5Group.createGroup("RadioGroup");
        QList<Core::FITKRadioGroupValue> radioGroupList = paraRadioGroup->getRadioValues();
        int valueCount = radioGroupList.size();
        writeIntAttribute(radioGroupH5, "ValueCount", &valueCount);
        for (int j = 0; j < valueCount; ++j)
        {
            std::string nameRadio = std::to_string(j);
            H5::Group radioH5Group = radioGroupH5.createGroup(nameRadio);
            Core::FITKRadioGroupValue radioGroup = radioGroupList.at(j);
            writeStrAttribute(radioH5Group, "ValueName", radioGroup._name.toStdString());
            //数据组
            H5::Group valueH5Group = radioH5Group.createGroup("Value");
            if (radioGroup._value) parameterToolW(valueH5Group, radioGroup._value);
            //标签
            QStringList label;
            for (int z = 0; z < radioGroup._labelValue.size(); ++z)
            {
                if (radioGroup._labelValue.at(z))
                    label.append("true");
                else
                    label.append("false");
            }
            writeStrAttribute(radioH5Group, "LabelValue", label.join(';').toStdString());
        }
        //当前索引
        int currentIndex = paraRadioGroup->getCurrentValueIndex();
        writeIntAttribute(h5Group, "CurrentIndex", &currentIndex);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterDoubleListW(H5::Group& h5Group, Core::FITKParamDoubleList* paraDoubleList)
    {
        if (!paraDoubleList) return false;
        int valueCount = paraDoubleList->getCount();
        writeIntAttribute(h5Group, "ValueCount", &valueCount);
        for (int j = 0; j < valueCount; ++j)
        {
            Core::FITKParamDouble* paraDouble = paraDoubleList->getDoubleData(j);
            if (!paraDouble)continue;
            std::string nameDouble = std::to_string(j);
            H5::Group doubleH5Group = h5Group.createGroup(nameDouble);
            writeNDataObject(paraDouble, doubleH5Group);
            double value = paraDouble->getValue();
            double range[2] = { 0 };
            paraDouble->getRange(range);
            writeDoubleAttribute(doubleH5Group, "Value", &value);
            writeDoubleAttribute(doubleH5Group, "Range", &range, 1, 2);
        }
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterBoolGroupW(H5::Group& h5Group, Core::FITKParamBoolGroup* paraBoolGroup)
    {
        if (!paraBoolGroup) return false;
        bool value = paraBoolGroup->getValue();
        writeBoolAttribute(h5Group, "Value", &value);
        H5::Group boolGroupH5 = h5Group.createGroup("BoolGroup");
        Core::FITKParameter* boolGroup = paraBoolGroup->getValueGroup();
        if (boolGroup) parameterToolW(boolGroupH5, boolGroup);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterToolR(H5::Group& h5Group, Core::FITKParameter* paraData)
    {
        if (!paraData)return false;
        paraData->clear();
        bool ok = false;
        if (!h5Group.attrExists("paraCount"))return false;
        int paraCount = readIntAttribute(h5Group, "paraCount", &ok);
        if (!ok)return false;
        for (int i = 0; i < paraCount; ++i)
        {
            std::string name = std::to_string(i);
            if (!h5Group.nameExists(name))continue;
            H5::Group childH5Group = h5Group.openGroup(name);
            int paraType = readIntAttribute(h5Group, name, &ok);
            if (!ok) return false;
            Core::FITKAbstractEasyParam* para = nullptr;
            if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPBool)
            {
                para = new Core::FITKParamBool;
                Core::FITKParamBool* paraBool = dynamic_cast<Core::FITKParamBool*>(para);
                this->parameterBoolR(childH5Group, paraBool);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPCombox)
            {
                para = new Core::FITKParamCombox;
                Core::FITKParamCombox* paraCombox = dynamic_cast<Core::FITKParamCombox*>(para);
                this->parameterComboxR(childH5Group, paraCombox);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDouble)
            {
                para = new Core::FITKParamDouble;
                Core::FITKParamDouble* paraDouble = dynamic_cast<Core::FITKParamDouble*>(para);
                this->parameterDoubleR(childH5Group, paraDouble);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPInt)
            {
                para = new Core::FITKParamInt;
                Core::FITKParamInt* paraInt = dynamic_cast<Core::FITKParamInt*>(para);
                this->parameterIntR(childH5Group, paraInt);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPLabel)
            {
                para = new Core::FITKParamLabel;
                Core::FITKParamLabel* paraLabel = dynamic_cast<Core::FITKParamLabel*>(para);
                this->parameterLabelR(childH5Group, paraLabel);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPString)
            {
                para = new Core::FITKParamString;
                Core::FITKParamString* paraString = dynamic_cast<Core::FITKParamString*>(para);
                this->parameterStringR(childH5Group, paraString);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPRadioGroup)
            {
                para = new Core::FITKParamRadioGroup;
                Core::FITKParamRadioGroup* paraRadioGroup = dynamic_cast<Core::FITKParamRadioGroup*>(para);
                this->parameterRadioGroupR(childH5Group, paraRadioGroup);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPDoubleList)
            {
                para = new Core::FITKParamDoubleList;
                Core::FITKParamDoubleList* paraDoubleList = dynamic_cast<Core::FITKParamDoubleList*>(para);
                this->parameterDoubleListR(childH5Group, paraDoubleList);
            }
            else if (paraType == Core::FITKAbstractEasyParam::FITKEasyParamType::FEPBoolGroup)
            {
                para = new Core::FITKParamBoolGroup;
                Core::FITKParamBoolGroup* paraBoolGroup = dynamic_cast<Core::FITKParamBoolGroup*>(para);
                this->parameterBoolGroupR(childH5Group, paraBoolGroup);
            }
            if (!para)return false;
            readNDataObject(para, childH5Group);
            paraData->appendDataObj(para);
        }
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterBoolR(H5::Group& h5Group, Core::FITKParamBool* paraBool)
    {
        if (!paraBool) return false;
        bool value = readBoolAttribute(h5Group, "Value");
        paraBool->setValue(value);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterComboxR(H5::Group& h5Group, Core::FITKParamCombox* paraCombox)
    {
        if (!paraCombox) return false;
        QString value = QString::fromStdString(readStrAttribute(h5Group, "Value"));
        paraCombox->setValue(value.split(";"));
        int currentIndex = readIntAttribute(h5Group, "CurrentIndex");
        paraCombox->setIndex(currentIndex);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterDoubleR(H5::Group& h5Group, Core::FITKParamDouble* paraDouble)
    {
        if (!paraDouble)return false;
        double value = readDoubleAttribute(h5Group, "Value");
        paraDouble->setValue(value);
        if (!h5Group.attrExists("Range"))return false;
        double range[2] = { 0 };
        H5::Attribute attDirection = h5Group.openAttribute("Range");
        attDirection.read(H5::PredType::NATIVE_DOUBLE, &range);
        paraDouble->setRange(range);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterIntR(H5::Group& h5Group, Core::FITKParamInt* paraInt)
    {
        if (!paraInt)return false;
        int value = readIntAttribute(h5Group, "Value");
        paraInt->setValue(value);
        if (!h5Group.attrExists("Range"))return false;
        int range[2] = { 0 };
        H5::Attribute attDirection = h5Group.openAttribute("Range");
        attDirection.read(H5::PredType::NATIVE_INT, &range);
        paraInt->setRange(range);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterLabelR(H5::Group& h5Group, Core::FITKParamLabel* paraLabel)
    {
        if (!paraLabel)return false;
        QString value = QString::fromStdString(readStrAttribute(h5Group, "Value"));
        paraLabel->setValue(value.split(';'));
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterStringR(H5::Group& h5Group, Core::FITKParamString* paraString)
    {
        if (!paraString)return false;
        QString value = QString::fromStdString(readStrAttribute(h5Group, "Value"));
        paraString->setValue(value);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterRadioGroupR(H5::Group& h5Group, Core::FITKParamRadioGroup* paraRadioGroup)
    {
        if (!paraRadioGroup)return false;
        if (!h5Group.nameExists("SubValue"))return false;
        H5::Group subGroupH5 = h5Group.openGroup("SubValue");
        if (subGroupH5.getNumAttrs() > 0)
        {
            Core::FITKParameter* subValue = new Core::FITKParameter;
            parameterToolR(subGroupH5, subValue);
            paraRadioGroup->setSubValue(subValue);
        }
        if (!h5Group.nameExists("RadioGroup"))return false;
        H5::Group radioGroupH5 = h5Group.openGroup("RadioGroup");
        int valueCount = readIntAttribute(radioGroupH5, "ValueCount");
        for (int j = 0; j < valueCount; ++j)
        {
            std::string nameRadio = std::to_string(j);
            if (!radioGroupH5.nameExists(nameRadio))return false;
            
            H5::Group radioH5Group = radioGroupH5.openGroup(nameRadio);
            QString valueName = QString::fromStdString(readStrAttribute(radioH5Group, "ValueName"));
            //标签
            QStringList label = QString::fromStdString(readStrAttribute(radioH5Group, "LabelValue")).split(';');
            QList<bool> labelValue;
            for (int z = 0; z < label.size(); ++z)
            {
                if (label.at(z) == "false")
                    labelValue.append(false);
                else if (label.at(z) == "true")
                    labelValue.append(true);
            }
            //数据组
            if (!radioH5Group.nameExists("Value")) return false;
            H5::Group valueH5Group = radioH5Group.openGroup("Value");
            Core::FITKParameter* radioValue = nullptr;
            if (valueH5Group.getNumAttrs() > 0)
            {
                radioValue = new Core::FITKParameter;
                parameterToolR(valueH5Group, radioValue);
            }
            paraRadioGroup->appendValue(valueName, radioValue, labelValue);
        }
        //当前索引
        int currentIndex = readIntAttribute(h5Group, "CurrentIndex");
        paraRadioGroup->setCurrentIndex(currentIndex);
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterDoubleListR(H5::Group& h5Group, Core::FITKParamDoubleList* paraDoubleList)
    {
        if (!paraDoubleList)return false;
        int valueCount = readIntAttribute(h5Group, "ValueCount");
        for (int j = 0; j < valueCount; ++j)
        {
            std::string nameDouble = std::to_string(j);
            if (!h5Group.nameExists(nameDouble))continue;
            H5::Group doubleH5Group = h5Group.openGroup(nameDouble);
            Core::FITKParamDouble* paraDouble = new Core::FITKParamDouble;
            readNDataObject(paraDouble, doubleH5Group);
            double value = readDoubleAttribute(doubleH5Group, "Value");
            double range[2] = { 0 };
            readDoubleAttribute(doubleH5Group, "Range", range, 1, 2);
            paraDouble->setValue(value);
            paraDouble->setRange(range);
            paraDoubleList->pushDoubleData(paraDouble);
        }
        return true;
    }

    bool FITKFlowOFHDF5AbstractAdaptor::parameterBoolGroupR(H5::Group& h5Group, Core::FITKParamBoolGroup* paraBoolGroup)
    {
        if (!paraBoolGroup)return false;
        bool value = readBoolAttribute(h5Group, "Value");
        if (!h5Group.nameExists("BoolGroup"))return false;
        H5::Group boolGroupH5 = h5Group.openGroup("BoolGroup");
        if (boolGroupH5.getNumAttrs() > 0)
        {
            Core::FITKParameter* boolGroup = new Core::FITKParameter;
            parameterToolR(boolGroupH5, boolGroup);
            paraBoolGroup->setValueGroup(boolGroup);
        }
        return true;
    }
}
