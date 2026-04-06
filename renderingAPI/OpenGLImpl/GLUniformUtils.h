#pragma once
#include <external/Glad/glad/glad.h>
#include <external/GLM/gtc/type_ptr.hpp>
#include <string>

namespace ve
{
	/// <summary>
	/// A static utility class for binding uniform variables to shader programs in OpenGL.
	/// </summary>
	class GLUniformUtils
	{
	public:
		/// <summary>
		/// Bind a 4x4 matrix uniform variable to a shader program. 
		/// The uniform variable is identified by its name,
		/// </summary>
		static void BindUniformMat4(const glm::mat4& matrix, const std::string& name, GLuint program);
		/// <summary>
		/// Bind an integer uniform variable to a shader program.
		/// </summary>
		static void BindUniform1i(int b, const std::string& name, GLuint program);

		/// <summary>
		/// Bind a vec4 uniform variable to a shader program.
		/// </summary>
		static void BindUniformVec4(const glm::vec4& v, const std::string& name, GLuint program);

		/// <summary>
		/// Bind a float uniform variable to a shader program.
		/// </summary>
		static void BindUniform1f(float f, const std::string& name, GLuint program);
	};
}