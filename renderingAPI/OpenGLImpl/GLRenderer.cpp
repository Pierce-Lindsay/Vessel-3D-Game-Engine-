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

	std::expected<void, Diagnostic> GLRenderer::Register(Mesh* mesh)
	{
		auto er = RegisterMesh(mesh);
		if (!er)
			return std::unexpected(er.error());		
		return {};
	}

	std::expected<void, Diagnostic> GLRenderer::Draw(Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
	{
		// Look up the GLMesh for the given mesh using the rendering handle
		auto handle = mesh->GetRenderingHandle();
		if (!handle.has_value())
		{
			return std::unexpected(VE_ERROR_DIAGNOSTIC("Mesh has not been registered with the renderer. Cannot draw mesh."));
		}
		if (mesh->RequiresReRegister())
		{
			if (meshMap.contains(handle.value()))
				meshMap.erase(handle.value());

			auto er = RegisterMesh(mesh);
			if (!er)
				return std::unexpected(er.error());

			handle = mesh->GetRenderingHandle();
		}

		if (!handle.has_value())
			return std::unexpected(VE_ERROR_DIAGNOSTIC("Mesh has not been registered with the renderer. Cannot draw mesh."));

		const auto& glMesh = meshMap.at(handle.value());
		glMesh.Bind();

		for (auto& subMesh : mesh->GetSubMeshes())
		{

			auto material = subMesh.material;
			// Here we would set up any shader uniforms or other state needed for rendering the mesh
			auto handle = material->GetRenderingHandle();
			if (!handle.has_value())
			{
				return std::unexpected(VE_ERROR_DIAGNOSTIC("Material has not been registered with the renderer. Cannot draw mesh."));
			}

			if (material->RequiresReRegister())
			{
				if (materialMap.contains(handle.value()))
					materialMap.erase(handle.value());

				auto er = RegisterMaterial(material);
				if (!er)
					return std::unexpected(er.error());
				handle = material->GetRenderingHandle();

			}
			//clean up repeat code here later
			if (!handle.has_value())
			{
				return std::unexpected(VE_ERROR_DIAGNOSTIC("Material has not been registered with the renderer. Cannot draw mesh."));
			}

			const auto& glMaterial = materialMap.at(handle.value());
			glMaterial.Bind();

			// Here we would set any shader uniforms needed for rendering with this material, such as the color uniform
			GLUniformUtils::BindUniformVec4(material->GetColor(), "color", glMaterial.GetShaderProgram());

			//in here temporarily bind the model, view, and projection matrices as uniforms for the shader program.
			GLUniformUtils::BindUniformMat4(model, "modelMatrix", glMaterial.GetShaderProgram());
			GLUniformUtils::BindUniformMat4(view, "viewMatrix", glMaterial.GetShaderProgram());
			GLUniformUtils::BindUniformMat4(projection, "projectionMatrix", glMaterial.GetShaderProgram());

			// Render the mesh using glDrawElements with the index count from the GLMesh
			glDrawElements(GL_TRIANGLES, subMesh.size, GL_UNSIGNED_INT, reinterpret_cast<void*>(subMesh.indexOffset * sizeof(uint32_t)));
		}
		glMesh.Unbind();
		return {};
	}

	std::expected<void, Diagnostic> GLRenderer::Init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			return std::unexpected(VE_ERROR_DIAGNOSTIC("Failed to initialize GLAD"));
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); // fires callback on the same thread, stack trace works
		glDebugMessageCallback([](GLenum source, GLenum type, GLuint id, GLenum severity,
			GLsizei length, const GLchar* message, const void* userParam) {
				if (severity == GL_DEBUG_SEVERITY_HIGH)
					VE_WARN(std::format("Potential OpenGL Problem: {}", message));
			}, nullptr);

		glDisable(GL_CULL_FACE); // temporarily disable to check
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		return {};
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

	std::expected<GLuint, Diagnostic> GLRenderer::RegisterShader(const std::string& name)
	{
		if (shaderProgramMap.contains(name))
		{
			VE_WARN(std::format("Shader program {} is already registered. Returning existing handle.", name));
			return shaderProgramMap[name];
		}

		auto fullDir = shaderDirectory / name;
		auto programHandle = GLShaderUtils::CompileShader(fullDir.string());
		if (!programHandle.has_value())
		{
			return std::unexpected(VE_ERROR_DIAGNOSTIC(programHandle.error()));
		}
			
		shaderProgramMap[name] = programHandle.value();
		return programHandle.value();
	}

	std::expected<void, Diagnostic> GLRenderer::RegisterMaterial(Material* material)
	{
		//check if already registered and doesn't require reregister
		if (material->IsRegisteredWithRenderer() && !material->RequiresReRegister())
			return {};
		//register material
		GLMaterial glMaterial(material);
		// If the shader program is not already registered, this will compile and register it. Otherwise, it will return the existing handle.
		auto shaderProgramHandle = RegisterShader(material->GetShaderName());
		if (!shaderProgramHandle.has_value())
		{
			return std::unexpected(shaderProgramHandle.error());
		}
		glMaterial.SetShaderProgram(shaderProgramHandle.value());
		materialMap[materialCounter] = std::move(glMaterial);
		material->SetRenderingHandle(materialCounter);
		materialCounter++;
		return {};
	}
	std::expected<void, Diagnostic> GLRenderer::RegisterMesh(Mesh* mesh)
	{
		//register geometry
		GLMesh glMesh(mesh);
		meshMap[meshCounter] = std::move(glMesh);
		mesh->SetRenderingHandle(meshCounter);
		meshCounter++;
		
		//register materials in subMeshes
		auto diag = VE_INFO_DIAGNOSTIC("Grouping diagnostic:");
		for (auto& subMesh : mesh->GetSubMeshes())
		{
			auto err = RegisterMaterial(subMesh.material);
			if (!err)
				diag.AddAdditionalDiagnostic(err.error());
		}
		if (diag.GetSubDiagnostics().size())
			return std::unexpected(diag);
		return {};
	}
}