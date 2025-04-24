#pragma once

#include "Texture.h"

namespace Engine::Rendering
{
    class RenderTexture: public Texture
    {
    private:
        unsigned int mFrameBuffer = -1;
    public:
        bool Create(int width, int height);
        bool SetAsRenderTarget();
        void Unload();
    };
};