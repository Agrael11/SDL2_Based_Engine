#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"
#include "RenderTexture.h"
#include "../Math/Color.h"

namespace Engine::Rendering
{
    class Renderer
    {
        private:
            SDL_Renderer* mRenderer;

        public:
            SDL_Renderer* GetSDL_Renderer();

            void Init(SDL_Window &window, Uint32 flags);
            void Begin();
            void End();
            bool DrawSprite(Sprite &sprite, Rectangle &destination, Rectangle *source = NULL, double rotation = 0, bool flipHorizontal = false, bool flipVertical = false);
            bool DrawRenderTexture(RenderTexture &renderTexture, Rectangle &destination, Rectangle *source = NULL, double rotation = 0, bool flipHorizontal = false, bool flipVertical = false);
            void Clean(Color &color);
            void SetViewport(int x, int y, int width, int height);
            bool SetRenderTarget(RenderTexture &texture);
            bool CleanRenderTarget();

            void Destroy();
    };
};