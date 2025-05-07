/**
 *
 * @file FITKMeshGenOFAPI.h
 * @brief 接口声明
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-07-17
 *
 */
#ifndef _FITK_MESH_GEN_OF_API_H_
#define _FITK_MESH_GEN_OF_API_H_

#include <QtCore/QtGlobal>


#if defined(FITKMeshGenOF_API)
#define FITKMeshGenOFAPI Q_DECL_EXPORT
#else
#define FITKMeshGenOFAPI Q_DECL_IMPORT
#endif

#endif
