#include "../Config.h"

#ifdef USE_SDL2D
    #include "2D/RenderTexture.cpp"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/RenderTexture.cpp"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL/RenderTexture.cpp"
        #endif
    #endif
#endif