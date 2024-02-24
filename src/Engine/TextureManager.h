#pragma once

#include "Rendering/Renderer.h"
#include "Rendering/RenderTexture.h"
#include "Rendering/ImageTexture.h"
#include "Rendering/Texture.h"

class TextureManager
{
	private:
		TextureManager();

	public:
		enum class TextureType { ImageTextureType, RenderTextureType, BasicTextureType };

		static bool AddTexture(std::string id, std::string filename, Engine::Rendering::Renderer& renderer);
		static bool AddTexture(std::string id, int width, int height, Engine::Rendering::Renderer& renderer);
		static bool AddTexture(std::string id, Engine::Rendering::Texture texture);
		static bool AddTexture(std::string id, Engine::Rendering::RenderTexture texture);
		static bool AddTexture(std::string id, Engine::Rendering::ImageTexture texture);

		static bool TextureExists(std::string id);

		static TextureType GetTextureType(std::string id);
		static Engine::Rendering::Texture& GetTexture(std::string id);
		static Engine::Rendering::ImageTexture& GetImageTexture(std::string id);
		static Engine::Rendering::RenderTexture& GetRenderTexture(std::string id);

		static bool RemoveTexture(std::string id);
		static bool RemoveAll();
};