/**
 * @file   FITKAbsGeoModelPartitionFace.h
 * @brief  面分块
 * @author YanZhiHui (chanyuantiandao@126.com)
 * @date   2025-04-23
 */
#ifndef  FITKABSGEOMODELPARTITIONFACE_H
#define  FITKABSGEOMODELPARTITIONFACE_H

#include "FITKInterfaceGeometryAPI.h"
#include "FITK_Interface/FITKInterfaceGeometry/FITKAbsGeoCommand.h"
#include <QVector>
#include <array>

namespace Interface
{
    /**
     * @brief  面分块.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2025-04-23
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelPartitionFace :
        public FITKAbsGeoCommand
    {
        FITKCLASS(Interface, FITKAbsGeoModelPartitionFace);
    public:
        FITKAbsGeoModelPartitionFace() = default;
        ~FITKAbsGeoModelPartitionFace() override = default;

        void setFaces(QList<Interface::VirtualShape> faces) { m_Faces = faces; }
        QList<Interface::VirtualShape> faces() const { return m_Faces; }

    protected:
        QList<Interface::VirtualShape> m_Faces{};
    };

    /**
     * @brief  使用草图进行面分块.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2025-04-23
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelPartitionFaceWithSketch :
        public FITKAbsGeoModelPartitionFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelPartitionFaceWithTwoPoints);
    public:
        FITKAbsGeoModelPartitionFaceWithSketch() = default;
        ~FITKAbsGeoModelPartitionFaceWithSketch() override = default;
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

        void setSketch(int id) { m_SketchId = id; }
        int sketch() const { return m_SketchId; }

    protected:
        int m_SketchId{};
    };

    /**
     * @brief  使用两点进行面分块.
     * @author YanZhiHui (chanyuantiandao@126.com)
     * @date   2025-04-23
     */
    class FITKInterfaceGeometryAPI FITKAbsGeoModelPartitionFaceWithTwoPoints :
        public FITKAbsGeoModelPartitionFace
    {
        FITKCLASS(Interface, FITKAbsGeoModelPartitionFaceWithTwoPoints);
    public:
        FITKAbsGeoModelPartitionFaceWithTwoPoints() = default;
        ~FITKAbsGeoModelPartitionFaceWithTwoPoints() override = default;
        FITKGeoEnum::FITKGeometryComType getGeometryCommandType() override;

        void setStartPoint(QVector<double> point) { m_StartPoint = point; }
        QVector<double> startPoint() const { return m_StartPoint; }
        void setEndPoint(QVector<double> point) { m_EndPoint = point; }
        QVector<double> endPoint() const { return m_EndPoint; }

    protected:
        QVector<double> m_StartPoint{};
        QVector<double> m_EndPoint{};
    };
}

#endif // !FITKABSGEOMODELPARTITIONFACE_H
