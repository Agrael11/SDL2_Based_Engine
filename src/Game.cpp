#include <SDL_mixer.h>
#include "Game.h"

#include "Engine/BaseGame.h"
#include "Engine/Helper/Logger.h"
#include "Engine/Helper/format.h"
#include "Engine/Audio/Audio.h"

using namespace Engine::Helper;
using namespace Engine::Audio;
using namespace Engine::Rendering;

Game::Game(int width, int height, std::string windowTitle)
{
    this->Load(width, height, windowTitle);
}
void Game::Init()
{
    InitAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

void Game::LoadContent()
{
}

void Game::Draw(double delta)
{
    renderer.Begin();

    renderer.Clean(255,0,255,255);

    renderer.End();
}

void Game::HandleEvent(SDL_Event e)
{
    if (e.type == SDL_QUIT)
    {
        this->mRunning = false;
    }
    else if( e.type == SDL_KEYDOWN )
    {
        this->KeyDown(e.key);
    }
    else if (e.type == SDL_KEYUP)
    {
        this->KeyUp(e.key);
    }
    else if (e.type == SDL_MOUSEMOTION)
    {
        this->MouseMove(e.motion);
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        this->MouseButtonDown(e.button);
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        this->MouseButtonDown(e.button);
    }
    else if (e.type == SDL_MOUSEWHEEL)
    {
        this->MouseWheelMove(e.wheel);
    }
    else if (e.type == SDL_CONTROLLERAXISMOTION)
    {
        this->ControllerAxisMove(e.caxis);
    }
    else if (e.type == SDL_CONTROLLERBUTTONDOWN)
    {
        this->ControllerButtonDown(e.cbutton);
    }
    else if (e.type == SDL_CONTROLLERBUTTONUP)
    {
        this->ControllerButtonUp(e.cbutton);
    }
}

bool Game::Update(double delta)
{
    if (!this->mRunning)
    {
        return false;
    }
    
    return true;
}

void Game::Exit()
{
    QuitAudio();
}


void Game::KeyDown(SDL_KeyboardEvent e)
{
    Logger::Log(Logger::Info, string_format("Key code %d down.", e.keysym.scancode));
    switch (e.keysym.scancode)
    {
        case SDL_SCANCODE_ESCAPE:
            this->mRunning = false;
            break;
        case SDL_SCANCODE_F4:
            this->mPressedF4 = true;
            break;  
        default:
            break;
    }
}

void Game::KeyUp(SDL_KeyboardEvent e)
{
    if (e.keysym.scancode == SDL_SCANCODE_F4)
    {
        if (this->mPressedF4)
        {
            ToggleFullscreen();
            this->mPressedF4 = false;
        }
    }
}

void Game::MouseMove(SDL_MouseMotionEvent e)
{
}

void Game::MouseButtonDown(SDL_MouseButtonEvent e)
{
    Logger::Log(Logger::Info, string_format("Mouse button %d pressed (Clicks: %d).", e.button, e.clicks));
}

void Game::MouseButtonUp(SDL_MouseButtonEvent e)
{
}

void Game::MouseWheelMove(SDL_MouseWheelEvent e)
{
}

void Game::ControllerAxisMove(SDL_ControllerAxisEvent e)
{
}

void Game::ControllerButtonDown(SDL_ControllerButtonEvent e)
{
    Logger::Log(Logger::Info, string_format("Controller button %d down.", e.button));
}

void Game::ControllerButtonUp(SDL_ControllerButtonEvent e)
{
}