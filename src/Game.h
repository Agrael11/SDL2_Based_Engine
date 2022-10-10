#pragma once

#include <map>

#include "Engine/BaseGame.h"
#include "Engine/Rendering/Sprite.h"
#include "Engine/Rendering/RenderTexture.h"
#include "Engine/Audio/Music.h"
#include "Engine/Audio/Sound.h"

class Game: public Engine::BaseGame
{
private:
    bool mRunning;
public:

private:
    void KeyDown(SDL_KeyboardEvent e);
    void KeyUp(SDL_KeyboardEvent e);
    void MouseMove(SDL_MouseMotionEvent e);
    void MouseButtonDown(SDL_MouseButtonEvent e);
    void MouseButtonUp(SDL_MouseButtonEvent e);
    void MouseWheelMove(SDL_MouseWheelEvent e);
    void ControllerAxisMove(SDL_ControllerAxisEvent e);
    void ControllerButtonDown(SDL_ControllerButtonEvent e);
    void ControllerButtonUp(SDL_ControllerButtonEvent e);
public:
    Game(int width, int height, std::string windowTitle);
    void Init();
    void LoadContent();
    void HandleEvent(SDL_Event e);
    bool Update(double deltaTime);
    void Draw(double deltaTime);
    void Exit();
};