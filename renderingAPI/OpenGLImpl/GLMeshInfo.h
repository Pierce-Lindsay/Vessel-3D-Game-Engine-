#pragma once
#include "external/Glad/glad/glad.h"

namespace ve
{
	/// <summary>
	/// A struct for storing the OpenGL info associated with a mesh. This includes the Vertex Array Object (VAO),
	/// Vertex Buffer Object (VBO), and Element Buffer Object (EBO) handles.
	/// </summary>
	struct GLMeshInfo
	{
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		GLsizei indexCount;
	};
}