HEADERS += \ 
    $$PWD/FITKInterfaceMeshAPI.h \
    $$PWD/FITKMeshVTKMap.h \
    $$PWD/FITKUnstructuredMeshVTK.h \
    $$PWD/FITKMeshFeatureVTK.h \
    $$PWD/FITKStructuredMeshVTK.h \
    $$PWD/FITKUnstructuredFluidMeshVTK.h \

SOURCES += \
    $$PWD/FITKUnstructuredMeshVTK.cpp \
    $$PWD/FITKMeshFeatureVTK.cpp \
    $$PWD/FITKStructuredMeshVTK.cpp \
    $$PWD/FITKUnstructuredFluidMeshVTK.cpp \
    
FORMS += \
#    $$PWD/PluginManageDialog.ui \
 
 
#RESOURCES += ../qrc/qianfan.qrc

#RC_FILE += ../qrc/qianfan.rc
 
 DISTFILES += \
    $$PWD/License.txt \
    