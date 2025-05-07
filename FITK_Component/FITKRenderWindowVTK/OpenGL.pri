win32{

DEFINES    +=  GLUT_DISABLE_ATEXIT_HACK

INCLUDEPATH +=  ../../Tools/Win64/OpenGL/glew/include/  \
                ../../Tools/Win64/OpenGL/freeglut/include/ \


Debug:LIBS +=  -L../../Tools/Win64/OpenGL/glew/lib/Release/x64/ \
         -lglew32 \
         -lglew32s \
         -lOpenGL32 \
         -L../../Tools/Win64/OpenGL/freeglut/lib/x64/ \
         -lfreeglut \


Release:LIBS +=  -L../../Tools/Win64/OpenGL/glew/lib/Release/x64/ \
         -lglew32 \
         -lglew32s \
         -lOpenGL32 \
         -L../../Tools/Win64/OpenGL/freeglut/lib/x64/ \
         -lfreeglut \
}

unix{
INCLUDEPATH +=   ../../Tools/Linux64/VTK/include/vtk-9.0/  \


LIBS +=  -L../../Tools/Linux64/VTK/lib   \

}
