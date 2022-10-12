#include "RenderTexture.h"
#include "../Helper/Logger.h"
#include "../Helper/format.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;

bool RenderTexture::Create(int width, int height, SDL_Renderer* renderer)
{
    Logger::Log(Logger::Info, "Creating render texture");
    this->mAccess = SDL_TEXTUREACCESS_TARGET;
    this->mTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, this->mAccess, width, height);

    if (this->mTexture == NULL)
    {
        Logger::Log(Logger::Error, string_format("Unable to create render texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    
    this->mSize.x = width;
    this->mSize.y = height;

    this->originX = 0;
    this->originY = 0;

    return true;
}

void RenderTexture::SetOrigin(double x, double y)
{
    this->originX = x;
    this->originY = y;
}

int RenderTexture::GetWidth()
{
    return this->mSize.x;
}

int RenderTexture::GetHeight()
{
    return this->mSize.y;
}

SDL_Point* RenderTexture::GetSize()
{
    return &this->mSize;
}

bool RenderTexture::SetAsRenderTarget(SDL_Renderer* renderer)
{
    if (SDL_SetRenderTarget(renderer, this->mTexture) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set render texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::Draw(SDL_Rect* destinationRectangle, SDL_Renderer* renderer, double rotationRad, SDL_RendererFlip flipping)
{
    SDL_Point actualOrigin;
    actualOrigin.x = (int)(destinationRectangle->w * originX);
    actualOrigin.y = (int)(destinationRectangle->w * originX);

    if (SDL_RenderCopyEx(renderer, this->mTexture, NULL, destinationRectangle, rotationRad, &actualOrigin, flipping) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to draw texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::Draw(SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle, SDL_Renderer* renderer, double rotationRad, SDL_RendererFlip flipping)
{
    SDL_Point actualOrigin;
    actualOrigin.x = (int)(destinationRectangle->w * originX);
    actualOrigin.y = (int)(destinationRectangle->w * originX);
    
    if (SDL_RenderCopyEx(renderer, this->mTexture, sourceRectangle, destinationRectangle, rotationRad, &actualOrigin, flipping) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to draw texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::SetBlendMode(SDL_BlendMode mode)
{
    if (SDL_SetTextureBlendMode(this->mTexture, mode) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture blend mode! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::SetAlphaMod(int alpha)
{
    if (SDL_SetTextureAlphaMod(this->mTexture, alpha) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture alpha mod! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::SetColorMod(int r, int g, int b)
{
    if (SDL_SetTextureColorMod(this->mTexture, r, g, b) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture color mod! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

void RenderTexture::Unload()
{
    SDL_DestroyTexture(this->mTexture);
    this->mTexture = NULL;
}