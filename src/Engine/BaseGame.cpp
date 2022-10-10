#include "BaseGame.h"
#include "Rendering/Renderer.h"
#include "Helper/Logger.h"
#include "Helper/Format.h"

using namespace Engine;
using namespace Engine::Helper;

BaseGame::BaseGame()
{

}

void BaseGame::Load(int width, int height, std::string windowTitle)
{
    this->windowWidth = width;
    this->windowHeight = height;
    this->windowTitle = windowTitle;
    
    Logger::Log(Logger::Info, "Initializing SDL2..");
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) < 0 )
    {
        Logger::Log(Logger::Error, string_format("SDL could not initialize! SDL_Error: %s", SDL_GetError()));
        return;
    }

    this->mFullscreen = false;

    Logger::Log(Logger::Info, "Creating Window...");
    this->mWindow = SDL_CreateWindow(
        this->windowTitle.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        this->windowWidth,
        this->windowHeight,
        0
    );

    if (this->mWindow == NULL)
    {
        Logger::Log(Logger::Error, string_format("Window could not be created! SDL_Error:: %s", SDL_GetError()));
        return;
    }

    Logger::Log(Logger::Info, "Initializing renderer");
    renderer.Init(this->mWindow, SDL_RENDERER_ACCELERATED);
}

SDL_Point BaseGame::GetWindowSize()
{
    SDL_Point point;
    point.x = this->windowWidth;
    point.y = this->windowHeight;
    return point;
}

std::string BaseGame::GetWindowTitle()
{
    return this->windowTitle;
}

void BaseGame::SetWindowSize(SDL_Point size)
{
    if (this->mFullscreen)
    {
        this->mOriginalWidth = size.x;
        this->mOriginalWidth = size.y;
        return;
    }

    this->windowWidth = size.x;
    this->windowHeight = size.y;
    SDL_SetWindowSize(this->mWindow, this->windowWidth, this->windowHeight);
}

void BaseGame::SetWindowSize(int width, int height)
{
    if (this->mFullscreen)
    {
        this->mOriginalWidth = width;
        this->mOriginalWidth = height;
        return;
    }

    this->windowWidth = width;
    this->windowHeight = height;
    SDL_SetWindowSize(this->mWindow, this->windowWidth, this->windowHeight);
}

void BaseGame::SetWindowTitle(std::string title)
{
    this->windowTitle = title;
    SDL_SetWindowTitle(this->mWindow, this->windowTitle.c_str());
}

void BaseGame::ToggleFullscreen()
{
#if EMSCRIPTEN
    Logger::Log(Logger::Warning, "Not supported in SDL currently.");
    return;
#else
    if (!this->mFullscreen)
    {
        if (SDL_SetWindowFullscreen(this->mWindow, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
        {
            Logger::Log(Logger::Warning, string_format("Failed to switch to fullscreen. SDL Error: %s.", SDL_GetError()));
            return;
        }
        this->mOriginalWidth = this->windowWidth;
        this->mOriginalHeight = this->windowHeight;
        SDL_GetWindowSize(this->mWindow, &this->windowWidth, &this->windowHeight);
        this->mFullscreen = true;
        return;
    }
    
    
    if (SDL_SetWindowFullscreen(this->mWindow, 0) != 0)
    {
        Logger::Log(Logger::Warning, string_format("Failed to switch to windowed. SDL Error: %s.", SDL_GetError()));
        return;
    }
    this->windowWidth = this->mOriginalWidth;
    this->windowHeight = this->mOriginalHeight;
    this->mFullscreen = false;
#endif
}

void BaseGame::Init()
{
}

void BaseGame::LoadContent()
{

}

void BaseGame::HandleEvent(SDL_Event e)
{
    
}

bool BaseGame::Update(double deltaTime)
{
    return false;
}

void BaseGame::Draw(double deltaTime)
{

}

void BaseGame::Exit()
{
}

void BaseGame::Unload()
{
    Logger::Log(Logger::Info, "Unloading Game...");
    this->Exit();
    Logger::Log(Logger::Info, "Destroying Renderer...");
    this->renderer.Destroy();
    Logger::Log(Logger::Info, "Destroying Window...");
    SDL_DestroyWindow(this->mWindow);
    this->mWindow = NULL;
    Logger::Log(Logger::Info, "Quitting SDL2...");
    SDL_Quit();
}