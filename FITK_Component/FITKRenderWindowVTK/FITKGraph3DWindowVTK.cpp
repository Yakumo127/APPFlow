﻿#include "ui_FITKGraph3DWindowVTK.h"
#include "FITKGraph3DWindowVTK.h"
#include "FITKGraphRender.h"
#include "FITKBoundaryActor.h"
#include "FITKGraphObjectVTK.h"
#include "FITKGraphOperator.h"
#include "FITKGraphInteractionStyle.h"
#include "FITKLegendScaleActor.h"
#include "FITKGraph3DClipDialog.h"
#include "FITK_Kernel/FITKCore/FITKOperatorRepo.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"

#include <vtkCamera.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkWindowToImageFilter.h>
#include <vtkPNGWriter.h>
#include <vtkJPEGWriter.h>
#include <vtkTIFFWriter.h>
#include <vtkBMPWriter.h>
#include <vtkLightCollection.h>
#include <vtkLight.h>
#include <vtkVersionMacros.h>
#include <vtkMapper.h>
#include <vtkExtractGeometry.h>
#include <vtkPlane.h>
#include <vtkDataSetMapper.h>
#include <vtkProperty.h>
#include <vtkAppendFilter.h>

#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)
VTK_MODULE_INIT(vtkRenderingVolumeOpenGL2);

#if VTK_MAJOR_VERSION < 8
#include <QVTKWidget2.h>
#include <vtkGenericOpenGLRenderWindow.h>
#else
#include <QVTKOpenGLNativeWidget.h>
#endif

#include <QVBoxLayout>
#include <QDebug>
#include <QToolBar>
#include <QToolButton>
#include <QFile>
#include <QLabel>
#include <QPushButton>
#include <QMutexLocker>
#include <QFileDialog>
#include <QToolButton>
#include <QDebug>
#include <QFileInfo>
#include <QtSvg/QSvgGenerator>
#include <QPainter>

namespace Comp
{
    QMutex FITKGraph3DWindowVTK::_mutex;

    FITKGraph3DWindowVTK::FITKGraph3DWindowVTK(Graph3DWindowInitializer* ini)
        :_initializer(ini)
    {
        if (_initializer == nullptr) return;

        // 解决Z-fighting问题。
        vtkMapper::SetResolveCoincidentTopologyToPolygonOffset();

        m_ui = new Ui::FITKGraph3DWindowVTK();
        m_ui->setupUi(this);

#if VTK_MAJOR_VERSION >= 9
        QVTKOpenGLNativeWidget* vtkWidget = new QVTKOpenGLNativeWidget;
        m_renderWindow = vtkWidget->renderWindow();
        m_interactor = (QVTKInteractor*)m_renderWindow->GetInteractor();
        m_vtkWidget = vtkWidget;
#elif VTK_MAJOR_VERSION == 8
        QVTKOpenGLNativeWidget* vtkWidget = new QVTKOpenGLNativeWidget;
        m_renderWindow = vtkWidget->GetRenderWindow();
        m_interactor = (QVTKInteractor*)m_renderWindow->GetInteractor();
        m_vtkWidget = vtkWidget;
#else
        QVTKWidget2* vtkWidget = new QVTKWidget2;
        m_renderWindow = m_vtkWidget->GetRenderWindow();
        m_interactor = m_renderWindow->GetInteractor();
        m_vtkWidget = vtkWidget;
#endif

        QLayout* lay = layout();
        if (!lay)
        {
            setLayout(new QVBoxLayout);
            lay = layout();
        }

        lay->addWidget(m_vtkWidget);

        //相机创建
        m_camera = vtkCamera::New();

        // Release模式关闭VTK自身的警告。（2025/01/21）
#ifdef QT_DEBUG
        m_renderWindow->SetGlobalWarningDisplay(true);
#else
        m_renderWindow->SetGlobalWarningDisplay(false);
#endif

        // 初始化三维窗口渲染频率。（2025/01/21体渲染支持）
        m_interactor->SetDesiredUpdateRate(15);
        m_interactor->SetStillUpdateRate(0.5);

        m_actorBound = new FITKBoundaryActor;

        int renderNum = _initializer->getLayerCount();

        //动态创建图层
        for (int i = 0; i < renderNum; i++)
        {
            FITKGraphRender* renderer = new FITKGraphRender(this);
            vtkRenderer* rendervtk = renderer->getRenderer();
            if (rendervtk) rendervtk->SetLayer(i);
            m_renders.insert(i, renderer);
        }

        //设置渲染图层数量
        m_renderWindow->SetNumberOfLayers(renderNum);

        //多Render协同同步，统一设置camera
        for (auto render : m_renders.values())
        {
            if (render == nullptr)continue;
            render->getRenderer()->SetActiveCamera(m_camera);
        }

        this->init();
        setFocusPolicy(Qt::ClickFocus);

        //设置名称
        this->setWindowTitle(QString("View Port-%1").arg(this->getGraphWidgetID()));

        //渲染窗口工具栏初始化
        _renderToolBarLayout = new QGridLayout(m_vtkWidget);
        _renderToolBarLayout->setContentsMargins(0, 0, 0, 0);
        _renderToolBar = new QToolBar(m_vtkWidget);
        _renderToolBar->setContentsMargins(0, 0, 0, 0);
        _renderToolBar->setIconSize(QSize(40, 40));
        _renderIconToolBar = new QToolBar(m_vtkWidget);
        _renderIconToolBar->setContentsMargins(0, 0, 0, 0);
        //初始化action
        initActions();
        //默认不显示action
        setIsShowActions(false);

        // 初始化定时器。
        m_timerView.setInterval(m_interval);
        m_timerView.setSingleShot(true);
        connect(&m_timerView, &QTimer::timeout, this, &FITKGraph3DWindowVTK::slot_changingView);
    }

    void FITKGraph3DWindowVTK::showEvent(QShowEvent* event)
    {
        if (!m_initFlag)
        {
            m_initFlag = true;

            // 设置相机视角 Added by ChengHaotian
//             double position[3]{ 1,1,1 };
//             double focalPoint[3]{ 0,0,0 };
//             double viewUp[3]{ 0,1,0 };
            this->setView(_defFp, _defVp, _defPos);

            // 初始化坐标轴 Added by ChengHaotian
            if (m_axesWidget)
            {
                m_axesWidget->SetOutlineColor(0.9300, 0.5700, 0.1300);
                m_axesWidget->SetViewport(0, 0, 0.2, 0.2);
                m_axesWidget->SetEnabled(true);
                m_axesWidget->InteractiveOff();
            }
        }

        QWidget::showEvent(event);
    }

    FITKGraph3DWindowVTK::~FITKGraph3DWindowVTK()
    {
        // 析构 Added by ChengHaotian
        if (m_legendScaleActor)
        {
            m_legendScaleActor->Delete();
            m_legendScaleActor = nullptr;
        }

        if (m_ui != nullptr) delete m_ui; m_ui = nullptr;
        if (m_camera != nullptr)m_camera->Delete(); m_camera = nullptr;
        if (m_axesWidget != nullptr)m_axesWidget->Delete(); m_axesWidget = nullptr;
        if (m_interactionStyle != nullptr)m_interactionStyle->Delete(); m_interactionStyle = nullptr;
        if (m_actorBound != nullptr) delete m_actorBound;

        //渲染图层链表释放
        for (auto re : m_renders.values())
        {
            if (re == nullptr)continue;
            delete re;
            re = nullptr;
        }
        m_renders.clear();

#if VTK_MAJOR_VERSION <= 7
        if (m_vtkWidget)
        {
            // For VTK 7 Added by ChengHaotian
            m_vtkWidget->setParent(nullptr);
            m_vtkWidget->deleteLater();
            m_vtkWidget = nullptr;
        }
#endif
    }

    void FITKGraph3DWindowVTK::reRender()
    {
        m_renderWindow->Render();
    }

    void FITKGraph3DWindowVTK::setAxesEnable(bool state)
    {
        m_axesWidget->SetEnabled(state);
    }

    void FITKGraph3DWindowVTK::setView(double * focalPoint, double * viewUp, double * position)
    {
        // 异常处理。
        for (int i = 0; i < 3; i++)
        {
            if (qIsNaN(focalPoint[i]) || qIsNaN(viewUp[i]) || qIsNaN(position[i]))
            {
                return;
            }
        }

        //设置VTK中相机的视角
        if (m_camera == nullptr) return;
        m_camera->SetViewUp(viewUp);
        m_camera->SetPosition(position);
        m_camera->SetFocalPoint(focalPoint);

        //多个Render的大小不同，需要统一计算出合适相机视角
        fitView();

        //通知交互器窗口视角发生变化
        if (m_interactionStyle)
        {
            m_interactionStyle->Rotate();
            m_interactionStyle->EndRotate();
        }
    }

    void FITKGraph3DWindowVTK::setDefaultView(double* focalPoint, double* viewUp, double* position)
    {
        for (int i = 0; i < 3; ++i)
        {
            _defFp[i] = focalPoint[i];
            _defVp[i] = viewUp[i];
            _defPos[i] = position[i];
        }
    }

    void FITKGraph3DWindowVTK::setISOView(double* focalPoint, double* viewUp, double* position)
    {
        for (int i = 0; i < 3; ++i)
        {
            _ISOFp[i] = focalPoint[i];
            _ISOVp[i] = viewUp[i];
            _ISOPos[i] = position[i];
        }
    }

    bool FITKGraph3DWindowVTK::getView(double * pos, double * focual, double * viewup)
    {
        if (m_camera == nullptr)return false;
        m_camera->GetPosition(pos);
        m_camera->GetFocalPoint(focual);
        m_camera->GetViewUp(viewup);
        return true;
    }

    void FITKGraph3DWindowVTK::setViewBounds(double* bds)
    {
        if (m_renders.isEmpty())
        {
            return;
        }

        // 获取渲染器设置包围盒。
        FITKGraphRender* fRender = m_renders[0];
        if (!fRender)
        {
            return;
        }

        vtkRenderer* renderer = fRender->getRenderer();
        if (!renderer)
        {
            return;
        }

        renderer->ResetCamera(bds);

        // 刷新渲染。
        reRender();
    }

    void FITKGraph3DWindowVTK::fastAddObject(int index, FITKGraphObjectVTK* object)
    {
        FITKGraphRender* fRender = m_renders.value(index);
        if (!fRender)
        {
            return;
        }

        fRender->addObject(object);

        // 添加控件。
        int nWidget = object->getWidgetCount();
        for (int i = 0; i < nWidget; i++)
        {
            vtkInteractorObserver* widget = object->getWidget(i);
            if (!widget)
            {
                continue;
            }

            // 设置交互器。
            if (m_renderWindow)
            {
                widget->SetInteractor(m_renderWindow->GetInteractor());
            }

            // 控件默认使用最下层渲染器，防止遮挡其他演员。
            int index = 0;// _initializer->getLayerCount() - 1;
            FITKGraphRender* render = m_renders[index];
            if (render)
            {
                widget->SetCurrentRenderer(render->getRenderer());
            }
        }
    }

    void FITKGraph3DWindowVTK::addObject(int index, FITKGraphObjectVTK * object, bool fitview)
    {
        FITKGraphRender* r = m_renders.value(index);
        if (r == nullptr)return;

        int graphCount = getGraphObjCount();

        r->addObject(object);

        // 添加控件。
        int nWidget = object->getWidgetCount();
        for (int i = 0; i < nWidget; i++)
        {
            vtkInteractorObserver* widget = object->getWidget(i);
            if (!widget)
            {
                continue;
            }

            // 设置交互器。
            if (m_renderWindow)
            {
                widget->SetInteractor(m_renderWindow->GetInteractor());
            }

            // 控件默认使用最下层渲染器，防止遮挡其他演员。
            int index = 0;// _initializer->getLayerCount() - 1;
            FITKGraphRender* render = m_renders[index];
            if (render)
            {
                widget->SetCurrentRenderer(render->getRenderer());
            }

            // widget->SetCurrentRenderer(m_renderer);
        }

        //添加actor后，不同Render的相机发生变化需要自适应
        if (fitview && graphCount == 0)
        {
            this->fitView();
        }
        else
        {
            updateBoundray();
        }
        //else
        //{ 
        //    this->reRender();
        //    /*if (graphCount == 0)
        //    {
        //        this->fitView();
        //    }*/
        //}
    }

    QList<FITKGraphObjectVTK*> FITKGraph3DWindowVTK::getAllGraphObj()
    {
        QList<FITKGraphObjectVTK*> objs = {};
        for (FITKGraphRender* render :m_renders.values()) {
            if (render == nullptr) {
                continue;
            }
            Core::FITKGraphObjManager* objManager = render->getGraphObjManager();
            if (objManager == nullptr) {
                continue;
            }

            int objCount = objManager->getGraphObjCount();
            for (int i = 0; i < objCount; i++) {
                objs.append(dynamic_cast<FITKGraphObjectVTK*>(objManager->getGraphObjAt(i)));
            }
        }
        return objs;
    }

    void FITKGraph3DWindowVTK::clear()
    {
        for (auto render : m_renders.values())
        {
            if (render == nullptr)continue;
            render->clear();
        }
    }

    void FITKGraph3DWindowVTK::setBackground(double topValue[3], double bottomValue[3])
    {
        //设置所有图层的背景颜色
        for (auto render : m_renders.values())
        {
            if (render == nullptr)continue;
            render->getRenderer()->SetBackground(topValue);
            render->getRenderer()->SetBackground2(bottomValue);
        }
    }

    void FITKGraph3DWindowVTK::fitView()
    {
        double bound[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };

        bool emptyWindow = true;
        for (auto render : m_renders.values())
        {
            if (render == nullptr)continue;

            //获取渲染图层中的所有actor，并计算大小
            double length = render->getActorBounds(bound);
            if (length > 0) emptyWindow = false;
        }

        if (emptyWindow)
        {
            bound[0] = bound[2] = bound[4] = -1;
            bound[1] = bound[3] = bound[5] = 1;
        }
        //更新边界
        if (m_actorBound != nullptr)
            m_actorBound->updateBoundary(bound);

        for (auto render : m_renders.values())
        {
            render->getRenderer()->ResetCamera(bound);
        }

        reRender();
    }

    void FITKGraph3DWindowVTK::setIsShowClipAction(bool isShow)
    {
        if (_renderToolBar == nullptr || _renderToolBar->isHidden() == true) {
            return;
        }
        for (QAction* clipAction : _renderToolBar->actions()) {
            if (clipAction == nullptr || clipAction->objectName() != "actionRenderClip") {
                continue;
            }
            clipAction->setVisible(isShow);
            break;
        }
    }

    void FITKGraph3DWindowVTK::updateBoundray()
    {
        double bound[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };

        bool emptyWindow = true;
        for (auto render : m_renders.values())
        {
            if (render == nullptr)continue;

            //获取渲染图层中的所有actor，并计算大小
            double length = render->getActorBounds(bound);
            if (length > 0) emptyWindow = false;
        }

        if (emptyWindow)
        {
            bound[0] = bound[2] = bound[4] = -1;
            bound[1] = bound[3] = bound[5] = 1;
        }
        //更新边界
        if (m_actorBound != nullptr)
            m_actorBound->updateBoundary(bound);

        // 重置相机视距。
        vtkRenderer* renderer = getVTKRenderer();
        if (renderer)
        {
            renderer->ResetCameraClippingRange();
        }
    }

    void FITKGraph3DWindowVTK::SetGlobalWarningDisplay(bool isOpen)
    {
        if (m_renderWindow == nullptr)return;
        m_renderWindow->SetGlobalWarningDisplay(isOpen);
    }

    FITKGraphInteractionStyle * FITKGraph3DWindowVTK::getGraphInteractionStyle()
    {
        return m_interactionStyle;
    }

    void FITKGraph3DWindowVTK::flush()
    {
        this->reRender();
    }

    void FITKGraph3DWindowVTK::setBackgroundColor(float* rgb1, float* rgb2 /*=nullptr*/)
    {
        const int n = this->getRenderCount();
        for (int i = 0; i < n; ++i)
        {
            FITKGraphRender* r = this->getRenderer(i);
            if (r) r->setBackgroundColor(rgb1, rgb2);
        }
    }

    void FITKGraph3DWindowVTK::getBackgroundColor(float * rgb1, float * rgb2)
    {
        const int n = this->getRenderCount();
        for (int i = 0; i < n; ++i)
        {
            FITKGraphRender* r = this->getRenderer(i);
            if (r == nullptr)continue;
            vtkRenderer* render = r->getRenderer();
            if (render == nullptr)continue;

            double* butColor = render->GetBackground2();
            rgb1[0] = butColor[0];
            rgb1[1] = butColor[1];
            rgb1[2] = butColor[2];

            if (rgb2 != nullptr) {
                double* topColor = render->GetBackground();
                rgb2[0] = topColor[0];
                rgb2[1] = topColor[1];
                rgb2[2] = topColor[2];
            }
            return;
        }
    }

    void FITKGraph3DWindowVTK::setInteractionStyle(FITKGraphInteractionStyle* style)
    {
        if (style == nullptr)return;
        m_interactionStyle = style;
        //添加交互器
        m_interactionStyle->setInteractor(m_interactor);
        //添加事件对应的窗口
        m_interactionStyle->setGraph3DWin(this);

        //设置框选器对应的渲染图层，默认选择最表面的渲染图层
        int lastRenderIndex = m_renders.size() - 1;
        if (lastRenderIndex >= 0 && m_renders.value(lastRenderIndex) != nullptr)
        {
            m_interactionStyle->setAreaPickRenderer(m_renders.value(lastRenderIndex)->getRenderer());
        }
    }

    FITKGraphRender* FITKGraph3DWindowVTK::getRenderer(int index)
    {
        //越界判断
        if (index < 0 || index >= m_renders.size())return nullptr;
        return m_renders.value(index);
    }

    int FITKGraph3DWindowVTK::getRenderCount()
    {
        if (m_renderWindow)
            return m_renderWindow->GetNumberOfLayers();
        return 0;
    }

    vtkRenderWindow* FITKGraph3DWindowVTK::getVTKRenderWindow()
    {
        return m_renderWindow;
    }

    vtkCamera* FITKGraph3DWindowVTK::getVTKCamera()
    {
        // 获取VTK相机。
        return m_camera;
    }

    vtkRenderer* FITKGraph3DWindowVTK::getVTKRenderer(int index)
    {
        // 获取VTK渲染器。
        if (index == -1)
        {
            int nRender = getRenderCount();
            if (nRender == 0)
            {
                return nullptr;
            }

            FITKGraphRender* render = getRenderer(nRender - 1);
            if (!render)
            {
                return nullptr;
            }

            return render->getRenderer();
        }
        else
        {
            FITKGraphRender* render = getRenderer(index);
            if (!render)
            {
                return nullptr;
            }

            return render->getRenderer();
        }
    }

    //     void FITKGraph3DWindow::setAredPickerState(bool state)
    //     {
    //         if (m_interactionStyle == nullptr)return;
    //         m_interactionStyle->setAredPickerState(state);
    //     }

    void FITKGraph3DWindowVTK::setParallelProjection(bool enable)
    {
        if (m_camera == nullptr) return;
        m_camera->SetParallelProjection(enable);
        this->reRender();
    }

    void FITKGraph3DWindowVTK::removeGraphObj(Core::FITKAbstractGraphObject* gobj)
    {
        FITKGraphObjectVTK* objvtk = dynamic_cast<FITKGraphObjectVTK*>(gobj);
        if (objvtk == nullptr) return;

        for (auto render : m_renders)
        {
            if (render == nullptr) continue;
            render->removeObject(objvtk);
        }
    }

    int FITKGraph3DWindowVTK::getGraphObjCount()
    {
        int c = 0;
        for (auto render : m_renders)
        {
            if (render == nullptr) continue;
            c += render->getGraphObjectCount();
        }
        return c;
    }

    bool FITKGraph3DWindowVTK::getGraphObjCenter(double* center)
    {

        double bound[6] = { 9e64, -9e64, 9e64, -9e64, 9e64, -9e64 };

        bool emptyWindow = true;
        for (auto render : m_renders.values())
        {
            if (render == nullptr)continue;

            //获取渲染图层中的所有actor，并计算大小
            double length = render->getActorBounds(bound);
            if (length > 0) emptyWindow = false;
        }

        if (emptyWindow)
        {
            bound[0] = bound[2] = bound[4] = -1;
            bound[1] = bound[3] = bound[5] = 1;
        }
        center[0] = (bound[0] + bound[1]) / 2.0;
        center[1] = (bound[2] + bound[3]) / 2.0;
        center[2] = (bound[4] + bound[5]) / 2.0;
        return true;
    }

    void FITKGraph3DWindowVTK::saveImage(const QString & image, int w, int h)
    {
        Q_UNUSED(w);
        Q_UNUSED(h);
        if (image.isEmpty())return;
        vtkWindowToImageFilter* imageFilter = vtkWindowToImageFilter::New();
        imageFilter->SetInput(m_renderWindow);
        //设置缩放比例，比例需要根据窗口大小自己计算
        //imageFilter->SetScale(2)

        switch (_imageType)
        {
        case Comp::FITKGraphWinImageType::FITK_PNG: {
            vtkSmartPointer<vtkPNGWriter> pngWriter = vtkSmartPointer<vtkPNGWriter>::New();
            pngWriter->SetFileName(image.toLocal8Bit());
            pngWriter->SetInputConnection(imageFilter->GetOutputPort());
            pngWriter->Write();
            m_renderWindow->Finalize();
            break;
        }
        case Comp::FITKGraphWinImageType::FITK_JPEG: {
            vtkSmartPointer<vtkJPEGWriter> jpegWriter = vtkSmartPointer<vtkJPEGWriter>::New();
            jpegWriter->SetFileName(image.toLocal8Bit());
            jpegWriter->SetInputConnection(imageFilter->GetOutputPort());
            jpegWriter->Write();
            m_renderWindow->Finalize();
            break;
        }
        case Comp::FITKGraphWinImageType::FITK_TIFF: {
            vtkSmartPointer<vtkTIFFWriter> tiffWriter = vtkSmartPointer<vtkTIFFWriter>::New();
            tiffWriter->SetFileName(image.toLocal8Bit());
            tiffWriter->SetInputConnection(imageFilter->GetOutputPort());
            tiffWriter->Write();
            m_renderWindow->Finalize();
            break;
        }
        case Comp::FITKGraphWinImageType::FITK_BMP: {
            vtkSmartPointer<vtkBMPWriter> bmpWriter = vtkSmartPointer<vtkBMPWriter>::New();
            bmpWriter->SetFileName(image.toLocal8Bit());
            bmpWriter->SetInputConnection(imageFilter->GetOutputPort());
            bmpWriter->Write();
            m_renderWindow->Finalize();
            break;
        }
        case  FITKGraphWinImageType::FITK_SVG: {
            QSvgGenerator svgGenerator;
            svgGenerator.setFileName(image);
            svgGenerator.setSize(size());
            svgGenerator.setViewBox(QRect(0, 0, size().width(), size().height()));

            QPainter painter;
            painter.begin(&svgGenerator);
            render(&painter);
            painter.end();
        }
        }

        QString messageText = QString(tr("The specified viewports were printed to file \"%1\"").arg(image));
        AppFrame::FITKMessageNormal(messageText);
    }

    void FITKGraph3DWindowVTK::showScaleLegend(bool visibility)
    {
        if (m_legendScaleActor)
        {
            m_legendScaleActor->SetVisibility(visibility);
        }
    }

    void FITKGraph3DWindowVTK::addActionsToolBar(QList<QAction*> actions, QAction* beforeAction)
    {
        //互斥锁
        QMutexLocker locer(&_mutex);

        if (_renderToolBarLayout == nullptr)return;
        //追加action
        _renderToolBar->insertActions(beforeAction, actions);
        setToolBarPos(_renderBarStyle);

        //修改toolbar中所有的action背景颜色为透明
        QList<QToolButton*> buttons = _renderToolBar->findChildren<QToolButton*>();
        for (auto b : buttons) {
            if (b == nullptr)continue;
            b->setStyleSheet("background: transparent;");
            b->setToolTipDuration(1);
        }
    }

    void FITKGraph3DWindowVTK::setToolBarPos(FITKGraphWinToolBarPos pos)
    {
        if (_renderToolBar == nullptr || _renderToolBarLayout == nullptr)return;

        _renderBarStyle = pos;

        switch (pos)
        {
            //1：左顶
        case FITKGraphWinToolBarPos::FITKLeftTop: {
            _renderToolBar->setOrientation(Qt::Vertical);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignLeft | Qt::AlignTop);
            break;
        }
                                                  //2：左中 
        case FITKGraphWinToolBarPos::FITKLeftCenter: {
            _renderToolBar->setOrientation(Qt::Vertical);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignLeft | Qt::AlignVCenter);
            break;
        }
                                                     //3：左底
        case FITKGraphWinToolBarPos::FITKLeftBottom: {
            _renderToolBar->setOrientation(Qt::Vertical);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignLeft | Qt::AlignBottom);
            break;
        }
                                                     //4：底部
        case FITKGraphWinToolBarPos::FITKBottomCenter: {
            _renderToolBar->setOrientation(Qt::Horizontal);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignHCenter | Qt::AlignBottom);
            break;
        }
                                                       //5：右底  
        case FITKGraphWinToolBarPos::FITKRightBottom: {
            _renderToolBar->setOrientation(Qt::Vertical);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignRight | Qt::AlignBottom);
            break;
        }
                                                      //6：右中
        case FITKGraphWinToolBarPos::FITKRightCenter: {
            _renderToolBar->setOrientation(Qt::Vertical);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
            break;
        }
                                                      //7：右上 
        case FITKGraphWinToolBarPos::FITKRightTop: {
            _renderToolBar->setOrientation(Qt::Vertical);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignRight | Qt::AlignTop);
            break;
        }
                                                   //8：顶部
        case FITKGraphWinToolBarPos::FITKTopCenter: {
            _renderToolBar->setOrientation(Qt::Horizontal);
            _renderToolBarLayout->addWidget(_renderToolBar, 0, 0, Qt::AlignHCenter | Qt::AlignTop);
            break;
        }
        }
    }

    void FITKGraph3DWindowVTK::initRenderIcon(const QPixmap& image, FITKGraphWinToolBarPos pos)
    {
        //互斥锁
        QMutexLocker locker(&_mutex);
        _renderIconToolBar->clear();

        QLabel* label = new QLabel(m_vtkWidget);
        label->setPixmap(image);

        //将 QLabel 添加到布局中的指定位置
        _renderIconToolBar->addWidget(label);

        switch (pos)
        {
            //左侧顶部
        case FITKGraphWinToolBarPos::FITKLeftTop: _renderToolBarLayout->addWidget(_renderIconToolBar, 0, 0, Qt::AlignLeft | Qt::AlignTop); break;
            //左侧底部
        case FITKGraphWinToolBarPos::FITKLeftBottom: _renderToolBarLayout->addWidget(_renderIconToolBar, 0, 0, Qt::AlignLeft | Qt::AlignBottom); break;
            //右侧底部
        case FITKGraphWinToolBarPos::FITKRightBottom: _renderToolBarLayout->addWidget(_renderIconToolBar, 0, 0, Qt::AlignRight | Qt::AlignBottom); break;
            //右侧顶部
        case FITKGraphWinToolBarPos::FITKRightTop: _renderToolBarLayout->addWidget(_renderIconToolBar, 0, 0, Qt::AlignRight | Qt::AlignTop); break;
        }
    }

    QList<QAction*> FITKGraph3DWindowVTK::getActions()
    {
        if (_renderToolBar == nullptr)return QList<QAction*>();
        return _renderToolBar->actions();
    }

    void FITKGraph3DWindowVTK::setIsShowActions(bool isShow)
    {
        if (_renderToolBar == nullptr) {
            return;
        }

        if (isShow == false) {
            _renderToolBar->hide();
        }
        else
        {
            _renderToolBar->show();
        }
    }

    void FITKGraph3DWindowVTK::slotActionViewFrontEvent()
    {
        //前视角参数初始化
        double position[3]{ 0,0,1 };
        double focalPoint[3]{ 0,0,0 };
        double viewUp[3]{ 0,1,0 };
        this->setView(focalPoint, viewUp, position);
    }

    void FITKGraph3DWindowVTK::slotActionViewBackEvent()
    {
        //后视角参数初始化
        double position[3]{ 0,0,-1 };
        double focalPoint[3]{ 0,0,0 };
        double viewUp[3]{ 0,1,0 };
        this->setView(focalPoint, viewUp, position);
    }

    void FITKGraph3DWindowVTK::slotActionViewTopEvent()
    {
        //顶部视角参数初始化
        double position[3]{ 0,1,0 };
        double focalPoint[3]{ 0,0,0 };
        double viewUp[3]{ 0,0,-1 };
        this->setView(focalPoint, viewUp, position);
    }
    void FITKGraph3DWindowVTK::slotActionViewBottomEvent()
    {
        //底部视角参数初始化
        double position[3]{ 0,-1,0 };
        double focalPoint[3]{ 0,0,0 };
        double viewUp[3]{ 0,0,1 };
        this->setView(focalPoint, viewUp, position);
    }
    void FITKGraph3DWindowVTK::slotActionViewLeftEvent()
    {
        //左视角参数初始化
        double position[3]{ -1,0,0 };
        double focalPoint[3]{ 0,0,0 };
        double viewUp[3]{ 0,1,0 };
        this->setView(focalPoint, viewUp, position);
    }
    void FITKGraph3DWindowVTK::slotActionViewRightEvent()
    {
        //右视角参数初始化
        double position[3]{ 1,0,0 };
        double focalPoint[3]{ 0,0,0 };
        double viewUp[3]{ 0,1,0 };
        this->setView(focalPoint, viewUp, position);
    }
    void FITKGraph3DWindowVTK::slotActionViewIsoEvent()
    {
        //正视角参数初始化
//         double position[3]{ 1,1,1 };
//         double focalPoint[3]{ 0,0,0 };
//         double viewUp[3]{ 0,0,1 };
        this->setView(_ISOFp, _ISOVp, _ISOPos);
    }

    void FITKGraph3DWindowVTK::slotActionViewPanEvent()
    {
        //自适应
        fitView();
    }

    void FITKGraph3DWindowVTK::slotActionSaveImageEvent()
    {
        //保存图片文件获取
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG (*.png) ;; JPEG(*.jpeg) ;; TIFF(*.tiff) ;; BMP(*.bmp) ;; SVG(*.svg)"));
        if (filePath.isEmpty())return;
        QFile file(filePath);
        QFileInfo fileInfo(file);
        QString fileSuffix = fileInfo.suffix();
        if (fileSuffix == "png") {
            _imageType = FITKGraphWinImageType::FITK_PNG;
        }
        else if (fileSuffix == "jpeg") {
            _imageType = FITKGraphWinImageType::FITK_JPEG;
        }
        else if (fileSuffix == "tiff") {
            _imageType = FITKGraphWinImageType::FITK_TIFF;
        }
        else if (fileSuffix == "bmp") {
            _imageType = FITKGraphWinImageType::FITK_BMP;
        }
        else if (fileSuffix == "svg") {
            _imageType = FITKGraphWinImageType::FITK_SVG;
        }
        else {
            _imageType = FITKGraphWinImageType::FITK_PNG;
        }
        saveImage(filePath);
    }

    void FITKGraph3DWindowVTK::slotActionViewParallelEvent()
    {
        //平行投影
        setParallelProjection(true);
    }

    void FITKGraph3DWindowVTK::slotActionViewPerspectiveEvent()
    {
        //正交投影
        setParallelProjection(false);
    }

    void FITKGraph3DWindowVTK::slotActionClipEvent(bool isCreateNewModel)
    {
        FITKGraph3DClipDialog* dialog = new FITKGraph3DClipDialog(this, isCreateNewModel);
        dialog->show();
    }

    void FITKGraph3DWindowVTK::init()
    {
        //追加边界actor
        if (_initializer && _initializer->getLayerCount() > 0)
        {
            int index = _initializer->getLayerCount() - 1;
            if (this->getRenderer(index) && this->getRenderer(index)->getRenderer())
            {
                vtkActor* actor = nullptr;
                if (m_actorBound) actor = m_actorBound->getActor();
                if (actor)
                    this->getRenderer(index)->getRenderer()->AddActor(actor);
            }

        }

        // 创建比例尺（默认隐藏） Added by ChengHaotian
        //@{
        FITKGraphRender* fRender = this->getRenderer(0);
        if (fRender)
        {
            vtkRenderer* renderer = fRender->getRenderer();
            if (renderer)
            {
                m_legendScaleActor = FITKLegendScaleActor::New();
                m_legendScaleActor->SetVisibility(false);
                renderer->AddActor(m_legendScaleActor);
            }
        }
        //@}

        //坐标系创建
        //设置坐标系所在的图层
        vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
        vtkOrientationMarkerWidget* axesWidget = vtkOrientationMarkerWidget::New();
        axesWidget->SetInteractor(m_interactor);
        axesWidget->SetOrientationMarker(axesActor);
        axesWidget->SetDefaultRenderer(getRenderer(0)->getRenderer());
        m_axesWidget = axesWidget;

        // 初始化光照 Added by ChengHaotian
        for (FITKGraphRender* fRender : m_renders)
        {
            if (!fRender)
            {
                continue;
            }

            vtkRenderer* renderer = fRender->getRenderer();
            if (!renderer)
            {
                continue;
            }

            // Initialize light.
            renderer->RemoveAllLights();

            vtkLight* light1 = renderer->MakeLight();
            light1->SetExponent(0.);
            light1->SetLightTypeToHeadlight();
            // light1->SetPositional(true);
            renderer->AddLight(light1);
        }

        //设置自定义交互器
        if (_initializer == nullptr) return;
        this->setInteractionStyle(_initializer->getStyle());
    }

    void FITKGraph3DWindowVTK::initActions()
    {
        QList<QAction*> actions = {};
        QAction* action = nullptr;

        //前视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewFront");
        action->setIcon(QIcon(":FITKIcons/icoR_viewFront.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewFrontEvent()));
        actions.append(action);
        //后视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewBack");
        action->setIcon(QIcon(":FITKIcons/icoR_viewBack.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewBackEvent()));
        actions.append(action);
        //顶部视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewTop");
        action->setIcon(QIcon(":FITKIcons/icoR_viewTop.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewTopEvent()));
        actions.append(action);
        //底部视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewBottom");
        action->setIcon(QIcon(":FITKIcons/icoR_viewBottom.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewBottomEvent()));
        actions.append(action);
        //左侧视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewLeft");
        action->setIcon(QIcon(":FITKIcons/icoR_viewLeft.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewLeftEvent()));
        actions.append(action);
        //右侧视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewRight");
        action->setIcon(QIcon(":FITKIcons/icoR_viewRight.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewRightEvent()));
        actions.append(action);
        //正视角按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewIso");
        action->setIcon(QIcon(":FITKIcons/icoR_viewIso.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewIsoEvent()));
        actions.append(action);
        //自适应按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewAuto");
        action->setIcon(QIcon(":FITKIcons/icoR_autofit.png"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewPanEvent()));
        actions.append(action);
        //保存图片按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionSaveImage");
        action->setIcon(QIcon(":FITKIcons/icoR_saveimage.png"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionSaveImageEvent()));
        actions.append(action);
        //平行投影按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewParallel");
        action->setIcon(QIcon(":FITKIcons/icoR_viewParallel.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewParallelEvent()));
        actions.append(action);
        //正交投影按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionViewPerspective");
        action->setIcon(QIcon(":FITKIcons/icoR_viewPerspective.svg"));
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionViewPerspectiveEvent()));
        actions.append(action);
        //裁切按钮添加
        action = new QAction(m_vtkWidget);
        action->setObjectName("actionRenderClip");
        action->setIcon(QIcon(":FITKIcons/icoR_clip.png"));
        //裁切按钮默认隐藏
        action->setVisible(false);
        connect(action, SIGNAL(triggered()), this, SLOT(slotActionClipEvent()));
        actions.append(action);

        addActionsToolBar(actions);
    }

    void FITKGraph3DWindowVTK::setUserInformation(QVariant info)
    {
        m_userInfo = info;
    }

    QVariant FITKGraph3DWindowVTK::getUserInformation()
    {
        return m_userInfo;
    }

    void FITKGraph3DWindowVTK::setViewAnime(double* focalPoint, double* viewUp, double* position)
    {
        // 异常处理。
        for (int i = 0; i < 3; i++)
        {
            if (qIsNaN(focalPoint[i]) || qIsNaN(viewUp[i]) || qIsNaN(position[i]))
            {
                return;
            }
        }

        startChangingView(focalPoint, viewUp, position);
    }

    void FITKGraph3DWindowVTK::startChangingView(double* foc, double* up, double* pos)
    {
        if (m_timerView.isActive())
        {
            m_timerView.stop();
        }

        m_currStep = 0;

        // 保存目标相机参数。
        for (int i = 0; i < 3; i++)
        {
            m_tarFoc3[i] = foc[i];
            m_tarUp3[i] = up[i];
            m_tarPos3[i] = pos[i];
        }

        // 启动定时器。
        m_timerView.start();
    }

    void FITKGraph3DWindowVTK::slot_changingView()
    {
        m_currStep++;

        if (m_currStep >= m_viewStep)
        {
            // 设置相机视角至目标属性。
            m_camera->SetViewUp(m_tarUp3);
            m_camera->SetPosition(m_tarPos3);
            m_camera->SetFocalPoint(m_tarFoc3);
            return;
        }

        double* currFoc = m_camera->GetFocalPoint();
        double* currUp = m_camera->GetViewUp();
        double* currPos = m_camera->GetPosition();

        double deltaFoc3[3]{ 0., 0., 0. };
        double deltaUp3[3]{ 0., 0., 0. };
        double deltaPos3[3]{ 0., 0., 0. };

        // 计算相机变量。
        int steps = m_viewStep - m_currStep;
        for (int i = 0; i < 3; i++)
        {
            deltaFoc3[i] = (m_tarFoc3[i] - currFoc[i]) / steps;
            deltaUp3[i] = (m_tarUp3[i] - currUp[i]) / steps;
            deltaPos3[i] = (m_tarPos3[i] - currPos[i]) / steps;
        }

        // 设置相机视角。
        m_camera->SetViewUp(currUp[0] + deltaUp3[0], currUp[1] + deltaUp3[1], currUp[2] + deltaUp3[2]);
        m_camera->SetPosition(currPos[0] + deltaPos3[0], currPos[1] + deltaPos3[1], currPos[2] + deltaPos3[2]);
        m_camera->SetFocalPoint(currFoc[0] + deltaFoc3[0], currFoc[1] + deltaFoc3[1], currFoc[2] + deltaFoc3[2]);

        // 刷新渲染。
        reRender();

        // 启动定时器执行下一步。
        m_timerView.start();
    }
}