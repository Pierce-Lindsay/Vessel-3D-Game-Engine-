#pragma once
#include <external/Glad/glad/glad.h>
#include <external/GLM/gtc/type_ptr.hpp>
#include <string>

namespace ve
{
	class GLUniformUtils
	{
	public:
		static void BindUniformMat4(glm::mat4 matrix, std::string name, GLuint program);
		static void BindUniform1i(int b, std::string name, GLuint program);
		static void BindUniformVec4(glm::vec4 v, std::string name, GLuint program);
		static void BindUniform1f(float f, std::string name, GLuint program);
	};
}