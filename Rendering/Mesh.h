#pragma once
#include <vector>
#include "Material.h"
#include "Resource.h"
namespace ve
{
	/// <summary>
	/// A class representing a 3D mesh, 
	/// which includes vertex data, normal data, texture coordinate data, 
	/// and index data for rendering.
	/// </summary>
	class Mesh : public Resource {
	public:
		Mesh(const std::vector<float>& vertices, const std::vector<float>& texCoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices, Material* material);
		//Mesh(const std::vector<float>& interleavedVertices, std::vector<unsigned int>& indices, Material* material);
		Mesh();
		~Mesh();
		/// <summary>
		/// Get the vertex data for the mesh.
		/// </summary>
		const std::vector<float>& GetVertices() const;
		/// <summary>
		 /// Get the normal data for the mesh.
		 /// </summary>
		const std::vector<float>& GetNormals() const;
		/// <summary>
		/// Get the texture coordinate data for the mesh.
		///		
		const std::vector<float>& GetTexCoords() const;
		/// <summary>
		/// Get the index data for the mesh.
		/// </summary>
		const std::vector<unsigned int>& GetIndices() const;

		/// <summary>
		/// Get the material for the mesh.
		/// </summary>
		/// <returns></returns>
		Material* GetMaterial() const;

	private:
		std::vector<float> vertices;
		std::vector<float> normals;
		std::vector<float> texCoords;
		std::vector<unsigned int> indices;
	
		Material* material; // The material for the mesh, which could include shader information and other rendering properties
	};
}
