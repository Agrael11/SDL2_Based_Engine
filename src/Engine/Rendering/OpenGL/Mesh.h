#pragma once

#include <vector>
#include "VertexStructure.h"

namespace Engine::Rendering
{
	enum class MeshType
	{
		Static,
		Dynamic,
		Stream
	};
	enum class MeshDrawMode
	{
		Points,
		Lines,
		LineStrip,
		Triangles,
		TriangleStrip
	};

	class Mesh
	{
	private:
		MeshType mType = MeshType::Static;
		MeshDrawMode mDrawMode = MeshDrawMode::Triangles;
		VertexStructure mVertexStructure;
		uint32_t mVertexBuffer = -1;
		uint32_t mVertexArray = -1;
		uint32_t mIndexBuffer = -1;
		uint32_t mIndicesCount = 0;


	public:
		Mesh(MeshType type, MeshDrawMode drawMode, VertexStructure vertexStructure, std::vector<float>& vertices, std::vector<uint32_t> indicies);
		~Mesh();
		void SetVertices(std::vector<float>& vertices);
		void SetIndicies(std::vector<uint32_t>& indices);
		void UpdateVerticesSubBuffer(std::vector<float>& vertices, int offset);
		void UpdateIndicesSubBuffer(std::vector<uint32_t>& vertices, int offset);
		void UpdateVerticesBuffer(std::vector<float>& vertices, int offset = 0);
		void UpdateIndicesBuffer(std::vector<uint32_t>& vertices, int offset = 0);
		MeshType GetType();
		void SetDrawMode(MeshDrawMode drawMode);
		MeshDrawMode GetDrawMode();
		void Draw();
		void Bind();
		void Unbind();

	};
}