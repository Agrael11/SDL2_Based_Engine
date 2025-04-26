#ifdef USE_SDL2D
#include "2D/MaterialProperty.h"
#else
#ifdef USE_OPENGL
#include "OpenGL/MaterialProperty.h"
#else
#ifdef USE_OPENGL_ES
#include "OpenGL/MaterialProperty.h"
#endif
#endif
#endif