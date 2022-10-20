#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "../../Math/Rectangle.h"
#include "../../Math/Vector2.h"
#include "../../Math/Vector2f.h"
#include "../../Math/Colorf.h"
#include "Shader.h"

using namespace Engine::Math;

namespace Engine::Rendering::BlendMode
{
    enum BlendMode {Add, Subtract, ReverseSubtract, Min, Max};
}

namespace Engine::Rendering
{
    class Renderer;
    class Sprite
    {
    private:
        unsigned int mTexture;
        Vector2 mSize;
        Colorf mColor;
        
        unsigned int mVAO;

        void mBuildVAO();

    public:
        Rectangle sourceRectangle;
        Vector2f origin;

        bool Load(std::string filePath, Renderer &renderer);
        bool Load(std::string filePath, Rectangle sourceRectangle, Renderer &renderer);
        void SetOrigin(float x, float y);
        void SetSourceRectangle(Rectangle &r);
        int GetWidth();
        int GetHeight();
        Vector2* GetSize();
        bool Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad = 0, bool flipHorizontal = false, bool flipVertical = false);
        bool SetBlendMode(Engine::Rendering::BlendMode::BlendMode mode);
        bool SetColorMod(Colorf &color);
        void Unload();
    };
};