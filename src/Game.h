#pragma once

#include <vector>

#include "Engine/BaseGame.h"
#include "Engine/Rendering/Sprite.h"
#include "Engine/Rendering/RenderTexture.h"
#include "Engine/Audio/Music.h"
#include "Engine/Audio/Sound.h"

#define START_LENGTH 4
#define MAX_TIMER 250
#define TILE_SIZE 4
#define PLAY_SIZE 16
#define DEATH_ZONE 10000
#define MOUSE_AREA 4

class Game: public Engine::BaseGame
{
private:
    bool mRunning;
    bool mPressedF4;
    Color mColorBlack;
    Color mColorDarkGray;
    Color mColorDarkBlue;
    Color mColorDarkRed;
    Color mColorLightGreen;
    
public:
    Engine::Rendering::RenderTexture mainTarget;
    Engine::Rendering::RenderTexture blackSquare;
    Engine::Rendering::RenderTexture blueSquare;
    Engine::Rendering::RenderTexture greenSquare;
    Engine::Rendering::Sprite backgroundImage;

    Engine::Math::Vector2 playerPos;
    double timer;
    Engine::Math::Vector2 point;
    int direction;
    int nextDirection;

    int tailLength;
    int realLength;
    std::vector<Vector2> tails;

    float rotato;

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

    Engine::Rendering::RenderTexture BuildTexture(int width, int height, Color &color);
    void GeneratePoint();
    void ResetGame();
    void Move(int dir);

    Game(int width, int height, std::string windowTitle);
    void Init();
    void LoadContent();
    void HandleEvent(SDL_Event e);
    bool Update(double deltaTime);
    void Draw(double deltaTime);
    void Exit();
};