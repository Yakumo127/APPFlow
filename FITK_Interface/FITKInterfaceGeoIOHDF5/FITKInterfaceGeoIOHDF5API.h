/*****************************************************************//**
 * @file    FITKInterfaceGeoIOHDF5API.h
 * @brief   HDF5 API.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-09-09
 *********************************************************************/

#ifndef _FITKINTERFACEGEOIOHDF5_API_H_
#define _FITKINTERFACEGEOIOHDF5_API_H_

#include <QtCore/QtGlobal>

#include <QDebug>

#if defined(FITKINTERFACEGEOIOHDF5_API)
#define FITKINTERFACEGEOIOHDF5API Q_DECL_EXPORT
#else
#define FITKINTERFACEGEOIOHDF5API Q_DECL_IMPORT
#endif

#endif
