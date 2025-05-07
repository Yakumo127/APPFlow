/*****************************************************************//**
 * @file    FITKOCCModelOperFace.h
 * @brief   抽象线操作类
 *
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-08-19
 *********************************************************************/

#ifndef  FITKOCCMODELOPERFACE_H
#define  FITKOCCMODELOPERFACE_H

#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoModelOperFace.h"


namespace OCC
{
    /**
     * @brief  抽象面操作类
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-31
     */
    class FITKGeoCompOCCAPI FITKOCCModelOperFace : public Interface::FITKAbsGeoModelOperFace, public OCCShapeAgent
    {
    public:
        FITKOCCModelOperFace();
        virtual ~FITKOCCModelOperFace() override = default;

        /**
         * @brief   更新模型
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-19
         */
        virtual bool update() override;

    private:

        /**
         * @brief   填补孔洞
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        bool updateFillHoles(QList<TopoDS_Shape> shapes);

        /**
         * @brief   删除悬浮边
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-29
         */
        bool updateDeleteFloatingEdge(QList<TopoDS_Shape> shapes);

        /**
         * @brief   将点映射到面
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        bool updateImprintMapPointToFace(QList<TopoDS_Shape> shapes);

        /**
         * @brief   将线映射到面
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        bool updateImprintMapLineToFace(QList<TopoDS_Shape> shapes);

        /**
         * @brief   将圆映射到面
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        bool updateImprintMapCircleToFace(QList<TopoDS_Shape> shapes);
    };

    /**
     * @brief  抽象面操作类 填补孔洞
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-31
     */
    class FITKGeoCompOCCAPI FITKOCCModelOperFaceFillHoles : public Interface::FITKAbsGeoModelOperFaceFillHoles, public OCCShapeAgent
    {
    public:
        FITKOCCModelOperFaceFillHoles();
        virtual ~FITKOCCModelOperFaceFillHoles() override = default;
        /**
             * @brief   更新模型
             * @return  true
             * @return  false
             * @author  fulipeng (fulipengqd@yeah.net)
             * @date    2024-08-19
             */
        virtual bool update() override;

    private:

        /**
         * @brief   填补孔洞
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        bool updateFillHoles(QList<TopoDS_Shape> shapes);

    };

    /**
     * @brief  抽象面操作类 填补缝隙
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-31
     */
    class FITKGeoCompOCCAPI FITKOCCModelOperFaceFillGaps : public Interface::FITKAbsGeoModelOperFaceFillGaps, public OCCShapeAgent
    {
    public:
        FITKOCCModelOperFaceFillGaps();
        virtual ~FITKOCCModelOperFaceFillGaps() override = default;
        /**
             * @brief   更新模型
             * @return  true
             * @return  false
             * @author  fulipeng (fulipengqd@yeah.net)
             * @date    2024-08-19
             */
        virtual bool update() override;

    private:

        /**
         * @brief   填补缝隙
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        bool updateFillGaps(QList<TopoDS_Shape> shapes);

        /**
         * @brief   检查并强制曲线闭合
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-23
         */
        TopoDS_Shape CheckAndForceCurveClosure(QList<TopoDS_Shape> shapes, bool& isSuccessful);
    };

    /**
     * @brief  抽象面操作类 删除悬浮边
     * @author fulipeng (fulipengqd@yeah.net)
     * @date   2024-08-31
     */
    class FITKGeoCompOCCAPI FITKOCCModelOperFaceDeleteFloatingEdge : public Interface::FITKAbsGeoModelOperFaceDeleteFloatingEdge, public OCCShapeAgent
    {
    public:
        FITKOCCModelOperFaceDeleteFloatingEdge();
        virtual ~FITKOCCModelOperFaceDeleteFloatingEdge() override = default;
        /**
             * @brief   更新模型
             * @return  true
             * @return  false
             * @author  fulipeng (fulipengqd@yeah.net)
             * @date    2024-08-19
             */
        virtual bool update() override;

    private:

        /**
         * @brief   删除悬浮边
         * @param   shapes：操作形状列表
         * @return  true
         * @return  false
         * @author  fulipeng (fulipengqd@yeah.net)
         * @date    2024-08-31
         */
        bool updateDeleteFloatingEdge(QList<TopoDS_Shape> shapes);
    };
}

#endif // !FITKABSGEOMODELOPERLINE_H