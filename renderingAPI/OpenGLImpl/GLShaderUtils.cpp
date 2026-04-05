#include "GLShaderUtils.h"
#include "Instrumentation/logging/LogManager.h"

namespace ve
{
	struct shader_sources {
		std::string vertex_source;
		std::string tcs_source;
		std::string tes_source;
		std::string geo_source;
		std::string fragment_source;
	};

	shader_sources GetSources(const std::string& filepath)
	{
		shader_sources sources;

		std::string shader_source;
		std::ifstream file;
		file.open(filepath);
		if (file.is_open())
			std::cout << filepath << " file opened" << '\n';
		//create modes for pushing data
		//a mode will be true until proven otherwise
		enum class shader_push_mode {
			VERTEX,
			TCS,
			TES,
			GEO,
			FRAGMENT,
		};
		shader_push_mode mode = shader_push_mode::VERTEX;
		while (file)
		{
			//get the current line of file
			std::string line;
			std::getline(file, line);

			if (line == "//shader vertex")
			{
				mode = shader_push_mode::VERTEX;
			}
			else if (line == "//shader tcs")
			{
				mode = shader_push_mode::TCS;
			}
			else if (line == "//shader tes")
			{
				mode = shader_push_mode::TES;
			}
			else if (line == "//shader geometry")
			{
				mode = shader_push_mode::GEO;
			}
			else if (line == "//shader fragment")
			{
				mode = shader_push_mode::FRAGMENT;
			}


			switch (mode)
			{
			case shader_push_mode::VERTEX:
			{
				sources.vertex_source.append(line);
				sources.vertex_source.append("\n");
				break;
			}
			case shader_push_mode::TES:
			{
				sources.tes_source.append(line);
				sources.tes_source.append("\n");
				break;
			}
			case shader_push_mode::TCS:
			{
				sources.tcs_source.append(line);
				sources.tcs_source.append("\n");
				break;
			}
			case shader_push_mode::GEO:
			{
				sources.geo_source.append(line);
				sources.geo_source.append("\n");
				break;
			}
			case shader_push_mode::FRAGMENT:
			{
				sources.fragment_source.append(line);
				sources.fragment_source.append("\n");
				break;
			}
			default:
				break;
			}

		}

		file.close();

		return sources;
	}


	void GLShaderUtils::CheckFailedCompile(GLuint shader, const std::string& shaderName)
	{
		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);

			// Provide the infolog in whatever manor you deem best.

			std::string errorString;
			
			for (int i = 0; i < errorLog.size(); i++)
			{
				errorString += errorLog[i];
			}
			VE_ERROR(std::format("Error in {} Shader! \n {}", shaderName, errorString));
			// Exit with failure.
			glDeleteShader(shader); // Don't leak the shader.
			return;
		}
	}

	GLuint GLShaderUtils::CompileShader(const std::string& fullPath)
	{
		VE_LOG(std::format("Compiling shader: {}", fullPath));
		auto sources = GetSources(fullPath);
		const GLchar* vertex_shader_source[]{ sources.vertex_source.c_str() };
		const GLchar* TCS_shader_source[]{ sources.tcs_source.c_str() };
		const GLchar* TES_shader_source[]{ sources.tes_source.c_str() };
		const GLchar* geo_shader_source[]{ sources.geo_source.c_str() };
		const GLchar* fragment_shader_source[]{ sources.fragment_source.c_str() };

		//create shaders and compile them, then link them to a program
		GLuint program;
		GLuint vertex_shader;
		GLuint TCS_shader;
		GLuint TES_shader;
		GLuint geo_shader;
		GLuint fragment_shader;

		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		CheckFailedCompile(vertex_shader, "Vertex");

		TCS_shader = glCreateShader(GL_TESS_CONTROL_SHADER);
		glShaderSource(TCS_shader, 1, TCS_shader_source, NULL);
		glCompileShader(TCS_shader);

		CheckFailedCompile(TCS_shader, "TCS");

		TES_shader = glCreateShader(GL_TESS_EVALUATION_SHADER);
		glShaderSource(TES_shader, 1, TES_shader_source, NULL);
		glCompileShader(TES_shader);

		CheckFailedCompile(TES_shader, "TES");

		geo_shader = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geo_shader, 1, geo_shader_source, NULL);
		glCompileShader(geo_shader);

		CheckFailedCompile(geo_shader, "GEO");

		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		CheckFailedCompile(fragment_shader, "Fragment");

		program = glCreateProgram();

		glAttachShader(program, vertex_shader);

		if (sources.tcs_source.empty() == false)
			glAttachShader(program, TCS_shader);

		if (sources.tes_source.empty() == false)
			glAttachShader(program, TES_shader);

		if (sources.geo_source.empty() == false)
			glAttachShader(program, geo_shader);


		glAttachShader(program, fragment_shader);
		glLinkProgram(program);
		//program contains shaders so they can be deleted now
		glDeleteShader(vertex_shader);
		glDeleteShader(TCS_shader);
		glDeleteShader(TES_shader);
		glDeleteShader(geo_shader);
		glDeleteShader(fragment_shader);
		return program;
	}

	
}

