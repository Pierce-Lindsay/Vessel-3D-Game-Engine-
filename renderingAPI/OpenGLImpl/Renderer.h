#pragma once
#include "IRenderer.h"
#include "GLMesh.h"
#include "GLMaterial.h"
#include <unordered_map>

namespace ve
{
	class RendererOpenGL : public IRenderer
	{
	public:
		RendererOpenGL();
		~RendererOpenGL();
		/// <summary>
		/// Register a mesh for rendering. Automatically builds the OpenGL components for the mesh 
		/// and saves the handle to the mesh in the Mesh class for later use. 
		/// The handle is used to look up the GLMesh for rendering.
		/// </summary>
		/// <param name="mesh"></param>
		void Register(Mesh* mesh) override;
		void Draw(const Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;
		bool Init() override;
		bool ShutDown() override;

		void SetClearColor(const glm::vec4& color) override;

		void Clear() override;

		void SetViewport(int x, int y, int width, int height) override;

	private:
		std::unordered_map<size_t, GLMesh> meshMap;
		std::unordered_map<size_t, GLMaterial> materialMap;
		size_t materialCounter = 0;
		std::unordered_map<std::string, GLuint> shaderProgramMap; // Map from shader name to shader program handle
		size_t meshCounter = 0;
	};
}