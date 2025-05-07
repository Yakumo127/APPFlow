/*****************************************************************//**
 * @file    FITKFluidVTKGraphAdaptorAPI.h
 * @brief   For export macro.
 *  
 * @author  ChengHaotian (yeguangbaozi@foxmail.com)
 * @date    2024-07-15
 *********************************************************************/

#ifndef _FITKFluidVTKGRAPHADAPTOR_API_H_
#define _FITKFluidVTKGRAPHADAPTOR_API_H_

#include <QtCore/QtGlobal>

#include <QDebug>

#if defined(FITKFLUIDGRAPHADAPTOR_API)
#define FITKFLUIDGRAPHADAPTORAPI Q_DECL_EXPORT
#else
#define FITKFLUIDGRAPHADAPTORAPI Q_DECL_IMPORT
#endif

#endif
