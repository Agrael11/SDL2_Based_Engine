#include "RenderTexture.h"
#include "../../Helper/Logger.h"
#include "../../Helper/format.h"
#include "Renderer.h"
#include "../../Math/MathHelper.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;
using namespace Engine::Math;

bool RenderTexture::Create(int width, int height, Renderer &renderer)
{
    Logger::Log(Logger::Info, "Creating render texture");
    this->mAccess = SDL_TEXTUREACCESS_TARGET;
    this->mTexture = SDL_CreateTexture(renderer.GetSDL_Renderer(), SDL_PIXELFORMAT_RGBA8888, this->mAccess, width, height);

    if (this->mTexture == NULL)
    {
        Logger::Log(Logger::Error, string_format("Unable to create render texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    
    this->mSize = Vector2(width, height);

    this->origin = Vector2f(0, 0);

    return true;
}

void RenderTexture::SetOrigin(float x, float y)
{
    this->origin.X = x;
    this->origin.Y = y;
}

int RenderTexture::GetWidth()
{
    return this->mSize.X;
}

int RenderTexture::GetHeight()
{
    return this->mSize.Y;
}

Vector2* RenderTexture::GetSize()
{
    return &this->mSize;
}

bool RenderTexture::SetAsRenderTarget(Renderer &renderer)
{
    if (SDL_SetRenderTarget(renderer.GetSDL_Renderer(), this->mTexture) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set render texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::Draw(Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
{
    SDL_Point actualOrigin;
    actualOrigin.x = (int)(destinationRectangle.Width * this->origin.X);
    actualOrigin.y = (int)(destinationRectangle.Height * this->origin.Y);

    //printf("Origin: %f, %f; ActualOrigin: %d, %d; destinationRectangle: %d, %d\n", this->origin.X, this->origin.Y, actualOrigin.x, actualOrigin.y, destinationRectangle.Width, destinationRectangle.Height);

    int flip = ((flipHorizontal) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE) | ((flipVertical) ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    
    rotationRad = MathHelper::RadToDeg(rotationRad);

    SDL_Rect dstRect = destinationRectangle.GetSDL_Rect();

    if (SDL_RenderCopyEx(renderer.GetSDL_Renderer(), this->mTexture, NULL, &dstRect, rotationRad, &actualOrigin, (SDL_RendererFlip)flip) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to draw texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::Draw(Rectangle &sourceRectangle, Rectangle &destinationRectangle, Renderer &renderer, double rotationRad, bool flipHorizontal, bool flipVertical)
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

bool RenderTexture::SetBlendMode(SDL_BlendMode mode)
{
    if (SDL_SetTextureBlendMode(this->mTexture, mode) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to set texture blend mode! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

bool RenderTexture::SetColorMod(Color &color)
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

void RenderTexture::Unload()
{
    SDL_DestroyTexture(this->mTexture);
    this->mTexture = NULL;
}