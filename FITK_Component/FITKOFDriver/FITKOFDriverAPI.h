/**
 *
 * @file    FITKOFDriverAPI.h
 * @brief   声明openFOAM网格划分驱动
 * @author  fulipeng (fulipengqd@yeah.net)
 * @date    2024-06-20
 *
 */
#ifndef FITKOFDRIVER_API_H
#define FITKOFDRIVER_API_H

#include <QtCore/QtGlobal>

#if defined(FITKOFDRIVER_API)
    #define FITKOFDRIVERAPI Q_DECL_EXPORT
#else
    #define FITKOFDRIVERAPI Q_DECL_IMPORT
#endif

#endif
