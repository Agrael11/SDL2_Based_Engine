#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace Engine::Rendering
{
    class RenderTexture
    {
    private:
        SDL_Texture* mTexture;
        SDL_TextureAccess mAccess;
        int mWidth;
        int mHeight;

    public:
        bool Create(int width, int height, SDL_Renderer* renderer);
        int GetWidth();
        int GetHeight();
        bool SetAsRenderTarget(SDL_Renderer* renderer);
        bool Draw(SDL_Rect* destinationRectangle, SDL_Renderer* renderer);
        bool SetBlendMode(SDL_BlendMode mode);
        bool SetAlphaMod(int alpha);
        bool SetColorMod(int r, int g, int b);
        void Unload();
    };
};