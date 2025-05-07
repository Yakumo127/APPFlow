﻿#ifndef _FITKOCCOper_BOOL_H___
#define _FITKOCCOper_BOOL_H___


#include "FITKAbstractOCCModel.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoOperBool.h"

class TopoDS_Shape;

namespace OCC
{
    class FITKGeoCompOCCAPI FITKOCCOperBool :public Interface::FITKAbsGeoOperBool,
        public OCCShapeAgent
    {
    public:
        explicit FITKOCCOperBool();
        virtual ~FITKOCCOperBool() = default;


        /**
       * @brief 更新模型
       * @return true 更新成功
       * @return false 更新失败
       * @author LiBaojun (libaojunqd@foxmail.com)
       * @date 2024-06-05
       */
        virtual bool update() override;

    private:
        TopoDS_Shape cut(const TopoDS_Shape* shape1, const TopoDS_Shape* shape2);
        TopoDS_Shape common(const TopoDS_Shape* shape1, const TopoDS_Shape* shape2);
        TopoDS_Shape add(const TopoDS_Shape* shape1, const TopoDS_Shape* shape2);




    };
}


#endif
