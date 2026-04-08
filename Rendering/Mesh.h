#pragma once
#include <vector>
#include "Material.h"
#include "Resource.h"
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
		//Mesh(const std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices, Material* material);
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
		/// Get the material for the mesh.
		/// </summary>
		/// <returns></returns>
		Material* GetMaterial() const;

	private:
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		
		Material* material; // The material for the mesh, which could include shader information and other rendering properties
	};
}
