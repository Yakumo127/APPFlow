#ifndef FITKOFMESHIOAPI_H
#define FITKOFMESHIOAPI_H


#include <QtCore/QtGlobal>


#ifdef FITKOFMeshIO_API
#define FITKOFMeshIOAPI Q_DECL_EXPORT
#else
#define FITKOFMeshIOAPI Q_DECL_IMPORT
#endif

#endif // FITKOFMESHIOAPI_H
