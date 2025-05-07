/**
 *
 * @file FITKComboBox.h
 * @brief  封装qcombobox，添加ListView
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-06-20
 *
 */
#ifndef __FITK__COMBO_BOX_H___
#define __FITK__COMBO_BOX_H___

#include <QComboBox>
#include "FITKWidgetAPI.h"

/**
 * @brief 封装qcombobox，添加ListView
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-06-20
 */
class FITKWidgetAPI FITKComboBox : public QComboBox
{
    Q_OBJECT
public:
    /**
     * @brief Construct a new FITKComboBox object
     * @param[i]  parent         父对象
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-06-20
     */
    explicit FITKComboBox(QWidget* parent = nullptr);
    /**
     * @brief Destroy the FITKComboBox object
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-06-20
     */
    virtual ~FITKComboBox();
signals:
    ;
    /**
     * @brief    点击信号
     * @param[i]  
     * @author   BaGuijun (baguijun@163.com)
     * @date     2024-11-27
     */
    void clicked(bool);
protected:
    /**
     * @brief    鼠标点击事件重写
     * @param[i] event           事件
     * @author   BaGuijun (baguijun@163.com)
     * @date     2024-11-27
     */
    void mousePressEvent(QMouseEvent *event);
};



#endif
