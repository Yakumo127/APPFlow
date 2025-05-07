﻿#include "OperatorsGeoCylinderManager.h"

#include "GUIFrame/MainWindow.h"
#include "GUIFrame/PropertyWidget.h"
#include "GUIWidget/GUIPickInfo.h"
#include "GUIWidget/PickedDataProvider.h"
#include "GUIWidget/PickedData.h"
#include "GUIWidget/WidgetOCCEvent.h"
#include "OperatorsInterface/GraphEventOperator.h"
#include "OperatorsInterface/TreeEventOperator.h"
#include "GUIDialog/GUIGeometryDialog/CylinderInfoWidget.h"
#include "GUIDialog/GUIGeometryDialog/GeometryDeleteDialog.h"
#include "GUIDialog/GUIMeshDialog/MeshGeoWidget.h"

#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFGeometryData.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelCylinder.h"

namespace ModelOper
{
    OperatorsGeoCylinderManager::OperatorsGeoCylinderManager()
    {

    }

    OperatorsGeoCylinderManager::~OperatorsGeoCylinderManager()
    {

    }

    bool OperatorsGeoCylinderManager::execGUI()
    {
        QWidget* widget = nullptr;
        QDialog* dialog = nullptr;

        GUI::MainWindow* mainWindow = dynamic_cast<GUI::MainWindow*>(FITKAPP->getGlobalData()->getMainWindow());
        if (mainWindow == nullptr)return false;
        GUI::PropertyWidget* propertyWidget = mainWindow->getPropertyWidget();
        if (propertyWidget == nullptr)return false;
        Interface::FITKGeoCommandList* geometryData = FITKAPP->getGlobalData()->getGeometryData<Interface::FITKGeoCommandList>();
        if (geometryData == nullptr) return false;

        int objID = -1;
        this->argValue("objID", objID);

        switch (_operType) {
        case ModelOper::OperManagerBase::Create:
            widget = new GUI::CylinderInfoWidget(this);
            break;
        case ModelOper::OperManagerBase::Edit: {
            Interface::FITKAbsGeoModelCylinder* obj = dynamic_cast<Interface::FITKAbsGeoModelCylinder*>(geometryData->getDataByID(objID));
            widget = new GUI::CylinderInfoWidget(obj, this);
            break;
        }
        case ModelOper::OperManagerBase::Copy:
            break;
        case ModelOper::OperManagerBase::Delete:
            dialog = new GUI::GeometryDeleteDialog(dynamic_cast<Interface::FITKAbsGeoCommand*>(geometryData->getDataByID(objID)), this);
            break;
        case ModelOper::OperManagerBase::Rename:
            break;
        }

        if (mainWindow->getPropertyWidget() && widget) {
            propertyWidget->setWidget(widget);
        }

        if (dialog) {
            dialog->show();
        }

        return false;
    }

    bool OperatorsGeoCylinderManager::execProfession()
    {
        // 获取模型树控制器
        auto treeOper = Core::FITKOperatorRepo::getInstance()->getOperatorT<EventOper::TreeEventOperator>("ModelTreeEvent");
        if (treeOper == nullptr) return false;
        EventOper::GraphEventOperator* graphOper = FITKOPERREPO->getOperatorT<EventOper::GraphEventOperator>("GraphPreprocess");
        if (graphOper == nullptr)return false;
        GUI::MainWindow* mainWindow = dynamic_cast<GUI::MainWindow*>(FITKAPP->getGlobalData()->getMainWindow());
        if (mainWindow == nullptr)return false;
        GUI::PropertyWidget* propertyWidget = mainWindow->getPropertyWidget();
        if (propertyWidget == nullptr)return false;

        int objID = -1;
        this->argValue("objID", objID);

        switch (_operType) {
        case ModelOper::OperManagerBase::Create: {
            graphOper->updateGraph(objID);
            treeOper->updateTree();
            graphOper->reRender(true);
            break;
        }
        case ModelOper::OperManagerBase::Edit:
            graphOper->updateGraph(objID);
            treeOper->updateTree();
			graphOper->reRender(true);
            break;
        case ModelOper::OperManagerBase::Copy:
            break;
        case ModelOper::OperManagerBase::Delete: {
            graphOper->updateGraph(objID);
            treeOper->updateTree();
            graphOper->reRender(true);

            //更新网格划分区域界面
            GUI::MeshGeoWidget* widget = dynamic_cast<GUI::MeshGeoWidget*>(propertyWidget->getCurrentWidget());
            if (widget)widget->updateWidget();
            break;
        }
        case ModelOper::OperManagerBase::Rename:
            break;
        }

        return true;
    }

    void OperatorsGeoCylinderManager::eventProcess(int index, QVariant value)
    {
        //几何基点重选择事件
        if (index == 0) {
            //拾取信息设置
            GUI::GUIPickInfoStru pinfo;
            pinfo._pickObjType = GUI::GUIPickInfo::PickObjType::POBJVert;
            pinfo._pickMethod = GUI::GUIPickInfo::PickMethod::PMSingle;
            //保存参数
            GUI::GUIPickInfo::SetPickInfo(pinfo);

            //拾取对象获取事件绑定
            GraphData::PickedDataProvider* pickD = GraphData::PickedDataProvider::getInstance();
            if (pickD == nullptr) return;
            connect(pickD, SIGNAL(sig_dataPicked()), this, SLOT(slotReselectOriginPoint()));
        }        
        //面组选择
        else if (index == 1) {
            int objID = -1;
            int curRow = -1;
            QList<int> faceIDs = {};
            this->argValue("objID", objID);
            this->argValue("curRow", curRow);
            this->argValue("faceIDs", faceIDs);

            //拾取对象获取事件绑定
            GraphData::PickedDataProvider* pickD = GraphData::PickedDataProvider::getInstance();
            pickD->addDataManually(Interface::FITKModelEnum::FMSSurface, objID, faceIDs);
            if (pickD == nullptr) return;

            //拾取信息设置
            GUI::GUIPickInfoStru pinfo;
            pinfo._pickObjType = GUI::GUIPickInfo::PickObjType::POBJFace;
            pinfo._pickMethod = GUI::GUIPickInfo::PickMethod::PMIndividually;
            //保存参数
            GUI::GUIPickInfo::SetPickInfo(pinfo, objID);

            EventOper::GraphEventOperator* graphOper = FITKOPERREPO->getOperatorT<EventOper::GraphEventOperator>("GraphPreprocess");
            if (graphOper == nullptr)return;
            graphOper->reRender();
        }
        //选择面组结束事件
        else if (index == 2) {
            slotSelectFaceGroup();
        }
    }

    void OperatorsGeoCylinderManager::slotReselectOriginPoint()
    {
        GraphData::PickedDataProvider* pickD = GraphData::PickedDataProvider::getInstance();
        if (pickD == nullptr) return;
        disconnect(pickD, SIGNAL(sig_dataPicked()), this, SLOT(slotReselectOriginPoint()));

        //拾取信息设置
        GUI::GUIPickInfoStru pinfo;
        pinfo._pickObjType = GUI::GUIPickInfo::PickObjType::POBJNone;
        pinfo._pickMethod = GUI::GUIPickInfo::PickMethod::PMNone;
        //保存参数
        GUI::GUIPickInfo::SetPickInfo(pinfo);

        QList<GraphData::PickedData*> pickData = pickD->getPickedList();
        if (pickData.size() == 0)return;
        if (!pickData[0])return;

        double point[3] = { 0,0,0 };
        GUI::WidgetOCCEvent::getPoint(pickData[0], point);

        GUI::MainWindow* mainWindow = dynamic_cast<GUI::MainWindow*>(FITKAPP->getGlobalData()->getMainWindow());
        if (mainWindow == nullptr)return;
        GUI::PropertyWidget* propertyWidget = mainWindow->getPropertyWidget();
        if (propertyWidget == nullptr)return;

        GUI::CylinderInfoWidget* cudeWidget = dynamic_cast<GUI::CylinderInfoWidget*>(propertyWidget->getCurrentWidget());
        if (cudeWidget == nullptr)return;
        cudeWidget->setOriginPoint(point);

        pickD->clearPickedData();
    }

    void OperatorsGeoCylinderManager::slotSelectFaceGroup()
    {
        GraphData::PickedDataProvider* pickD = GraphData::PickedDataProvider::getInstance();
        if (pickD == nullptr) return;

        //拾取信息设置
        GUI::GUIPickInfoStru pinfo;
        pinfo._pickObjType = GUI::GUIPickInfo::PickObjType::POBJNone;
        pinfo._pickMethod = GUI::GUIPickInfo::PickMethod::PMNone;
        GUI::GUIPickInfo::SetPickInfo(pinfo);

        QList<GraphData::PickedData*> pickData = pickD->getPickedList();

        QList<int> faceID = GUI::WidgetOCCEvent::getFaces(pickData);

        //界面获取
        GUI::MainWindow* mainWindow = dynamic_cast<GUI::MainWindow*>(FITKAPP->getGlobalData()->getMainWindow());
        if (mainWindow == nullptr)return;
        GUI::PropertyWidget* propertyWidget = mainWindow->getPropertyWidget();
        if (propertyWidget == nullptr)return;
        GUI::CylinderInfoWidget* cudeWidget = dynamic_cast<GUI::CylinderInfoWidget*>(propertyWidget->getCurrentWidget());
        if (cudeWidget == nullptr)return;

        int curRow = -1;
        this->argValue("curRow", curRow);
        cudeWidget->setFaceGroupValue(curRow, faceID);

        pickD->clearPickedData();

        //刷新渲染窗口
        EventOper::GraphEventOperator* graphOper = FITKOPERREPO->getOperatorT<EventOper::GraphEventOperator>("GraphPreprocess");
        if (graphOper == nullptr)return;
        graphOper->reRender();
    }
}
