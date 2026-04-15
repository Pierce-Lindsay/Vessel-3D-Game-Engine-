#include "Mesh.h"


namespace ve
{
	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, Material* material)
		: vertices(vertices), indices(indices)
	{
		//1 submesh
		subMeshes.emplace_back("default", 0, indices.size(), material);
	}

	Mesh::Mesh(const std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices, const std::vector<SubMesh>& subMeshes)
		:vertices(vertices), indices(indices), subMeshes{subMeshes}
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

		/// <summary>
	/// Get a vector of the mesh's submeshes.
	/// </summary>
	/// <returns></returns>
	const std::vector<SubMesh>& Mesh::GetSubMeshes() const
	{
		return subMeshes;
	}

	/// <summary>
	/// Set the submeshes for the mesh, copies them.
	/// </summary>
	void Mesh::SetSubMeshes(const std::vector<SubMesh>& subMeshes)
	{
		this->subMeshes = subMeshes;
	}
}