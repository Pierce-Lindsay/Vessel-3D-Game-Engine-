#pragma once
#include <vector>
#include "Material.h"
#include "Resource.h"
#include "SubMesh.h"
namespace ve
{
	/// <summary>
	/// A class representing a 3D mesh, 
	/// which includes vertex data, texture coordinate, normal data, 
	/// and index data for rendering.
	/// </summary>
	class Mesh : public Resource {
	public:
		/// <summary>
		/// Create a mesh with interleaved vertices
		/// 4 position
		/// 2 uv
		/// 3 normal
		/// and indices mapping triangles to the interleaved vertices.
		/// </summary>
		Mesh(const std::vector<float>& interleavedVertices, const std::vector<unsigned int>& indices, Material* material);
		Mesh(const std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices, const std::vector<SubMesh>& subMeshes);
		Mesh();
		~Mesh();
		/// <summary>
		/// Get the vertex data for the mesh.
		/// </summary>
		const std::vector<float>& GetVertices() const;
		
		/// <summary>
		/// Get the index data for the mesh.
		/// </summary>
		const std::vector<unsigned int>& GetIndices() const;

		/// Set interleaved vertices
		/// 4 position
		/// 2 uv
		/// 3 normal
		void SetVertices(const std::vector<float>& interleavedVertices);

		/// <summary>
		/// Set the indices for mapping triangles to the vertices.
		/// </summary>
		/// <param name="indices"></param>
		void SetIndices(const std::vector<unsigned int>& indices);

		/// <summary>
		/// Get a vector of the mesh's submeshes.
		/// </summary>
		/// <returns></returns>
		const std::vector<SubMesh>& GetSubMeshes() const;

		/// <summary>
		/// Set the submeshes for the mesh, copies them.
		/// </summary>
		void SetSubMeshes(const std::vector<SubMesh>& subMeshes);

	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		std::vector<SubMesh> subMeshes;
	};
}
