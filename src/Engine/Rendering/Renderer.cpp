#include "Renderer.h"
#include "../Helper/format.h"
#include "../Helper/Logger.h"

using namespace Engine::Helper;
using namespace Engine::Rendering;

SDL_Renderer* Renderer::GetSDL_Renderer()
{
    return this->mRenderer;
}

void Renderer::Init(SDL_Window* window, Uint32 flags)
{
    this->mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
}

void Renderer::Begin()
{

}

void Renderer::End()
{
    SDL_RenderPresent(this->mRenderer);
}

bool Renderer::DrawSprite(Sprite* sprite, SDL_Rect* destination, SDL_Rect* source, double rotation, SDL_RendererFlip flipping)
{
    if (source == NULL)
    {
        return sprite->Draw(destination, this->mRenderer, rotation, flipping);
    }
    return sprite->Draw(source, destination, this->mRenderer, rotation, flipping);
}

bool Renderer::DrawRenderTexture(RenderTexture* renderTexture, SDL_Rect* destination, SDL_Rect* source, double rotation, SDL_RendererFlip flipping)
{
    if (source == NULL)
    {
        return renderTexture->Draw(destination, this->mRenderer, rotation, flipping);
    }
    return renderTexture->Draw(source, destination, this->mRenderer, rotation, flipping);
}

void Renderer::Clean(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(this->mRenderer, r, g, b, a);
    SDL_RenderClear(this->mRenderer);
}
    
void Renderer::SetViewport(int x, int y, int width, int height)
{
    SDL_Rect viewport;
    viewport.x = x;
    viewport.y = y;
    viewport.w = width;
    viewport.h = height;
    SDL_RenderSetViewport(this->mRenderer, &viewport);
}

bool  Renderer::SetRenderTarget(RenderTexture* texture)
{
    return texture->SetAsRenderTarget(this->mRenderer);
}
bool Renderer::CleanRenderTarget()
{
    if (SDL_SetRenderTarget(this->mRenderer, NULL) != 0)
    {
        Logger::Log(Logger::Error, string_format("Unable to clean render texture! SDL Error: %s", SDL_GetError()));
        return false;
    }
    return true;
}

void Renderer::Destroy()
{
    SDL_DestroyRenderer(this->mRenderer);
    this->mRenderer = NULL;
}