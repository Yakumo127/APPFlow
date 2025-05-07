/*****************************************************************//**
 * @file    FITKGeoOCCIOHDF5API.h
 * @brief   For export macro.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-09-09
 *********************************************************************/

#ifndef _FITKGEOOCCIOHDF5_API_H_
#define _FITKGEOOCCIOHDF5_API_H_

#include <QtCore/QtGlobal>

#include <QDebug>

#if defined(FITKGEOOCCIOHDF5_API)
#define FITKGEOOCCIOHDF5API Q_DECL_EXPORT
#else
#define FITKGEOOCCIOHDF5API Q_DECL_IMPORT
#endif

#endif
