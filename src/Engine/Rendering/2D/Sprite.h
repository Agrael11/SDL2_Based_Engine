#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../../Math/Rectangle.h"
#include "../../Math/Vector2.h"
#include "../../Math/Vector2f.h"
#include "../../Math/Colorf.h"
#include "Texture.h"

using namespace Engine::Math;

namespace Engine::Rendering::BlendMode
{
    enum BlendMode {None, Add, Blend, Mod};
}

namespace Engine::Rendering
{
    class Renderer;
    class Sprite
    {
    private:
        Texture mTexture;
        Vector2 mSize;
        Colorf mColor;

    public:
        Rectangle sourceRectangle;
        Vector2f origin;

        bool Load(Texture texture, Renderer &renderer);
        bool Load(Texture texture, Rectangle sourceRectangle, Renderer &renderer);
        Texture* GetTexture();
        void SetOrigin(float x, float y);
        void SetSourceRectangle(Rectangle &r);
        int GetWidth();
        int GetHeight();
        Vector2* GetSize();
        bool Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool SetBlendMode(BlendMode::BlendMode mode);
        bool SetColorMod(Colorf &color);
        void Unload();
    };
};