#pragma once

#include "../Config.h"

#ifdef USE_SDL2D
#include <SDL.h>
#endif

namespace Engine::Math
{
    class Vector2f;
    class Vector2
    {
        public:
        int X;
        int Y;

        Vector2();
        Vector2(int x, int y);

        float Distance(Vector2 &other);
        void Normalize();
        float GetMagnitude();
        void SetMagnitude(float magnitude);
        Vector2f GetVector2f();

        Vector2 operator+ (Vector2 const &other);
        Vector2 operator- (Vector2 const &other);
        Vector2 operator* (float mult);
        Vector2 operator/ (float mult);

        #ifdef USE_SDL2D
        SDL_Point GetSDL_Point();
        #endif
    };
};