#pragma once

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
		virtual void Render() = 0;
		virtual bool Init() = 0;
		virtual bool ShutDown() = 0;
	};
}
