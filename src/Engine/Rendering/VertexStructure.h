#ifdef USE_SDL2D
    #include "2D/VertexStructure.h"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/VertexStructure.h"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL/VertexStructure.h"
        #endif
    #endif
#endif