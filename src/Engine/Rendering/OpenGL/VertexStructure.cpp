#include "VertexStructure.h"

using Engine::Rendering::VertexStructure;

void VertexStructure::AddAttribute(int length, int location, std::string name)
{
	this->attributeLength.push_back(length);
	this->attributeLocation.push_back(location);
	this->attributeName.push_back(name);
}

const int VertexStructure::GetAttributeLength(int index)
{
	return this->attributeLength[index];
}

const int VertexStructure::GetAttributeLocation(int index)
{
	return this->attributeLocation[index];
}

const std::string_view VertexStructure::GetAttributeName(int index)
{
	return this->attributeName[index];
}

int VertexStructure::GetAttributeCount()
{
	return static_cast<int>(this->attributeLength.size());
}

int VertexStructure::GetTotalSize()
{
	int totalSize = 0;
	for (int i = 0; i < this->attributeLength.size(); i++)
	{
		totalSize += this->attributeLength[i];
	}
	return totalSize;
}