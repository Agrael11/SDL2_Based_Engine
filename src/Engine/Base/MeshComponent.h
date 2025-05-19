#pragma once

#include <string>
#include "IComponent.h"

namespace Engine::Base
{
	class MeshComponent : public IComponent
	{
	public:
		MeshComponent();
		~MeshComponent() override {}
		void Update(float deltaTime) override {}
		std::string GetMeshName();
		void SetMeshName(const std::string& mesh_name);
	private:
		std::string mName;
	};
}