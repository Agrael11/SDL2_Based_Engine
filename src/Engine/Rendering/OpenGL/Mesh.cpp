#include "Mesh.h"
#include "../../Helper/Logger.h"

#include <cstring>

#include "VertexStructure.h"
#include "glad/glad.h"	

using namespace Engine::Rendering;
using namespace Engine::Helper;

Mesh::Mesh(MeshType type, MeshDrawMode drawMode, VertexStructure vertexStructure, std::vector<float>& vertices, std::vector<uint32_t> indicies)
	: mType(type), mDrawMode(drawMode), mVertexStructure(vertexStructure)
{
	//Set variables
	this->mType = type;
	this->mDrawMode = drawMode;
	this->mVertexStructure = vertexStructure;
	this->mVertexArray = -1;
	this->mVertexBuffer = -1;
	this->mIndexBuffer = -1;

	// Create Vertex Array Object
	glGenVertexArrays(1, &this->mVertexArray);
	if (this->mVertexArray == -1)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to create Vertex Array Object");
		return;
	}

	glBindVertexArray(this->mVertexArray);
	auto error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to bind Vertex Array Object {}", error);
		return;
	}

	// Create Vertex Buffer Object
	glGenBuffers(1, &this->mVertexBuffer);
	if (this->mVertexBuffer == -1)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to create Vertex Buffer Object");
		return;
	}	

	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to bind Vertex Buffer Object {}", error);
		return;
	}


	// Create Index Buffer Object
	glGenBuffers(1, &this->mIndexBuffer);
	if (this->mIndexBuffer == -1)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to create Index Buffer Object");
		return;
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIndexBuffer);
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to bind Index Buffer Object {}", error);
		return;
	}

	// Set vertex data
	switch (this->mType)
	{
	case MeshType::Static:
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		break;
	case MeshType::Dynamic:
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
		break;
	case MeshType::Stream:
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STREAM_DRAW);
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Unknown MeshType");
		break;
	}
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to set vertex data {}", error);
		return;
	}

	// Set index data
	switch (this->mType)
	{
	case MeshType::Static:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STATIC_DRAW);
		break;
	case MeshType::Dynamic:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_DYNAMIC_DRAW);
		break;
	case MeshType::Stream:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STREAM_DRAW);
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Unknown MeshType");
		break;
	}
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to set index data {}", error);
		return;
	}

	this->mIndicesCount = static_cast<uint32_t>(indicies.size());

		// Set vertex attributes
	int totalSize = this->mVertexStructure.GetTotalSize() * sizeof(float);
	int location = 0;
	for (int i = 0; i < this->mVertexStructure.GetAttributeCount(); i++)
	{
		int pointer = this->mVertexStructure.GetAttributeLocation(i);
		int length = this->mVertexStructure.GetAttributeLength(i);
		glVertexAttribPointer(pointer, length, GL_FLOAT, GL_FALSE, totalSize, (void*)(uintptr_t(location)));
		glEnableVertexAttribArray(pointer);
		location += length * sizeof(float);
	}
	error = glGetError();
	if (error != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Mesh() - Failed to set vertex attributes {}", error);
		return;
	}

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	// Delete buffers
	if (this->mVertexArray != 1)
	{
		glDeleteVertexArrays(1, &this->mVertexArray);
	}
	if (this->mVertexBuffer != -1)
	{
		glDeleteBuffers(1, &this->mVertexBuffer);
	}
	if (this->mIndexBuffer != -1)
	{
		glDeleteBuffers(1, &this->mIndexBuffer);
	}
}

void Mesh::SetVertices(std::vector<float>& vertices)
{
	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	// Set vertex data
	switch (this->mType)
	{
	case MeshType::Static:
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		break;
	case MeshType::Dynamic:
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_DRAW);
		break;
	case MeshType::Stream:
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STREAM_DRAW);
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::SetVertices() - Unknown MeshType");
		break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::SetVertices() - Failed to set vertex data {}", glError);
		return;
	}
}

void Mesh::SetIndicies(std::vector<unsigned int>& indicies)
{
	// Bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIndexBuffer);
	// Set index data
	switch (this->mType)
	{
	case MeshType::Static:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STATIC_DRAW);
		break;
	case MeshType::Dynamic:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_DYNAMIC_DRAW);
		break;
	case MeshType::Stream:
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size() * sizeof(uint32_t), indicies.data(), GL_STREAM_DRAW);
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::Setindicies() - Unknown MeshType");
		break;
	}

	this->mIndicesCount = static_cast<uint32_t>(indicies.size());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::SetIndices() - Failed to set index data {}", glError);
		return;
	}
}

void Mesh::UpdateVerticesSubBuffer(std::vector<float>& vertices, int offset)
{
	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	// Set vertex data
	switch (this->mType)
	{
	case MeshType::Static:
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), vertices.size() * sizeof(float), vertices.data());
		break;
	case MeshType::Dynamic:
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), vertices.size() * sizeof(float), vertices.data());
		break;
	case MeshType::Stream:
		glBufferSubData(GL_ARRAY_BUFFER, offset * sizeof(float), vertices.size() * sizeof(float), vertices.data());
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::UpdateVerticesSubBuffer() - Unknown MeshType");
		break;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::UpdateVerticesSubBuffer() - Failed to set vertex data {}", glError);
		return;
	}
}

void Mesh::UpdateIndicesSubBuffer(std::vector<uint32_t>& vertices, int offset) 
{
	// Bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIndexBuffer);
	// Set index data
	switch (this->mType)
	{
	case MeshType::Static:
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), vertices.size() * sizeof(uint32_t), vertices.data());
		break;
	case MeshType::Dynamic:
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), vertices.size() * sizeof(uint32_t), vertices.data());
		break;
	case MeshType::Stream:
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset * sizeof(uint32_t), vertices.size() * sizeof(uint32_t), vertices.data());
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::UpdateIndicesSubBuffer() - Unknown MeshType");
		break;
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::UpdateIndicesSubBuffer() - Failed to set index data {}", glError);
		return;
	}
}

void Mesh::UpdateVerticesBuffer(std::vector<float>& vertices, int offset)
{
	// Bind vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	// Set vertex data
	void* ptr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (ptr)
	{
		memcpy((char*)ptr + offset * sizeof(float), vertices.data(), vertices.size() * sizeof(float));
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}
	else
	{
		Logger::log(Logger::Level::Error, "Mesh::UpdateVerticesBuffer() - Failed to map buffer");
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::UpdateVerticesBuffer() - Failed to set vertex data {}", glError);
		return;
	}
}

void Mesh::UpdateIndicesBuffer(std::vector<uint32_t>& vertices, int offset)
{
	// Bind index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIndexBuffer);
	// Set index data
	void* ptr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	if (ptr)
	{
		memcpy((char*)ptr + offset * sizeof(uint32_t), vertices.data(), vertices.size() * sizeof(uint32_t));
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}
	else
	{
		Logger::log(Logger::Level::Error, "Mesh::UpdateIndicesBuffer() - Failed to map buffer");
	}
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::UpdateIndicesBuffer() - Failed to set index data {}", glError);
		return;
	}
}

MeshType Mesh::GetType()
{
	return this->mType;
}

void Mesh::SetDrawMode(MeshDrawMode drawMode)
{
	this->mDrawMode = drawMode;
}

MeshDrawMode Mesh::GetDrawMode()
{
	return this->mDrawMode;
}

void Mesh::Draw()
{
	glBindVertexArray(this->mVertexArray);
	switch (this->mDrawMode)
	{
	case MeshDrawMode::Points:
		glDrawElements(GL_POINTS, this->mIndicesCount, GL_UNSIGNED_INT, (void*)0);
		break;
	case MeshDrawMode::Lines:
		glDrawElements(GL_LINES, this->mIndicesCount, GL_UNSIGNED_INT, (void*)0);
		break;
	case MeshDrawMode::LineStrip:
		glDrawElements(GL_LINE_STRIP, this->mIndicesCount, GL_UNSIGNED_INT, (void*)0);
		break;
	case MeshDrawMode::Triangles:
		glDrawElements(GL_TRIANGLES, this->mIndicesCount, GL_UNSIGNED_INT, (void*)0);
		break;
	case MeshDrawMode::TriangleStrip:
		glDrawElements(GL_TRIANGLE_STRIP, this->mIndicesCount, GL_UNSIGNED_INT, (void*)0);
		break;
	default:
		Logger::log(Logger::Level::Error, "Mesh::Draw() - Unknown MeshDrawMode");
		break;
	}

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Draw() - Failed to draw mesh {}", glError);
		return;
	}
}

void Mesh::Bind()
{
	glBindVertexArray(this->mVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIndexBuffer);

	auto glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		Logger::log(Logger::Level::Error, "Mesh::Bind() - Failed to bind mesh {}", glError);
		return;
	}
}

void Mesh::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}