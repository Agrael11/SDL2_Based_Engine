#ifdef USE_SDL2D
    #include "2D/FontTexture.h"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/FontTexture.h"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL_ES/FontTexture.h"
        #endif
    #endif
#endif