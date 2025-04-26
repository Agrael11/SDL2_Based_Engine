#pragma once

#include <string>

namespace Engine::Rendering
{
	class Shader;
}

namespace Engine::Managers
{
	class ShaderManager
	{
	private:
		ShaderManager();

	public:
		static bool AddShader(std::string id, std::string vertexFilePath, std::string fragmentFilePath);
		static bool AddShader(std::string id, Engine::Rendering::Shader& shader);

		static bool ShaderExists(std::string id);

		static Engine::Rendering::Shader& GetShader(std::string id);
		static unsigned int GetShaderHandle(std::string id);

		static bool RemoveShader(std::string id);
		static bool RemoveAll();
	};
};