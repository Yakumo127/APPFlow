/**********************************************************************
 * @file   FITKOFInitialConditions.h
 * @brief  initial Conitions数据对象
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date   2024-08-23
 *********************************************************************/
#ifndef _FITK_OF_Initial_Conditions__H___
#define _FITK_OF_Initial_Conditions__H___
 
#include "FITKInterfaceFlowOFAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITKOFEnum.hpp"

namespace Core
{
    class FITKParameter;
}

namespace Interface
{
    class FITKAbsGeoCommand;
    /**
     * @brief  几何补丁
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-09-03
     */
    class FITKInterfaceFlowOFAPI FITKOFGeometryPatch
    {
    public:
        explicit FITKOFGeometryPatch(int geoId, FITKOFSolverInitialEnum::FITKPatchApplyObjectType type);
        virtual ~FITKOFGeometryPatch();

        /**
         * @brief 获取几何Id
         * @return int
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-23
         */
        int getGeometryId();
        /**
         * @brief 获取几何数据对象
         * @return Interface::FITKAbsGeoCommand*
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date 2024-07-26
         */
        Interface::FITKAbsGeoCommand* getGeometryModel();
        /**
         * @brief    获取参数
         * @return   Core::FITKParameter *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-04
         */
        Core::FITKParameter* getFieldPara();
        /**
         * @brief    获取类型
         * @return   FITKOFSolverInitialEnum::FITKPatchApplyObjectType
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-04
         */
        FITKOFSolverInitialEnum::FITKPatchApplyObjectType getAppltTo();

    private:
        int _geometryId{ 0 };
        Core::FITKParameter* _fieldPara{};
        FITKOFSolverInitialEnum::FITKPatchApplyObjectType _applyType{ FITKOFSolverInitialEnum::FITKPatchApplyObjectType::Cells };
    };
    /**
     * @brief  初始条件数据对象
     * @author liuzhonghua (liuzhonghuaszch@163.com)
     * @date   2024-09-03
     */
    class FITKInterfaceFlowOFAPI FITKOFInitialConditions : public Core::FITKAbstractNDataObject
    {
        Q_OBJECT
            FITKCLASS(Interface, FITKOFInitialConditions);
    public:
        explicit FITKOFInitialConditions();
        virtual ~FITKOFInitialConditions();
        /**
         * @brief    获取基础初始化
         * @return   Core::FITKParameter *
         * @author   liuzhonghua (liuzhonghuaszch@163.com)
         * @date     2024-09-03
         */
        Core::FITKParameter* getBasicData();

        int getPatchCount();

        FITKOFGeometryPatch* getPatch(int index);

        void removePatch(int index);

        void appendPatch(FITKOFGeometryPatch* patch);

    protected:
    private:
        /**
         * @brief  基础初始化参数
         * @author liuzhonghua (liuzhonghuaszch@163.com)
         * @date   2024-09-03
         */
        Core::FITKParameter* _basic{};

        QList<FITKOFGeometryPatch*> _patchs{};
    };
}


#endif
