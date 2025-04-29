#include "Material.h"
#include "MaterialProperty.h"

#include "glad/glad.h"

#include "../../Managers/ShaderManager.h"
#include "../../Managers/TextureManager.h"

#include "Shader.h"
#include "Texture.h"
#include "../../Helper/Logger.h"

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"


using namespace Engine::Rendering;

void Material::SetShader(std::string shaderID)
{
	this->mShaderID = shaderID;
}

std::string Material::GetShader()
{
	return this->mShaderID;	
}

void Material::SetProperty(std::string name, MaterialProperty& property)
{
	mProperties[name] = property;
}

bool Material::PropertyExists(std::string name)
{
	return mProperties.find(name) != mProperties.end();
}

MaterialProperty& Material::GetProperty(std::string name)
{
	if (!PropertyExists(name))
	{
		Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Warning, "Material property {} doesn't exists.", name);
	}

	return mProperties[name];
}





bool Material::Apply()
{
	try
	{
		Shader& shader = Engine::Managers::ShaderManager::GetShader(mShaderID);
		shader.UseShader();
		uint32_t shaderHandle = shader.GetHandle();
		int textureId = 0;
		for (auto& [propertyName, property] : mProperties)
		{
			if (!ApplyProperty(shaderHandle, property, textureId))
			{
				Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Error, "Failed to apply material property: {}", propertyName);
				return false;
			}
		}
	}
	catch (const std::bad_any_cast& e)
	{
		Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Fatal, "Failed to apply Material", e.what());
		return false;
	}
	return true;
}

bool Material::Reset()
{

	try
	{
		Shader& shader = Engine::Managers::ShaderManager::GetShader(mShaderID);
		shader.UseShader();
		uint32_t shaderHandle = shader.GetHandle();
		int textureId = 0;
		for (auto& [propertyName, property] : mProperties)
		{
			if (property.GetType() == MaterialPropertyType::Texture)
			{
				glActiveTexture(GL_TEXTURE0 + textureId);
				glBindTexture(GL_TEXTURE_2D, 0);
				textureId++;
			}
			if (glGetError() != GL_NO_ERROR)
			{
				Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Error, "Failed to reset material property: {}", propertyName);
				return false;
			}
		}
	}
	catch (const std::bad_any_cast& e)
	{
		Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Fatal, "Failed to reset Material", e.what());
		return false;
	}
	return true;
}

bool Material::ApplyProperty(uint32_t shader, MaterialProperty& property, int& textureID)
{
	uint32_t location = glGetUniformLocation(shader, property.GetName().c_str());
	MaterialPropertyType type = property.GetType();
	bool vector = property.IsVector();
	std::any value = property.GetValue();
	switch (type)
	{
	case MaterialPropertyType::Float1:
		if (vector)
		{
			std::vector<float> vec = std::any_cast<std::vector<float>>(value);
			glUniform1fv(location, static_cast<GLsizei>(vec.size()), vec.data());
		}
		else
		{
			glUniform1f(location, std::any_cast<float>(value));
		}
		break;
	case MaterialPropertyType::Float2:
		if (vector)
		{
			std::vector<glm::vec2> vec = std::any_cast<std::vector<glm::vec2>>(value);
			std::vector<float> vec_flattenned;
			for (int i = 0; i < vec.size(); i++)
			{
				vec_flattenned.push_back(vec[i].x);
				vec_flattenned.push_back(vec[i].y);
			}
			glUniform2fv(location, static_cast<GLsizei>(vec.size()), vec_flattenned.data());
		}
		else
		{
			glm::vec2 vec = std::any_cast<glm::vec2>(value);
			glUniform2f(location, vec.x, vec.y);
		}
		break;
	case MaterialPropertyType::Float3:
		if (vector)
		{
			std::vector<glm::vec3> vec = std::any_cast<std::vector<glm::vec3>>(value);
			std::vector<float> vec_flattenned;
			for (int i = 0; i < vec.size(); i++)
			{
				vec_flattenned.push_back(vec[i].x);
				vec_flattenned.push_back(vec[i].y);
				vec_flattenned.push_back(vec[i].z);
			}
			glUniform3fv(location, static_cast<GLsizei>(vec.size()), vec_flattenned.data());
		}
		else
		{
			glm::vec3 vec = std::any_cast<glm::vec3>(value);
			glUniform3f(location, vec.x, vec.y, vec.z);
		}
		break;
	case MaterialPropertyType::Float4:
		if (vector)
		{
			std::vector<glm::vec4> vec = std::any_cast<std::vector<glm::vec4>>(value);
			std::vector<float> vec_flattenned;
			for (int i = 0; i < vec.size(); i++)
			{
				vec_flattenned.push_back(vec[i].x);
				vec_flattenned.push_back(vec[i].y);
				vec_flattenned.push_back(vec[i].z);
				vec_flattenned.push_back(vec[i].w);
			}
			glUniform4fv(location, static_cast<GLsizei>(vec.size()), vec_flattenned.data());
		}
		else
		{
			glm::vec4 vec = std::any_cast<glm::vec4>(value);
			glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
		}
		break;
	case MaterialPropertyType::Matrix2x2:
		glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat2x2>(value)));
		break;
	case MaterialPropertyType::Matrix2x3:
		glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat2x3>(value)));
		break;
	case MaterialPropertyType::Matrix2x4:
		glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat2x4>(value)));
		break;
	case MaterialPropertyType::Matrix3x2:
		glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat3x2>(value)));
		break;	
	case MaterialPropertyType::Matrix3x3:
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat3x3>(value)));
		break;
	case MaterialPropertyType::Matrix3x4:
		glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat3x4>(value)));
		break;
	case MaterialPropertyType::Matrix4x2:
		glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat4x2>(value)));
		break;
	case MaterialPropertyType::Matrix4x3:
		glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat4x3>(value)));
		break;
	case MaterialPropertyType::Matrix4x4:
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(std::any_cast<glm::mat4x4>(value)));
		break;
	case MaterialPropertyType::Texture:
		GLint maxTextureUnits;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureUnits);
		if (textureID >= maxTextureUnits)
		{
			Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Error, "Texture ID limit reached ({}). Cannot bind more textures.", maxTextureUnits);
			return false;
		}
		try
		{
			Texture& texture = Engine::Managers::TextureManager::GetTexture<Texture>(std::any_cast<std::string>(value));
			glActiveTexture(GL_TEXTURE0 + textureID);
			glBindTexture(GL_TEXTURE_2D, texture.GetHandle());
			glUniform1i(location, textureID);
			textureID++;
		}
		catch (const std::bad_any_cast& e)
		{
			Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Error, "Failed to cast texture name: {}", e.what());
			return false;
		}
	}

	if (glGetError() != GL_NO_ERROR)
	{
		Engine::Helper::Logger::log(Engine::Helper::Logger::Level::Error, "OpenGL error while applying material property: {}", property.GetName());
		return false;
	}
	return true;
}