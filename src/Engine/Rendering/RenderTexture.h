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
        SDL_Point mSize;

    public:
        double originX;
        double originY;

        bool Create(int width, int height, SDL_Renderer* renderer);
        void SetOrigin(double x, double y);
        int GetWidth();
        int GetHeight();
        SDL_Point* GetSize();
        bool SetAsRenderTarget(SDL_Renderer* renderer);
        bool Draw(SDL_Rect* destinationRectangle, SDL_Renderer* renderer, double rotationRad = 0, SDL_RendererFlip flipping = SDL_RendererFlip::SDL_FLIP_NONE);
        bool Draw(SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, SDL_Renderer* renderer, double rotationRad = 0, SDL_RendererFlip flipping = SDL_RendererFlip::SDL_FLIP_NONE);
        bool SetBlendMode(SDL_BlendMode mode);
        bool SetAlphaMod(int alpha);
        bool SetColorMod(int r, int g, int b);
        void Unload();
    };
};