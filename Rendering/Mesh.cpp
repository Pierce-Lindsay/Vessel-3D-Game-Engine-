#include "Mesh.h"


namespace ve
{
	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<float>& texcoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices, Material* material)
		: vertices(vertices), texCoords(texcoords), normals(normals), indices(indices), material(material)
	{
	}
	Mesh::Mesh()
	{
	}
	Mesh::~Mesh()
	{
	}

	const std::vector<float>& Mesh::GetVertices() const { return vertices; }
	const std::vector<float>& Mesh::GetNormals() const { return normals; }
	const std::vector<float>& Mesh::GetTexCoords() const { return texCoords; }

	const std::vector<unsigned int>& Mesh::GetIndices() const { return indices; }
	const size_t Mesh::GetRenderingHandle() const { return renderingHandle; }
	void Mesh::SetRenderingHandle(size_t handle) { renderingHandle = handle; }
	Material* Mesh::GetMaterial() const { return material; }
}