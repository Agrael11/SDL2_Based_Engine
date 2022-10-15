#ifdef USE_SDL2D
    #include "2D/Sprite.h"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/Sprite.h"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL_ES/Sprite.h"
        #endif
    #endif
#endif