﻿/**
 *
 * @file FITKVec3D.h
 * @brief 声明三维节点与向量
 * @author LiBaojun (libaojunqd@foxmail.com)
 * @date 2024-02-27
 *
 */
#ifndef _FITKVEC3D_H__
#define _FITKVEC3D_H__

#include "FITKAbstractObject.hpp"

namespace Core
{
    /**
     * @brief 三维点类
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-02-27
     */
    class FITKCoreAPI FITKPoint : public FITKAbstractObject
    {
    public:
        /**
         * @brief Construct a new FITKPoint object
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        FITKPoint();
        /**
         * @brief Construct a new FITKPoint object
         * @param[i]  x              x坐标
         * @param[i]  y              y坐标
         * @param[i]  z              z坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        FITKPoint(double x, double y, double z);
        /**
         * @brief Construct a new FITKPoint object
         * @param[i]  c              坐标值，3个值
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        FITKPoint(double* c);
        /**
         * @brief Construct a new FITKPoint object
         * @param[i]  point          拷贝对象
         * @author LiBaojun (libaojunqd@ifoxmail.com)
         * @date 2024-02-27
         */
        FITKPoint(const FITKPoint& point);
        /**
         * @brief 获取X坐标
         * @return double
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        double x() const;
        /**
         * @brief 获取y坐标
         * @return double
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        double y() const;
        /**
         * @brief 获取z坐标
         * @return double
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        double z() const;
        /**
         * @brief 获取坐标
         * @param[o]  c             输出坐标值，3个分量
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        void getCoor(double* c) const;

        /**
         * @brief 设置坐标
         * @param[i]  x              x坐标
         * @param[i]  y              y坐标
         * @param[i]  z              z坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-25
         */
         void setCoor(double x, double y, double z);
         /**
          * @brief 运算符重载
          * @author LiBaojun(libaojunqd@foxmail.com)
          * @date 2024 - 05 - 25
          */
         void operator = (const FITKPoint & p);         
         /**
          * @brief 运算符重载
          * @author LiBaojun(libaojunqd@foxmail.com)
          * @date 2024 - 05 - 25
          */
         double operator [] (const int & index);

    protected:
        /**
         * @brief 坐标值
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        double _coor[3] = { 0,0,0 };
    };

    /**
     * @brief 节点类，带ID
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-07
     */
    class FITKCoreAPI FITKNode : public FITKPoint
    {
    public:
        using FITKPoint::FITKPoint;
        FITKNode() = default;
        /**
         * @brief Construct a new FITKNode object
         * @param[i]  id             节点id
         * @param[i]  x              节点x坐标
         * @param[i]  y              节点y坐标
         * @param[i]  z              节点z坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        FITKNode(const int id, const double x, const double y, const double z);
        /**
         * @brief Construct a new FITKNode objecti
         * @param[i]  id            节点id
         * @param[i] coor           节点坐标
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        FITKNode(const int id, const double* coor);
        /**
         * @brief 设置节点ID
         * @param[i]  id          节点ID
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        void setNodeID(const int id);
        /**
         * @brief 获取节点ID
         * @return int
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-27
         */
        int getNodeID() const;

    private:
        /**
         * @brief 节点ID号
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-02-29
         */
        int _nodeID{ -1 };
    };
    /**
     * @brief 向量
     * @author LiBaojun (libaojunqd@foxmail.com)
     * @date 2024-03-07
     */
    class FITKCoreAPI FITKVec3D : public FITKPoint
    {
    public:
        using FITKPoint::FITKPoint;
        /**
         * @brief Construct a new FITKPoint object
         * @param[i]  point          拷贝对象
         * @author LiBaojun (libaojunqd@ifoxmail.com)
         * @date 2024-02-27
         */
        FITKVec3D(const FITKPoint& point);

        FITKVec3D(const FITKPoint& endPt, const FITKPoint& startPt);
        /**
         * @brief 获取向量的模
         * @return double
         * @author LiBaojun (libaojunqd@foxmail.com)
         * @date 2024-05-25
         */
        double getNorm() const;
        /**
       * @brief 向量归一化
       * @author LiBaojun (libaojunqd@foxmail.com)
       * @date 2024-05-25
       */
        void normalize();

    };
}



#endif
