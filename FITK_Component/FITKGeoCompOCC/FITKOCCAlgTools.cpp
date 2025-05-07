#include "FITKOCCAlgTools.h"

// OCC
#include <gp_Trsf.hxx>
#include <gp_Ax1.hxx>
#include <gp_Quaternion.hxx>
#include <NCollection_Mat4.hxx>

#include <QDebug>

// Data
#include "FITK_Kernel/FITKCore/FITKVec3DAlg.h"

namespace OCC
{
    Interface::FITKAbstractTransformTool* FITKOCCAlgToolCreator::createTransformTool()
    {
        // Create the transform tool.
        return new FITKOCCTransformTool;
    }

    // Transformation.
    //@{
    FITKOCCTransformTool::FITKOCCTransformTool()
    {
        // Create the transform.
        m_Transformation = new gp_Trsf;
    }

    FITKOCCTransformTool::~FITKOCCTransformTool()
    {
        if (m_Transformation)
        {
            delete m_Transformation;
            m_Transformation = nullptr;
        }
    }

    double FITKOCCTransformTool::degToRad(double degree)
    {
        return degree * FITK_PI / 180.;
    }

    double FITKOCCTransformTool::radToDeg(double rad)
    {
        return rad * 180. / FITK_PI;
    }

    void FITKOCCTransformTool::setTransform(double* iTrans, double* iAxisPt1, double* iAxisPt2, double iAngleDeg)
    {
        transform(iTrans[0], iTrans[1], iTrans[2]);
        rotate(iAxisPt1, iAxisPt2, iAngleDeg);
    }

    void FITKOCCTransformTool::transform(double iX, double iY, double iZ)
    {
        // Perform a translate.
        gp_Trsf newTrans;

        try
        {
            newTrans.SetTranslation(gp_Pnt(0., 0., 0.), gp_Pnt(iX, iY, iZ));
        }
        catch (...)
        {
            return;
        }
        
        *m_Transformation = newTrans * *m_Transformation;
    }

    void FITKOCCTransformTool::rotate(double* iPt1, double* iPt2, double iAngleDeg)
    {
        // Perform a rotate.
        gp_Trsf newTrans;

        try
        {
            gp_Pnt pt1(iPt1[0], iPt1[1], iPt1[2]);
            gp_Pnt pt2(iPt2[0], iPt2[1], iPt2[2]);
            gp_Vec dir(pt1, pt2);
            dir.Normalize();

            gp_Ax1 axis(pt1, dir);
            newTrans.SetRotation(axis, degToRad(iAngleDeg));
        }
        catch (...)
        {
            return;
        }

        *m_Transformation = newTrans * *m_Transformation;
    }

    bool FITKOCCTransformTool::isRotation(double* oPt1, double* oPt2, double & oAngleDeg)
    {
        // Right hand.
        gp_Quaternion rotation = m_Transformation->GetRotation();

        oPt1[0] = 0.;
        oPt1[1] = 0.;
        oPt1[2] = 0.;

        if (qFuzzyCompare(rotation.X(), 0.) && qFuzzyCompare(rotation.Y(), 0.) && qFuzzyCompare(rotation.Z(), 0.))
        {
            oPt2[0] = 0.;
            oPt2[1] = 0.;
            oPt2[2] = 1.;
            oAngleDeg = 0.;
        }
        else
        {
            gp_Vec dir(rotation.X(), rotation.Y(), rotation.Z());
            dir.Normalize();
            oPt2[0] = dir.X();
            oPt2[1] = dir.Y();
            oPt2[2] = dir.Z();
            oAngleDeg = radToDeg(2.0 * std::acos(rotation.W()));
        }

        return true;
    }

    void FITKOCCTransformTool::transformPoint(double* iPt, double* oPt)
    {
        gp_Pnt pnt(iPt[0], iPt[1], iPt[2]);
        pnt.Transform(*m_Transformation);
        oPt[0] = pnt.X();
        oPt[1] = pnt.Y();
        oPt[2] = pnt.Z();
    }

    void FITKOCCTransformTool::transformDirection(double* iDir, double* oDir)
    {
        gp_Vec dir(iDir[0], iDir[1], iDir[2]);
        dir.Normalize();
        dir.Transform(*m_Transformation);
        oDir[0] = dir.X();
        oDir[1] = dir.Y();
        oDir[2] = dir.Z();
    }

    void FITKOCCTransformTool::data(double oMat[3][3], double* oVec)
    {
        NCollection_Mat4<Standard_Real> mat4;
        m_Transformation->GetMat4(mat4);
        for (int row = 0; row < 3; row++)
        {
            for (int col = 0; col < 3; col++)
            {
                oMat[row][col] = mat4.GetValue(row, col);
            }
        }

        oVec[0] = mat4.GetValue(0, 3);
        oVec[1] = mat4.GetValue(1, 3);
        oVec[2] = mat4.GetValue(2, 3);
    }

    void FITKOCCTransformTool::setData(double iMat[3][3], double* iVec) 
    {
        m_Transformation->SetValues(
            iMat[0][0], iMat[0][1], iMat[0][2], iVec[0], 
            iMat[1][0], iMat[1][1], iMat[1][2], iVec[1], 
            iMat[2][0], iMat[2][1], iMat[2][2], iVec[2] );
    }
    //@}
}
