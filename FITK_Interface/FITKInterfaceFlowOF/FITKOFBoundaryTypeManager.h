/**********************************************************************
 * @file   FITKOFBoundaryTypeManager.h
 * @brief  边界类型管理器
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-26
 *********************************************************************/
#ifndef _FITK_OF_BOUNDARY_TYPEMANAGER_H___
#define _FITK_OF_BOUNDARY_TYPEMANAGER_H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITKOFEnum.hpp"
#include <functional>
#include <QStringList>
#include <QHash>

namespace Interface
{
    class FITKOFAbsBoundaryType;
}

typedef std::function<Interface::FITKOFAbsBoundaryType*()>  CREATEBOUNDARYTYPEFUN;

namespace Interface
{

    struct FITKOFBoundaryTypeInfo
    {
        QString _boundaryTypeName{};
        QHash<FITKOFSolverTypeEnum::FITKOFBoundaryType, QStringList> _enableBoundary;//边界类型, 变量名
        CREATEBOUNDARYTYPEFUN _createFuns;
    };

    class FITKInterfaceFlowOFAPI FITKOFBoundaryTypeManager
    {
    public:
        explicit FITKOFBoundaryTypeManager();
        virtual ~FITKOFBoundaryTypeManager();

        QStringList filterBoundariesType(FITKOFSolverTypeEnum::FITKOFSolverType solverType, FITKOFSolverTypeEnum::FITKOFBoundaryType boundaryType, QString variableType);

        FITKOFBoundaryTypeInfo getBoundaryTypeInfo(QString boundaryTypeName, FITKOFSolverTypeEnum::FITKOFSolverType solverType, QString variableType, FITKOFSolverTypeEnum::FITKOFBoundaryType boundaryType);
    
    private:
        /**
         * @brief    初始化SIMPLE求解器Boundary Type数据信息
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-31
         */
        void initSIMPLESolverBTy();
        /**
         * @brief    初始化Inter求解器Boundary Type数据信息
         * @return   void
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-08-31
         */
        void initInterSolverBTy();

    private:
        /**
         * @brief  边界数据信息 求解器，边界信息
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-08-31
         */
        QHash<FITKOFSolverTypeEnum::FITKOFSolverType, QList<FITKOFBoundaryTypeInfo*>> m_boundaryTypes{};
    };
}


#endif
