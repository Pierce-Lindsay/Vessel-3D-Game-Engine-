#pragma once
#include "Mesh.h"
#include <expected>
#include "Instrumentation/logging/LogManager.h"
#include <external/glm/gtx/norm.hpp>

namespace ve
{
	/// <summary>
	/// A class for parsing .obj files. Parses them into a mesh object.
	/// </summary>
	class OBJLoader
	{
	public:
		/// <summary>
		/// Loads a mesh from an OBJ file at the given file path and 
		/// stores the data in the provided mesh object.
		/// </summary>
		static std::expected<void, std::string> LoadOBJ(const std::string& filePath, Mesh* mesh);

	private:

		/// <summary>
		/// A position, normal, and uv combination to form an index for a face.
		///0 means not specified, so we can use that to determine 
		/// if we need place default values for missing data
		/// </summary>
		struct FaceIndex
		{
			int vertexIndex;
			int uvIndex;
			int normalIndex;
		};

		friend bool operator==(const FaceIndex& a, const FaceIndex& b) {
			return a.vertexIndex == b.vertexIndex && a.uvIndex == b.uvIndex && a.normalIndex == b.normalIndex;
		}

		/// <summary>
		/// Hash function for FaceIndex.
		/// </summary>
		struct FaceIndexHash
		{
			size_t operator()(const FaceIndex& k) const {
				size_t seed = 0;
				seed ^= std::hash<int>{}(k.vertexIndex) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				seed ^= std::hash<int>{}(k.uvIndex) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				seed ^= std::hash<int>{}(k.normalIndex) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
				return seed;
			}
		};


		// Helper functions for parsing different OBJ elements
		
		/// <summary>
		/// Parses a glm::vec4 from a line.
		/// </summary>
		static std::expected<glm::vec4, std::string> ParseVec4(const std::string& line);


		/// <summary>
		/// Parses a glm::vec3 from a line.
		/// </summary>
		static std::expected<glm::vec3, std::string> ParseVec3(const std::string& line);


		/// <summary>
		/// Parses a glm::vec2 from a line.
		/// </summary>
		static std::expected<glm::vec2, std::string> ParseVec2(const std::string& line);


		/// <summary>
		/// Parses a position vertex attribute from a line.
		/// </summary>
		static std::expected<void, std::string> ParseVertex(const std::string& line, std::vector<glm::vec4>& vertices);

		/// <summary>
		/// Parses a vertex normal attribute from a line.
		/// </summary>
		static std::expected<void, std::string> ParseNormal(const std::string& line, std::vector<glm::vec3>& normals);

		/// <summary>
		/// Parses a uv vertex attribute from a line.
		/// </summary>
		static std::expected<void, std::string> ParseUV(const std::string& line, std::vector<glm::vec2>& uvs);

		/// <summary>
		/// Parses a face of vertices from a line.
		/// </summary>
		static std::expected<void, std::string> ParseFace(const std::string& line, std::vector<FaceIndex>& faceIndices);

		// <summary>
		/// Parses an individual FaceIndex of a face of vertices from a line.
		/// </summary>
		static std::expected<const char*, std::string> ParseFaceIndex(const std::string& line, const char* linePtr, FaceIndex& face);

		// <summary>
		/// Takes a pointer from where to start in a line and skips over all blank spaces, returns pointer to first non-blank space
		/// or the end of the line.
		/// </summary>
		static const char* SkipOverWhiteSpaces(const std::string& line, const char* start);

		/// <summary>
		/// Triangulates a vector of faceIndices, returning a created vector. Fan triangulates
		/// if there or more than 3 indices.
		/// </summary>
		static std::vector<FaceIndex> FanTriangulate(const std::vector<FaceIndex>& faceIndices);

		/// <summary>
		/// Parses an arbitrary glm::vec from teh given line and updates outValue 
		/// with the parsed data. Allows for a min fill depth that will
		/// not return a warning if the vec's current fill depth >= min fill depth.
		/// </summary>
		template <int N, typename T>
		static std::expected<void, std::string> ParseVec(const std::string& line, int minimumFillDepth, glm::vec<N, T>& outValue)
		{
			const char* lineEnd = line.data() + line.size();
			//find first non white space
			const char* linePtr = SkipOverWhiteSpaces(line, line.data());

			for (int i = 0; i < N; i++)
			{
				if (linePtr >= lineEnd)
				{
					if (minimumFillDepth >= i)
						return {};
					return std::unexpected("While passing vec, unexpectedly reached the end of the line!");
				}

				auto [newPtr, ec] = std::from_chars(linePtr, lineEnd, outValue[i]);
				if (ec != std::errc())
					return std::unexpected("Error passing vec, unexpectedly reached the end of the line!");

				linePtr = SkipOverWhiteSpaces(line, newPtr);
			}
			return {};
		}
	};
}