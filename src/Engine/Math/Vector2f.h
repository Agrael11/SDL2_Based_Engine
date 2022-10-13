#pragma once

#include "../Config.h"

#ifdef USE_SDL2D
#include <SDL.h>
#endif

namespace Engine::Math
{
    class Vector2;
    class Vector2f
    {
        public:
        float X;
        float Y;

        Vector2f();
        Vector2f(float x, float y);

        float Distance(Vector2f &other);
        void Normalize();
        float GetMagnitude();
        void SetMagnitude(float magnitude);
        Vector2 GetVector2();

        Vector2f operator+ (Vector2f const &other);
        Vector2f operator- (Vector2f const &other);
        Vector2f operator* (float mult);
        Vector2f operator/ (float mult);

        #ifdef USE_SDL2D
        SDL_Point GetSDL_Point();
        #endif
    };
};