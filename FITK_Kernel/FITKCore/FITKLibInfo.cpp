/**
 *
 * @file FITKLibInfo.cpp
 * @brief FITK库信息类实现
 * @author libaojun (libaojunqd@foxmail.com)
 * @date 2025-04-09
 *
 */
#include "FITKLibInfo.h"
#include <QStringList>
#include <QDebug>

namespace Core
{
    //静态变量初始化
    FITKLibInfo* FITKLibInfo::_instance = nullptr;
    QMutex FITKLibInfo::m_mutex;

    void FITKLibInfo::registerLibrary(const QString& name, const QString& version, const QString& buildDate)
    {
        m_libraries.insert(name, LibraryInfo(name, version, buildDate));
    }

    LibraryInfo FITKLibInfo::getLibraryInfo(const QString& name) const
    {
        return m_libraries.value(name, LibraryInfo());
    }

    QStringList FITKLibInfo::getRegisteredLibraries() const
    {
        return m_libraries.keys();
    }

    QString FITKLibInfo::getVersion(const QString& name) const
    { 
        return m_libraries.value(name).version;
    }

    QString FITKLibInfo::getBuildDate(const QString& name) const
    { 
        return m_libraries.value(name).buildDate;
    }    void FITKLibInfo::printAllLibraryInfo() const
    { 
        qDebug() << "========== Library Information ==========";
        QStringList sortedKeys = m_libraries.keys();
        sortedKeys.sort();
        for (const QString& key : sortedKeys) 
        {
            const LibraryInfo& lib = m_libraries.value(key);
            qDebug() << "Library Name:" << lib.name;
            qDebug() << "Version     :" << lib.version;
            qDebug() << "Build Time  :" << lib.buildDate;
            qDebug() << "----------------------------------------";
        }
        qDebug() << "======================================";
    }    QStringList FITKLibInfo::toStringList() const
    { 
        QStringList result;
        QStringList sortedKeys = m_libraries.keys();
        sortedKeys.sort();
        for (const QString& key : sortedKeys) 
        {
            const LibraryInfo& lib = m_libraries.value(key);
            QString libInfo = QString("Library: %1 | Version: %2 | Build Time: %3")
                .arg(lib.name)
                .arg(lib.version)
                .arg(lib.buildDate);
            result.append(libInfo);
        }
        return result;
    }

    void FITKLibInfo::initialize()
    {
        // 注册 FITKCore 库的基本信息
        registerLibrary("FITKCore", "1.0.0", QString("%1 %2").arg(__DATE__).arg(__TIME__)); 
    }

    void FITKLibInfo::finalize()
    {
        m_libraries.clear();
    }

    FITKLibInfoDeleator::~FITKLibInfoDeleator()
    {
        if (FITKLibInfo::_instance)
            delete FITKLibInfo::_instance;
        FITKLibInfo::_instance = nullptr;
    }

    static FITKLibInfoDeleator __LIBINFO_DELEATOR__;
}
