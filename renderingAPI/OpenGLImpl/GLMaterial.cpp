#include "GLMaterial.h"

namespace ve
{
	GLMaterial::GLMaterial(Material* material)
	{
		shaderName = material->GetShaderName();
	}

	GLMaterial::GLMaterial()
	{
		shaderName = "default.shader";
	}

	GLMaterial::~GLMaterial()
	{
		// Here we would delete the shader program
	}
	GLuint GLMaterial::GetShaderProgram() const
	{
		return shaderProgram;
	}

	const std::string& GLMaterial::GetShaderName() const
	{
		return shaderName;
	}

	void GLMaterial::Bind() const
	{
		//Get the current shader program to avoid redundant calls to glUseProgram
		GLint currentProgram;
		glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);

		if (currentProgram != shaderProgram)
		{
			glUseProgram(shaderProgram);
		}

		SetUniforms();
	}

	void GLMaterial::SetUniforms() const
	{
	}

	void GLMaterial::SetShaderProgram(GLuint shaderProgram)
	{
		this->shaderProgram = shaderProgram;
	}
}