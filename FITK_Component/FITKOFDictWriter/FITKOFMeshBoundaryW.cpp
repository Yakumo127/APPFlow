#include "FITKOFMeshBoundaryW.h"
#include "FITK_Kernel/FITKCore/FITKEnumTransformer.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFPhysicsData.h"
#include "FITK_Interface/FITKInterfaceFlowOF/FITKOFBoundary.h"

#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredFluidMeshVTK.h"
#include "FITK_Interface/FITKInterfaceModel/FITKElementList.h"
#include <QTextStream>
#include <QFileInfo>
#include <QtMath>
#include <QFile>
#include <QDir>
//命名空间
namespace IO
{
    FITKOFMeshBoundaryW::FITKOFMeshBoundaryW()
    {
    }
    FITKOFMeshBoundaryW::~FITKOFMeshBoundaryW()
    {
    }

    void FITKOFMeshBoundaryW::setFilePath(const QString& filePath)
    {
        FITKOFAbstractDictWriter::setFilePath(filePath);
        QFileInfo fileInfo(filePath);
        //判断是否是路径
        if (!fileInfo.isDir())return;
        m_fileName = QString("%1/constant/polyMesh/boundary").arg(filePath);
    }

    bool FITKOFMeshBoundaryW::run()
    {
        //获取路径
        QDir dir;
        QString path = m_fileName.mid(0, m_fileName.lastIndexOf('/'));
        //路径是否存在
        if (!dir.exists(path))return true;
        //打开文件
        QFile file(m_fileName);
        if (file.exists())file.remove();
        //设置写出
        if (!file.open(QIODevice::ReadWrite | QIODevice::NewOnly))
        {
            file.close();
            return false;
        }
        //打开文件流
        m_stream = new QTextStream(&file);
        //写出数据
        bool Ok = this->meshBoundaryW();
        //关闭文件
        file.close();
        delete m_stream;

        return Ok;
    }

    QString FITKOFMeshBoundaryW::getFileName()
    {
        return m_fileName;
    }

    void FITKOFMeshBoundaryW::dictObjectFoamFile()
    {
        //FoamFile
        if (!m_stream)return;
        *m_stream << "FoamFile" << endl;
        *m_stream << "{" << endl;
        *m_stream << "    version    2.0;" << endl;
        *m_stream << "    format    ascii;" << endl;
        *m_stream << "    class    polyBoundaryMesh;" << endl;
        *m_stream << "    location    \"constant/polyMesh\";" << endl;
        *m_stream << "    object    boundary;" << endl;
        *m_stream << "}" << endl;
    }

    bool FITKOFMeshBoundaryW::meshBoundaryW()
    {
        if (!m_stream)return false;
        //获取全局数据管理器
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return false;
        //获取网格数据
        Interface::FITKUnstructuredFluidMeshVTK* meshData = globalData->getMeshData<Interface::FITKUnstructuredFluidMeshVTK>();
        if (!meshData)return false;
        Interface::FITKBoundaryMeshVTKManager* boundaryMeshMgr = meshData->getBoundaryMeshManager();
        if (!boundaryMeshMgr)return false;
        //获取物理数据
        Interface::FITKOFPhysicsData* physicsData = globalData->getPhysicsData<Interface::FITKOFPhysicsData>();
        if (!physicsData)return false;
        //获取BoundaryManager
        Interface::FITKOFBoundaryManager* boundaryPhyMgr = physicsData->getBoundaryManager();
        if (!boundaryPhyMgr)return false;
        //FoamFile
        this->dictObjectFoamFile();
        //设置边界
        int count = boundaryMeshMgr->getDataCount();
        *m_stream << count << endl;
        *m_stream << "(" << endl;
        for (int i = 0; i < count; ++i)
        {
            Interface::FITKBoundaryMeshVTK* boundaryMesh = boundaryMeshMgr->getDataByIndex(i);
            if (!boundaryMesh)continue;
            QString meshName = boundaryMesh->getDataObjectName();
            *m_stream << QString("    %1").arg(meshName) << endl;
            *m_stream << "    {" << endl;
            //获取边界类型
            Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType type = Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BEmpty;
            Interface::FITKOFBoundary* boundaryData = boundaryPhyMgr->getBoundary(boundaryMesh->getDataObjectID());
            if (boundaryData) type = boundaryData->getBoundaryType();
            if (type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BWall)
                *m_stream << QString("        type            wall;") << endl;
            else if (type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BPressureInlet || type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BVelocityInlet
                || type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BPressureOutlet || type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BOutflow)
                *m_stream << QString("        type            patch;") << endl;
            else if (type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BSymmetry)
                *m_stream << QString("        type            symmetry;") << endl;
            else if (type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BWedge)
                *m_stream << QString("        type            wedge;") << endl;
            else if (type == Interface::FITKOFSolverTypeEnum::FITKOFBoundaryType::BEmpty)
                *m_stream << QString("        type            empty;") << endl;
            //设置面和单元
            int faceNum = boundaryMesh->getElementCount();
            *m_stream << QString("        nFaces          %1;").arg(faceNum) << endl;
            QVariant value = boundaryMesh->getUserData(Core::FITKUserData::FITKUserRole);
            *m_stream << QString("        startFace       %1;").arg(value.toInt()) << endl;
            *m_stream << "    }" << endl;
        }
        
        *m_stream << ")" << endl;
        return true;
    }
}



