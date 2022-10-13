#include "../Config.h"

#ifdef USE_SDL2D
    #include "2D/Sprite.cpp"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/Sprite.cpp"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL_ES/Sprite.cpp"
        #endif
    #endif
#endif



