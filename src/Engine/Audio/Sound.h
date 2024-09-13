#pragma once

#include <iostream>
#include <SDL_mixer.h>

namespace Engine::Audio
{
    class Sound
    {
        public:
            Sound() = default;
            ~Sound();

            Sound(const Sound&) = delete;
            Sound& operator=(const Sound&) = delete;

            Sound(Sound&&) noexcept;
            Sound& operator=(Sound&&) noexcept;

            bool load(std::string_view path);
            bool play(int loops);
            bool play(int loops, int volume);
            bool isPlaying();
            bool stop();
            void unload();

        private:
            std::unique_ptr<Mix_Chunk, void(*)(Mix_Chunk*)> m_chunk{ nullptr, Mix_FreeChunk };
            int m_channel = -1;
    };
};