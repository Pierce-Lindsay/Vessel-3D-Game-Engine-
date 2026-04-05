#pragma once
#include <filesystem>
#include <string>

namespace ve
{
	class FileUtils
	{
	public:
		/// <summary>
		/// Attempts to find the marker file among parent of or current working directory. Returns the
		/// path that the marker file lies within or empty if not found.
		/// </summary>
		/// <param name="markerFileName"></param>
		/// <returns></returns>
		static std::filesystem::path GetPathToMarker(const std::string& markerFileName);
	};

}