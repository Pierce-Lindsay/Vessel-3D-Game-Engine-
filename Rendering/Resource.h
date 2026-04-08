#pragma once
#include <expected>
#include <string>

namespace ve
{
	/// <summary>
	/// A base class for resources that can be registered with the renderer. 
	/// This includes meshes and materials... and potentially other resources in the future.
	/// </summary>
	class Resource
	{
	protected:
		size_t renderingHandle = 0;
		bool registeredWithRenderer = false;
		bool requiresReRegister = false;
	public:
		/// <summary>
		/// Generate a new resource. The rendering handle is invalid until the resource is registered with the renderer, 
		/// at which point it will be set to a valid handle. 
		/// </summary>
		Resource();
		virtual ~Resource();

		/// <summary>
		/// Get the handle to the Rendering API resource associated with this resource.
		/// If the resource has not been registered with the renderer, 
		/// this will return an error string instead of a handle.
		/// </summary>
		const std::expected<size_t, std::string> GetRenderingHandle() const;

		/// <summary>
		/// Set the handle to the Rendering API resource associated with this resource.
		/// </summary>
		void SetRenderingHandle(size_t handle);

		/// <summary>
		/// Get whether the resource has been registered with the renderer.
		/// </summary>
		const bool IsRegisteredWithRenderer() const;

		/// <summary>
		/// Get whether the resource should be reregistered before the next draw call.
		/// </summary>
		const bool RequiresReRegister() const;

		/// <summary>
		/// Set that the resource should be reregistered before the next draw call.
		/// </summary>
		/// <param name="b"></param>
		void SetRequiresReRegister();
	};
}