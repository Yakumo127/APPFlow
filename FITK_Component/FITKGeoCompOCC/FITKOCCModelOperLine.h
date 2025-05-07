/*****************************************************************//**
 * @file    FITKAbsGeoModelOperLine.h
 * @brief   抽象线操作类
 *
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-08-19
 *********************************************************************/

#ifndef  FITKOCCMODELOPERLINE_H
#define  FITKOCCMODELOPERLINE_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperLine.h"


namespace OCC
{
    class FITKGeoCompOCCAPI FITKOCCModelOperLine : public Interface::FITKAbsGeoModelOperLine, public OCCShapeAgent
    {
    public:
        FITKOCCModelOperLine();
        virtual ~FITKOCCModelOperLine() override = default;

        /**
         * @brief 更新模型
         * @return true
         * @return false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-19
         */
        virtual bool update() override;

    private:

        /**
         * @brief 合并
         * @param   shapes：操作形状列表
         * @return true
         * @return false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-19
         */
        bool updateMerge(QList<TopoDS_Shape> shapes);

        /**
         * @brief 按中点分割
         * @param   shapes：操作形状列表
         * @return true
         * @return false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-19
         */
        bool updateSplitByMiddlePosition(QList<TopoDS_Shape> shapes);

        /**
         * @brief 按角度分割
         * @param   shapes：操作形状列表
         * @return true
         * @return false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-19
         */
        bool updateSplitByAngle(QList<TopoDS_Shape> shapes);
    };

    class FITKGeoCompOCCAPI FITKOCCModelMiddleOperLine : public Interface::FITKAbsGeoModelMiddleOperLine, public OCCShapeAgent
    {
    public:
        FITKOCCModelMiddleOperLine();
        virtual ~FITKOCCModelMiddleOperLine() override = default;

        /**
         * @brief 更新模型
         * @return true
         * @return false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-19
         */
        virtual bool update() override;

    private:
        /**
         * @brief 按中点分割
         * @param   shapes：操作形状列表
         * @return true
         * @return false
         * @author fulipeng (fulipengqd@yeah.net)
         * @date   2024-08-19
         */
        bool updateSplitByMiddlePosition(QList<TopoDS_Shape> shapes);
    };
}

#endif // !FITKABSGEOMODELOPERLINE_H