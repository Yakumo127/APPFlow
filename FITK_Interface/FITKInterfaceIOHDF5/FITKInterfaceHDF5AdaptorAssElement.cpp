﻿#include "FITKInterfaceHDF5AdaptorAssElement.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Reader.h"
#include "FITK_Interface/FITKInterfaceIO/FITKAbstractHDF5Writer.h"

#include "FITK_Interface/FITKInterfacePhysics/FITKAbstractMaterial.h"
#include "FITK_Interface/FITKInterfacePhysics/FITKAbstractSection.h"
#include "FITK_Interface/FITKInterfacePhysics/FITKSectionAssign.h"
#include "FITK_Interface/FITKInterfaceModel/FITKAssElement.h"

//命名空间
namespace IO
{
    QString FITKInterfaceHDF5AdaptorAssemblyElementLine::getAdaptorClass()
    {
        return "FITKInterfaceHDF5AdaptorAssemblyElementLine";
    }

    bool FITKInterfaceHDF5AdaptorAssemblyElementLine::adaptR()
    {
        auto assElement = dynamic_cast<Interface::FITKAbstractAssemblyElement*>(_dataObj);
        if (!_reader || !_h5Group || !assElement) return false;
        bool isR = true;
        isR &= readAssemblyElementLine(assElement, *_h5Group);
        return isR;
    }

    bool FITKInterfaceHDF5AdaptorAssemblyElementLine::adaptW()
    {
        auto assElement = dynamic_cast<Interface::FITKAbstractAssemblyElement*>(_dataObj);
        if (!_writer || !_h5Group || !assElement) return false;
        bool isW = true;
        isW &= writeAssemblyElementLine(assElement, *_h5Group);
        return isW;
    }
    bool FITKInterfaceHDF5AdaptorAssemblyElementLine::readAssemblyElementLine(Interface::FITKAbstractAssemblyElement * assElement, H5::Group & h5Group)
    {
        //转换判空
        auto element = dynamic_cast<Interface::FITKAssemblyElementLine*>(assElement);
        if (!element) return false;

        //Base
        //ElementID
        int elementID = readIntAttribute(h5Group, "ElementID");
        element->setElementID(elementID);
        //Node1MID Node1ID
        int Node1MID = readIntAttribute(h5Group, "Node1MID");
        int Node1ID = readIntAttribute(h5Group, "Node1ID");
        element->setNode1(Node1MID, Node1ID);
        //Node2MID Node2ID
        int Node2MID = readIntAttribute(h5Group, "Node2MID");
        int Node2ID = readIntAttribute(h5Group, "Node2ID");
        element->setNode2(Node2MID, Node2ID);
        return true;

    }
    bool FITKInterfaceHDF5AdaptorAssemblyElementLine::writeAssemblyElementLine(Interface::FITKAbstractAssemblyElement * assElement, H5::Group & h5Group)
    {
        //转换判空
        auto element = dynamic_cast<Interface::FITKAssemblyElementLine*>(assElement);
        if (!element) return false;

        //Base
        //ElementID
        int elementID = element->getElementID();
        writeIntAttribute(h5Group, "ElementID", &elementID);
        //Node1MID Node1ID
        int Node1MID, Node1ID;
        element->getNode1(Node1MID, Node1ID);
        writeIntAttribute(h5Group, "Node1MID", &Node1MID);
        writeIntAttribute(h5Group, "Node1ID", &Node1ID);
        //Node2MID Node2ID
        int Node2MID, Node2ID;
        element->getNode2(Node2MID, Node2ID);
        writeIntAttribute(h5Group, "Node2MID", &Node2MID);
        writeIntAttribute(h5Group, "Node2ID", &Node2ID);
        return true;
    }
}