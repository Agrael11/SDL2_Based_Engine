#include "../Helper/Logger.h"

#include "Music.h"

using namespace Engine::Helper;
using namespace Engine::Audio;

Music::~Music()
{
    unload();
}

Music::Music(Music&& other) noexcept
    : m_music(std::move(other.m_music))
{
}

// Move assignment operator
Music& Music::operator=(Music&& other) noexcept
{
    if (this != &other)
    {
        m_music = std::move(other.m_music);
    }
    return *this;
}

bool Music::load(std::string_view path)
{
    this->unload();

    Mix_Music* mixMusic = Mix_LoadMUS(path.data());
    if (mixMusic == nullptr)
    {
        Logger::log(Logger::Level::Error, "Failed to load music file {}! SDL_Mixer Error: {}", path.data(), Mix_GetError());
        return false;
    }
    this->m_music.reset(mixMusic);
    return true;
}

void Music::setVolume(int volume)
{
    Mix_VolumeMusic(volume);
}

bool Music::play(int loops)
{
    if (Mix_PlayingMusic())
    {
        Logger::log(Logger::Level::Error, "Music is already playing.");
        return false;
    }
    if (Mix_PlayMusic(this->m_music.get(), loops) != 0)
    {
        Logger::log(Logger::Level::Error, "Failed to play music! SDL_Mixer Error: {}", Mix_GetError());
        return false;
    }
    return true;
}

bool Music::play(int loops, bool override, int fadeout)
{
    if (Mix_PlayingMusic())
    {
        if (!override)
        {
            Logger::log(Logger::Level::Error, "Music is already playing.");
            return false;
        }

        if (fadeout > 0)
        {
            Mix_FadeOutMusic(fadeout);
        }
        else
        {
            Mix_HaltMusic();
        }
    }
    if (Mix_PlayMusic(this->m_music.get(), loops) != 0)
    {
        Logger::log(Logger::Level::Error, "Failed to play music! SDL_Mixer Error: {}", Mix_GetError());
        return false;
    }
    return true;
}

bool Music::pause()
{
    if (Mix_PlayingMusic() == 0)
    {
        Logger::log(Logger::Level::Error, "No music is playing.");
        return false;
    }
    if (Mix_PausedMusic())
    {
        Logger::log(Logger::Level::Info, "Music already paused.");
        return true;
    }
    Mix_PauseMusic();
    return true;
}

bool Music::rewind()
{
    if (Mix_PlayingMusic() == 0)
    {
        Logger::log(Logger::Level::Error, "No music is playing.");
        return false;
    }
    Mix_RewindMusic();
    return true;
}

bool Music::isPlaying()
{
    return (Mix_PlayingMusic() == 1 || Mix_PausedMusic() == 0);

}

bool Music::resume()
{
    if (Mix_PlayingMusic() == 0)
    {
        Logger::log(Logger::Level::Error, "No music is playing.");
        return false;
    }
    if (Mix_PausedMusic() == 0)
    {
        Logger::log(Logger::Level::Info, "Music is not paused.");
        return true;
    }
    Mix_ResumeMusic();
    return true;
}

bool Music::stop(int fadeout)
{
    if (Mix_PlayingMusic() == 0)
    {
        Logger::log(Logger::Level::Error, "No music is playing.");
        return false;
    }
    if (fadeout > 0)
    {
        Mix_FadeOutMusic(fadeout);
        return true;
    }
    Mix_HaltMusic();
    return true;
}

void Music::unload()
{
    if (this->m_music)
    {
        this->m_music.reset();
    }
}