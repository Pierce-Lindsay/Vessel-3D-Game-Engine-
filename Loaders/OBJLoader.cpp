#include "OBJLoader.h"
#include <fstream>
#include <filesystem>
#include <charconv>
#include <cctype>
#include <unordered_map>
#include <format>
#include <external/glm/gtc/type_ptr.hpp>
//generate each list of vertex data

//go through face data to create a list of face Indexes
//iflength is > 3 use fan triangulation method to generate additional indices
//then go through all face Indexes and add all unique to the map
//we also need a list of 3 uint face indices to generate the final index buffer for the mesh, 
// so we can store the index of each face Index in the map in that list as well

//the map will essentially store all unique vertex combinations and their corresponding index in the final vertex array, 
// so we can easily generate the final vertex array and index buffer for the mesh

namespace ve
{
	//Default values for vertex attributes
	glm::vec4 DEFAULT_POS = { 0,0,0,1 };
	glm::vec3 DEFAULT_NORMAL = { 0, 1, 0 };
	glm::vec2 DEFAULT_TEX = { 0, 0 };

	std::expected<const char*, std::string> OBJLoader::ParseFaceIndex(const std::string& line, const char* linePtr, FaceIndex& face)
	{
		face = { 0, 0, 0 }; //defaults are 0 because .obj are 1 indexed, 0 accesses a default value in 
		//pos, normal, or uv
		auto lineEnd = line.data() + line.size();
			// Face definition
			//"v/vt/vn" "v//vn" "v/vt" "v" ""
			//grab vertex index
		const char* ptr = SkipOverWhiteSpaces(line, linePtr);
		if (*linePtr == 'v')
			ptr++; // Start after "f v"

		if (ptr >= lineEnd)
			return std::unexpected("Reached the end of teh line unexpectedly");

		auto [newPtr, ec] = std::from_chars(ptr, lineEnd, face.vertexIndex);
		if (ec != std::errc())
			return std::unexpected("Failed to parse vertex index in line");

		ptr += newPtr - ptr;

		if (*ptr == ' ')
		{
			// If we hit a space, it means we need to grab the next index
			return ptr + 1;
		}
		else if (ptr >= lineEnd)
			return ptr;
		else if (*ptr == '/')
		{
			// If we hit a '/', it means we need to grab the texture/normal index
			ptr++;
			if (*ptr == '/') // If we hit another '/', it means we have no texture coordinate
			{
				ptr++;
				if (*ptr == 'v')
					ptr += 2;// Skip the 'vn' prefix
				if (ptr >= lineEnd)
					return std::unexpected("Reached the end of teh line unexpectedly");

				auto [newPtr, ec] = std::from_chars(ptr, lineEnd, face.normalIndex);
				if (ec != std::errc())
					return std::unexpected("Failed to parse normal index in line");
				ptr += newPtr - ptr;
				return ptr;
			}
			else
			{
				if(*ptr == 'v')
					ptr += 2; // Skip the 'vt' prefix
				if (ptr >= lineEnd)
					return std::unexpected("Reached the end of teh line unexpectedly");

				auto [newPtr, ec] = std::from_chars(ptr, lineEnd, face.uvIndex);
				if (ec != std::errc())
					return std::unexpected("Failed to parse texture coordinate index in line");
				ptr += newPtr - ptr;
				if (*ptr == '/') // If we hit another '/', 
				{
					ptr++;
					if (*ptr == 'v')
						ptr += 2;// Skip the 'vn' prefix

					if (ptr >= lineEnd)
						return std::unexpected("Reached the end of teh line unexpectedly");

					auto [newPtr, ec] = std::from_chars(ptr, lineEnd, face.normalIndex);
					if (ec != std::errc())
					{
						return std::unexpected("Failed to parse normal index in line");
					}
					ptr += newPtr - ptr;
				}
				return ptr;
			}
		}
		else
			return std::unexpected("Unexpected character while parsing face index in line");
	}

	std::vector<OBJLoader::FaceIndex> OBJLoader::FanTriangulate(const std::vector<FaceIndex>& faceIndices)
	{
		//invalid if greater than 
		auto size = faceIndices.size();
		if (size <= 3)
			return faceIndices;

		//total number of indices that will be made
		size_t totalPoints = (size - 2) * 3;

		std::vector<FaceIndex> triangualted;
		triangualted.reserve(totalPoints);

		//triangulates any face: 0,1,2; 0, 2, 3; 0, 3, 4...
		for (int i = 0; i < size - 2; i++)
		{
			triangualted.push_back(faceIndices[0]);
			triangualted.push_back(faceIndices[i + 1]);
			triangualted.push_back(faceIndices[i + 2]);
		}
		return triangualted;
	}
	
	const char* OBJLoader::SkipOverWhiteSpaces(const std::string& line, const char* start)
	{
		auto end = line.data() + line.size();
		while (start < end)
		{
			if (*start != ' ')
				return start;
			start++;
		}
		return end;
	}

	std::expected<glm::vec4, std::string> OBJLoader::ParseVec4(const std::string& line)
	{
		glm::vec4 result = DEFAULT_POS;
		auto er = ParseVec(line, 3, result);
		if(!er)
			return std::unexpected("Error while parsing vec4!");	
		return result;
	}

	std::expected<glm::vec3, std::string> OBJLoader::ParseVec3(const std::string& line)
	{
		glm::vec3 result = DEFAULT_NORMAL;
		auto er = ParseVec(line, 3, result);
		if(!er)
			return std::unexpected("Error while parsing vec3!");
		return result;		
	}

	std::expected<glm::vec2, std::string> OBJLoader::ParseVec2(const std::string& line)
	{
		glm::vec2 result = DEFAULT_TEX;
		auto er = ParseVec(line, 2, result);
		if(!er)
			return std::unexpected("Error while parsing vec3!");
		return result;
	}

	std::expected<void, std::string> OBJLoader::ParseVertex(const std::string& line, std::vector<glm::vec4>& vertices)
	{
		// Vertex position
		auto vertex = ParseVec4(line.substr(1));
		if (!vertex.has_value())
			return std::unexpected(std::format("Failed to parse vertex position in line: {}", line));
		vertices.push_back(*vertex);
		return {};
	}

	std::expected<void, std::string> OBJLoader::ParseNormal(const std::string& line, std::vector<glm::vec3>& normals)
	{
		// Vertex normal
		auto normal = ParseVec3(line.substr(2));
		if (!normal.has_value())
			return std::unexpected(std::format("Failed to parse vertex normal in line: {}", line));
		normals.push_back(*normal);
		return {};
	}

	std::expected<void, std::string> OBJLoader::ParseUV(const std::string& line, std::vector<glm::vec2>& uvs)
	{
		// Texture coordinate
		auto uv = ParseVec2(line.substr(2));
		if (!uv.has_value())
			return std::unexpected(std::format("Failed to parse texture coordinate in line: {}", line));
		uvs.push_back(*uv);
		return {};
	}

	std::expected<void, std::string> OBJLoader::ParseFace(const std::string& line, std::vector<FaceIndex>& faceIndices)
	{
		auto subLine = line.substr(1); // Remove "f" prefix
		const char* linePtr = subLine.data();
		while (linePtr < subLine.data() + subLine.size())
		{
			FaceIndex faceIndex;
			auto ptr = ParseFaceIndex(subLine, linePtr, faceIndex);
			if (!ptr)
				return std::unexpected(std::format("{} in line: {}", ptr.error(), subLine));

			linePtr = ptr.value();
			faceIndices.push_back(faceIndex);
		}
		return {};
	}

	std::expected<void, std::string> OBJLoader::LoadOBJ(const std::string& filePath, Mesh* mesh)
	{
		if(!std::filesystem::exists(filePath))
			return std::unexpected(std::format("OBJ file not found at path: {}", filePath));

		std::ifstream file(filePath);

		if (!file.is_open())
			return std::unexpected(std::format("Failed to open OBJ file at path: {}", filePath));

		//to collect all parsing warnings
		std::string warningLog = "";

		std::vector<glm::vec4> vertices{ DEFAULT_POS };
		std::vector<glm::vec2> uvs{ DEFAULT_TEX };
		std::vector<glm::vec3> normals{ DEFAULT_NORMAL };
		std::vector<unsigned int> indices;
		//for iterating through all faces in sorted order 0 - n...
		std::vector<FaceIndex> uniqueIndexList;
		// Map to store unique vertex combinations and their corresponding index in the final vertex array
		std::unordered_map <FaceIndex, unsigned int, FaceIndexHash> uniqueIndexMap; 
		unsigned int nextUniqueFaceIndex = 0;


		std::string line;
		while (std::getline(file, line))
		{
			// Process the OBJ file line by line
			if(line.starts_with("#"))
			{
				continue; // Skip comments
			}
			else if (line.starts_with("v "))
			{
				auto er = ParseVertex(line, vertices);
				if (!er)
					warningLog += er.error() + '\n';
			}
			else if (line.starts_with("vt"))
			{
				auto er = ParseUV(line, uvs);
				if (!er)
					warningLog += er.error() + '\n';;
			}
			else if (line.starts_with("vn"))
			{
				auto er = ParseNormal(line, normals);
				if (!er)
					warningLog += er.error() + '\n';;
			}
			else if (line.starts_with("f "))
			{
				std::vector<FaceIndex> faceIndices;
				auto er = ParseFace(line, faceIndices);
				if (!er)
				{
					warningLog += er.error();
					continue;
				}
				//valid, so triangulate faces (if n==3, does nothing)
				if (faceIndices.size() > 3)
					faceIndices = FanTriangulate(faceIndices);

				//for every unique faceIndex, add to the map and list, for all find the corresponding index
				for (auto& faceIndex : faceIndices)
				{
					if (!uniqueIndexMap.contains(faceIndex))
					{
						uniqueIndexMap[faceIndex] = nextUniqueFaceIndex;
						uniqueIndexList.push_back(faceIndex);
						indices.push_back(nextUniqueFaceIndex);
						nextUniqueFaceIndex++;
					}
					else 
						indices.push_back(uniqueIndexMap[faceIndex]);
				}		
			}
			else if (line.starts_with(" "))
			{
				//assume empty line as there is no header
				continue;
			}
			else
			{
				// Unrecognized line format, log a warning
				warningLog += std::format("Unrecognized line in OBJ file: {}", line) + '\n';
				//keep going, we don't want to fail just because of some unrecognized lines
			}
		}

		//finally, interleave vertices into our actual final data form
		//use indices to find the coorect index in our list of shape, normal, and uv info
		std::vector<float> interleaved;
		interleaved.reserve(uniqueIndexMap.size() * 9);

		for (auto i = 0; i < uniqueIndexList.size(); i++)
		{
			auto& face = uniqueIndexList[i];
			float* ptr = glm::value_ptr(vertices[face.vertexIndex]);
			interleaved.insert(interleaved.end(), ptr, ptr + 4); //vertex info

			ptr = glm::value_ptr(vertices[face.uvIndex]);
			interleaved.insert(interleaved.end(), ptr, ptr + 2);

			ptr = glm::value_ptr(vertices[face.normalIndex]);
			interleaved.insert(interleaved.end(), ptr, ptr + 3);
		}

		mesh->SetVertices(interleaved);
		mesh->SetIndices(indices);
		file.close();
		if (!warningLog.empty())
			return std::unexpected(warningLog);
		return {};
	}
}