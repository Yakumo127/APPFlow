﻿#include "FITKOCCModelSimpleShape.h"
#include <BRepPrimAPI_MakeBox.hxx>
#include <gp_Ax2.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>

namespace OCC
{

    FITKOCCModelBox::FITKOCCModelBox():OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;
    }

    bool FITKOCCModelBox::update()
    {
        gp_Pnt pt1(_point1[0], _point1[1], _point1[2]);
        gp_Pnt pt2(_point1[0]+_lengthParam[0], _point1[1]+ _lengthParam[1], _point1[2]+ _lengthParam[2]);
        //错误判断
        if (pt1.Distance(pt2) < 1e-9)
        {
            printLog(tr("Invalid length !"), 3);
            return false;
        }

        //创建长方体

        // 异常处理。
        try
        {
            BRepPrimAPI_MakeBox cmd(pt1, pt2);
            cmd.Build();
            if (!cmd.IsDone())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            const TopoDS_Shape & output = cmd.Shape();
            if (output.IsNull())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            _occShapeAgent->updateShape(cmd.Shape());
        }
        catch (...)
        {
            printLog(tr("Invalid parameters !"), 3);
            return false;
        }
       
        return true;
    }

    FITKOCCModelCylinder::FITKOCCModelCylinder() :OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;

    }

    bool FITKOCCModelCylinder::update()
    {
        // 异常处理。
        try
        {
            //创建轴线
            gp_Ax2 anAxis;
            anAxis.SetLocation(gp_Pnt(_location[0], _location[1], _location[2]));
            anAxis.SetDirection(gp_Dir(_direction[0], _direction[1], _direction[2]));
            //创建圆柱
            if (_length < 1e-9)
            {
                printLog(tr("Invalid length !"), 3);
                return false;
            }

            if (_radius < 1e-9)
            {
                printLog(tr("Invalid radius !"), 3);
                return false;
            }

            BRepPrimAPI_MakeCylinder cmd(anAxis, _radius, _length);
            cmd.Build();
            if (!cmd.IsDone())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            const TopoDS_Shape & output = cmd.Shape();
            if (output.IsNull())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            _occShapeAgent->updateShape(output);
        }
        catch(...)
        {
            printLog(tr("Invalid parameters !"), 3);
            return false;
        }

        return true;
    }

    FITKOCCModelSphere::FITKOCCModelSphere():OCCShapeAgent(this)
    {
        _shapeAgent = _occShapeAgent;

    }

    bool FITKOCCModelSphere::update()
    {
        // 异常处理。
        try
        {
            //错误判断
            gp_Pnt pt(_location[0], _location[1], _location[2]);
            if (_radius < 1e-6)
            {
                printLog(tr("Invalid radius !"), 3);
                return false;
            }

            //创建球体
            BRepPrimAPI_MakeSphere cmd(pt, _radius);
            cmd.Build();
            if (!cmd.IsDone())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            const TopoDS_Shape & output = cmd.Shape();
            if (output.IsNull())
            {
                printLog(tr("Invalid parameters !"), 3);
                return false;
            }

            _occShapeAgent->updateShape(cmd.Shape());
        }
        catch (...)
        {
            printLog(tr("Invalid parameters !"), 3);
            return false;
        }

        return true;
    }

}
