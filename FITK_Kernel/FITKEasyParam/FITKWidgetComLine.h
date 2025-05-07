/**
 * 
 * @file FITKWidgetComLine.h
 * @brief 单个参数组件界面
 * @author BaGuijun (baguijun@163.com)
 * @date 2024-08-16
 * 
 */
#ifndef _FITKWidgetComLine_H
#define _FITKWidgetComLine_H

#include "FITKEasyParamAPI.h"
#include <QWidget>

class QToolBox;

namespace Ui {
    class FITKWidgetComLine;
}

namespace Core
{
    class FITKAbstractEasyParam;
    /**
     * @brief 单个参数组件界面
     * @author BaGuijun (baguijun@163.com)
     * @date 2024-08-16
     */
    class FITKEasyParamAPI FITKWidgetComLine : public QWidget
    {
        Q_OBJECT;
    public:
        /**
         * @brief Construct a new comp Cal Line Widget object
         * @param[i]  data           数据对象
         * @param[i]  parent         父对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-08-16
         */
        FITKWidgetComLine(FITKAbstractEasyParam* data, QWidget* parent = nullptr);
        /**
         * @brief Destroy the comp Cal Line Widget object
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-08-16
         */
        ~FITKWidgetComLine();
        /**
         * @brief 初始化函数
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-08-16
         */
        void init();
        /**
         * @brief    创建QToolBox
         * @param[i] parent 父对象
         * @return   QToolBox *  QToolBox对象
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-08-23
         */
        static QToolBox* CreateToolBox(QWidget* parent = nullptr);
        /**
         * @brief    获取界面对应的数据
         * @return   FITKAbstractEasyParam* data
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-14
         */
        FITKAbstractEasyParam* getData();
    private:
        /**
         * @brief ui对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-08-16
         */
        Ui::FITKWidgetComLine* _ui = nullptr;
        /**
         * @brief 数据对象
         * @author BaGuijun (baguijun@163.com)
         * @date 2024-08-16
         */
        FITKAbstractEasyParam* _data = nullptr;
    };
}

#endif
