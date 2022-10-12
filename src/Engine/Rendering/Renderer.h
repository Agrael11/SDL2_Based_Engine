#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"
#include "RenderTexture.h"

namespace Engine::Rendering
{
    class Renderer
    {
        private:
            SDL_Renderer* mRenderer;

        public:
            SDL_Renderer* GetSDL_Renderer();

            void Init(SDL_Window* window, Uint32 flags);
            void Begin();
            void End();
            bool DrawSprite(Sprite* sprite, SDL_Rect* destination, SDL_Rect* source = NULL, double rotation = 0, SDL_RendererFlip flipping = SDL_FLIP_NONE);
            bool DrawRenderTexture(RenderTexture* renderTexture, SDL_Rect* destination, SDL_Rect* source = NULL, double rotation = 0, SDL_RendererFlip flipping = SDL_FLIP_NONE);
            void Clean(int r, int g, int b, int a);
            void SetViewport(int x, int y, int width, int height);
            bool SetRenderTarget(RenderTexture* texture);
            bool CleanRenderTarget();

            void Destroy();
    };
};