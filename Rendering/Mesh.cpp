#include "Mesh.h"


namespace ve
{
	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Material* material)
		: vertices(vertices), indices(indices), material(material)
	{
	}

	//Mesh::Mesh(const std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices, Material* material)
	//{
	//
	//}
	Mesh::Mesh()
	{
	}
	Mesh::~Mesh()
	{
	}

	const std::vector<float>& Mesh::GetVertices() const { return vertices; }

	const std::vector<unsigned int>& Mesh::GetIndices() const { return indices; }
	Material* Mesh::GetMaterial() const { return material; }

	void Mesh::SetVertices(const std::vector<float>& interleavedVertices)
	{
		vertices = interleavedVertices;
		SetRequiresReRegister();
	}

	void Mesh::SetIndices(const std::vector<unsigned int>& indices)
	{
		this->indices = indices;
		SetRequiresReRegister();
	}
}