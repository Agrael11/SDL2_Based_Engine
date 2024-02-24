#include <random>
#include <time.h>

#include "Game.h"

#include "Engine/BaseGame.h"
#include "Engine/Helper/Logger.h"
#include "Engine/Audio/Audio.h"
#include "Engine/Support.h"
#include "Engine/Helper/StringHelp.h"
#include "Engine/Rendering/ImageTexture.h"

#include "Engine/Math/Color.h"
#include "Engine/Math/Colorf.h"

using namespace Engine::Helper;
using namespace Engine::Math;
using namespace Engine::Audio;
using namespace Engine::Rendering;

RenderTexture Game::BuildTexture(int width, int height, Colorf &color)
{
    RenderTexture texture;
    texture.Create(width, height, renderer);

    this->renderer.SetRenderTarget(texture);
    this->renderer.Begin();
    
    this->renderer.Clean(color);

    this->renderer.End();
    this->renderer.CleanRenderTarget();

    return texture;
}

void Game::GeneratePoint()
{
    bool interferes = true;
    while (interferes)
    {
        interferes = false;
        this->point.X = rand() % 16;
        this->point.Y = rand() % 16;
        //Check Head
        interferes |= (this->point.X == this->playerPos.X && this->point.Y == this->playerPos.Y);
        //Check Tails
        for (Vector2 point : this->tails)
        {
            interferes |= (this->point.X == point.X && this->point.Y == point.Y);
        }
    }
}

void Game::ResetGame()
{
    this->playerPos.X = PLAY_SIZE/2;
    this->playerPos.Y = PLAY_SIZE/2;

    srand((int)(time(NULL)));

    this->GeneratePoint();

    this->direction = 0;
    this->nextDirection = 0;

    this->realLength = 0;
    this->tailLength = START_LENGTH;

    this->tails.clear();

    this->timer = 0;
    this->score = 0;
}

void Game::Move(int dir)
{
    switch (dir)
    {
        case 3:
            if (this->direction != 1) this->nextDirection = 3;
            break;  
        case 1:
            if (this->direction != 3) this->nextDirection = 1;
            break;
        case 2:
            if (this->direction != 0) this->nextDirection = 2;
            break;
        case 0:
            if (this->direction != 2) this->nextDirection = 0;
            break;
    }
}




Game::Game(int width, int height, std::string windowTitle)
{
    this->Load(width, height, windowTitle);
    this->mRunning = true;
}

void Game::Init()
{
    if (Engine::Support::audio)
    {
        InitAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    }
    
    this->mColorBlack = Colorf(0.8f,0.8f,0.8f,1.0f);
    this->mColorDarkGray = Colorf(0.1f,0.1f,0.1f,1.0f);
    this->mColorDarkBlue = Colorf(0.1f,0.1f,1.0f,1.0f);
    this->mColorDarkRed = Colorf(0.3f,0.1f,0.1f,1.0f);
    this->mColorLightGreen = Colorf(0.5f,0.85f,0.5f,1.0f);

    this->rotato = 0;
    this->ResetGame();
}

void Game::LoadContent()
{
    #ifndef USE_SDL2D
    this->mShader.LoadFromFile("Assets/mainShader.vert", "Assets/mainShader.frag");
    #endif

    this->mainRenderTexture.Create(64, 64, renderer);
    this->blackSquareTexture = this->BuildTexture(4,4,this->mColorDarkGray);
    this->blueSquareTexture = this->BuildTexture(4,4,this->mColorDarkBlue);
    this->greenSquareTexture = this->BuildTexture(4,4,this->mColorLightGreen);
    this->backgroundImageTexture.Load("Assets/BG.png", renderer);

    this->mainTarget.Load(this->mainRenderTexture, renderer);
    this->blackSquare.Load(this->blackSquareTexture, renderer);
    this->blueSquare.Load(this->blueSquareTexture, renderer);
    this->greenSquare.Load(this->greenSquareTexture, renderer);
    this->greenSquare.SetOrigin(0.5f, 0.5f);

    this->backgroundImage.Load(this->backgroundImageTexture, renderer);
    Colorf cMod(0.1f,0.1f,0.1f,1.f);
    this->backgroundImage.SetColorMod(cMod);

    this->font.Load("Assets/turpis.ttf", 8, renderer);
    int wrap = this->windowWidth - 20;
    if (this->windowWidth > this->windowHeight)
    {
        wrap = this->windowHeight - 20;
    }
    Color white(255,255,255,255);
    this->textTexture.Generate("Lorem Ipsum, Hnedá líška vraj vie skákať, lol!", this->font, white, renderer, wrap);
    this->text.Load(this->textTexture, renderer);
}

void Game::Draw(double delta)
{
    this->renderer.SetRenderTarget(this->mainRenderTexture);
    this->renderer.Begin();
    this->renderer.Clean(this->mColorDarkRed);
    #ifndef USE_SDL2D
    this->renderer.SetActiveShader(&this->mShader);
    #endif
    Rectangle pos = Rectangle(0,0,64,64);

    this->renderer.DrawSprite(this->backgroundImage, pos);

    //Draw point
    
    pos.X = point.X * TILE_SIZE;
    pos.Y = (PLAY_SIZE-point.Y-1) * TILE_SIZE;
    #ifdef USE_SDL2D
    pos.Y = point.Y * TILE_SIZE;
    #else
    pos.Y = (PLAY_SIZE-point.Y-1) * TILE_SIZE;
    #endif
    pos.Width = TILE_SIZE;
    pos.Height = TILE_SIZE;

    this->renderer.DrawSprite(this->greenSquare, pos, NULL, rotato, false, false);
    

    //Draw tail
    
    for (Vector2 tail : this->tails)
    {
        pos.X = tail.X * TILE_SIZE;
        #ifdef USE_SDL2D
        pos.Y = tail.Y * TILE_SIZE;
        #else
        pos.Y = (PLAY_SIZE-tail.Y-1) * TILE_SIZE;
        #endif
        pos.Width = TILE_SIZE;
        pos.Height = TILE_SIZE;

        this->renderer.DrawSprite(this->blueSquare, pos);
    }

    //Draw Head

    pos.X = this->playerPos.X * TILE_SIZE;
    #ifdef USE_SDL2D
    pos.Y = this->playerPos.Y * TILE_SIZE;
    #else
    pos.Y = (PLAY_SIZE-this->playerPos.Y-1) * TILE_SIZE;
    #endif
    pos.Width = TILE_SIZE;
    pos.Height = TILE_SIZE;
    
    this->renderer.DrawSprite(this->blackSquare, pos);

    int wrap = 62;
    Color white(255,255,255,255);
    this->textTexture.Generate(string_format("%d", this->score), this->font, white, renderer, wrap);
    this->text.SetTexture(this->textTexture);
    
    pos.X = 1;
    #if USE_SDL2D
    pos.Y = 1;
    #else
    pos.Y = 63-this->text.GetHeight();
    #endif
    pos.Width = (int)(this->text.GetHeight() * this->text.GetRatio());
    pos.Height = this->text.GetHeight();
    
    this->renderer.DrawSprite(this->text, pos);

    this->renderer.End();


    //Draw canvas
    
    this->renderer.CleanRenderTarget();
    this->renderer.Begin();

    this->renderer.Clean(this->mColorBlack);

    if (this->windowWidth < this->windowHeight)
    {
        pos.X = 0;
        pos.Y = (this->windowHeight-this->windowWidth)/2;
        pos.Width = this->windowWidth;
        pos.Height = this->windowWidth;
        this->renderer.DrawSprite(mainTarget, pos);
    }
    else
    {
        pos.X = (this->windowWidth-this->windowHeight)/2;
        pos.Y = 0;
        pos.Width = this->windowHeight;
        pos.Height = this->windowHeight;
        this->renderer.DrawSprite(mainTarget, pos);
    }

    this->renderer.End();
    
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
        if (Engine::Support::controller)
        {
            this->ControllerAxisMove(e.caxis);
        }
    }
    else if (e.type == SDL_CONTROLLERBUTTONDOWN)
    {
        if (Engine::Support::controller)
        {
            this->ControllerButtonDown(e.cbutton);
        }
    }
    else if (e.type == SDL_CONTROLLERBUTTONUP)
    {
        if (Engine::Support::controller)
        {
            this->ControllerButtonUp(e.cbutton);
        }
    }
}

bool Game::Update(double delta)
{
    if (!this->mRunning)
    {
        return false;
    }

    this->rotato += (float)delta * 0.01f;
    while (this->rotato > 6.28f)
    {
        this->rotato -= 6.28f;
    }

    this->timer += delta;
    if (this->timer >= MAX_TIMER)
    {
        this->timer -= MAX_TIMER;

        //Check Tail collision

        for (Vector2 point : this->tails)
        {
            if (point.X == this->playerPos.X && point.Y == this->playerPos.Y)
            {
                ResetGame();
                return true;
            }
        }

        //Grow/Shrink Tail

        if (this->realLength > this->tailLength)
        {
            this->tails.erase(tails.begin());
            this->realLength--;
        }
        if (this->realLength <= this->tailLength)
        {
            this->realLength++;
            Vector2 tailPoint(this->playerPos.X, this->playerPos.Y);
            this->tails.push_back(tailPoint);
        }

        this->direction = this->nextDirection;

        //MOVEMENT
        switch (this->direction)
        {
            case 0:
                this->playerPos.X++;
                break;
            case 1:
                this->playerPos.Y++;
                break;
            case 2:
                this->playerPos.X--;
                break;
            case 3:
                this->playerPos.Y--;
                break;
        }

        //Screen Wrapping

        if (this->playerPos.X < 0) this->playerPos.X += PLAY_SIZE;
        if (this->playerPos.X > PLAY_SIZE-1) this->playerPos.X -= PLAY_SIZE;
        if (this->playerPos.Y < 0) this->playerPos.Y += PLAY_SIZE;
        if (this->playerPos.Y > PLAY_SIZE-1) this->playerPos.Y -= PLAY_SIZE;

        //Check Point Collision

        if (this->playerPos.X == this->point.X && this->playerPos.Y == this->point.Y)
        {
            this->tailLength++;
            this->GeneratePoint();
            this->score += 10;
        }

    }

    return true;
}

void Game::Exit()
{
    QuitAudio();
}


void Game::KeyDown(SDL_KeyboardEvent e)
{
    switch (e.keysym.scancode)
    {
        case SDL_SCANCODE_ESCAPE:
            this->mRunning = false;
            break;
        case SDL_SCANCODE_F4:
            this->mPressedF4 = true;
            break;  
        case SDL_SCANCODE_W:
        case SDL_SCANCODE_UP:
            this->Move(3);
            break;  
        case SDL_SCANCODE_S:
        case SDL_SCANCODE_DOWN:
            this->Move(1);
            break;
        case SDL_SCANCODE_A:
        case SDL_SCANCODE_LEFT:
            this->Move(2);
            break;
        case SDL_SCANCODE_D:
        case SDL_SCANCODE_RIGHT:
            this->Move(0);
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
    if (e.state != 0)
    {
        if (e.x > windowWidth - windowWidth / MOUSE_AREA)
        {
            this->Move(0);
        }
        else if (e.x < windowWidth / MOUSE_AREA)
        {
            this->Move(2);
        }
        if (e.y > windowHeight - windowHeight / MOUSE_AREA)
        {
            this->Move(1);
        }
        else if (e.y < windowHeight / MOUSE_AREA)
        {
            this->Move(3);
        }
    }
}

void Game::MouseButtonDown(SDL_MouseButtonEvent e)
{
    if (e.x > windowWidth - windowWidth / MOUSE_AREA)
    {
        this->Move(0);
    }
    else if (e.x < windowWidth / MOUSE_AREA)
    {
        this->Move(2);
    }
    if (e.y > windowHeight - windowHeight / MOUSE_AREA)
    {
        this->Move(1);
    }
    else if (e.y < windowHeight / MOUSE_AREA)
    {
        this->Move(3);
    }
}

void Game::MouseButtonUp(SDL_MouseButtonEvent e)
{
}

void Game::MouseWheelMove(SDL_MouseWheelEvent e)
{
}

void Game::ControllerAxisMove(SDL_ControllerAxisEvent e)
{   
    if (e.axis == SDL_CONTROLLER_AXIS_LEFTX) 
    {
        if (e.value < -DEATH_ZONE || e.value > DEATH_ZONE)
        {
            printf("%d, %d\n", e.axis, e.value);
        }
        if (e.value < -DEATH_ZONE) this->Move(2);
        else if (e.value > DEATH_ZONE) this->Move(0);
    }
    else if (e.axis == SDL_CONTROLLER_AXIS_LEFTY)
    {
        if (e.value < -DEATH_ZONE || e.value > DEATH_ZONE)
        {
            printf("%d, %d\n", e.axis, e.value);
        }
        if (e.value < -DEATH_ZONE) this->Move(3);
        else if (e.value > DEATH_ZONE) this->Move(1);
    }
}

void Game::ControllerButtonDown(SDL_ControllerButtonEvent e)
{
    switch (e.button)
    {
        case SDL_CONTROLLER_BUTTON_BACK:
            this->mRunning = false;
            break;
        case SDL_CONTROLLER_BUTTON_START:
            this->mPressedF4 = true;
            break;  
        case SDL_CONTROLLER_BUTTON_DPAD_UP:
            this->Move(3);
            break;  
        case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
            this->Move(1);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
            this->Move(2);
            break;
        case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
            this->Move(0);
            break;
        default:
            break;
    }
}

void Game::ControllerButtonUp(SDL_ControllerButtonEvent e)
{
}