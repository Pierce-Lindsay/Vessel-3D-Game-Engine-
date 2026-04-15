#pragma once
#include "Mesh.h"
#include <filesystem>
#include "Camera.h"
#include "Instrumentation/logging/Diagnostic.h"

namespace ve
{

	struct DrawQueueElement
	{
		Mesh* mesh;
		//copy model so that multithreaded isn't affected by changing values
		glm::mat4 model;
	};

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
		virtual std::expected<void, Diagnostic> Register(Mesh* mesh) = 0;

		/// <summary>
		/// Draw a mesh using the provided model, 
		/// view, and projection matrices. The mesh must have been 
		/// registered with the renderer before calling this method.
		/// </summary>
		virtual std::expected<void, Diagnostic> Draw(Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) = 0;

		/// <summary>
		/// Draw a mesh using the provided model matrix and camera. 
		/// The mesh must have been registered with the renderer before calling this method.
		/// </summary>
		std::expected<void, Diagnostic> Draw(Mesh* mesh, const glm::mat4& model, const Camera* camera);

		/// <summary>
		/// Queue a mesh to be draw withe the given model matrix.
		/// The mesh is drawn when DrawQueue is called.
		/// </summary>
		void QueueADraw(Mesh* mesh, const glm::mat4& model);

		/// <summary>
		/// Draws the entire queue for the renderer with the given
		/// camera.
		/// </summary>
		std::expected<void, Diagnostic> DrawQueue(const Camera* camera);

		/// <summary>
		/// Draws the entire queue for the renderer with the given
		/// view and projection matrices.
		/// </summary>
		virtual std::expected<void, Diagnostic> DrawQueue(const glm::mat4& view, const glm::mat4& projection);

		/// <summary>
		/// Initialize the renderer. 
		/// This should set up any necessary resources or state for rendering.
		/// </summary>
		virtual std::expected<void, Diagnostic> Init() = 0;

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
		std::expected<void, Diagnostic> SetShaderDirectory(const std::filesystem::path& path);

		/// <summary>
		/// Get the directory where shader files are located.
		/// </summary>
		/// <returns></returns>
		std::filesystem::path GetShaderDirectory() const;

	protected:
		std::filesystem::path shaderDirectory = "shaders/";

		std::vector<DrawQueueElement> drawQueue;
	};
}
