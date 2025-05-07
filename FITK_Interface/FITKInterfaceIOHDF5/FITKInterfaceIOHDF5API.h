/**
 *
 * @file FITKInterfaceIOHDF5API.h
 * @brief  声明接口
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-03-08
 *
 */
#ifndef _FITKINTERFACEIO_HDF5_API_H_
#define _FITKINTERFACEIO_HDF5_API_H_

#include <QtCore/QtGlobal>


#if defined(FITKInterfaceIOHDF5_API)
#define FITKINTERFACEHDF5IOAPI Q_DECL_EXPORT
#else
#define FITKINTERFACEHDF5IOAPI Q_DECL_IMPORT
#endif

#endif
