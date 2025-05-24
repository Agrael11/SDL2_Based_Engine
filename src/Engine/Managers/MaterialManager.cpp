#include "MaterialManager.h"

#include <unordered_map>
#include <memory>
#include "../Helper/Logger.h"

#include "../Rendering/Material.h"


using namespace Engine::Helper;
using namespace Engine::Managers;
using namespace Engine::Rendering;


std::unordered_map<std::string, std::unique_ptr<Material>> m_materials;

MaterialManager::MaterialManager()
{
}

bool MaterialManager::AddMaterial(std::string id, Material& material)
{
	if (MaterialExists(id))
	{
		Logger::log(Logger::Level::Error, "Material {} already loaded", id);
		return false;
	}

	m_materials[id] = std::make_unique<Material>(std::move(material));
	return true;
}

bool MaterialManager::MaterialExists(std::string id)
{
	return (m_materials.count(id) > 0);
}

Material& MaterialManager::GetMaterial(std::string id)
{
	if (!MaterialExists(id))
	{
		throw std::runtime_error("Material " + id + " does not exist");
	}
	return *m_materials[id];
}

bool MaterialManager::RemoveMaterial(std::string id)
{
	if (!MaterialExists(id))
	{
		Logger::log(Logger::Level::Error, "Material {} does not exist", id);
		return false;
	}

	m_materials[id].reset();
	m_materials.erase(id);
	Logger::log(Logger::Level::Info, "Removed {} from Material Manager", id);
	return true;
}

bool MaterialManager::RemoveAll()
{
	for (auto& shader : m_materials)
	{
		shader.second.reset();
	}
	m_materials.clear();
	Logger::log(Logger::Level::Info, "Removed all materials from Material Manager");
	return true;
}