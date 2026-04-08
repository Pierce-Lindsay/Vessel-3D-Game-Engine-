#include "Resource.h"

namespace ve
{
	Resource::Resource()
	{
	}
	Resource::~Resource()
	{
	}
	const std::expected<size_t, std::string> Resource::GetRenderingHandle() const
	{
		if (!registeredWithRenderer)
		{
			return std::unexpected("Resource has not been registered with the renderer.");
		}
		return renderingHandle;
	}
	void Resource::SetRenderingHandle(size_t handle)
	{
		this->renderingHandle = handle;
		registeredWithRenderer = true;
		requiresReRegister = false;
	}
	const bool Resource::IsRegisteredWithRenderer() const
	{
		return registeredWithRenderer;
	}

	const bool Resource::RequiresReRegister() const
	{
		return requiresReRegister;
	}

	void Resource::SetRequiresReRegister()
	{
		requiresReRegister = true;
	}
}