#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "../../Math/Rectangle.h"
#include "../../Math/Vector2.h"
#include "../../Math/Vector2f.h"
#include "../../Math/Color.h"

using namespace Engine::Math;

namespace Engine::Rendering
{
    class Renderer;
    class RenderTexture
    {
    private:
        SDL_Texture* mTexture;
        SDL_TextureAccess mAccess;
        Vector2 mSize;

    public:
        Vector2f origin;

        bool Create(int width, int height, Renderer &renderer);
        void SetOrigin(float x, float y);
        int GetWidth();
        int GetHeight();
        Vector2* GetSize();
        bool SetAsRenderTarget(Renderer &enderer);
        bool Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool SetBlendMode(SDL_BlendMode mode);
        bool SetColorMod(Color &color);
        void Unload();
    };
};