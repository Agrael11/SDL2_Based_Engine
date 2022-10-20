#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Sprite.h"
#include "RenderTexture.h"
#include "../../Math/Colorf.h"
#include "../../Math/Rectangle.h"

namespace Engine::Rendering
{
    class Renderer
    {
        private:
            //SDL_Renderer* mRenderer;
            SDL_GLContext mContext;
            SDL_Window* mWindowReference;
            Shader* mActiveShader;
            Rectangle mViewPort;
            bool mRenderTexture;

        public:
            SDL_Renderer* GetSDL_Renderer();

            bool Init(SDL_Window &window, Uint32 flags);
            void Begin();
            void End();
            bool DrawSprite(Sprite &sprite, Engine::Math::Rectangle &destination, Engine::Math::Rectangle *source = NULL, double rotation = 0, bool flipHorizontal = false, bool flipVertical = false);
            bool DrawRenderTexture(RenderTexture &renderTexture, Engine::Math::Rectangle &destination, Engine::Math::Rectangle *source = NULL, double rotation = 0, bool flipHorizontal = false, bool flipVertical = false);
            void Clean(Color &color);
            void Clean(Colorf &color);
            void SetViewport(int x, int y, int width, int height);
            Rectangle GetViewport();
            bool SetRenderTarget(RenderTexture &texture);
            bool CleanRenderTarget();
            void SetActiveShader(Shader* shader);
            Shader* GetActiveShader();

            void Destroy();
    };
};