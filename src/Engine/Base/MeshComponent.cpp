#include "MeshComponent.h"

using namespace Engine::Base;

MeshComponent::MeshComponent()
{
	this->mName = "DefaultMesh";
}

std::string MeshComponent::GetMeshName()
{
	return this->mName;
}

void MeshComponent::SetMeshName(const std::string& mesh_name)
{
	this->mName = mesh_name;
}