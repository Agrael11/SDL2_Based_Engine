#pragma once

#include <iostream>

#include "../../Math/Vector2.h"

namespace Engine::Rendering
{
    enum class TextureFilter
    {
        Nearest,
        Linear,
        NearestMipmapNearest,
        LinearMipmapNearest,
        NearestMipmapLinear,
        LinearMipmapLinear
    };

    enum class TextureWrap
    {
        Repeat,
        MirroredRepeat,
        ClampToEdge,
        ClampToBorder
    };
    class Renderer;
    class Texture
    {
    protected:
        unsigned int mTexture = -1;
        Engine::Math::Vector2 mSize;
        TextureFilter mMinFilterMode = TextureFilter::Linear;
        TextureFilter mMagFilterMode = TextureFilter::Linear;
		TextureWrap mWrapModeS = TextureWrap::ClampToEdge;
        TextureWrap mWrapModeT = TextureWrap::ClampToEdge;
        bool mipmapping = false;
    public:
        TextureWrap& GetTextureWrapS();
        TextureWrap& GetTextureWrapT();
        static bool IsFilterMipmapping(TextureFilter& filter);
        static uint32_t TextureFilterToInt(TextureFilter& filter);
        static uint32_t TextureWrapToInt(TextureWrap& wrap);
        TextureFilter& GetMinTextureFilter();
        TextureFilter& GetMagTextureFilter();
        void SetTextureWrapMode(TextureWrap wrapModeS, TextureWrap wrapModeT);
		void SetTextureFilterMode(TextureFilter minFilter, TextureFilter magFilter);
        void Activate(int id, int location);
        int GetWidth();
        int GetHeight();
        Engine::Math::Vector2 GetSize();
        unsigned int GetHandle();
        virtual void Unload();
    };
};