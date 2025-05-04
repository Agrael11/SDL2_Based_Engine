#include "Texture.h"

#include <iostream>
#include "glad/glad.h"

#include "../../Math/Vector2.h"
#include "../../Helper/Logger.h"

using namespace Engine::Math;
using namespace Engine::Helper;
using namespace Engine::Rendering;

unsigned int Texture::GetHandle()
{
    return this->mTexture;
}

TextureWrap& Texture::GetTextureWrapS()
{
	return this->mWrapModeS;
}

TextureWrap& Texture::GetTextureWrapT()
{
	return this->mWrapModeT;
}

uint32_t Texture::TextureWrapToInt(TextureWrap& wrap)
{
	switch (wrap)
	{
	case TextureWrap::Repeat:
		return GL_REPEAT;
	case TextureWrap::MirroredRepeat:
		return GL_MIRRORED_REPEAT;
	case TextureWrap::ClampToEdge:
		return GL_CLAMP_TO_EDGE;
	case TextureWrap::ClampToBorder:
		return GL_CLAMP_TO_BORDER;
	default:
		return GL_REPEAT;
	}
}

TextureFilter& Texture::GetMinTextureFilter()
{
	return this->mMinFilterMode;
}
TextureFilter& Texture::GetMagTextureFilter()
{
	return this->mMagFilterMode;
}

uint32_t Texture::TextureFilterToInt(TextureFilter& filter)
{
	switch (filter)
	{
	case TextureFilter::Nearest:
		return GL_NEAREST;
	case TextureFilter::Linear:
		return GL_LINEAR;
	case TextureFilter::NearestMipmapNearest:
		return GL_NEAREST_MIPMAP_NEAREST;
	case TextureFilter::LinearMipmapNearest:
		return GL_LINEAR_MIPMAP_NEAREST;
	case TextureFilter::NearestMipmapLinear:
		return GL_NEAREST_MIPMAP_LINEAR;
	case TextureFilter::LinearMipmapLinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		return GL_LINEAR;
	}
}

void Texture::SetTextureWrapMode(TextureWrap wrapModeS, TextureWrap wrapModeT)
{
	this->mWrapModeS = wrapModeS;
	this->mWrapModeT = wrapModeT;
	glBindTexture(GL_TEXTURE_2D, this->mTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToInt(wrapModeS));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToInt(wrapModeT));
	glBindTexture(GL_TEXTURE_2D, 0);

}

bool Texture::IsFilterMipmapping(TextureFilter& filter)
{
	if (filter == TextureFilter::NearestMipmapNearest ||
		filter == TextureFilter::LinearMipmapNearest ||
		filter == TextureFilter::NearestMipmapLinear ||
		filter == TextureFilter::LinearMipmapLinear)
	{
		return true;
	}
	return false;
}

void Texture::SetTextureFilterMode(TextureFilter minFilter, TextureFilter magFilter)
{
	this->mMinFilterMode = minFilter;
	this->mMagFilterMode = magFilter;
	glBindTexture(GL_TEXTURE_2D, this->mTexture);
	if (IsFilterMipmapping(minFilter) || IsFilterMipmapping(magFilter))
	{
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureFilterToInt(this->mMinFilterMode));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureFilterToInt(this->mMagFilterMode));
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Activate(int id, int location)
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, this->mTexture);
	glUniform1i(location, id);
}

int Texture::GetWidth()
{
    return this->mSize.X;
}

int Texture::GetHeight()
{
    return this->mSize.Y;
}

Vector2 Texture::GetSize()
{
    return this->mSize;
}

void Texture::Unload()
{
    glDeleteTextures(1, &this->mTexture);
}