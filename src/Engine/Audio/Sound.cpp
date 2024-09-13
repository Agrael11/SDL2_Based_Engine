#include "../Helper/Logger.h"

#include "Sound.h"

using namespace Engine::Helper;
using namespace Engine::Audio;

Sound::~Sound()
{
    unload();
}

Sound::Sound(Sound&& other) noexcept
    : m_chunk(std::move(other.m_chunk)), m_channel(other.m_channel)
{
    other.m_channel = -1;
}

Sound& Sound::operator=(Sound&& other) noexcept
{
    if (this != &other)
    {
        m_chunk = std::move(other.m_chunk);
        m_channel = other.m_channel;

        other.m_channel = -1;
    }
    return *this;
}

bool Sound::load(std::string_view path)
{
    this->unload();

    Mix_Chunk* chunk = Mix_LoadWAV(path.data());
    if (chunk == nullptr)
    {
        Logger::log(Logger::Level::Error, "Failed to load sound chunk file {}! SDL_Mixer Error: {}", path.data(), Mix_GetError());
        return false;
    }
    this->m_chunk.reset(chunk);
    return true;
}

bool Sound::play(int loops)
{
    int channel = Mix_PlayChannel(-1, this->m_chunk.get(), loops);
    if (channel == -1)
    {
        Logger::log(Logger::Level::Error, "Failed to play sound! SDL_Mixer Error: {}", Mix_GetError());
        return false;
    }
    this->m_channel = channel;
    return true;
}

bool Sound::play(int loops, int volume)
{
    int channel = Mix_PlayChannel(-1, this->m_chunk.get(), loops);
    if (channel == -1)
    {
        Logger::log(Logger::Level::Error, "Failed to play sound! SDL_Mixer Error: {}", Mix_GetError());
        return false;
    }
    Mix_Volume(channel, volume);
    this->m_channel = channel;
    return true;
}

bool Sound::isPlaying()
{
    return Mix_Playing(this->m_channel) != 0;
}

bool Sound::stop()
{
    if (Mix_HaltChannel(this->m_channel) == 0)
    {
        Logger::log(Logger::Level::Error, "Failed to stop sound! SDL_Mixer Error: {}", Mix_GetError());
        return false;
    }
    return true;
}

void Sound::unload()
{
    if (this->m_chunk)
    {
        m_chunk.reset();
    }
}