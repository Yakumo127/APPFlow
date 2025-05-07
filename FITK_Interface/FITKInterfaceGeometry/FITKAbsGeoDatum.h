/*****************************************************************//**
 * @file    FITKAbsGeoDatum.h
 * @brief   体特征处理数据抽象类。

 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-08-30
 *********************************************************************/

#ifndef  FITKABSGEODATUM_H
#define  FITKABSGEODATUM_H

#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataObject.h"
#include "FITK_Kernel/FITKCore/FITKAbstractDataManager.hpp"
#include "FITK_Kernel/FITKAppFramework/FITKAppFramework.h"
#include "FITK_Kernel/FITKAppFramework/FITKSignalTransfer.h"

#include "FITKGeoEnum.h"
#include "FITKAbsGeoCommand.h"
#include "FITKInterfaceGeometryAPI.h"

namespace Interface
{
    /**
     * @brief   基准元素抽象类。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoDatum : public FITKAbsGeoCommand
    {
        FITKCLASS(Interface, FITKAbsGeoDatum);
    public:
        /**
         * @brief   基准元素创建方式枚举。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-31
         */
        enum DatumCreatedType
        {
            DCT_System = 0,
            DCT_UserDefine
        };

        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKAbsGeoDatum() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        virtual ~FITKAbsGeoDatum() = default;

        /**
         * @brief   设置是否可编辑。
         * @param   flag：是否可编辑
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-11
         */
        void setEditable(bool flag);

        /**
         * @brief   设置基准元素位置。
         * @param   pos：坐标
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        void setPosition(double* pos);

        /**
         * @brief   获取基准元素位置。
         * @param   pos：坐标
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        void getPosition(double* pos);

        /**
         * @brief   获取基准元素类型。[纯虚函数]
         * @return  基准元素类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        virtual FITKGeoEnum::FITKDatumType getDatumType() = 0;

        /**
         * @brief   获取几何命令类型。[虚函数][重写]
         * @return  命令类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-10
         */
        virtual FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

        /**
         * @brief   获取基准元素可编辑性。
         * @return  是否可编辑
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-31
         */
        bool editable();

        /**
         * @brief   更新数据对象。[虚函数]
         * @return  是否更新成功
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-04
         */
        virtual bool update() { return true; };

        /**
         * @brief  打印信息到控制台.
         * @param  type 信息类型 1-normal 2-warning 3-error 4-info
         * @param  msg 信息内容
         * @author YanZhiHui (chanyuantiandao@126.com)
         * @date   2024-08-28
         */
        void printLog(QString msg, int type = 1)
        {
            AppFrame::FITKSignalTransfer* sigTrans = FITKAPP->getSignalTransfer();
            if (sigTrans)
            {
                sigTrans->outputMessageSig(type, msg);
            }
        }

    protected:
        /**
         * @brief   位置坐标。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        double m_pos[3]{ 0., 0., 0. };

        /**
         * @brief   基准元素创建方式。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-31
         */
        DatumCreatedType m_createdType = DCT_UserDefine;

        // 指定数据管理器为友元类。
        friend class FITKDatumList;

    };

    /**
     * @brief   基准点类。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoDatumPoint : public FITKAbsGeoDatum
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKAbsGeoDatumPoint() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        virtual ~FITKAbsGeoDatumPoint() = default;

        /**
         * @brief   获取基准元素类型。[重写]
         * @return  基准元素类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

    };

    /**
     * @brief   基准线类。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoDatumLine : public FITKAbsGeoDatum
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKAbsGeoDatumLine() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        virtual ~FITKAbsGeoDatumLine() = default;

        /**
         * @brief   获取基准元素类型。[虚函数][重写]
         * @return  基准元素类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

        /**
         * @brief   设置有限基准线信息。
         * @param   pos1：位置1
         * @param   pos2：位置2
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        void setFiniteLine(double* pos1, double* pos2);

        /**
         * @brief   获取无限基准线信息。
         * @param   pos1：位置1
         * @param   pos2：位置2
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        void getFiniteLine(double* pos1, double* pos2);

        /**
         * @brief   设置有限基准线信息。
         * @param   pos：中心
         * @param   dir：方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        void setInfiniteLine(double* pos, double* dir);

        /**
         * @brief   获取无限基准线信息。
         * @param   pos：中心
         * @param   dir：方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        void getInfiniteLine(double* pos, double* dir);

        /**
         * @brief   设置基准线结束坐标。
         * @param   pos：坐标
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-04
         */
        void setPosition2(double* pos);

        /**
         * @brief   获取基准线结束坐标。
         * @param   pos：坐标
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-04
         */
        void getPosition2(double* pos);

        /**
         * @brief   设置基准线方向。
         * @param   dir：方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        void setDirection(double* dir);

        /**
         * @brief   获取基准线方向。
         * @param   dir：方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        void getDirection(double* dir);

        /**
         * @brief   设置基准线是否为无限范围。
         * @param   flag：是否无限
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-11
         */
        void setIsInfinite(bool flag);

        /**
         * @brief   获取基准线结束坐标。
         * @return  是否为无限基准线
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-11
         */
        bool getIsInfinite();

    protected:
        /**
         * @brief   基准线结束坐标。（有限基准线使用）
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        double m_pos2[3]{ 0., 0., 1. };

        /**
         * @brief   基准线方向。（无限基准线使用）
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-16
         */
        double m_dir[3]{ 0., 0., 0. };

        /**
         * @brief   是否无限。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-10-11
         */
        bool m_isInfinite = false;

    };

    /**
     * @brief   基准平面类。(默认XOY平面)
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoDatumPlane : public FITKAbsGeoDatum
    {
    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKAbsGeoDatumPlane() = default;

        /**
         * @brief   析构函数。[虚函数]
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        virtual ~FITKAbsGeoDatumPlane();

        /**
         * @brief   获取基准元素类型。[重写]
         * @return  基准元素类型
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        FITKGeoEnum::FITKDatumType getDatumType() override;

        /**
         * @brief   设置基准面信息。
         * @param   pos：面中心点坐标
         * @param   normal：面法向
         * @param   up：面向上方向
         * @return  是否为有效平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        void setPlane(double* pos, double* normal, double* up);

        /**
         * @brief   获取基准面信息。
         * @param   pos：面中心点坐标
         * @param   normal：面法向
         * @param   up：面向上方向
         * @return  是否为有效平面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-09-05
         */
        void getPlane(double* pos, double* normal, double* up);

        /**
         * @brief   设置基准面法向。
         * @param   nor：法向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        void setNormal(double* nor);

        /**
         * @brief   获取基准面法向。
         * @param   nor：法向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        void getNormal(double* nor);

        /**
         * @brief   设置基准面向上方向。
         * @param   up：向上方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        void setUp(double* up);

        /**
         * @brief   获取基准面向上方向。
         * @param   up：向上方向
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        void getUp(double* up);

    protected:
        /**
         * @brief   基准面法向。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        double m_nor[3]{ 0., 0., 1. };

        /**
         * @brief   基准面向上方向。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        double m_up[3]{ 0., 1., 0. };
    };

    /**
     * @brief   基准元素管理器类。
     * @author  ChengHaotian (yeguangbaozi@foxmail.com)
     * @date    2024-08-30
     */
    class FITKInterfaceGeometryAPI FITKDatumList :
        public Core::FITKAbstractDataManager<Interface::FITKAbsGeoDatum>
    {
    public:
        /**
         * @brief   系统默认基准面。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        enum PrincipalPlnType
        {
            PPT_XOY = 0,
            PPT_YOZ,
            PPT_ZOX
        };

        /**
         * @brief   系统默认基准轴。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        enum PrincipalAxisType
        {
            PAT_X = 0,
            PAT_Y,
            PAT_Z
        };

    public:
        /**
         * @brief   构造函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        explicit FITKDatumList();

        /**
         * @brief   析构函数。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2024-08-30
         */
        virtual ~FITKDatumList();

        /**
         * @brief   获取系统默认基准面。
         * @param   type：基准面类型
         * @return  基准面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumPlane* getPrincipalPlane(PrincipalPlnType type);

        /**
         * @brief   获取系统默认基准轴。
         * @param   type：基准轴类型
         * @return  基准面
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumLine* getPrincipalAxis(PrincipalAxisType type);

        /**
         * @brief   重新根据ID查询数据逻辑，增加系统默认基准元素判断。[虚函数][重写]
         * @param   id：数据ID
         * @return  基准元素
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        virtual Interface::FITKAbsGeoDatum* getDataByID(const int id) override;

    protected:
        /**
         * @brief   系统默认XOY基准面。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumPlane* m_planeXOY{ nullptr };

        /**
         * @brief   系统默认YOZ基准面。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumPlane* m_planeYOZ{ nullptr };

        /**
         * @brief   系统默认ZOX基准面。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumPlane* m_planeZOX{ nullptr };

        /**
         * @brief   系统默认X基准轴。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumLine* m_axisX{ nullptr };

        /**
         * @brief   系统默认Y基准轴。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumLine* m_axisY{ nullptr };

        /**
         * @brief   系统默认Z基准轴。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-17
         */
        FITKAbsGeoDatumLine* m_axisZ{ nullptr };

    };
}

#endif // !FITKABSGEODATUM_H
