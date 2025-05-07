#include "FITKInterfaceHDF5AdaptorSampleCurve.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoSampleCurve.h"
#include"FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"

namespace IO
{
    QString IO::FITKInterfaceHDF5AdaptorSampleCurve::getAdaptorClass()
    {
        return "OCC::FITKOCCSampleCurve";
    }

    bool FITKInterfaceHDF5AdaptorSampleCurve::adaptR()
    {
        //错误判断
        Interface::FITKAbsGeoSampleCurve* comm = dynamic_cast<Interface::FITKAbsGeoSampleCurve*>(_dataObj);
        if (!_reader || !comm || !_h5Group) return false;

        // 读取 SampleMethod
        bool ok = false;
        std::string smethod = this->readStrAttribute(*_h5Group, "SampleMethod");
        Interface::FITKAbsGeoSampleCurve::SampleMethod me =
            Core::FITKEnumTransfer<Interface::FITKAbsGeoSampleCurve::SampleMethod>().
            fromString(QString::fromStdString(smethod), ok);
        if (!ok) return false;
        comm->setSampleMethod(me);

        // 读取 SampleCurve
        int curveArray[3] = {0,0,0};
        this->readIntAttribute(*_h5Group, "SampleCurve", curveArray, 1, 3);
        Interface::VirtualShape curve;
        curve.CmdId = curveArray[0];
        curve.VirtualTopoId = curveArray[1];
        curve.VirtualTopoIndex = curveArray[2];
        comm->setSampleCurve(curve);

        // 读取 SampleCount
        int count= 0;
        this->readIntAttribute(*_h5Group, "SampleCount", &count,1,1);
        comm->setSamplePointCount(count);

        return true;
    }
    bool FITKInterfaceHDF5AdaptorSampleCurve::adaptW()
    {
        //错误判断
        Interface::FITKAbsGeoSampleCurve* comm = dynamic_cast<Interface::FITKAbsGeoSampleCurve*>(_dataObj);
        if (!_writer || !comm || !_h5Group) return false;
        
        Interface::FITKAbsGeoSampleCurve::SampleMethod me = comm->getSampleMethod();
        // 使用 FITKEnumTransformer 将 me 变量转为字符串
        bool ok = false;
        QString meStr = Core::FITKEnumTransfer<Interface::FITKAbsGeoSampleCurve::SampleMethod>().
            toString(me,ok);
        if (!ok) return false;

        this->writeStrAttribute(*_h5Group, "SampleMethod", meStr.toStdString());
        Interface::VirtualShape curve = comm->getSampleCurve();
        int curveArray[3] = { curve.CmdId,curve.VirtualTopoId,curve.VirtualTopoIndex };
        this->writeIntAttribute(*_h5Group, "SampleCurve", curveArray, 1, 3);
        int count = comm->getSamplePointCount();
        this->writeIntAttribute(*_h5Group, "SampleCount", &count);
        
        return true;
    }
}
