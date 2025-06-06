win32{

INCLUDEPATH +=  ../Tools/Win64/VTK/include/vtk-9.0/  \


Debug:LIBS +=  -L../Tools/Win64/VTK/libd/  \                                  
               -lvtkChartsCore-9.0d  \
               -lvtkCommonColor-9.0d  \
               -lvtkCommonComputationalGeometry-9.0d  \
               -lvtkCommonCore-9.0d  \
               -lvtkCommonDataModel-9.0d  \
               -lvtkCommonExecutionModel-9.0d  \
               -lvtkCommonMath-9.0d  \
               -lvtkCommonMisc-9.0d  \
               -lvtkCommonSystem-9.0d  \
               -lvtkCommonTransforms-9.0d  \
               -lvtkDICOMParser-9.0d  \
               -lvtkDomainsChemistry-9.0d  \
               -lvtkFiltersAMR-9.0d  \
               -lvtkFiltersCore-9.0d  \
               -lvtkFiltersExtraction-9.0d  \
               -lvtkFiltersFlowPaths-9.0d  \
               -lvtkFiltersGeneral-9.0d  \
               -lvtkFiltersGeneric-9.0d  \
               -lvtkFiltersGeometry-9.0d  \
               -lvtkFiltersHybrid-9.0d  \
               -lvtkFiltersHyperTree-9.0d  \
               -lvtkFiltersImaging-9.0d  \
               -lvtkFiltersModeling-9.0d  \
               -lvtkFiltersParallel-9.0d  \
               -lvtkFiltersParallelImaging-9.0d  \
               -lvtkFiltersPoints-9.0d  \
               -lvtkFiltersProgrammable-9.0d  \
               -lvtkFiltersSMP-9.0d  \
               -lvtkFiltersSelection-9.0d  \
               -lvtkFiltersSources-9.0d  \
               -lvtkFiltersStatistics-9.0d  \
               -lvtkFiltersTexture-9.0d  \
               -lvtkFiltersTopology-9.0d  \
               -lvtkFiltersVerdict-9.0d  \
               -lvtkGUISupportQt-9.0d  \
               -lvtkGUISupportQtSQL-9.0d  \
               -lvtkGeovisCore-9.0d  \
               -lvtkIOAMR-9.0d  \
               -lvtkIOAsynchronous-9.0d  \
               -lvtkIOCityGML-9.0d  \
               -lvtkIOCore-9.0d  \
               -lvtkIOEnSight-9.0d  \
               -lvtkIOExodus-9.0d  \
               -lvtkIOExport-9.0d  \
               -lvtkIOExportGL2PS-9.0d  \
               -lvtkIOExportPDF-9.0d  \
               -lvtkIOGeometry-9.0d  \
               -lvtkIOImage-9.0d  \
               -lvtkIOImport-9.0d  \
               -lvtkIOInfovis-9.0d  \
               -lvtkIOLSDyna-9.0d  \
               -lvtkIOLegacy-9.0d  \
               -lvtkIOMINC-9.0d  \
               -lvtkIOMotionFX-9.0d  \
               -lvtkIOMovie-9.0d  \
               -lvtkIONetCDF-9.0d  \
               -lvtkIOOggTheora-9.0d  \
               -lvtkIOPLY-9.0d  \
               -lvtkIOParallel-9.0d  \
               -lvtkIOParallelXML-9.0d  \
               -lvtkIOSQL-9.0d  \
               -lvtkIOSegY-9.0d  \
               -lvtkIOTecplotTable-9.0d  \
               -lvtkIOVeraOut-9.0d  \
               -lvtkIOVideo-9.0d  \
               -lvtkIOXML-9.0d  \
               -lvtkIOXMLParser-9.0d  \
               -lvtkImagingColor-9.0d  \
               -lvtkImagingCore-9.0d  \
               -lvtkImagingFourier-9.0d  \
               -lvtkImagingGeneral-9.0d  \
               -lvtkImagingHybrid-9.0d  \
               -lvtkImagingMath-9.0d  \
               -lvtkImagingMorphological-9.0d  \
               -lvtkImagingSources-9.0d  \
               -lvtkImagingStatistics-9.0d  \
               -lvtkImagingStencil-9.0d  \
               -lvtkInfovisCore-9.0d  \
               -lvtkInfovisLayout-9.0d  \
               -lvtkInteractionImage-9.0d  \
               -lvtkInteractionStyle-9.0d  \
               -lvtkInteractionWidgets-9.0d  \
               -lvtkParallelCore-9.0d  \
               -lvtkParallelDIY-9.0d  \
               -lvtkRenderingAnnotation-9.0d  \
               -lvtkRenderingContext2D-9.0d  \
               -lvtkRenderingCore-9.0d  \
               -lvtkRenderingFreeType-9.0d  \
               -lvtkRenderingGL2PSOpenGL2-9.0d  \
               -lvtkRenderingImage-9.0d  \
               -lvtkRenderingLOD-9.0d  \
               -lvtkRenderingLabel-9.0d  \
               -lvtkRenderingOpenGL2-9.0d  \
               -lvtkRenderingQt-9.0d  \
               -lvtkRenderingSceneGraph-9.0d  \
               -lvtkRenderingUI-9.0d  \
               -lvtkRenderingVolume-9.0d  \
               -lvtkRenderingVolumeOpenGL2-9.0d  \
               -lvtkRenderingVtkJS-9.0d  \
               -lvtkTestingRendering-9.0d  \
               -lvtkViewsContext2D-9.0d  \
               -lvtkViewsCore-9.0d  \
               -lvtkViewsInfovis-9.0d  \
               -lvtkViewsQt-9.0d  \
               -lvtkWrappingTools-9.0d  \
               -lvtkdoubleconversion-9.0d  \
               -lvtkexodusII-9.0d  \
               -lvtkexpat-9.0d  \
               -lvtkfreetype-9.0d  \
               -lvtkgl2ps-9.0d  \
               -lvtkglew-9.0d  \
               -lvtkhdf5-9.0d  \
               -lvtkhdf5_hl-9.0d  \
               -lvtkjpeg-9.0d  \
               -lvtkjsoncpp-9.0d  \
               -lvtklibharu-9.0d  \
               -lvtklibproj-9.0d  \
               -lvtklibxml2-9.0d  \
               -lvtkloguru-9.0d  \
               -lvtklz4-9.0d  \
               -lvtklzma-9.0d  \
               -lvtkmetaio-9.0d  \
               -lvtknetcdf-9.0d  \
               -lvtkogg-9.0d  \
               -lvtkpng-9.0d  \
               -lvtkpugixml-9.0d  \
               -lvtksqlite-9.0d  \
               -lvtksys-9.0d  \
               -lvtktheora-9.0d  \
               -lvtktiff-9.0d  \
               -lvtkverdict-9.0d  \
               -lvtkzlib-9.0d  \

Release:LIBS +=  -L../Tools/Win64/VTK/lib/  \
                 -lvtkChartsCore-9.0  \
                 -lvtkCommonColor-9.0  \
                 -lvtkCommonComputationalGeometry-9.0  \
                 -lvtkCommonCore-9.0  \
                 -lvtkCommonDataModel-9.0  \
                 -lvtkCommonExecutionModel-9.0  \
                 -lvtkCommonMath-9.0  \
                 -lvtkCommonMisc-9.0  \
                 -lvtkCommonSystem-9.0  \
                 -lvtkCommonTransforms-9.0  \
                 -lvtkDICOMParser-9.0  \
                 -lvtkDomainsChemistry-9.0  \
                 -lvtkFiltersAMR-9.0  \
                 -lvtkFiltersCore-9.0  \
                 -lvtkFiltersExtraction-9.0  \
                 -lvtkFiltersFlowPaths-9.0  \
                 -lvtkFiltersGeneral-9.0  \
                 -lvtkFiltersGeneric-9.0  \
                 -lvtkFiltersGeometry-9.0  \
                 -lvtkFiltersHybrid-9.0  \
                 -lvtkFiltersHyperTree-9.0  \
                 -lvtkFiltersImaging-9.0  \
                 -lvtkFiltersModeling-9.0  \
                 -lvtkFiltersParallel-9.0  \
                 -lvtkFiltersParallelImaging-9.0  \
                 -lvtkFiltersPoints-9.0  \
                 -lvtkFiltersProgrammable-9.0  \
                 -lvtkFiltersSMP-9.0  \
                 -lvtkFiltersSelection-9.0  \
                 -lvtkFiltersSources-9.0  \
                 -lvtkFiltersStatistics-9.0  \
                 -lvtkFiltersTexture-9.0  \
                 -lvtkFiltersTopology-9.0  \
                 -lvtkFiltersVerdict-9.0  \
                 -lvtkGUISupportQt-9.0  \
                 -lvtkGUISupportQtSQL-9.0  \
                 -lvtkGeovisCore-9.0  \
                 -lvtkIOAMR-9.0  \
                 -lvtkIOAsynchronous-9.0  \
                 -lvtkIOCityGML-9.0  \
                 -lvtkIOCore-9.0  \
                 -lvtkIOEnSight-9.0  \
                 -lvtkIOExodus-9.0  \
                 -lvtkIOExport-9.0  \
                 -lvtkIOExportGL2PS-9.0  \
                 -lvtkIOExportPDF-9.0  \
                 -lvtkIOGeometry-9.0  \
                 -lvtkIOImage-9.0  \
                 -lvtkIOImport-9.0  \
                 -lvtkIOInfovis-9.0  \
                 -lvtkIOLSDyna-9.0  \
                 -lvtkIOLegacy-9.0  \
                 -lvtkIOMINC-9.0  \
                 -lvtkIOMotionFX-9.0  \
                 -lvtkIOMovie-9.0  \
                 -lvtkIONetCDF-9.0  \
                 -lvtkIOOggTheora-9.0  \
                 -lvtkIOPLY-9.0  \
                 -lvtkIOParallel-9.0  \
                 -lvtkIOParallelXML-9.0  \
                 -lvtkIOSQL-9.0  \
                 -lvtkIOSegY-9.0  \
                 -lvtkIOTecplotTable-9.0  \
                 -lvtkIOVeraOut-9.0  \
                 -lvtkIOVideo-9.0  \
                 -lvtkIOXML-9.0  \
                 -lvtkIOXMLParser-9.0  \
                 -lvtkImagingColor-9.0  \
                 -lvtkImagingCore-9.0  \
                 -lvtkImagingFourier-9.0  \
                 -lvtkImagingGeneral-9.0  \
                 -lvtkImagingHybrid-9.0  \
                 -lvtkImagingMath-9.0  \
                 -lvtkImagingMorphological-9.0  \
                 -lvtkImagingSources-9.0  \
                 -lvtkImagingStatistics-9.0  \
                 -lvtkImagingStencil-9.0  \
                 -lvtkInfovisCore-9.0  \
                 -lvtkInfovisLayout-9.0  \
                 -lvtkInteractionImage-9.0  \
                 -lvtkInteractionStyle-9.0  \
                 -lvtkInteractionWidgets-9.0  \
                 -lvtkParallelCore-9.0  \
                 -lvtkParallelDIY-9.0  \
                 -lvtkRenderingAnnotation-9.0  \
                 -lvtkRenderingContext2D-9.0  \
                 -lvtkRenderingCore-9.0  \
                 -lvtkRenderingFreeType-9.0  \
                 -lvtkRenderingGL2PSOpenGL2-9.0  \
                 -lvtkRenderingImage-9.0  \
                 -lvtkRenderingLOD-9.0  \
                 -lvtkRenderingLabel-9.0  \
                 -lvtkRenderingOpenGL2-9.0  \
                 -lvtkRenderingQt-9.0  \
                 -lvtkRenderingSceneGraph-9.0  \
                 -lvtkRenderingUI-9.0  \
                 -lvtkRenderingVolume-9.0  \
                 -lvtkRenderingVolumeOpenGL2-9.0  \
                 -lvtkRenderingVtkJS-9.0  \
                 -lvtkTestingRendering-9.0  \
                 -lvtkViewsContext2D-9.0  \
                 -lvtkViewsCore-9.0  \
                 -lvtkViewsInfovis-9.0  \
                 -lvtkViewsQt-9.0  \
                 -lvtkWrappingTools-9.0  \
                 -lvtkdoubleconversion-9.0  \
                 -lvtkexodusII-9.0  \
                 -lvtkexpat-9.0  \
                 -lvtkfreetype-9.0  \
                 -lvtkgl2ps-9.0  \
                 -lvtkglew-9.0  \
                 -lvtkhdf5-9.0  \
                 -lvtkhdf5_hl-9.0  \
                 -lvtkjpeg-9.0  \
                 -lvtkjsoncpp-9.0  \
                 -lvtklibharu-9.0  \
                 -lvtklibproj-9.0  \
                 -lvtklibxml2-9.0  \
                 -lvtkloguru-9.0  \
                 -lvtklz4-9.0  \
                 -lvtklzma-9.0  \
                 -lvtkmetaio-9.0  \
                 -lvtknetcdf-9.0  \
                 -lvtkogg-9.0  \
                 -lvtkpng-9.0  \
                 -lvtkpugixml-9.0  \
                 -lvtksqlite-9.0  \
                 -lvtksys-9.0  \
                 -lvtktheora-9.0  \
                 -lvtktiff-9.0  \
                 -lvtkverdict-9.0  \
                 -lvtkzlib-9.0  \                        
}

unix{
INCLUDEPATH +=  ../../VTK/include/vtk-9.0/  \


LIBS +=  -L../VTK/lib/  \  
                 -lvtkChartsCore-9.0  \
                 -lvtkCommonColor-9.0  \
                 -lvtkCommonComputationalGeometry-9.0  \
                 -lvtkCommonCore-9.0  \
                 -lvtkCommonDataModel-9.0  \
                 -lvtkCommonExecutionModel-9.0  \
                 -lvtkCommonMath-9.0  \
                 -lvtkCommonMisc-9.0  \
                 -lvtkCommonSystem-9.0  \
                 -lvtkCommonTransforms-9.0  \
                 -lvtkDICOMParser-9.0  \
                 -lvtkDomainsChemistry-9.0  \
                 -lvtkFiltersAMR-9.0  \
                 -lvtkFiltersCore-9.0  \
                 -lvtkFiltersExtraction-9.0  \
                 -lvtkFiltersFlowPaths-9.0  \
                 -lvtkFiltersGeneral-9.0  \
                 -lvtkFiltersGeneric-9.0  \
                 -lvtkFiltersGeometry-9.0  \
                 -lvtkFiltersHybrid-9.0  \
                 -lvtkFiltersHyperTree-9.0  \
                 -lvtkFiltersImaging-9.0  \
                 -lvtkFiltersModeling-9.0  \
                 -lvtkFiltersParallel-9.0  \
                 -lvtkFiltersParallelImaging-9.0  \
                 -lvtkFiltersPoints-9.0  \
                 -lvtkFiltersProgrammable-9.0  \
                 -lvtkFiltersSMP-9.0  \
                 -lvtkFiltersSelection-9.0  \
                 -lvtkFiltersSources-9.0  \
                 -lvtkFiltersStatistics-9.0  \
                 -lvtkFiltersTexture-9.0  \
                 -lvtkFiltersTopology-9.0  \
                 -lvtkFiltersVerdict-9.0  \
                 -lvtkGUISupportQt-9.0  \
                 -lvtkGUISupportQtSQL-9.0  \
                 -lvtkGeovisCore-9.0  \
                 -lvtkIOAMR-9.0  \
                 -lvtkIOAsynchronous-9.0  \
                 -lvtkIOCityGML-9.0  \
                 -lvtkIOCore-9.0  \
                 -lvtkIOEnSight-9.0  \
                 -lvtkIOExodus-9.0  \
                 -lvtkIOExport-9.0  \
                 -lvtkIOExportGL2PS-9.0  \
                 -lvtkIOExportPDF-9.0  \
                 -lvtkIOGeometry-9.0  \
                 -lvtkIOImage-9.0  \
                 -lvtkIOImport-9.0  \
                 -lvtkIOInfovis-9.0  \
                 -lvtkIOLSDyna-9.0  \
                 -lvtkIOLegacy-9.0  \
                 -lvtkIOMINC-9.0  \
                 -lvtkIOMotionFX-9.0  \
                 -lvtkIOMovie-9.0  \
                 -lvtkIONetCDF-9.0  \
                 -lvtkIOOggTheora-9.0  \
                 -lvtkIOPLY-9.0  \
                 -lvtkIOParallel-9.0  \
                 -lvtkIOParallelXML-9.0  \
                 -lvtkIOSQL-9.0  \
                 -lvtkIOSegY-9.0  \
                 -lvtkIOTecplotTable-9.0  \
                 -lvtkIOVeraOut-9.0  \
                 -lvtkIOVideo-9.0  \
                 -lvtkIOXML-9.0  \
                 -lvtkIOXMLParser-9.0  \
                 -lvtkImagingColor-9.0  \
                 -lvtkImagingCore-9.0  \
                 -lvtkImagingFourier-9.0  \
                 -lvtkImagingGeneral-9.0  \
                 -lvtkImagingHybrid-9.0  \
                 -lvtkImagingMath-9.0  \
                 -lvtkImagingMorphological-9.0  \
                 -lvtkImagingSources-9.0  \
                 -lvtkImagingStatistics-9.0  \
                 -lvtkImagingStencil-9.0  \
                 -lvtkInfovisCore-9.0  \
                 -lvtkInfovisLayout-9.0  \
                 -lvtkInteractionImage-9.0  \
                 -lvtkInteractionStyle-9.0  \
                 -lvtkInteractionWidgets-9.0  \
                 -lvtkParallelCore-9.0  \
                 -lvtkParallelDIY-9.0  \
                 -lvtkRenderingAnnotation-9.0  \
                 -lvtkRenderingContext2D-9.0  \
                 -lvtkRenderingCore-9.0  \
                 -lvtkRenderingFreeType-9.0  \
                 -lvtkRenderingGL2PSOpenGL2-9.0  \
                 -lvtkRenderingImage-9.0  \
                 -lvtkRenderingLOD-9.0  \
                 -lvtkRenderingLabel-9.0  \
                 -lvtkRenderingOpenGL2-9.0  \
                 -lvtkRenderingQt-9.0  \
                 -lvtkRenderingSceneGraph-9.0  \
                 -lvtkRenderingUI-9.0  \
                 -lvtkRenderingVolume-9.0  \
                 -lvtkRenderingVolumeOpenGL2-9.0  \
                 -lvtkRenderingVtkJS-9.0  \
                 -lvtkTestingRendering-9.0  \
                 -lvtkViewsContext2D-9.0  \
                 -lvtkViewsCore-9.0  \
                 -lvtkViewsInfovis-9.0  \
                 -lvtkViewsQt-9.0  \
                 -lvtkWrappingTools-9.0  \
                 -lvtkdoubleconversion-9.0  \
                 -lvtkexodusII-9.0  \
                 -lvtkexpat-9.0  \
                 -lvtkfreetype-9.0  \
                 -lvtkgl2ps-9.0  \
                 -lvtkglew-9.0  \
                 -lvtkhdf5-9.0  \
                 -lvtkhdf5_hl-9.0  \
                 -lvtkjpeg-9.0  \
                 -lvtkjsoncpp-9.0  \
                 -lvtklibharu-9.0  \
                 -lvtklibproj-9.0  \
                 -lvtklibxml2-9.0  \
                 -lvtkloguru-9.0  \
                 -lvtklz4-9.0  \
                 -lvtklzma-9.0  \
                 -lvtkmetaio-9.0  \
                 -lvtknetcdf-9.0  \
                 -lvtkogg-9.0  \
                 -lvtkpng-9.0  \
                 -lvtkpugixml-9.0  \
                 -lvtksqlite-9.0  \
                 -lvtksys-9.0  \
                 -lvtktheora-9.0  \
                 -lvtktiff-9.0  \
                 -lvtkverdict-9.0  \
                 -lvtkzlib-9.0  \ 
}
