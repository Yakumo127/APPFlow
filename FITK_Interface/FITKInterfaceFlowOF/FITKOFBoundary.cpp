#include "FITKOFBoundary.h"
#include "FITKOFBoundaryType.h"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKGlobalData.h"
#include "FITK_Interface/FITKInterfaceMesh/FITKUnstructuredFluidMeshVTK.h"

namespace Interface
{

    FITKOFBoundary::FITKOFBoundary(FITKOFSolverTypeEnum::FITKOFBoundaryType bType)
        :_boundaryType(bType)
    {
    }

    FITKOFBoundary::~FITKOFBoundary()
    {
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _flow.begin(); iter != _flow.end(); ++iter)
        {
            if (iter->second) delete iter->second;
        }
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _turbulence.begin(); iter != _turbulence.end(); ++iter)
        {
            if (iter->second) delete iter->second;
        }
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _phases.begin(); iter != _phases.end(); ++iter)
        {
            if (iter->second) delete iter->second;
        }
    }

    FITKOFSolverTypeEnum::FITKOFBoundaryType FITKOFBoundary::getBoundaryType()
    {
        return _boundaryType;
    }

    void FITKOFBoundary::setMeshBoundaryID(int meshId)
    {
        _meshBoundaryID = meshId;
        auto mesh = this->getMeshBoundary();
        if (mesh)
            this->setUserData(Core::FITKUserData::FITKUserRole, mesh->getDataObjectName());
    }

    int FITKOFBoundary::getMeshBoundaryID()
    {
        return _meshBoundaryID;
    }

    FITKBoundaryMeshVTK* FITKOFBoundary::getMeshBoundary()
    {
        AppFrame::FITKGlobalData* globalData = FITKAPP->getGlobalData();
        if (!globalData)return nullptr;
        Interface::FITKUnstructuredFluidMeshVTK* meshData = globalData->getMeshData< Interface::FITKUnstructuredFluidMeshVTK>();
        if (meshData == nullptr)return nullptr;
        Interface::FITKBoundaryMeshVTKManager* boundMeshManager = meshData->getBoundaryMeshManager();
        if (boundMeshManager == nullptr)return nullptr;
        return boundMeshManager->getDataByID(_meshBoundaryID);
    }

    int FITKOFBoundary::getFlowCount()
    {
        return _flow.size();
    }

    QString FITKOFBoundary::getFlowVariableName(int index)
    {
        if (index < 0 || index >= _flow.size())return QString();
        return _flow[index].first;
    }

    FITKOFAbsBoundaryType* FITKOFBoundary::getFlowVBType(int index)
    {
        if (index < 0 || index >= _flow.size())return nullptr;
        return _flow[index].second;
    }

    int FITKOFBoundary::getTurbulenceCount()
    {
        return _turbulence.size();
    }

    QString FITKOFBoundary::getTurbulenceVariableName(int index)
    {
        if (index < 0 || index >= _turbulence.size())return QString();
        return _turbulence[index].first;
    }

    FITKOFAbsBoundaryType* FITKOFBoundary::getTurbulenceVBType(int index)
    {
        if (index < 0 || index >= _turbulence.size())return nullptr;
        return _turbulence[index].second;
    }

    int FITKOFBoundary::getPhasesCount()
    {
        return _phases.size();
    }

    QString FITKOFBoundary::getPhasesVariableName(int index)
    {
        if (index < 0 || index >= _phases.size())return QString();
        return _phases[index].first;
    }

    FITKOFAbsBoundaryType* FITKOFBoundary::getPhasesVBType(int index)
    {
        if (index < 0 || index >= _phases.size())return nullptr;
        return _phases[index].second;
    }

    void FITKOFBoundary::setFlowBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType)
    {
        if (!boundaryType)return;
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _flow.begin(); iter != _flow.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            if (iter->second)
                delete iter->second;
            iter->second = boundaryType;
            return;
        }
        _flow.append(QPair<QString, FITKOFAbsBoundaryType*>(variableName, boundaryType));
    }

    void FITKOFBoundary::setTurbulenceBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType)
    {
        if (!boundaryType)return;
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _turbulence.begin(); iter != _turbulence.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            if (iter->second)
                delete iter->second;
            iter->second = boundaryType;
            return;
        }
        _turbulence.append(QPair<QString, FITKOFAbsBoundaryType*>(variableName, boundaryType));
    }

    void FITKOFBoundary::setPhasesBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType)
    {
        if (!boundaryType)return;
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _phases.begin(); iter != _phases.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            if (iter->second)
                delete iter->second;
            iter->second = boundaryType;
            return;
        }
        _phases.append(QPair<QString, FITKOFAbsBoundaryType*>(variableName, boundaryType));
    }

    void FITKOFBoundary::setBoundary(QString variableName, FITKOFAbsBoundaryType* boundaryType)
    {
        if (!boundaryType)return;
        //Flow
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _flow.begin(); iter != _flow.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            if (iter->second)
                delete iter->second;
            iter->second = boundaryType;
            return;
        }
        //Turbulence
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _turbulence.begin(); iter != _turbulence.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            if (iter->second)
                delete iter->second;
            iter->second = boundaryType;
            return;
        }
        //Phases
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _phases.begin(); iter != _phases.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            if (iter->second)
                delete iter->second;
            iter->second = boundaryType;
            return;
        }
    }

    void FITKOFBoundary::clearTurbulenceBoundary()
    {
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _turbulence.begin(); iter != _turbulence.end(); ++iter)
        {
            if (iter->second) delete iter->second;
        }
        _turbulence.clear();
    }

    FITKOFAbsBoundaryType* FITKOFBoundary::getBoundary(QString variableName)
    {
        //Flow
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _flow.begin(); iter != _flow.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            return iter->second;
        }
        //Turbulence
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _turbulence.begin(); iter != _turbulence.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            return iter->second;
        }
        //Phases
        for (QList<QPair<QString, FITKOFAbsBoundaryType*>>::iterator iter = _phases.begin(); iter != _phases.end(); ++iter)
        {
            if (iter->first != variableName)continue;
            return iter->second;
        }
        return nullptr;
    }

    QList<FITKOFBoundary*> FITKOFBoundaryManager::getBoundarys(FITKOFSolverTypeEnum::FITKOFBoundaryType t)
    {
        QMutexLocker locker(&_mutex);
        QList<FITKOFBoundary*> bds{};
        const int n = this->getDataCount();
        for (int i = 0; i < n; i++)
        {
            FITKOFBoundary* bd = this->getDataByIndex(i);
            if(bd == nullptr) continue;
            if (bd->getBoundaryType() == t)
                bds.append(bd);
        }
        return bds;
    }

    FITKOFBoundary * FITKOFBoundaryManager::getBoundary(int MeshBoundaryID)
    {
        const int n = this->getDataCount();
        for (int i = 0; i < n; i++)
        {
            FITKOFBoundary* bd = this->getDataByIndex(i);
            if (bd == nullptr) continue;
            if (bd->getMeshBoundaryID() == MeshBoundaryID)return bd;
        }
        return nullptr;
    }

}

