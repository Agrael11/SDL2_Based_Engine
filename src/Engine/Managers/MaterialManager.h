#pragma once

#include <string>

namespace Engine::Rendering
{
	class Material;
}

namespace Engine::Managers
{
	class MaterialManager
	{
	private:
		MaterialManager();

	public:
		static bool AddMaterial(std::string id, Engine::Rendering::Material& material);

		static bool MaterialExists(std::string id);

		static Engine::Rendering::Material& GetMaterial(std::string id);
		
		static bool RemoveMaterial(std::string id);
		static bool RemoveAll();
	};
};