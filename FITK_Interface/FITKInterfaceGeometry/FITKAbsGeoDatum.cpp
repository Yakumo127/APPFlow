#include "FITKAbsGeoDatum.h" 

#include "FITKGeoInterfaceFactory.h" 

namespace Interface
{
    // 基准元素抽象类。
    //@{
    void FITKAbsGeoDatum::setEditable(bool flag)
    {
        m_createdType = flag ? DatumCreatedType::DCT_UserDefine : DatumCreatedType::DCT_System;
    }

    void FITKAbsGeoDatum::setPosition(double* pos)
    {
        // 保存位置。
        if (pos)
        {
            m_pos[0] = pos[0];
            m_pos[1] = pos[1];
            m_pos[2] = pos[2];
        }
    }

    void FITKAbsGeoDatum::getPosition(double* pos)
    {
        if (pos)
        {
            pos[0] = m_pos[0];
            pos[1] = m_pos[1];
            pos[2] = m_pos[2];
        }
    }

    FITKGeoEnum::FITKGeometryComType FITKAbsGeoDatum::getGeometryCommandType()
    {
        return FITKGeoEnum::FITKGeometryComType::FGTDatum;
    }

    bool FITKAbsGeoDatum::editable()
    {
        return m_createdType == DCT_UserDefine;
    }
    //@}

    // 基准点。
    //@{
    FITKGeoEnum::FITKDatumType FITKAbsGeoDatumPoint::getDatumType()
    {
        return FITKGeoEnum::FITKDatumType::FDTPoint;
    }
    //@}

    // 基准线。
    //@{
    FITKGeoEnum::FITKDatumType FITKAbsGeoDatumLine::getDatumType()
    {
        return FITKGeoEnum::FITKDatumType::FDTLine;
    }

    void FITKAbsGeoDatumLine::setFiniteLine(double* pos1, double* pos2)
    {
        // 保存线。
        for (int i = 0; i < 3; i++)
        {
            m_pos[i] = pos1[i];
            m_pos2[i] = pos2[i];
        }
    }

    void FITKAbsGeoDatumLine::getFiniteLine(double* pos1, double* pos2)
    {
        // 获取线。
        for (int i = 0; i < 3; i++)
        {
            pos1[i] = m_pos[i];
            pos2[i] = m_pos2[i];
        }
    }

    void FITKAbsGeoDatumLine::setInfiniteLine(double* pos, double* dir)
    {
        // 保存线。
        for (int i = 0; i < 3; i++)
        {
            m_pos[i] = pos[i];
            m_dir[i] = dir[i];
        }
    }

    void FITKAbsGeoDatumLine::getInfiniteLine(double* pos, double* dir)
    {
        // 获取线。
        for (int i = 0; i < 3; i++)
        {
            pos[i] = m_pos[i];
            dir[i] = m_dir[i];
        }
    }

    void FITKAbsGeoDatumLine::setPosition2(double* pos)
    {
        // 保存位置。
        if (pos)
        {
            m_pos2[0] = pos[0];
            m_pos2[1] = pos[1];
            m_pos2[2] = pos[2];
        }
    }

    void FITKAbsGeoDatumLine::getPosition2(double* pos)
    {
        if (pos)
        {
            pos[0] = m_pos2[0];
            pos[1] = m_pos2[1];
            pos[2] = m_pos2[2];
        }
    }

    void FITKAbsGeoDatumLine::setDirection(double* dir)
    {
        // 保存方向。
        if (dir)
        {
            m_dir[0] = dir[0];
            m_dir[1] = dir[1];
            m_dir[2] = dir[2];
        }
    }

    void FITKAbsGeoDatumLine::getDirection(double* dir)
    {
        if (dir)
        {
            dir[0] = m_dir[0];
            dir[1] = m_dir[1];
            dir[2] = m_dir[2];
        }
    }

    void FITKAbsGeoDatumLine::setIsInfinite(bool flag)
    {
        m_isInfinite = flag;
    }

    bool FITKAbsGeoDatumLine::getIsInfinite()
    {
        return m_isInfinite;
    }
    //@}

    FITKAbsGeoDatumPlane::~FITKAbsGeoDatumPlane()
    {
    }

    // 基准面。
    //@{
    FITKGeoEnum::FITKDatumType FITKAbsGeoDatumPlane::getDatumType()
    {
        return FITKGeoEnum::FITKDatumType::FDTPlane;
    }

    void FITKAbsGeoDatumPlane::setPlane(double* pos, double* normal, double* up)
    {
        // 设置全部信息。
        if (!pos || !normal || !up)
        {
            return;
        }

        for (int i = 0; i < 3; i++)
        {
            m_pos[i] = pos[i];
            m_nor[i] = normal[i];
            m_up[i] = up[i];
        }
    }

    void FITKAbsGeoDatumPlane::getPlane(double* pos, double* normal, double* up)
    {
        // 获取全部信息。
        if (!pos || !normal || !up)
        {
            return;
        }

        for (int i = 0; i < 3; i++)
        {
            pos[i] = m_pos[i];
            normal[i] = m_nor[i];
            up[i] = m_up[i];
        }
    }

    void FITKAbsGeoDatumPlane::setNormal(double* nor)
    {
        // 保存方向。
        if (nor)
        {
            m_nor[0] = nor[0];
            m_nor[1] = nor[1];
            m_nor[2] = nor[2];
        }
    }

    void FITKAbsGeoDatumPlane::getNormal(double* nor)
    {
        if (nor)
        {
            nor[0] = m_nor[0];
            nor[1] = m_nor[1];
            nor[2] = m_nor[2];
        }
    }

    void FITKAbsGeoDatumPlane::setUp(double* up)
    {
        // 保存方向。
        if (up)
        {
            m_up[0] = up[0];
            m_up[1] = up[1];
            m_up[2] = up[2];
        }
    }

    void FITKAbsGeoDatumPlane::getUp(double* up)
    {
        if (up)
        {
            up[0] = m_up[0];
            up[1] = m_up[1];
            up[2] = m_up[2];
        }
    }
    //@}

    // 基准元素管理器。
    //@{
    FITKDatumList::FITKDatumList()
    {
        double pos3[3]{ 0., 0., 0. };
        double xDir3[3]{ 1., 0., 0. };
        double yDir3[3]{ 0., 1., 0. };
        double zDir3[3]{ 0., 0., 1. };

        // XOY.
        m_planeXOY = new FITKAbsGeoDatumPlane;
        m_planeXOY->setDataObjectName("Plane XOY");
        m_planeXOY->setEditable(false);
        m_planeXOY->setPlane(pos3, zDir3, yDir3);
        m_planeXOY->update();

        // YOZ.
        m_planeYOZ = new FITKAbsGeoDatumPlane;
        m_planeYOZ->setDataObjectName("Plane YOZ");
        m_planeYOZ->setEditable(false);
        m_planeYOZ->setPlane(pos3, xDir3, zDir3);
        m_planeYOZ->update();

        // ZOX.
        m_planeZOX = new FITKAbsGeoDatumPlane;
        m_planeZOX->setDataObjectName("Plane ZOX");
        m_planeZOX->setEditable(false);
        m_planeZOX->setPlane(pos3, yDir3, xDir3);
        m_planeZOX->update();

        // X.
        m_axisX = new FITKAbsGeoDatumLine;
        m_axisX->setDataObjectName("Axis X");
        m_axisX->setEditable(false);
        m_axisX->setPosition(pos3);
        m_axisX->setDirection(xDir3);
        m_axisX->update();

        // Y.
        m_axisY = new FITKAbsGeoDatumLine;
        m_axisY->setDataObjectName("Axis Y");
        m_axisY->setEditable(false);
        m_axisY->setPosition(pos3);
        m_axisY->setDirection(yDir3);
        m_axisY->update();

        // Z.
        m_axisZ = new FITKAbsGeoDatumLine;
        m_axisZ->setDataObjectName("Axis Z");
        m_axisZ->setEditable(false);
        m_axisZ->setPosition(pos3);
        m_axisZ->setDirection(zDir3);
        m_axisZ->update();
    }

    FITKDatumList::~FITKDatumList()
    {
        // 删除系统默认基准面。
        if (m_planeXOY)
        {
            delete m_planeXOY;
            m_planeXOY = nullptr;
        }

        if (m_planeYOZ)
        {
            delete m_planeYOZ;
            m_planeYOZ = nullptr;
        }

        if (m_planeZOX)
        {
            delete m_planeZOX;
            m_planeZOX = nullptr;
        }

        // 删除系统默认基准轴。
        if (m_axisX)
        {
            delete m_axisX;
            m_axisX = nullptr;
        }

        if (m_axisY)
        {
            delete m_axisY;
            m_axisY = nullptr;
        }

        if (m_axisZ)
        {
            delete m_axisZ;
            m_axisZ = nullptr;
        }
    }

    Interface::FITKAbsGeoDatum* FITKDatumList::getDataByID(const int id)
    {
        // 查询系统默认基准面。
        if (m_planeXOY && m_planeXOY->getDataObjectID() == id)
        {
            return m_planeXOY;
        }

        if (m_planeYOZ && m_planeYOZ->getDataObjectID() == id)
        {
            return m_planeYOZ;
        }

        if (m_planeZOX && m_planeZOX->getDataObjectID() == id)
        {
            return m_planeZOX;
        }

        // 查询系统默认基准轴。
        if (m_axisX && m_axisX->getDataObjectID() == id)
        {
            return m_axisX;
        }

        if (m_axisY && m_axisY->getDataObjectID() == id)
        {
            return m_axisY;
        }

        if (m_axisZ && m_axisZ->getDataObjectID() == id)
        {
            return m_axisZ;
        }

        // 从管理器获取。
        return Core::FITKAbstractDataManager<Interface::FITKAbsGeoDatum>::getDataByID(id);
    }

    FITKAbsGeoDatumPlane* FITKDatumList::getPrincipalPlane(PrincipalPlnType type)
    {
        switch (type)
        {
        case Interface::FITKDatumList::PPT_XOY:
            return m_planeXOY;
        case Interface::FITKDatumList::PPT_YOZ:
            return m_planeYOZ;
        case Interface::FITKDatumList::PPT_ZOX:
            return m_planeZOX;
        default:
            return nullptr;
        }

        return nullptr;
    }

    FITKAbsGeoDatumLine* FITKDatumList::getPrincipalAxis(PrincipalAxisType type)
    {
        switch (type)
        {
        case Interface::FITKDatumList::PAT_X:
            return m_axisX;
        case Interface::FITKDatumList::PAT_Y:
            return m_axisY;
        case Interface::FITKDatumList::PAT_Z:
            return m_axisZ;
        default:
            return nullptr;
        }

        return nullptr;
    }
    //@}
}