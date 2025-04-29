#pragma once

#include <iostream>
#include <SDL_mixer.h>
#include <memory>

namespace Engine::Audio
{
    class Music
    {
        public:
            Music() = default;
            ~Music();

            Music(const Music&) = delete;
            Music& operator=(const Music&) = delete;

            Music(Music&&) noexcept;
            Music& operator=(Music&&) noexcept;

            bool load(std::string_view path);
            void setVolume(int volume);
            bool play(int loops);
            bool play(int loops, bool override, int fadeout);
            bool pause();
            bool rewind();
            bool isPlaying();
            bool resume();
            bool stop(int fadeout);
            void unload();

    private:
        std::unique_ptr<Mix_Music, void(*)(Mix_Music*)> m_music{nullptr, Mix_FreeMusic};
    };
};