#pragma once

#include <string>
#include "IComponent.h"

namespace Engine::Base
{
	class MaterialComponent : public IComponent
	{
	public:
		MaterialComponent();
		~MaterialComponent() override = default;
		std::string GetMaterialName();
		void SetMaterialName(const std::string& material_name);
	
	private:
		std::string mName;	
	};
}