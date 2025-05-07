/**
 *
 * @file FITKGeoCommandList.h
 * @brief 几何命令列表（撤销列表）
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-07-30
 *
 */
#ifndef _FITK_GEO_COMMANDLIST__H___
#define _FITK_GEO_COMMANDLIST__H___

#include "FITKInterfaceGeometryAPI.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITKAbsGeoCommand.h"
#include "FITKAbsGeoDatum.h"
#include "FITKAbsGeoSketch2D.h"
#include "FITKGlobalGeoComponent.h"

namespace Interface
{
    /**
     * @brief 几何命令列表（撤销列表）
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-07-30
     */
    class FITKInterfaceGeometryAPI FITKGeoCommandList : public Core::FITKAbstractDataObject, public FITKGeoCommandManager
    {
        FITKCLASS(Interface, FITKGeoCommandList);
    public:
        /**
         * @brief Construct a new FITKGeoCommandList object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-30
         */
        explicit FITKGeoCommandList();
        /**
         * @brief Destroy the FITKGeoCommandList object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-07-30
         */
        virtual ~FITKGeoCommandList();

        /**
         * @brief   数据名称检查。[虚函数][重写]
         * @param   被检测的名称[引用]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-20
         */
        virtual QString checkName(const QString & name) override;

        /**
         * @brief   获取基准元素管理器。
         * @return  基准元素类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKDatumList* getDatumManager();

        /**
         * @brief   设置当前激活草图数据ID。
         * @param   sketchDataId：草图数据ID（-1或ID为非草图数据则清除当前激活草图）[缺省]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-04
         */
        void setCurrentSketchID(int sketchDataId = -1);

        /**
         * @brief   获取当前激活中的草图数据。
         * @return  草图对象
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-04
         */
        FITKAbsGeoSketch2D* getCurrentSketchData();

        /**
         * @brief   获取全局几何分组管理器。
         * @return  全局几何分组管理器。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-28
         */
        FITKGlobalGeoComponentManager* getGlobalGeoCompManager();

        /**
         * @brief   获取是否可以执行撤销操作。[虚函数]
         * @return  是否可以撤销
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-20
         */
        virtual bool canUndo();

        /**
         * @brief   获取是否可以执行重做操作。[虚函数]
         * @return  是否可以重做
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-20
         */
        virtual bool canRedo();

        /**
         * @brief   撤销。[虚函数]
         * @return  是否撤销成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-06
         */
        virtual bool undo();

        /**
         * @brief   重做。[虚函数]
         * @return  是否重做成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-06
         */
        virtual bool redo();

        /**
         * @brief   重写添加数据对象功能。（添加命令并清空RedoList）[虚函数][重写]
         * @param   obj：数据对象
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-06
         */
        virtual void appendDataObj(Core::FITKAbstractDataObject* obj) override;

        /**
        * @brief 获取全部模型包围盒
        * @param[o] minPt 最小点位置
        * @param[o] maxPt 最大点位置
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-07-30
        */
        void getBoundaryBox(double* minPt, double* maxPt);

        /**
         * @brief   获取撤销列表。
         * @return  撤销列表
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-06
         */
        FITKGeoCommandManager* getUndoList();

        /**
         * @brief   获取重做列表。
         * @return  重做列表
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-06
         */
        FITKGeoCommandManager* getRedoList();

        /**
         * @brief   获取未被引用的命令列表。
         * @return  根节点命令列表
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-07
         */
        QList<FITKAbsGeoCommand*> getRootCommandList();

        /**
         * @brief   获取全局数据ID列表。
         * @return  全局数据ID列表
         * @author  libaojun
         * @date    2025-04-28
         */
        QList<int> getGlobalDataIDList();

    protected:
        /**
         * @brief   重做列表。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-06
         */
        FITKGeoCommandManager* m_redoList{ nullptr };

        /**
         * @brief   基准元素管理器。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKDatumList* m_datumMgr{ nullptr };

        /**
         * @brief   全局几何分组管理器。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-28
         */
        FITKGlobalGeoComponentManager* m_globalGeoCompMgr{ nullptr };

        /**
         * @brief   当前激活草图数据ID。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-04
         */
        int m_currentSketchID = -1;
    };
}


#endif
