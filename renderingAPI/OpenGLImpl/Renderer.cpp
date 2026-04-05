#include "Glad/glad.h"
#include "external/GLFW/glfw3.h"
#include <iostream>
#include "Renderer.h"
#include "external/GLM/gtc/type_ptr.hpp"
#include "GLUniformUtils.h"
#include "GLShaderUtils.h"
#include "Instrumentation/files/FileUtils.h"
#include "Instrumentation/logging/LogManager.h"
namespace ve
{
	RendererOpenGL::RendererOpenGL()
	{
	}

	RendererOpenGL::~RendererOpenGL()
	{

	}

	void RendererOpenGL::Register(Mesh* mesh)
	{
		//register geometry
		GLMesh glMesh(mesh);
		meshMap[meshCounter] = std::move(glMesh);
		mesh->SetRenderingHandle(meshCounter);
		meshCounter++;
		//register material
		GLMaterial glMaterial(mesh->GetMaterial());
		//change this later, temporary!!!
		auto shadersDir = FileUtils::GetPathToMarker("engine.root") / "assets" / "shaders";
		VE_LOG(std::format("Expected shaderDir: {}", shadersDir.string()));
		auto shaderName = glMaterial.GetShaderName();
		if (!shaderProgramMap.contains(shaderName))
		{
			auto fullDir = shadersDir / (shaderName);
			glMaterial.SetShaderProgram(GLShaderUtils::CompileShader(fullDir.string()));
			shaderProgramMap[shaderName] = glMaterial.GetShaderProgram();
		}
		else
		{
			glMaterial.SetShaderProgram(shaderProgramMap[shaderName]);
		}
		materialMap[materialCounter] = std::move(glMaterial);
		mesh->GetMaterial()->SetRenderingHandle(materialCounter);
		materialCounter++;
	}

	void RendererOpenGL::Draw(const Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{

		auto material = mesh->GetMaterial();
		// Here we would set up any shader uniforms or other state needed for rendering the mesh
		const auto& glMaterial = materialMap.at(mesh->GetMaterial()->GetRenderingHandle());
		glMaterial.Bind();

		// Look up the GLMesh for the given mesh using the rendering handle
		const auto& glMesh = meshMap.at(mesh->GetRenderingHandle());
		glMesh.Bind();

		// later add logic to check if program is already in use to avoid redundant calls to glUseProgram
		// Here we would set any shader uniforms needed for rendering with this material, such as the color uniform
		GLUniformUtils::BindUniformVec4(material->GetColor(), "color", glMaterial.GetShaderProgram());

		//in here temporarily bind the model, view, and projection matrices as uniforms for the shader program.
		GLUniformUtils::BindUniformMat4(model, "modelMatrix", glMaterial.GetShaderProgram());
		GLUniformUtils::BindUniformMat4(view, "viewMatrix", glMaterial.GetShaderProgram());
		GLUniformUtils::BindUniformMat4(projection, "projectionMatrix", glMaterial.GetShaderProgram());

		// Render the mesh using glDrawElements with the index count from the GLMesh
		glDrawElements(GL_TRIANGLES, glMesh.GetIndexCount(), GL_UNSIGNED_INT, 0);
		glMesh.Unbind();
	}

	bool RendererOpenGL::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << '\n';
			return false;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // fires callback on the same thread, stack trace works
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const void* userParam) {
				if (severity == GL_DEBUG_SEVERITY_HIGH)
					std::cerr << "OpenGL Error: " << message << std::endl;
			}, nullptr);

		glDisable(GL_CULL_FACE); // temporarily disable to check

		return true;
	}

	void RendererOpenGL::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void RendererOpenGL::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void RendererOpenGL::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	bool RendererOpenGL::ShutDown()
	{
		return true;
	}
}