#include "Audio.h"
#include "../Helper/Logger.h"

using namespace Engine::Helper;

bool Engine::Audio::InitAudio(int frequency, Uint16 format, int channels, int chunksize)
{
    if (Mix_OpenAudio(frequency, format, channels, chunksize) < 0)
    {
        Logger::Log(Logger::Error, "Error opening SDL audio. SDL_Mixer error: %s\n", Mix_GetError());
        return false;
    }
    return true;
}

void Engine::Audio::QuitAudio()
{
    Mix_Quit();
}