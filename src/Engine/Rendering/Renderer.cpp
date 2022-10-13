#include "../Config.h"

#ifdef USE_SDL2D
    #include "2D/Renderer.cpp"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/Renderer.cpp"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL/Renderer.cpp"
        #endif
    #endif
#endif