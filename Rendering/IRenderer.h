#pragma once
#include "Mesh.h"

namespace ve
{
	/// <summary>
	/// An interface for rendering the game. The renderer is responsible for drawing the current frame.
	/// </summary>
	class IRenderer
	{
	public:
		virtual ~IRenderer() = default;
		/// <summary>
		/// Render the current frame.
		/// </summary>
		virtual void Register(Mesh* mesh) = 0;
		virtual void Draw(const Mesh* mesh, const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection) = 0;
		virtual bool Init() = 0;
		virtual bool ShutDown() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(int x, int y, int width, int height) = 0;
	};
}
