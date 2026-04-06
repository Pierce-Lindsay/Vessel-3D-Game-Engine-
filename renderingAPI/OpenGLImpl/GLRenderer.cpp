#include "Glad/glad.h"
#include "external/GLFW/glfw3.h"
#include <iostream>
#include "GLRenderer.h"
#include "external/GLM/gtc/type_ptr.hpp"
#include "GLUniformUtils.h"
#include "GLShaderUtils.h"
#include "Instrumentation/logging/LogManager.h"
namespace ve
{
	GLRenderer::GLRenderer()
	{
	}

	GLRenderer::~GLRenderer()
	{

	}

	void GLRenderer::Register(Mesh* mesh)
	{
		//register geometry
		GLMesh glMesh(mesh);
		meshMap[meshCounter] = std::move(glMesh);
		mesh->SetRenderingHandle(meshCounter);
		meshCounter++;

		//register material
		auto material = mesh->GetMaterial();
		GLMaterial glMaterial(material);
		// If the shader program is not already registered, this will compile and register it. Otherwise, it will return the existing handle.
		auto shaderProgramHandle = RegisterShader(material->GetShaderName());
		if (!shaderProgramHandle.has_value())
		{
			VE_ERROR(std::format("Failed to compile shader program {}. Error: {}", material->GetShaderName(), shaderProgramHandle.error()));
			return;
		}
		glMaterial.SetShaderProgram(shaderProgramHandle.value());
		materialMap[materialCounter] = std::move(glMaterial);
		material->SetRenderingHandle(materialCounter);
		materialCounter++;
	}

	void GLRenderer::Draw(const Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{

		auto material = mesh->GetMaterial();
		// Here we would set up any shader uniforms or other state needed for rendering the mesh
		auto handle = material->GetRenderingHandle();
		if (!handle.has_value())
		{
			VE_ERROR(std::format("Material has not been registered with the renderer. Cannot draw mesh."));
			return;
		}

		const auto& glMaterial = materialMap.at(handle.value());
		glMaterial.Bind();

		// Look up the GLMesh for the given mesh using the rendering handle
		handle = mesh->GetRenderingHandle();
		if (!handle.has_value())
		{
			VE_ERROR(std::format("Mesh has not been registered with the renderer. Cannot draw mesh."));
			return;
		}
		const auto& glMesh = meshMap.at(handle.value());
		glMesh.Bind();

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

	bool GLRenderer::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			VE_ERROR("Failed to initialize GLAD");
			throw;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // fires callback on the same thread, stack trace works
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const void* userParam) {
				if (severity == GL_DEBUG_SEVERITY_HIGH)
					VE_WARN(std::format("Potential OpenGL Problem: {}", message));
			}, nullptr);

		glDisable(GL_CULL_FACE); // temporarily disable to check

		return true;
	}

	void GLRenderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void GLRenderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GLRenderer::SetBackfaceCulling(bool enabled)
	{
		if (enabled)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}

	void GLRenderer::SetDepthTesting(bool enabled)
	{
		if (enabled)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void GLRenderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	bool GLRenderer::ShutDown()
	{
		return true;
	}

	std::expected<GLuint, std::string> GLRenderer::RegisterShader(const std::string& name)
	{
		if (shaderProgramMap.contains(name))
		{
			VE_WARN(std::format("Shader program {} is already registered. Returning existing handle.", name));
			return shaderProgramMap[name];
		}

		auto fullDir = shaderDirectory / name;
		auto programHandle = GLShaderUtils::CompileShader(fullDir.string());
		if (!programHandle.has_value())
			return std::unexpected(programHandle.error());

		shaderProgramMap[name] = programHandle.value();
		return programHandle;
	}
}