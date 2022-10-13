#pragma once

#include "../Config.h"

//#ifdef USE_SDL2D
#include <SDL.h>
//#endif

namespace Engine::Math
{
    class Rectangle
    {
        public:
        int X;
        int Y;
        int Width;
        int Height;

        Rectangle();
        Rectangle(int x, int y, int width, int height);
        
        bool Intersects(Rectangle &other);
        bool Contains(Rectangle &other);
        int GetX2();
        int GetY2();

        //#ifdef USE_SDL2D
        SDL_Rect GetSDL_Rect();
        //#endif
    };
};