#include "Sprite.h"
#include "../../Helper/Logger.h"
#include "../../Helper/format.h"
#include "Renderer.h"
#include "../../Math/MathHelper.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;
using namespace Engine::Math;

bool Sprite::Load(std::string filePath, Renderer &renderer)
{
    Logger::Log(Logger::Info, string_format("Loading texture %s...", filePath.c_str()));
    this->mTexture = IMG_LoadTexture(renderer.GetSDL_Renderer(), filePath.c_str());

    if (this->mTexture == NULL)
    {
        Logger::Log(Logger::Error, string_format("Unable to load texture from file %s! SDL Error: %s", filePath.c_str(), SDL_GetError()));
        return false;
    }

    int sizeX = 0;
    int sizeY = 0;
    
    SDL_QueryTexture(this->mTexture, NULL, NULL, &sizeX, &sizeY);

    this->sourceRectangle = Rectangle(0, 0, sizeX, sizeY);
    this->mSize = Vector2(sizeX, sizeY);
    this->origin = Vector2f(0,0);

    return true;
}

bool Sprite::Load(std::string filePath, Rectangle sourceRectangle, Renderer &renderer)
{
    this->mTexture = IMG_LoadTexture(renderer.GetSDL_Renderer(), filePath.c_str());

    if (this->mTexture == NULL)
    {
        Logger::Log(Logger::Error, string_format("Unable to load texture from file %s! SDL Error: %s", filePath.c_str(), SDL_GetError()));
        return false;
    }

    this->mSize = Vector2(0, 0);
  
    SDL_QueryTexture(this->mTexture, NULL, NULL, &this->mSize.X, &this->mSize.Y);

    this->sourceRectangle = sourceRectangle;

    this->origin = Vector2f(0,0);

    return true;
}
void Sprite::SetOrigin(float x, float y)
{
    this->origin.X = x;
    this->origin.Y = y;
}

int Sprite::GetWidth()
{
    return this->mSize.X;
}

int Sprite::GetHeight()
{
    return this->mSize.Y;
}

Vector2* Sprite::GetSize()
{
    return &this->mSize;
}

bool Sprite::Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
{
    SDL_Point actualOrigin;
    actualOrigin.x = (int)(destinationRectangle.Width * this->origin.X);
    actualOrigin.y = (int)(destinationRectangle.Height * this->origin.Y);

    rotationRad = MathHelper::RadToDeg(rotationRad);

    int flip = ((flipHorizontal) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | ((flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

    SDL_Rect srcRect = this->sourceRectangle.GetSDL_Rect();
    SDL_Rect dstRect = destinationRectangle.GetSDL_Rect();

    if (SDL_RenderCopyEx(renderer.GetSDL_Renderer(), this->mTexture, &srcRect, &dstRect, rotationRad, &actualOrigin, (SDL_RendererFlip)flip) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to draw texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool Sprite::Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
{
    SDL_Point actualOrigin;
    actualOrigin.x = (int)(destinationRectangle.Width * this->origin.X);
    actualOrigin.y = (int)(destinationRectangle.Height * this->origin.Y);

    rotationRad = MathHelper::RadToDeg(rotationRad);

    int flip = ((flipHorizontal) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | ((flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);

    SDL_Rect srcRect = sourceRectangle.GetSDL_Rect();
    SDL_Rect dstRect = destinationRectangle.GetSDL_Rect();

    if (SDL_RenderCopyEx(renderer.GetSDL_Renderer(), this->mTexture, &srcRect, &dstRect, rotationRad, &actualOrigin, (SDL_RendererFlip)flip) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to draw texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool Sprite::SetBlendMode(SDL_BlendMode mode)
{
    if (SDL_SetTextureBlendMode(this->mTexture, mode) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture blend mode! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool Sprite::SetColorMod(Color &color)
{
    if (SDL_SetTextureColorMod(this->mTexture, color.R, color.G, color.B) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture color mod! SDL Error: %s", SDL_GetError()));
        return false;
    }
        if (SDL_SetTextureAlphaMod(this->mTexture, color.A) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture alpha mod! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

void Sprite::Unload()
{
    SDL_DestroyTexture(this->mTexture);
    this->mTexture = NULL;
}