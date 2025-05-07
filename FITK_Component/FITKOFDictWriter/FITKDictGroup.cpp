﻿#include "FITKDictGroup.h"
#include "FITKDictValue.h"
#include <QTextStream>
//命名空间
namespace DICT
{
    FITKDictGroup::~FITKDictGroup()
    {
        for (FITKDictValue* value : m_values)
            if (value)delete value;
    }

    FITKDictGroup::FITKDictGroup(const FITKDictGroup &other)
    {
        for (QList<FITKDictValue*>::const_iterator iter = other.m_values.begin(); iter != other.m_values.end(); ++iter)
        {
            if (!*iter)continue;
            FITKDictValue* value = *iter;
            this->m_values.append(new FITKDictValue(*value));
        }
    }

    FITKDictGroup &FITKDictGroup::operator=(const FITKDictGroup &other)
    {
        for (QList<FITKDictValue*>::const_iterator iter = other.m_values.begin(); iter != other.m_values.end(); ++iter)
        {
            if (!*iter)continue;
            FITKDictValue* value = *iter;
            this->m_values.append(new FITKDictValue(*value));
        }
        return *this;
    }

    FITKAbstractDict::DictType FITKDictGroup::getDictType()
    {
        return FITKAbstractDict::DictType::DictGroup;
    }

    int FITKDictGroup::count() const
    {
        return m_values.size();
    }

    FITKDictValue* FITKDictGroup::value(const QString key)
    {
        for (FITKDictValue* value : m_values)
        {
            if (!value)continue;
            if (value->getKey() == key)
                return value;
        }
        return nullptr;
    }

    FITKDictValue* FITKDictGroup::at(const int index)
    {
        if (index < 0 || m_values.size() <= index)return nullptr;
        return m_values[index];
    }

    void FITKDictGroup::append(QString key, FITKAbstractDict::DictType value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }

    void FITKDictGroup::append(QString key, bool value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }
    void FITKDictGroup::append(QString key, double value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }
    void FITKDictGroup::append(QString key, int value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }
    void FITKDictGroup::append(QString key, const QString &value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }
    void FITKDictGroup::append(QString key, const char *value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }
    void FITKDictGroup::append(QString key, const QStringList &value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }
    void FITKDictGroup::append(QString key, FITKAbstractDict* value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.append(dataValue);
    }

    void FITKDictGroup::insert(int index, QString key, FITKAbstractDict::DictType value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, bool value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, double value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, int value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, const QString &value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, const char *value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, const QStringList& value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }
    void FITKDictGroup::insert(int index, QString key, FITKAbstractDict* value)
    {
        FITKDictValue* dataValue = new FITKDictValue(value);
        dataValue->setKey(key);
        m_values.insert(index, dataValue);
    }

    void FITKDictGroup::removeAt(int index)
    {
        if (index < 0 || m_values.size() <= index)return;
        FITKDictValue* delValue = this->at(index);
        m_values.removeAt(index);
        if (delValue)delete delValue;
    }
    
    void FITKDictGroup::removeKey(QString key)
    {
        int num = m_values.size();
        for (int i = num - 1; i >= 0; --i)
        {
            FITKDictValue* value = m_values.at(i);
            if (!value)continue;
            if (value->getKey() == key)
            {
                if (value)delete value;
                m_values.removeAt(i);
            }
        }
    }

    void FITKDictGroup::writeDict(QTextStream* stream, QString lineStart)
    {
        if (!stream)return;
        QString line = lineStart + QString("\t");
        *stream << endl;
        *stream << QString("%1{").arg(lineStart) << endl;
        for (QList<FITKDictValue*>::iterator iter = m_values.begin(); iter != m_values.end(); ++iter)
        {
            if (!*iter)continue;
            (*iter)->writeDict(stream, line);
        }
        *stream << QString("%1}").arg(lineStart) << endl;
    }
}
