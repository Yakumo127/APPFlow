/**********************************************************************
 * @file   FITKParamString.h
 * @brief  字符串参数类型
 * @author BaGuijun (baguijun@163.com)
 * @date   2024-09-09
 *********************************************************************/
#ifndef FITKParamString_H
#define FITKParamString_H

#include "FITKEasyParamAPI.h"
#include "FITKAbstractEasyParam.h"

namespace Core
{
    /**
     * @brief  字符串参数类型
     * @author BaGuijun (baguijun@163.com)
     * @date   2024-09-09
     */
    class FITKEasyParamAPI FITKParamString : public FITKAbstractEasyParam
    {
        Q_OBJECT;
    public:
        /**
         * @brief    构造函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        FITKParamString();
        /**
         * @brief    析构函数
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        virtual ~FITKParamString();
        /**
         * @brief    获取数据类型
         * @return   FITKAbstractEasyParam::FITKEasyParamType  数据类型
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        virtual FITKAbstractEasyParam::FITKEasyParamType getParamType() override;
        /**
         * @brief    拷贝数据
         * @param[i] data    被拷贝数据
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        virtual void copyParaData(FITKAbstractEasyParam* data) override;
        /**
         * @brief    设置数据
         * @param[i] value   数据
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        void setValue(QString value);
        /**
         * @brief    获取数据
         * @return   QString   数据
         * @author   BaGuijun (baguijun@163.com)
         * @date     2024-09-09
         */
        QString getValue();
    private:
        /**
         * @brief  数据
         * @author BaGuijun (baguijun@163.com)
         * @date   2024-09-09
         */
        QString _value = "";
    };
}

#endif
