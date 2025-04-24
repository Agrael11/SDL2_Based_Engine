#pragma once

#include <iostream>

#include "Texture.h"

namespace Engine::Rendering
{
    class ImageTexture: public Texture
    {
    private:
    public:
        std::string name;
        bool Load(std::string filePath);
        void Unload();
    };
};