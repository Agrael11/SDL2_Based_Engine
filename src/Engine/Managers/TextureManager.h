#pragma once

#include <string>

namespace Engine::Rendering
{
	class Texture;
	class ImageTexture;
	class RenderTexture;
};

namespace Engine::Managers
{
	class TextureManager
	{
	private:
		TextureManager();

	public:
		enum class TextureType { ImageTextureType, RenderTextureType, BasicTextureType };

		static bool AddTexture(std::string id, std::string filename);
		static bool AddTexture(std::string id, int width, int height);
		static bool AddTexture(std::string id, Engine::Rendering::Texture& texture);
		static bool AddTexture(std::string id, Engine::Rendering::RenderTexture& texture);
		static bool AddTexture(std::string id, Engine::Rendering::ImageTexture& texture);

		static bool TextureExists(std::string id);

		static TextureType GetTextureType(std::string id);
		template <typename T>
		static T& GetTexture(std::string id);
		static unsigned int GetTextureHandle(std::string id);

		static bool RemoveTexture(std::string id);
		static bool RemoveAll();
	};
};