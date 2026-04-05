#include "FileUtils.h"

namespace ve
{
	std::filesystem::path FileUtils::GetPathToMarker(const std::string& markerFileName)
	{
		auto currentDir = std::filesystem::current_path();
		while (!currentDir.empty())
		{
			if (std::filesystem::exists(currentDir / markerFileName))
			{
				return currentDir;
			}
			currentDir = currentDir.parent_path();
		}

		return currentDir;
	}
}