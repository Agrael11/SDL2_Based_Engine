#pragma once

#include <string>
#include <any>
#include <vector>

#include "glm/glm.hpp"

namespace Engine::Rendering
{
	class Texture;

	enum class MaterialPropertyType
	{
		None = 0,
		Float1,
		Float2,
		Float3,
		Float4,
		Matrix2x2,
		Matrix2x3,
		Matrix2x4,
		Matrix3x2,
		Matrix3x3,
		Matrix3x4,
		Matrix4x2,
		Matrix4x3,
		Matrix4x4,
		Texture,
	};

	class MaterialProperty
	{
	private:
		std::string propertyName = "";
		std::any propertyValue;
		MaterialPropertyType propertyType = MaterialPropertyType::None;
		bool isVector = false;

	public:
		MaterialProperty()
		{
			propertyName = "";
			propertyValue = 0.0f;
			propertyType = MaterialPropertyType::None;
			isVector = false;
		}
		MaterialProperty(std::string name, std::vector<double> value);
		MaterialProperty(std::string name, std::vector<glm::vec2> value);
		MaterialProperty(std::string name, std::vector<glm::vec3> value);
		MaterialProperty(std::string name, std::vector<glm::vec4> value);
		MaterialProperty(std::string name, glm::mat2x2 value);
		MaterialProperty(std::string name, glm::mat2x3 value);
		MaterialProperty(std::string name, glm::mat2x4 value);
		MaterialProperty(std::string name, glm::mat3x2 value);
		MaterialProperty(std::string name, glm::mat3x3 value);
		MaterialProperty(std::string name, glm::mat3x4 value);
		MaterialProperty(std::string name, glm::mat4x2 value);
		MaterialProperty(std::string name, glm::mat4x3 value);
		MaterialProperty(std::string name, glm::mat4x4 value);
		MaterialProperty(std::string name, std::string value);

		std::string GetName();
		std::any GetValue();
		MaterialPropertyType GetType();
		bool IsVector();
	};
};