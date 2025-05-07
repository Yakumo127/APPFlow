/**
 * @file   FITKOFDictWriterAPI.h
 * @brief 声明写出接口
 * @author liuzhonghua (liuzhonghuaszch@163.com)
 * @date 2024-07-16
 */
#ifndef _FITKOFDICTWRITER_API_H_
#define _FITKOFDICTWRITER_API_H_

#include <QtCore/QtGlobal>


#if defined(FITKOFDictWriter_API)
#define FITKOFDictWriterAPI Q_DECL_EXPORT
#else
#define FITKOFDictWriterAPI Q_DECL_IMPORT
#endif

#endif
