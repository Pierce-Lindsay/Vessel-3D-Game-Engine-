#pragma once
#include "Mesh.h"
#include <filesystem>
#include "Camera.h"

namespace ve
{
	/// <summary>
	/// An interface for rendering the game. The renderer is responsible for drawing the current frame.
	/// </summary>
	class Renderer
	{
	public:
		virtual ~Renderer() = default;
		/// <summary>
		/// Register a mesh with the renderer. 
		/// This allows the renderer to prepare 
		/// any necessary resources for rendering the mesh,
		/// </summary>
		virtual void Register(Mesh* mesh) = 0;

		/// <summary>
		/// Draw a mesh using the provided model, 
		/// view, and projection matrices. The mesh must have been 
		/// registered with the renderer before calling this method.
		/// </summary>
		virtual void Draw(const Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) = 0;

		/// <summary>
		/// Draw a mesh using the provided model matrix and camera. 
		/// The mesh must have been registered with the renderer before calling this method.
		/// </summary>
		void Draw(const Mesh* mesh, const glm::mat4& model, const Camera* camera);

		/// <summary>
		/// Initialize the renderer. 
		/// This should set up any necessary resources or state for rendering.
		/// </summary>
		virtual bool Init() = 0;

		/// <summary>
		/// Shutdown the renderer. 
		/// This should clean up any resources or state used for rendering.
		/// </summary>
		virtual bool ShutDown() = 0;

		/// <summary>
		/// Set the clear color for the renderer. 
		/// This is the color that the screen will be cleared to when Clear() is called.
		/// </summary>
		virtual void SetClearColor(const glm::vec4& color) = 0;

		/// <summary>
		/// Clear the screen using the clear color set by SetClearColor.
		/// </summary>
		virtual void Clear() = 0;

		/// <summary>
		/// Set the viewport for rendering. 
		/// This defines the area of the screen that will be rendered to.
		/// </summary>
		virtual void SetViewport(int x, int y, int width, int height) = 0;

		/// <summary>
		/// Set whether backface culling is enabled.
		/// </summary>
		virtual void SetBackfaceCulling(bool enabled) = 0;

		/// <summary>
		/// Set whether depth testing is enabled.
		/// </summary>
		virtual void SetDepthTesting(bool enabled) = 0;

		/// <summary>
		/// Set the directory where shader files are located.
		/// </summary>
		/// <param name="path"></param>
		void SetShaderDirectory(const std::filesystem::path& path);

		/// <summary>
		/// Get the directory where shader files are located.
		/// </summary>
		/// <returns></returns>
		std::filesystem::path GetShaderDirectory() const;

	protected:
		std::filesystem::path shaderDirectory = "shaders/";
	};
}
