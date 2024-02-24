#include "TextureManager.h"

#include <unordered_map>
#include "Helper/Logger.h"

using namespace std;
using namespace Engine::Rendering;
using namespace Engine::Helper;

static std::unordered_map<std::string, Engine::Rendering::ImageTexture> mImageTextures;
static std::unordered_map<std::string, Engine::Rendering::RenderTexture> mRenderTextures;
static std::unordered_map<std::string, Engine::Rendering::Texture> mBasicTextures;

TextureManager::TextureManager()
{

}

bool TextureManager::AddTexture(std::string id, std::string filename, Engine::Rendering::Renderer& renderer)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::Log(Logger::Error, "Texture " + id + " (IT) already loaded");
		return false;
	}

	ImageTexture texture;
	if (!texture.Load(filename, renderer))
	{
		return false;
	}

	mImageTextures[id] = texture;
	Logger::Log(Logger::Info, "Added new " + id + " (IT) to Texture Manager");
	
	return true;
}

bool TextureManager::AddTexture(std::string id, int width, int height, Engine::Rendering::Renderer& renderer)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::Log(Logger::Error, "Texture " + id + " (RT) already loaded");
		return false;
	}

	RenderTexture texture;
	if (!texture.Create(width, height, renderer))
	{
		return false;
	}

	mRenderTextures[id] = texture;
	Logger::Log(Logger::Info, "Added new " + id + " (RT) to Texture Manager");

	return true;
}

bool TextureManager::AddTexture(std::string id, ImageTexture texture)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::Log(Logger::Error, "Texture " + id + " (IT)already loaded");
		return false;
	}

	mImageTextures[id] = texture;
	Logger::Log(Logger::Info, "Added " + id + " (IT) to Texture Manager");

	return true;
}

bool TextureManager::AddTexture(std::string id, RenderTexture texture)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::Log(Logger::Error, "Texture " + id + " (RT) already loaded");
		return false;
	}

	mRenderTextures[id] = texture;
	Logger::Log(Logger::Info, "Added " + id + " (RT)to Texture Manager");

	return true;
}

bool TextureManager::AddTexture(std::string id, Texture texture)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::Log(Logger::Error, "Texture " + id + " already loaded");
		return false;
	}

	mBasicTextures[id] = texture;
	Logger::Log(Logger::Info, "Added " + id + " to Texture Manager");

	return true;
}

bool TextureManager::TextureExists(std::string id)
{
	return ((mImageTextures.count(id) > 0) || (mRenderTextures.count(id) > 0) || (mBasicTextures.count(id) > 0));
}

TextureManager::TextureType TextureManager::GetTextureType(std::string id)
{
	if (mImageTextures.count(id) > 0)
	{
		return TextureType::ImageTextureType;
	}
	else if (mRenderTextures.count(id) > 0)
	{
		return TextureType::RenderTextureType;
	}
	else if (mBasicTextures.count(id) > 0)
	{
		return TextureType::BasicTextureType;
	}
	else
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}
}

Texture& TextureManager::GetTexture(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}

	switch (TextureManager::GetTextureType(id))
	{
		case TextureManager::TextureType::BasicTextureType:
			return mBasicTextures[id];
			break;
		case TextureManager::TextureType::ImageTextureType:
			return mImageTextures[id];
			break;
		case TextureManager::TextureType::RenderTextureType:
			return mRenderTextures[id];
			break;
		default:
			throw std::runtime_error("Texture " + id + " is of unknown type");
	}
}

ImageTexture& TextureManager::GetImageTexture(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}
	switch (TextureManager::GetTextureType(id))
	{
	case TextureManager::TextureType::ImageTextureType:
		return mImageTextures[id];
		break;
	default:
		throw std::runtime_error("Texture " + id + " is not ImageTexture");
		break;
	}
}

RenderTexture& TextureManager::GetRenderTexture(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}
	switch (TextureManager::GetTextureType(id))
	{
	case TextureManager::TextureType::RenderTextureType:
		return mRenderTextures[id];
		break;
	default:
		throw std::runtime_error("Texture " + id + " is not ImageTexture");
		break;
	}
}

bool TextureManager::RemoveTexture(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		Logger::Log(Logger::Warning, "Texture " + id + " does not exist");
		return false;
	}
	switch (TextureManager::GetTextureType(id))
	{
	case TextureManager::TextureType::BasicTextureType:
		mBasicTextures[id].Unload();
		mBasicTextures.erase(id);
		break;
	case TextureManager::TextureType::ImageTextureType:
		mImageTextures[id].Unload();
		mImageTextures.erase(id);
		break;
	case TextureManager::TextureType::RenderTextureType:
		mRenderTextures[id].Unload();
		mRenderTextures.erase(id);
		break;
	}
	return true;
}

bool TextureManager::RemoveAll()
{
	for (auto& texture: mBasicTextures)
	{
		texture.second.Unload();
	}
	for (auto& texture : mImageTextures)
	{
		texture.second.Unload();
	}
	for (auto& texture : mRenderTextures)
	{
		texture.second.Unload();
	}
	mBasicTextures.clear();
	mImageTextures.clear();
	mRenderTextures.clear();
	return true;
}