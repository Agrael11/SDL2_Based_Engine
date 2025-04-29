#include "ShaderManager.h"
#include "../Rendering/Shader.h"

#include <unordered_map>
#include "../Helper/Logger.h"

#include <memory>

using namespace Engine::Helper;
using namespace Engine::Managers;
using namespace Engine::Rendering;


std::unordered_map<std::string, std::unique_ptr<Shader>> m_shaders;

ShaderManager::ShaderManager()
{
}

bool ShaderManager::AddShader(std::string id, std::string vertexFilePath, std::string fragmentFilePath)
{
	if (ShaderExists(id))
	{
		Logger::log(Logger::Level::Error, "Shader {} already loaded", id);
		return false;
	}

	std::unique_ptr<Shader> shader = std::make_unique<Shader>();
	if (!shader->LoadFromFile(vertexFilePath, fragmentFilePath))
	{
		Logger::log(Logger::Level::Error, "Error loading Shader {}", id);
		shader.reset();
		return false;
	}
	
	m_shaders[id] = std::move(shader);

	return true;
}

bool ShaderManager::AddShader(std::string id, Shader& shader)
{
	if (ShaderExists(id))
	{
		Logger::log(Logger::Level::Error, "Shader {} already loaded", id);
		return false;
	}

	m_shaders[id] = std::make_unique<Shader>(std::move(shader));
	return true;
}

bool ShaderManager::ShaderExists(std::string id)
{
	return (m_shaders.count(id) > 0);
}

Shader& ShaderManager::GetShader(std::string id)
{
	if (!ShaderExists(id))
	{
		throw std::runtime_error("Shader " + id + " does not exist");
	}
	return *m_shaders[id];
}

unsigned int ShaderManager::GetShaderHandle(std::string id)
{
	if (!ShaderExists(id))
	{
		throw std::runtime_error("Shader " + id + " does not exist");
	}
	return m_shaders[id]->GetHandle();
}

bool ShaderManager::RemoveShader(std::string id)
{
	if (!ShaderExists(id))
	{
		Logger::log(Logger::Level::Error, "Shader {} does not exist", id);
		return false;
	}

	m_shaders[id]->Unload();
	m_shaders[id].reset();
	m_shaders.erase(id);
	Logger::log(Logger::Level::Info, "Removed {} from Shader Manager", id);
	return true;
}

bool ShaderManager::RemoveAll()
{
	for (auto& shader : m_shaders)
	{
		shader.second->Unload();
		shader.second.reset();
	}
	m_shaders.clear();
	Logger::log(Logger::Level::Info, "Removed all shaders from Shader Manager");
	return true;
}