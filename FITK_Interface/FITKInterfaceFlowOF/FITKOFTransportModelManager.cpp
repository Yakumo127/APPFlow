#include "FITKOFTransportModelManager.h"
#include "FITKOFTransportModel.h"

namespace Interface
{
    FITKOFTransportModelManager::FITKOFTransportModelManager()
    {
        this->initTransportModels();
    }

    FITKOFTransportModelManager::~FITKOFTransportModelManager()
    {

    }

    QStringList FITKOFTransportModelManager::filterTransportModels(FITKOFSolverTypeEnum::FITKOFSolverType solverType)
    {
        QStringList listType;
        //求解器遍历
        for (QList<FITKOFTransportModelInfo>::iterator iter = m_transportModels.begin(); iter != m_transportModels.end(); ++iter)
        {
            //进行过滤
            if (iter->_enableSolverType.contains(solverType))
                listType.append(iter->_transModelName);
        }
        return listType;
    }

    FITKOFTransportModelInfo FITKOFTransportModelManager::getTransportModelInfo(QString transModelName)
    {
        for (QList<FITKOFTransportModelInfo>::iterator iter = m_transportModels.begin(); iter != m_transportModels.end(); ++iter)
        {
            if (iter->_transModelName == transModelName) return *iter;
        }
        return FITKOFTransportModelInfo();
    }

    void FITKOFTransportModelManager::initTransportModels()
    {
        //Newtonian
        FITKOFTransportModelInfo infoNewtonian;
        infoNewtonian._transModelName = "Newtonian";
        infoNewtonian._enableSolverType << FITKOFSolverTypeEnum::FITKOFSolverType::SIMPLE << FITKOFSolverTypeEnum::FITKOFSolverType::INTER;
        infoNewtonian._createFuns = [&] {return new FITKOFTransModelNewtonian; };
        m_transportModels.append(infoNewtonian);
    }
}
