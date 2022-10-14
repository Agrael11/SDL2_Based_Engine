#pragma once

#include "../Config.h"

#ifdef USE_SDL2D
    #include "2D/RenderTexture.h"
#else
    #ifdef USE_OPENGL
        #include "OpenGL/RenderTexture.cph"
    #else
        #ifdef USE_OPENGL_ES
            #include "OpenGL/RenderTexture.h"
        #endif
    #endif
#endif