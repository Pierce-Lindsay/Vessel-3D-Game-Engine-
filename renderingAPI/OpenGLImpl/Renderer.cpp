#include "Glad/glad.h"
#include "external/GLFW/glfw3.h"
#include <iostream>
#include "Renderer.h"
namespace ve
{
	RendererOpenGL::RendererOpenGL()
	{
	}

	RendererOpenGL::~RendererOpenGL()
	{

	}

	void RendererOpenGL::Render()
	{

	}

	bool RendererOpenGL::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << '\n';
			return false;
		}
		return true;
	}

	bool RendererOpenGL::ShutDown()
	{
		return true;
	}
}