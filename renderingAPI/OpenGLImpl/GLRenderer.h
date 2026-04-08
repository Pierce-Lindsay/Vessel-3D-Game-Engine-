#pragma once
#include "Renderer.h"
#include "GLMesh.h"
#include "GLMaterial.h"
#include <unordered_map>
#include <expected>

namespace ve
{
	class GLRenderer : public Renderer
	{
	public:
		GLRenderer();
		~GLRenderer();
		/// <summary>
		/// Register a mesh for rendering. Automatically builds the OpenGL components for the mesh 
		/// and saves the handle to the mesh in the Mesh class for later use. 
		/// The handle is used to look up the GLMesh for rendering.
		/// </summary>
		/// <param name="mesh"></param>
		void Register(Mesh* mesh) override;

		void Draw(Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) override;
		bool Init() override;
		bool ShutDown() override;

		void SetClearColor(const glm::vec4& color) override;

		void Clear() override;

		void SetViewport(int x, int y, int width, int height) override;

		void SetBackfaceCulling(bool enabled) override;

		void SetDepthTesting(bool enabled) override;

	private:
		std::unordered_map<size_t, GLMesh> meshMap;
		std::unordered_map<size_t, GLMaterial> materialMap;
		size_t materialCounter = 0;
		std::unordered_map<std::string, GLuint> shaderProgramMap; // Map from shader name to shader program handle
		size_t meshCounter = 0;

		/// <summary>
		/// Registers a shader program with the given name. Assuming the shader
		/// is located at "path/[name]", compiles the shader program and saves the handle in the shaderProgramMap.
		/// If the shader program is already registered, it simply returns the existing handle.
		/// </summary>
		std::expected<GLuint, std::string> RegisterShader(const std::string& name);

		std::expected<void, std::string> RegisterMaterial(Material* material);
		std::expected<void, std::string> RegisterMesh(Mesh* mesh);

	};
}