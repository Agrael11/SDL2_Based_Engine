#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../Math/Rectangle.h"
#include "../Math/Vector2.h"
#include "../Math/Vector2f.h"
#include "../Math/Color.h"

using namespace Engine::Math;

namespace Engine::Rendering
{
    class Renderer;
    class Sprite
    {
    private:
        SDL_Texture* mTexture;
        Vector2 mSize;

    public:
        Rectangle sourceRectangle;
        Vector2f origin;

        bool Load(std::string filePath, Renderer &renderer);
        bool Load(std::string filePath, Rectangle sourceRectangle, Renderer &renderer);
        void SetOrigin(float x, float y);
        int GetWidth();
        int GetHeight();
        Vector2* GetSize();
        bool Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool SetBlendMode(SDL_BlendMode mode);
        bool SetColorMod(Color &color);
        void Unload();
    };
};