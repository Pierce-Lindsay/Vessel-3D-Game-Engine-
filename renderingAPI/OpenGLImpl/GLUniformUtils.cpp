#include "GLUniformUtils.h"

namespace ve
{
	void GLUniformUtils::BindUniformMat4(const glm::mat4& matrix, const std::string& name, GLuint program)
	{
		glUniformMatrix4fv(glGetUniformLocation(program,
			name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void GLUniformUtils::BindUniform1i(int b, const std::string& name, GLuint program)
	{
		glUniform1i(glGetUniformLocation(program,
			name.c_str()), b);
	}

	void GLUniformUtils::BindUniformVec4(const glm::vec4& v, const std::string& name, GLuint program)
	{
		glUniform4fv(glGetUniformLocation(program,
			name.c_str()), 1, glm::value_ptr(v));
	}

	void GLUniformUtils::BindUniform1f(float f, const std::string& name, GLuint program)
	{
		glUniform1f(glGetUniformLocation(program,
			name.c_str()), f);
	}
}