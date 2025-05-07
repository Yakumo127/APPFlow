#ifndef FITKParamLabel_H
#define FITKParamLabel_H

#include "FITKEasyParamAPI.h"
#include "FITKAbstractEasyParam.h"

namespace Core
{
    class FITKEasyParamAPI FITKParamLabel : public FITKAbstractEasyParam
    {
        Q_OBJECT;
    public:
        FITKParamLabel();
        virtual ~FITKParamLabel();

        virtual FITKAbstractEasyParam::FITKEasyParamType getParamType() override;
        virtual void copyParaData(FITKAbstractEasyParam* data) override;

        void setValue(QStringList value);
        void appendValue(QString value);
        bool isExist(QString v);
        QStringList getValue();

    private:
        QStringList _value{};
    };
}

#endif
