#pragma once
#include "external/Glad/glad/glad.h"

namespace ve
{
	struct GLMeshInfo
	{
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
		GLsizei indexCount;
	};
}