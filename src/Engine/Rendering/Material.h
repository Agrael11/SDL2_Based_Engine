#ifdef USE_SDL2D
#include "2D/Material.h"
#else
#ifdef USE_OPENGL
#include "OpenGL/Material.h"
#else
#ifdef USE_OPENGL_ES
#include "OpenGL/Material.h"
#endif
#endif
#endif