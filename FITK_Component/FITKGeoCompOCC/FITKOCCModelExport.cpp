﻿#include "FITKOCCModelExport.h"

// OCC
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <BRep_Builder.hxx>
#include <BRepTools.hxx>
#include <STEPControl_Writer.hxx>
#include <IGESControl_Writer.hxx>
#include <StlAPI.hxx>

// App
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"

// Abstract geometry
#include "FITK_Interface/FITKInterfaceGeometry/FITKGeoCommandList.h"

namespace OCC
{
    bool FITKOCCModelExport::update()
    {
        // 检查文件路径。
        if (_exportFileName.isEmpty())
        {
            return false;
        }

        // 获取全局几何数据列表。
        Interface::FITKGeoCommandList* geoData = FITKGLODATA->getGeometryData<Interface::FITKGeoCommandList>();
        if (!geoData)
        {
            return false;
        }

        // 初始化组合对象。
        BRep_Builder builder;
        TopoDS_Compound compound;
        builder.MakeCompound(compound);
      
        // 如果未设置保存ID则全部导出。
        if (_exportIds.isEmpty())
        {
            // 遍历所有模型，获取形状并组合成组合对象。
            QList<Interface::FITKAbsGeoCommand*> rootCmds = geoData->getRootCommandList();
            int nGeo = rootCmds.count();
            for (int i = 0; i < nGeo; i++)
            {
                Interface::FITKAbsGeoCommand* cmd = rootCmds[i];
                if (!cmd)
                {
                    return false;
                }

                // 获取OCC模型代理器。
                FITKAbstractOCCModel* occModel = cmd->getTShapeAgent<FITKAbstractOCCModel>();
                if (!occModel)
                {
                    continue;
                }

                // 获取形状并添加至组合对象。
                TopoDS_Shape* shape = occModel->getShape();
                builder.Add(compound, *shape);
            }

        }
        // 导出指定命令。
        else
        {
            int nValidCmd = 0;
            for (const int & id : _exportIds)
            {
                Interface::FITKAbsGeoCommand* cmd = geoData->getDataByID(id);
                if (!cmd)
                {
                    continue;
                }

                // 获取OCC模型代理器。
                FITKAbstractOCCModel* occModel = cmd->getTShapeAgent<FITKAbstractOCCModel>();
                if (!occModel)
                {
                    continue;
                }

                // 获取形状并添加至组合对象。
                TopoDS_Shape* shape = occModel->getShape();
                builder.Add(compound, *shape);

                nValidCmd++;
            }

            if (nValidCmd == 0)
            {
                return false;
            }
        }
        
        // 文件写出。
        bool flag = wirteFile(_exportFileName, compound);

        return flag;
    }

    bool FITKOCCModelExport::wirteFile(QString fileName, TopoDS_Shape & shape)
    {
        // 检查输入信息。
        if (fileName.isEmpty() || shape.IsNull())
        {
            return false;
        }

        // 获取文件后缀。
        QString lowerSuffix = fileName.split(".").last().trimmed().toLower();
        bool flag = false;
        QByteArray baName = fileName.toUtf8();

        // 导出brep。
        if (lowerSuffix == "brep")
        {
            flag = BRepTools::Write(shape, baName);
        }
        // 导出stp/step。
        else if (lowerSuffix == "stp" || lowerSuffix == "step")
        {
            STEPControl_Writer writer;
            writer.Transfer(shape, STEPControl_AsIs);
            flag = writer.Write(baName);
        }
        // 写出igs/iges。
        else if (lowerSuffix == "igs" || lowerSuffix == "iges")
        {
            IGESControl_Writer writer;
            writer.AddShape(shape);
            flag = writer.Write(baName);
        }
        // 写出stl。
        else if (lowerSuffix == "stl")
        {
            flag = StlAPI::Write(shape, baName);
        }

        return flag;
    }
}


