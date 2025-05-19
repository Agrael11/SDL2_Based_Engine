#include "MaterialComponent.h"

using namespace Engine::Base;

MaterialComponent::MaterialComponent()
{
	this->mName = "DefaultMaterial";
}

std::string MaterialComponent::GetMaterialName()
{
	return this->mName;
}

void MaterialComponent::SetMaterialName(const std::string& material_name)
{
	this->mName = material_name;
}