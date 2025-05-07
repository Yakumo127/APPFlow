#include "FITKOFMeshProcessor.h"
#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredFluidMeshVTK.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Component/FITKOFMeshIO/FITKOFMeshReader.h"
#include "FITK_Kernel/FITKAppFramework/FITKComponents.h"

namespace OF
{
    void FITKOFMeshProcessor::start(QStringList info /*= QStringList()*/)
    {
        QString path = getValue("WorkDir").toString();
        // 读取网格
        // 写出字典文件
        Interface::FITKUnstructuredFluidMeshVTK* mesh = FITKAPP->getGlobalData()->getMeshData<Interface::FITKUnstructuredFluidMeshVTK>();
        mesh->clearMesh();
        auto ofMeshReader = FITKAPP->getComponents()->getComponentTByName<IO::FITKOFMeshReader>("IO::FITKOFMeshReader");
        if (ofMeshReader == nullptr) return;
        ofMeshReader->setMeshFolder(path + "/constant/polyMesh/");
        ofMeshReader->setMeshObj(mesh);
        ofMeshReader->exec(0);
    }
}



