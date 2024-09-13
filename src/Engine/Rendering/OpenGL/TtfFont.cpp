#include "TtfFont.h"

#include <SDL_ttf.h>
#include "../../Helper/Logger.h"

using namespace Engine::Rendering;
using namespace Engine::Helper;

bool TtfFont::Load(std::string filePath, int size, Renderer &renderer)
{
    Logger::log(Logger::Level::Info, "Loading font {}...", filePath.c_str());
    this->mFont = TTF_OpenFont(filePath.c_str(), size);
    if (this->mFont == NULL)
    {
        Logger::log(Logger::Level::Error, "Could not load font {}. SDL_ttf Error: {}!", filePath.c_str(), TTF_GetError());
        return false;
    }

    return true;
}

TTF_Font* TtfFont::GetFont()
{
    return this->mFont;
}

void TtfFont::Unload()
{
    TTF_CloseFont(this->mFont);
    this->mFont = NULL;
}