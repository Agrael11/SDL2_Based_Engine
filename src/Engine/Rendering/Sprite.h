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

    public:
        SDL_Rect sourceRectangle;
        bool Load(std::string filePath, SDL_Renderer* renderer);
        bool Load(std::string filePath, SDL_Rect sourceRectangle, SDL_Renderer* renderer);
        bool Draw(SDL_Rect* destinationRectangle, SDL_Renderer* renderer);
        bool SetBlendMode(SDL_BlendMode mode);
        bool SetAlphaMod(int alpha);
        bool SetColorMod(int r, int g, int b);
        void Unload();
    };
};