/**
 *
 * @file FITKAbstractOCCModel.h
 * @brief OCC模型基类
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-06-05
 *
 */
#ifndef  _FITKABSTRACTOCCMODEL_H__
#define _FITKABSTRACTOCCMODEL_H__

#include "FITKGeoCompOCCAPI.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoShapeAgent.h"

class TopoDS_Shape;
class TopoDS_Face;

class QTextStream;
class QVector3D;

namespace OCC
{
    class FITKOCCModelPart;
    class FITKGeoComponentManager;
 
    /**
     * @brief OCC模型
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-05-29
     */
    class FITKGeoCompOCCAPI FITKAbstractOCCModel :public Interface::FITKAbsGeoShapeAgent 
    {
        // FITKCLASS(OCC, FITKAbstractOCCModel);
    public:
        /**
         * @brief Construct a new FITKAbstractOCCModel object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-29
         */
        explicit FITKAbstractOCCModel(Interface::FITKAbsGeoCommand* command);
        /**
         * @brief Destroy the FITKAbstractOCCModel object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-29
         */
        virtual ~FITKAbstractOCCModel();

        /**
         * @brief   设置部件。
         * @param   part：部件命令
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        void setPart(FITKOCCModelPart* part);

        /**
         * @brief   获取部件。
         * @return  部件命令
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        FITKOCCModelPart* getPart();

        /**
        * @brief 获取形状对象指针
        * return TopoDS_Shape*
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-06-04
        */
        TopoDS_Shape* getShape();
        /**
         * @brief 写出模型到文件
         * @param[i]  file           文件绝对路径（包含文件名）
         * @return true   写出成功
         * @return false  写出失败
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-28
         */
        virtual bool writeToFile(const QString & file);

        /**
         * @brief 获取形状的数量
         * @param type 形状类别
         * @return int 返回指定形状的数量，错误时返回-1
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-29
         */
        int getShapeCount(const Interface::FITKModelEnum::FITKModelSetType type) override;

        /**
         * @brief 获取形状
         * @param[i]  type 形状类别（1-点 2-线 3-面 4-实体）
         * @param[i]  id 形状的ID
         * @return TopoDS_Shape 返回形状对象
          * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-29
         */
         const TopoDS_Shape getShape(Interface::FITKModelEnum::FITKModelSetType type, const int id);
         /**
        * @brief 获取几何引擎类型
        * @return FITKGeoEnum::FITKGeoEngine
        * @author LiBaojun (libaojunqd@foxmail.com)
        * @date 2024-07-12
        */
         Interface::FITKGeoEnum::FITKGeoEngine getGeoEngine() override;
         /**
         * @brief 获取模型类型
         * @return AbsModelType
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
         Interface::FITKModelEnum::AbsModelType getAbsModelType() override;

         /**
          * @brief 获取模型包围盒
          * @param[o] minPt 最小点位置
          * @param[o] maxPt 最大点位置
          * @author LiBaojun (libaojunqd@foxmail.com)
          * @date 2024-07-30
          */
         bool getBoundaryBox(double* min, double* max) override;

         /**
          * @brief 更新形状
          * @param[i] shape 形状对象
          * @author LiBaojun (libaojunqd@foxmail.com)
          * @date 2024-07-30
          */
         void updateShape(const TopoDS_Shape& shape, bool builVTopo = true);
         /**
          * @brief 创建虚拓扑
          * @author LiBaojun (libaojunqd@foxmail.com)
          * @date 2024-08-12
          */
         void buildVirtualTopo() override;
         /**
          * @brief 模型三角化
          * @author LiBaojun (libaojunqd@foxmail.com)
          * @date 2024-08-12
          */
         void triangulation() override;

         /**
          * @brief   获取模型维度。[重写]
          * @return  维度（0-3）
          * @author  ChengHaotian (yeguangbaozi@foxmail.com)
          * @date    2024-12-13
          */
         int getDim() override;

         /**
          * @brief   创建并获取形状状态标记。[重写]
          * @param   形状状态标记[引用]
          * @return  是否有效
          * @author  ChengHaotian (yeguangbaozi@foxmail.com)
          * @date    2024-12-19
          */
         bool createShapeState(QVariant & stateVal) override;

    protected:
        /**
         * @brief 模型数据
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        TopoDS_Shape* _shape{};
        /**
         * @brief 是否正在执行构建拓扑
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        bool _buildingTopo{ false };

        /**
         * @brief   模型状态标记。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-04-01
         */
        int _hashCode = -1;

        /**
         * @brief   当前形状所属部件。
         * @author  ChengHaotian (yeguangbaozi@foxmail.com)
         * @date    2025-03-27
         */
        FITKOCCModelPart* m_part{ nullptr };

    };
    /**
     * @brief OCC形状代理器
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-08-12
     */
    class OCCShapeAgent
    {
    public:
        /**
         * @brief 构造函数
         * @param[i]  c             创建命令
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-12
         */
        explicit OCCShapeAgent(Interface::FITKAbsGeoCommand* c);
        /**
         * @brief Destroy the OCCShapeAgent object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-12
         */
        virtual ~OCCShapeAgent() = default;

    protected:
        /**
         * @brief OCC模型代理
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-08-12
         */
        FITKAbstractOCCModel* _occShapeAgent{};

    };
  
}


#endif
