#pragma once

#include <vector>

#include "Engine/BaseGame.h"
#include "Engine/Rendering/Sprite.h"
#include "Engine/Rendering/RenderTexture.h"
#include "Engine/Rendering/ImageTexture.h"
#include "Engine/Rendering/Shader.h"
#include "Engine/Audio/Music.h"
#include "Engine/Audio/Sound.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Colorf.h"

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
    Engine::Math::Colorf mColorBlack;
    Engine::Math::Colorf mColorDarkGray;
    Engine::Math::Colorf mColorDarkBlue;
    Engine::Math::Colorf mColorDarkRed;
    Engine::Math::Colorf mColorLightGreen;
    Engine::Rendering::Shader mShader;
    
public:
    Engine::Rendering::RenderTexture mainRenderTexture;
    Engine::Rendering::RenderTexture blackSquareTexture;
    Engine::Rendering::RenderTexture blueSquareTexture;
    Engine::Rendering::RenderTexture greenSquareTexture;
    Engine::Rendering::ImageTexture backgroundImageTexture;
    Engine::Rendering::Sprite mainTarget;
    Engine::Rendering::Sprite blackSquare;
    Engine::Rendering::Sprite blueSquare;
    Engine::Rendering::Sprite greenSquare;
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

    Engine::Rendering::RenderTexture BuildTexture(int width, int height, Colorf &color);
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