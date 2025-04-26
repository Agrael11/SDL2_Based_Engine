#pragma once

#include <memory>
#include <string>
#include <unordered_map>


namespace Engine::Rendering
{
	class MaterialProperty;

	class Material
	{
	private:
		std::string mShaderID;
		std::unordered_map<std::string, MaterialProperty> mProperties;
		bool ApplyProperty(uint32_t shader, MaterialProperty& property, int& textureID);

	public:
		void SetShader(std::string shaderID);
		std::string GetShader();

		void SetProperty(std::string name, MaterialProperty& property);
		bool PropertyExists(std::string);
		MaterialProperty& GetProperty(std::string name);

		bool Apply();
		bool Reset();
	};
};