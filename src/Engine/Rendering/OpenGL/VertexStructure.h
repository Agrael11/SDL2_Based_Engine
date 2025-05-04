#pragma once

#include <vector>
#include <string>

namespace Engine::Rendering
{

	class VertexStructure
	{
	private:
		std::vector<int> attributeLength;
		std::vector<int> attributeLocation;
		std::vector<std::string> attributeName;
	public:
		VertexStructure() = default;
		void AddAttribute(int length, int location, std::string name);
		const int GetAttributeLength(int index);
		const int GetAttributeLocation(int index);
		const std::string_view GetAttributeName(int index);
		int GetAttributeCount();
		int GetTotalSize();
	};
}