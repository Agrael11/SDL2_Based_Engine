#include "TextureManager.h"

#include <unordered_map>
#include "../Helper/Logger.h"
#include "../Rendering/RenderTexture.h"
#include "../Rendering/ImageTexture.h"
#include "../Rendering/Texture.h"
using namespace std;
using namespace Engine::Rendering;
using namespace Engine::Helper;
using namespace Engine::Managers;

static std::unordered_map<std::string, std::unique_ptr<Engine::Rendering::Texture>> mTextures;

TextureManager::TextureManager()
{

}

bool TextureManager::AddTexture(std::string id, std::string filename)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::log(Logger::Level::Error, "Texture {} (IT) already loaded", id);
		return false;
	}

	std::unique_ptr<ImageTexture> texture = std::make_unique<ImageTexture>();
	if (!texture->Load(filename))
	{
		texture.reset();
		return false;
	}

	mTextures[id] = std::move(texture);
	Logger::log(Logger::Level::Info, "Added new {} (IT) to Texture Manager", id);
	
	return true;
}

bool TextureManager::AddTexture(std::string id, int width, int height)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::log(Logger::Level::Error, "Texture {} (RT) already loaded", id);
		return false;
	}

	RenderTexture texture;
	if (!texture.Create(width, height))
	{
		return false;
	}

	mTextures[id] = std::make_unique<Engine::Rendering::RenderTexture>(std::move(texture));;
	Logger::log(Logger::Level::Info, "Added new {} (RT) to Texture Manager", id);

	return true;
}

bool TextureManager::AddTexture(std::string id, ImageTexture& texture)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::log(Logger::Level::Error, "Texture {} (IT) already loaded", id);
		return false;
	}

	mTextures[id] = std::make_unique<Engine::Rendering::ImageTexture>(std::move(texture));;
	Logger::log(Logger::Level::Info, "Added {} (IT) to Texture Manager", id);

	return true;
}

bool TextureManager::AddTexture(std::string id, RenderTexture& texture)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::log(Logger::Level::Error, "Texture {} (RT) already loaded", id);
		return false;
	}

	mTextures[id] = std::make_unique<Engine::Rendering::RenderTexture>(std::move(texture));;
	Logger::log(Logger::Level::Info, "Added {} (RT) to Texture Manager", id);

	return true;
}

bool TextureManager::AddTexture(std::string id, Texture& texture)
{
	if (TextureManager::TextureExists(id))
	{
		Logger::log(Logger::Level::Error, "Texture {} already loaded", id);
		return false;
	}

	mTextures[id] = std::make_unique<Engine::Rendering::Texture>(std::move(texture));;
	Logger::log(Logger::Level::Info, "Added {} to Texture Manager", id);

	return true;
}

bool TextureManager::TextureExists(std::string id)
{
	return (mTextures.count(id) > 0);
}

TextureManager::TextureType TextureManager::GetTextureType(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}

	Texture* texture = mTextures[id].get();
	if (dynamic_cast<RenderTexture*>(texture))
	{
		return TextureType::RenderTextureType;
	}
	if (dynamic_cast<ImageTexture*>(texture))
	{
		return TextureType::ImageTextureType;
	}
	return TextureType::BasicTextureType;
}

template <typename T>
T& TextureManager::GetTexture(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}

	Texture* texture = mTextures[id].get();

	if (dynamic_cast<T*>(texture))
	{
		return *static_cast<T*>(texture);
	}
	else
	{
		throw std::runtime_error("Texture " + id + " is not of the requested type");
	}
}

template RenderTexture& TextureManager::GetTexture<RenderTexture>(std::string);
template ImageTexture& TextureManager::GetTexture<ImageTexture>(std::string);
template Texture& TextureManager::GetTexture<Texture>(std::string);

unsigned int TextureManager::GetTextureHandle(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		throw std::runtime_error("Texture " + id + " does not exist");
	}
	
	return mTextures[id]->GetHandle();
}


bool TextureManager::RemoveTexture(std::string id)
{
	if (!(TextureManager::TextureExists(id)))
	{
		Logger::log(Logger::Level::Warning, "Texture {} does not exist", id);
		return false;
	}

	mTextures[id]->Unload();
	mTextures[id].reset();
	mTextures.erase(id);
	return true;
}

bool TextureManager::RemoveAll()
{
	for (auto& texture: mTextures)
	{
		texture.second->Unload();
		texture.second.reset();
	}
	mTextures.clear();
	return true;
}