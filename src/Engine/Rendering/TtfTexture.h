#ifdef USE_SDL2D
    #include "2D/TtfTexture.h"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/TtfTexture.h"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL_ES/TtfTexture.h"
        #endif
    #endif
#endif