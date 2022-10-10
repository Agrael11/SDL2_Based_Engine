#include "Sprite.h"
#include "../Helper/Logger.h"
#include "../Helper/format.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;

bool Sprite::Load(std::string filePath, SDL_Renderer* renderer)
{
    Logger::Log(Logger::Info, string_format("Loading texture %s...", filePath.c_str()));
    this->mTexture = IMG_LoadTexture(renderer, filePath.c_str());

    if (this->mTexture == NULL)
    {
        Logger::Log(Logger::Error, string_format("Unable to load texture from file %s! SDL Error: %s", filePath.c_str(), SDL_GetError()));
        return false;
    }
    
    this->sourceRectangle.x = 0;
    this->sourceRectangle.y = 0;
    SDL_QueryTexture(this->mTexture, NULL, NULL, &this->sourceRectangle.w, &this->sourceRectangle.h);

    return true;
}

bool Sprite::Load(std::string filePath, SDL_Rect sourceRectangle, SDL_Renderer* renderer)
{
    this->mTexture = IMG_LoadTexture(renderer, filePath.c_str());

    if (this->mTexture == NULL)
    {
        Logger::Log(Logger::Error, string_format("Unable to load texture from file %s! SDL Error: %s", filePath.c_str(), SDL_GetError()));
        return false;
    }

    this->sourceRectangle = sourceRectangle;

    return true;
}

bool Sprite::Draw(SDL_Rect* destinationRectangle, SDL_Renderer* renderer)
{
    if (SDL_RenderCopyEx(renderer, this->mTexture, &this->sourceRectangle, destinationRectangle, 0, NULL, SDL_RendererFlip::SDL_FLIP_NONE) != 0)
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

bool Sprite::SetAlphaMod(int alpha)
{
    if (SDL_SetTextureAlphaMod(this->mTexture, alpha) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture alpha mod! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool Sprite::SetColorMod(int r, int g, int b)
{
    if (SDL_SetTextureColorMod(this->mTexture, r, g, b) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture color mod! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

void Sprite::Unload()
{
    SDL_DestroyTexture(this->mTexture);
    this->mTexture = NULL;
}