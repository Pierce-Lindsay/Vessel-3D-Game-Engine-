#pragma once
#include "external/Glad/glad/glad.h"
#include "Rendering/Material.h"
#include <string>

namespace ve
{
	class GLMaterial
	{
	private:
		GLuint shaderProgram = 0; // The OpenGL shader program handle for this material
		std::string shaderName = "";


	public:

		/// <summary>
		/// Create an OpenGL material from the given Material.
		/// This constructor does NOT compile the shader program. 
		/// It only saves the shader name and other material properties for later use.
		/// </summary>
		/// <param name="material"></param>
		GLMaterial(Material* material);
		~GLMaterial();

		/// <summary>
		/// Initialize with default values. 
		/// This constructor is used when we want to create a GLMaterial
		/// without a corresponding Material.
		/// </summary>
		GLMaterial();

		/// <summary>
		/// Get the OpenGL shader program handle for this material.
		/// </summary>
		/// <returns></returns>
		GLuint GetShaderProgram() const;

		/// <summary>
		/// Get the name of the shader associated with this material. 
		/// This is used to look up the shader program
		/// </summary>
		const std::string& GetShaderName() const;

		/// <summary>
		/// Bind all neccessary OpenGL state for rendering with this material. 
		/// This will bind the shader program and set any necessary uniforms.
		/// </summary>
		void Bind() const;

		/// <summary>
		/// Set any necessary shader uniforms for rendering with this material.
		/// </summary>
		void SetUniforms() const;

		/// <summary>
		/// Set the OpenGL shader program handle for this material.
		/// </summary>
		/// <param name="shaderProgram"></param>
		void SetShaderProgram(GLuint shaderProgram);

	};
}