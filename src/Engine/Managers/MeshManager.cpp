#include "MeshManager.h"

#include "../Helper/Logger.h"
#include "../Rendering/Mesh.h"

#include <unordered_map>
#include <string>
#include <memory>

using namespace Engine::Managers;
using namespace Engine::Rendering;
using namespace Engine::Helper;

std::unordered_map<std::string, std::unique_ptr<Engine::Rendering::Mesh>> mMeshes;

bool MeshManager::AddMesh(std::string id, Engine::Rendering::Mesh& mesh)
{
	if (MeshExists(id))
	{
		Logger::log(Logger::Level::Error, "Mesh {} already loaded", id);
		return false;
	}

	mMeshes[id] = std::make_unique<Mesh>(std::move(mesh));
	return true;
}

bool MeshManager::MeshExists(std::string id)
{
	return (mMeshes.count(id) > 0);
}

Engine::Rendering::Mesh& MeshManager::GetMesh(std::string id)
{
	if (!MeshExists(id))
	{
		throw std::runtime_error("Mesh not found");
	}
	return *mMeshes[id];
}

bool MeshManager::RemoveMesh(std::string id)
{
	if (!MeshExists(id))
	{
		Logger::log(Logger::Level::Error, "Mesh {} does not exist", id);
		return false;
	}
	mMeshes[id].reset();
	mMeshes.erase(id);
	Logger::log(Logger::Level::Info, "Removed {} from Mesh Manager", id);
	return true;
}

bool MeshManager::RemoveAll()
{
	for (auto& mesh : mMeshes)
	{
		mesh.second.reset();
	}
	mMeshes.clear();
	Logger::log(Logger::Level::Info, "Removed all meshes from Meshes Manager");
	return true;
}
