#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Rendering/Renderer.h"

namespace Engine
{
    class BaseGame
    {
    private:
        SDL_Window* mWindow;
    public:
        Engine::Rendering::Renderer renderer;
        int windowWidth;
        int windowHeight;
        std::string windowTitle;
    private:
    public:
        BaseGame();

        SDL_Point GetWindowSize();
        std::string GetWindowTitle();

        void SetWindowSize(SDL_Point size);
        void SetWindowSize(int width, int height);
        void SetWindowTitle(std::string title);

        void Load(int width, int height, std::string windowTitle);
        virtual void Init();
        virtual void LoadContent();
        virtual void HandleEvent(SDL_Event e);
        virtual bool Update(double deltaTime);
        virtual void Draw(double deltaTime);
        virtual void Exit();
        void Unload();
    };
};