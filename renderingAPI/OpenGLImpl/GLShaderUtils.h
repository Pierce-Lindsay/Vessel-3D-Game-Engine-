#pragma once
#include <external/Glad/glad/glad.h>
#include <string>

namespace ve
{
	class GLShaderUtils
	{
	private:
		/// <summary>
		/// Check if the shader compilation failed and log the error if it did. 
		/// Deletes the shader if compilation failed to avoid memory leaks.
		/// </summary>
		static void CheckFailedCompile(GLuint shader, const std::string& shaderName);
	public:
		/// <summary>
		/// Compiles a shader program from a file path. 
		/// The file should contain the source code for all shader stages in use, 
		/// with each stage separated by a comment line in the format "//shader [stage]",
		/// where [stage] is one of "vertex", "tcs", "tes", "geometry", or "fragment".
		/// Returns the handle to the compiled shader program.
		/// </summary>
		static GLuint CompileShader(const std::string& fullPath);
	};
}