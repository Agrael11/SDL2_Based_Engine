#pragma once

#define USE_SDL2D

#ifndef USE_SDL
    #ifdef EMSCRIPTEN
        #define USE_OPENGL_ES
    #else
        #define USE_OPENGL
    #endif
#endif