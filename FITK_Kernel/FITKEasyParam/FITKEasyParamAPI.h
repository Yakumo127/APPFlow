 
#ifndef _FITKEASTPARAM_API_H_
#define _FITKEASTPARAM_API_H_

#include <QtCore/QtGlobal>


#if defined(FITKEasyParam_API)
#define FITKEasyParamAPI Q_DECL_EXPORT
#else
#define FITKEasyParamAPI Q_DECL_IMPORT
#endif

#endif
