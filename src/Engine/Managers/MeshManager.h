#pragma once

#include "../Rendering/Mesh.h"
#include <string>

namespace Engine::Managers
{
	class MeshManager
	{
	private:
		MeshManager() = default;
	public:
		static bool AddMesh(std::string id, Engine::Rendering::Mesh& mesh);
		
		static bool MeshExists(std::string id);
		
		static Engine::Rendering::Mesh& GetMesh(std::string id);

		static bool RemoveMesh(std::string id);
		static bool RemoveAll();
	};
}