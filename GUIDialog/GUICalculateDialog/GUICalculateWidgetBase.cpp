﻿#include "GUICalculateWidgetBase.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsManager.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKAbstractOFSolver.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKFlowPhysicsHandlerFactory.h"

namespace GUI
{
    GUICalculateWidgetBase::GUICalculateWidgetBase(EventOper::ParaWidgetInterfaceOperator * oper, QWidget * parent) :
        GUIWidgetBase(parent), _oper(oper)
    {
        _physicsManager = Interface::FITKOFPhysicsManager::getInstance();
        _solverManager = _physicsManager->getSolverManager();
        _physicsData = FITKAPP->getGlobalData()->getPhysicsData<Interface::FITKOFPhysicsData>();
        _factoryData = FITKAPP->getComponents()->getComponentTByName<Interface::FITKFlowPhysicsHandlerFactory>("FITKFlowPhysicsHandlerFactory");
    }

    GUICalculateWidgetBase::~GUICalculateWidgetBase()
    {

    }

    //-----------------------------------------------------------------------------------------------------
    
    GUICalculateSubWidgetBase::GUICalculateSubWidgetBase(QWidget* parent)
    {
        if (parent == nullptr)return;
        _calculateWdiget = dynamic_cast<GUICalculateWidgetBase*>(parent->parent());
    }

    GUICalculateSubWidgetBase::~GUICalculateSubWidgetBase()
    {

    }
}
