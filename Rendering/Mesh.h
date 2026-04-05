#pragma once
#include <vector>
#include "Material.h"

namespace ve
{
	class Mesh {
	public:
		Mesh(const std::vector<float>& vertices, const std::vector<float>& texCoords, const std::vector<float>& normals, const std::vector<unsigned int>& indices, Material* material);
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
		/// Get the rendering handle for the mesh.
		/// </summary>
		const size_t GetRenderingHandle() const;

		/// <summary>
		/// Set the rendering handle for the mesh.
		/// </summary>
		void SetRenderingHandle(size_t handle);

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

		size_t renderingHandle; // This could be an OpenGL handle or similar
		Material* material; // The material for the mesh, which could include shader information and other rendering properties
	};
}
