#pragma once

#include <SDL.h>
#include <SDL_image.h>

#include "../../Math/Rectangle.h"
#include "../../Math/Vector2.h"
#include "../../Math/Vector2f.h"
#include "../../Math/Colorf.h"
#include "Sprite.h"
#include "Shader.h"

using namespace Engine::Math;

namespace Engine::Rendering
{
    class Renderer;
    class RenderTexture
    {
    private:
        unsigned int mFrameBuffer;
        unsigned int mTexture;
        Vector2 mSize;
        Colorf mColor;
        Rectangle mSourceRectangle;

        unsigned int mVAO;

        void mBuildVAO();

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
        bool SetBlendMode(BlendMode::BlendMode mode);
        bool SetColorMod(Colorf &color);
        void Unload();
    };
};