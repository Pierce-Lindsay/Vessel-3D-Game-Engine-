#pragma once
#include "GLMeshInfo.h"
#include "Rendering/Mesh.h"

namespace ve
{
	/// <summary>
	/// An OpenGL implementation of a mesh for rendering. 
	/// This class is responsible for building the OpenGL components 
	/// for a given Mesh and providing methods for binding and unbinding the mesh for rendering.
	/// </summary>
	class GLMesh
	{
	public:

		/// <summary>
		/// Build the OpenGL components for the mesh. 
		/// Save the VAO, VBO, and EBO handles in the GLMeshInfo struct for later use.
		/// </summary>
		/// <param name="mesh"></param>
		GLMesh(const Mesh* mesh);

		/// <summary>
		/// Build a default GLMesh with no geometry. 
		/// This can be used as a placeholder or for meshes 
		/// that will have their geometry set up later.
		/// </summary>
		GLMesh();


		~GLMesh();



		/// <summary>
		/// Bind the mesh for rendering. This will bind the VAO and set up the vertex attributes.
		/// </summary>
		void Bind() const;

		/// <summary>
		/// Unbind the mesh. This will unbind the VAO.
		/// </summary>
		void Unbind() const;

		/// <summary>
		/// Get the number of indices in the mesh. 
		/// This is used for rendering the mesh with glDrawElements.
		/// </summary>
		GLsizei GetIndexCount() const;

	private:

		/// <summary>
		/// Build the vertex buffer object (VBO) for the mesh.
		/// </summary>
		void buildVBO(const std::vector<float>& vertices);
		/// <summary>
		/// Build the element buffer object (EBO) for the mesh.
		/// </summary>
		/// <param name="indices"></param>
		void buildEBO(const std::vector<unsigned int>& indices);

		/// <summary>
		/// Build the attributes for the mesh. 
		/// This will set up the vertex attribute pointers for the vertex data in the VBO.
		/// </summary>
		void buildAttributes();

		GLMeshInfo info;
	};
}