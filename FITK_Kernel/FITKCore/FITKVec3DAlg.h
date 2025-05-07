﻿
/**
 *
 * @file FITKVec3DAlg.h
 * @brief 矢量计算方法
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-04-19
 *
 */
#ifndef __FITKVEC3D_ALG_H__
#define __FITKVEC3D_ALG_H__

#include "FITKVec3D.h"

#define FITK_PI 3.14159265358979323846

namespace Core
{
    /**
    * @brief 计算矢量加法 a*aFac + b*bFac
    * @param[i]  a              第一个矢量
    * @param[i]  b              第二个矢量
    * @param[i]  aFac              第一个矢量因子
    * @param[i]  bFac              第二个矢量因子
    * @return FITKPoint
    * @author LiBaojun (libaojunqd@foxmail.com)
    * @date 2024-04-19
    */
    FITKPoint FITKCoreAPI Add(const FITKPoint& a, const FITKPoint& b, 
                              const double aFac = 1.0, const double bFac = 1.0);
    /**
    * @brief 计算矢量减法 a*aFac - b*bFac
    * @param[i]  a              第一个矢量
    * @param[i]  b              第二个矢量
    * @param[i]  aFac              第一个矢量因子
    * @param[i]  bFac              第二个矢量因子
    * @return FITKPoint
    * @author LiBaojun (libaojunqd@foxmail.com)
    * @date 2024-04-19
    */
    FITKPoint FITKCoreAPI Subtract(const FITKPoint& a, const FITKPoint& b, 
                                   const double aFac = 1.0, const double bFac = 1.0);

    /**
     * @brief 计算矢量叉乘
     * @param[i]  a              第一个矢量
     * @param[i]  b              第二个矢量
     * @return FITKPoint
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-19
     */
    FITKPoint FITKCoreAPI CrossProduct(const FITKPoint& a, const FITKPoint& b);

    /**
     * @brief 计算矢量点乘
     * @param[i]  a              第一个矢量
     * @param[i]  b              第二个矢量
     * @return FITKPoint
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-19
     */
    double FITKCoreAPI DotProduct(const FITKPoint & a, const FITKPoint & b);

    /**
     * @brief 点P绕轴Axis旋转，轴线过原点
     * @param[i]  P              输入点
     * @param[i]  Axis           轴线，轴线的起始点在原点
     * @param[i]  Angle          角度 弧度制
     * @return FITKPoint
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-19
     */
    FITKPoint FITKCoreAPI RotateAroundAxis(const FITKPoint& P,  FITKVec3D& Axis, double Angle);

    /**
     * @brief 点P绕轴任意Axis旋转
     * @param[i]  P              输入点
     * @param[i]  Basic          轴线基准点
     * @param[i]  Axis           轴线方向
     * @param[i]  Angle          角度
     * @return FITKPoint
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-04-19
     */
    FITKPoint FITKCoreAPI RotateAroundAnyAxis(const FITKPoint& P, const FITKPoint& BasicPt, FITKVec3D& Axis, double Angle);


    /**
    * @brief 计算两个点的距离
    * @param[i]  a              第一个点
    * @param[i]  b              第二个点
    * @return double
    * @author LiBaojun (libaojunqd@foxmail.com)
    * @date 2024-04-19
    */
    double FITKCoreAPI Distance(const FITKPoint& a, const FITKPoint& b);

    /**
    * @brief 计算两个矢量夹角
    * @param[i]  v1              第一矢量
    * @param[i]  v2              第二矢量
    * @return double 角度，弧度制表示
    * @author LiBaojun (libaojunqd@foxmail.com)
    * @date 2024-04-19
    */
    double FITKCoreAPI AngleBetweenVec(const FITKVec3D& v1, const FITKVec3D& v2);

}


#endif