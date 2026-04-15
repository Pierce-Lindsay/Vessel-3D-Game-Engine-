#pragma once
#include "Material.h"
#include <string>

namespace ve
{
	struct SubMesh
	{
		std::string name;
		size_t indexOffset;
		size_t size;
		Material* material;
	};
}
