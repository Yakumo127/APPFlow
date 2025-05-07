﻿#include "FITKFluidVTKViewAdaptorRegionMesh.h"

// Graph and data
#include "FITKFluidVTKGraphObjectRegionMesh.h"
#include "FITK_Interface/FITKInterfaceMeshGen/FITKRegionMeshSize.h"

namespace Exchange
{
    bool FITKFluidVTKViewAdaptorRegionMesh::update()
    {
        if (!_dataObj)
        {
            return false;
        }

        // If do not need to update and the output is not empty,
        // it means the output has been created, so return true.
        if (!m_needUpdate)
        {
            return (m_outputData != nullptr);
        }

        // Down cast the input data.
        Interface::FITKAbstractRegionMeshSize* data = dynamic_cast<Interface::FITKAbstractRegionMeshSize*>(_dataObj);
        if (!data)
        {
            return false;
        }

        // If output is exist, then delete it and create a new one.
        if (m_outputData)
        {
            delete m_outputData;
            m_outputData = nullptr;
        }

        // The output data object for view
        FITKFluidVTKGraphObjectRegionMesh* outputData = new FITKFluidVTKGraphObjectRegionMesh(data);

        m_needUpdate = false;

        // If the actor count is 0, then this graph object is invalid.
        if (outputData->getActorCount() == 0)
        {
            delete outputData;
            return false;
        }

        m_outputData = outputData;

        return true;
    }
}   // namespace Exchange
