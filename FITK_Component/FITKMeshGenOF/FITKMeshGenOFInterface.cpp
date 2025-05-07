#include "FITKMeshGenOFInterface.h"
#include "FITKOFMeshSizeGenerator.h"
#include "FITKOFGeometryMeshSizeGenerator.h"
#include "FITKOFMesherDriver.h"
#include "FITKOFMeshProcessor.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKMeshGenInterface.h"

namespace OF
{
    FITKMeshGenOFInterface::FITKMeshGenOFInterface()
    {
        //获取工厂
        Interface::FITKMeshGenInterface* mf = Interface::FITKMeshGenInterface::getInstance();
        if (nullptr == mf) return;
        //注册相关类
        mf->regMeshSizeGenerator(new FITKOFMeshSizeGenerator);
        mf->regGeometryMeshSizeGenerator(new FITKOFGeometryMeshSizeGenerator);
        mf->regMesherDriver(new FITKOFMesherDriver);
        mf->regMeshProcessor(new FITKOFMeshProcessor);
    }


    QString FITKMeshGenOFInterface::getComponentName()
    {
        //名称
        return QString("FITKMeshGenOF");
    }

    bool FITKMeshGenOFInterface::exec(const int indexPort)
    {
        return false;
    }


}



