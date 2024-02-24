#ifdef USE_SDL2D
	#include "2D/Texture.h"
#else
	#ifdef USE_OPENGL
		#include "OpenGL/Texture.h"
	#else
		#ifdef USE_OPENGL_ES
			#include "OpenGL/Texture.h"
		#endif
	#endif
#endif