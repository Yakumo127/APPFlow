/**********************************************************************
 * @file   FITKAbstractEasyParam.h
 * @brief  参数数据基类
 * @author BaGuijun (baguijun@163.com)
 * @date   2024-09-09
 *********************************************************************/
#ifndef _FITKABSTRACT_EASY_PARAM_H___
#define _FITKABSTRACT_EASY_PARAM_H___

#include "FITK_Kernel/FITKCore/FITKAbstractNDataObject.h"
#include "FITKEasyParamAPI.h"

namespace Core
{
    /**
     * @brief  参数数据基类
     * @author BaGuijun (baguijun@163.com)
     * @date   2024-09-09
     */
    class FITKEasyParamAPI  FITKAbstractEasyParam :  public FITKAbstractNDataObject
    {
        Q_OBJECT
    public:
        /**
         * @brief  数据类型
         * @author BaGuijun (baguijun@163.com)
         * @date   2024-09-09
         */
        enum FITKEasyParamType
        {
            FEPNone,
            FEPBool,
            FEPBoolGroup,
            FEPCombox,
            FEPComboxVector,
            FEPDouble,
            FEPDoubleList,
            FEPInt,
            FEPLabel,
            FEPRadioGroup,
            FEPString,
        };
        Q_ENUM(FITKEasyParamType);

    public:
        /**
         * @brief    构造函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        explicit FITKAbstractEasyParam() = default;
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        virtual ~FITKAbstractEasyParam();
        /**
         * @brief    获取数据类型
         * @return   FITKEasyParamType   数据类型
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        virtual FITKEasyParamType getParamType() = 0;
        /**
         * @brief    拷贝数据
         * @param[i] data       被拷贝数据
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        virtual void copyParaData(FITKAbstractEasyParam* data);
        /**
         * @brief    获取数据
         * @param[i] title       标签
         * @return   QVariant    数据
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-12
         */
        QVariant getData(QString title = "default");
        /**
         * @brief    设置数据(指针数据需自己管理)
         * @param[i] data        数据
         * @param[i] title       标签
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-12
         */
        void setData(QVariant data, QString title = "default");
        /**
         * @brief    获取所有数据标签
         * @return   QList<QString>     标签
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-10-12
         */
        QList<QString> getDataTitle();
    signals:
        ;
        /**
         * @brief    数据更改信号
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        void sigDataChange();
    protected:
        /**
         * @brief  数据
         * @author BaGuijun (baguijun@163.com)
         * @date   2024-10-12
         */
        QHash<QString, QVariant> _data = { };
    };
}

#endif
