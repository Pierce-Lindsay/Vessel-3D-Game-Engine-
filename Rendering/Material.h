#pragma once
#include <string>
#include "external/GLM/glm.hpp"
#include "Resource.h"
namespace ve
{
	/// <summary>
	/// A class representing the material properties for rendering a mesh. 
	/// This includes the shader to be used and the color of the material.
	/// </summary>
	class Material : public Resource
	{
	private:
		std::string shaderName;
		glm::vec4 color;

	public:
		Material(const std::string& shaderName, const glm::vec4& color);
		~Material();

		/// <summary>
		/// Get the name of the shader associated with this material. 
		/// This is used to determine which shader program to use when rendering a mesh with this material.
		/// </summary>
		const std::string& GetShaderName() const;

		/// <summary>
		/// Get the color of the material. 
		/// This is a simple representation of the material's color properties, 
		/// which can be used in the shader to determine how the material should be rendered.
		/// </summary>
		const glm::vec4& GetColor() const;

		/// <summary>
		/// Set the color of the material.
		/// </summary>
		void SetColor(const glm::vec4& color);
	};
}


