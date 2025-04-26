#include "MaterialProperty.h"
#include "Texture.h"
#include "../../Helper/Logger.h"

using namespace Engine::Rendering;

MaterialProperty::MaterialProperty(std::string name, std::vector<double> value)
{
	propertyName = name;
	propertyType = MaterialPropertyType::Float1;
	if (value.size() == 1)
	{
		propertyValue = value[0];
	}
	else
	{
		propertyValue = value;
		isVector = true;
	}
}

MaterialProperty::MaterialProperty(std::string name, std::vector<glm::vec2> value)
{
	propertyName = name;
	propertyType = MaterialPropertyType::Float2;
	if (value.size() == 1)
	{
		propertyValue = value[0];
	}
	else
	{
		propertyValue = value;
		isVector = true;
	}
}


MaterialProperty::MaterialProperty(std::string name, std::vector<glm::vec3> value)
{
	propertyName = name;
	propertyType = MaterialPropertyType::Float3;
	if (value.size() == 1)
	{
		propertyValue = value[0];
	}
	else
	{
		propertyValue = value;
		isVector = true;
	}
}


MaterialProperty::MaterialProperty(std::string name, std::vector<glm::vec4> value)
{
	propertyName = name;
	propertyType = MaterialPropertyType::Float4;
	if (value.size() == 1)
	{
		propertyValue = value[0];
	}
	else
	{
		propertyValue = value;
		isVector = true;
	}
}

MaterialProperty::MaterialProperty(std::string name, glm::mat2x2 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix2x2;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat2x3 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix2x3;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat2x4 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix2x4;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat3x2 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix3x2;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat3x3 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix3x3;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat3x4 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix3x4;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat4x2 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix4x2;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat4x3 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix4x3;
}

MaterialProperty::MaterialProperty(std::string name, glm::mat4x4 value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Matrix4x4;
}

MaterialProperty::MaterialProperty(std::string name, std::string value)
{
	propertyName = name;
	propertyValue = value;
	propertyType = MaterialPropertyType::Texture;
}

std::string MaterialProperty::GetName()
{
	return propertyName;
}

MaterialPropertyType MaterialProperty::GetType()
{
	return propertyType;
}

std::any MaterialProperty::GetValue()
{
	return propertyValue;
}

bool MaterialProperty::IsVector()
{
	return isVector;
}