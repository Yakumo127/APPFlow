#include "FITKOCCModelImport.h"
#include "FITK_Kernel/FITKAppFramework/FITKMessage.h"
#include "FITKOCCDXFReader.h"
#include <QFile>
#include <STEPControl_Reader.hxx>
#include <TopoDS_Shape.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx>
#include <StlAPI.hxx>
#include <QDateTime>
#include <QDebug>

namespace OCC
{
    FITKOCCModelImport::FITKOCCModelImport() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelImport::update()
    {
        //文件路径判断
        if (_importFileName.isEmpty() || !QFile::exists(_importFileName)) return false;
        AppFrame::FITKMessageNormal(QString("Import file from %1 ...").arg(_importFileName));
        qDebug() << "Import File: " << QDateTime::currentDateTime().toString("hh:mm:ss:zzz");
        const QString lowerStr = _importFileName.toLower();
        QByteArray ba = _importFileName.toLocal8Bit();
        const char* cfileName = ba.data();

        bool ok = false;

        if (lowerStr.endsWith(".brep"))
        {
            TopoDS_Shape ashape; //读取的结果
            BRep_Builder builder;
            ok = BRepTools::Read(ashape, (const Standard_CString)cfileName, builder);//读取成功返回true
            if (ok)
            {
                _occShapeAgent->updateShape(ashape);
            }
        }
        else if (lowerStr.endsWith(".stl"))
        {
            TopoDS_Shape ashape; //读取的结果
            ok = StlAPI::Read(ashape, (const Standard_CString)cfileName);
            if (ok)
            {
                _occShapeAgent->updateShape(ashape);
            }
        }
        else if (lowerStr.endsWith(".stp") || lowerStr.endsWith(".step"))
        {
            STEPControl_Reader aReader;
            Standard_Integer status = aReader.ReadFile(cfileName);
            ok = status == IFSelect_RetDone;
            //读取成功
            if (ok)
            {
                aReader.TransferRoots();
                const TopoDS_Shape&  S = aReader.OneShape();
                _occShapeAgent->updateShape(S);
            }

        }
        else if (lowerStr.endsWith(".igs") || lowerStr.endsWith(".iges"))
        {
            //igs reader 初始化
            TopoDS_Shape aShape;
            IGESControl_Controller::Init();
            IGESControl_Reader Reader;
            Standard_Integer status = Reader.ReadFile(cfileName);
            ok = status == IFSelect_RetDone;

            if (ok)
            {
                Reader.SetReadVisible(Standard_True);
                Reader.PrintCheckLoad(Standard_True, IFSelect_GeneralInfo);
                Reader.ClearShapes();
                Reader.TransferRoots();

                aShape = Reader.OneShape();
                _occShapeAgent->updateShape(aShape);
            }
        }
        //读取dxf
        else if (lowerStr.endsWith(".dxf"))
        {
            FITKOCCDXFReader reader(_importFileName);
            //读取成功
            ok = reader.read();
            if (ok)
            {
                TopoDS_Shape ashape = reader.getShape();
                _occShapeAgent->updateShape(ashape);
            }
        }
        else
        {
            AppFrame::FITKMessageError(QString("Unknown file format %1").arg(_importFileName));
            return false;
        }

        //读取失败报错
        if (!ok)
        {
            AppFrame::FITKMessageError(QString("Read file failed %1").arg(_importFileName));
            return false;
        }
        AppFrame::FITKMessageNormal(QString("Success import file from %1").arg(_importFileName));
        qDebug() << "Import finish: " << QDateTime::currentDateTime().toString("hh:mm:ss:zzz");

        return true;
    }

}



