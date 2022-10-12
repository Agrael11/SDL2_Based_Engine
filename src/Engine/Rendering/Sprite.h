#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

namespace Engine::Rendering
{
    class Sprite
    {
    private:
        SDL_Texture* mTexture;
        SDL_Point mSize;

    public:
        SDL_Rect sourceRectangle;
        double originX;
        double originY;

        bool Load(std::string filePath, SDL_Renderer* renderer);
        bool Load(std::string filePath, SDL_Rect sourceRectangle, SDL_Renderer* renderer);
        void SetOrigin(double x, double y);
        int GetWidth();
        int GetHeight();
        SDL_Point* GetSize();
        bool Draw(SDL_Rect* destinationRectangle, SDL_Renderer* renderer, double rotationRad = 0, SDL_RendererFlip flipping = SDL_RendererFlip::SDL_FLIP_NONE);
        bool Draw(SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, SDL_Renderer* renderer, double rotationRad = 0, SDL_RendererFlip flipping = SDL_RendererFlip::SDL_FLIP_NONE);
        bool SetBlendMode(SDL_BlendMode mode);
        bool SetAlphaMod(int alpha);
        bool SetColorMod(int r, int g, int b);
        void Unload();
    };
};