#pragma once
#include <string>
#include "external/GLM/glm.hpp"

namespace ve
{
	class Material 
	{
	private:
		std::string shaderName;
		size_t renderingHandle;
		glm::vec4 color;

	public:
		Material(const std::string& shaderName, const glm::vec4& color);
		~Material();

		const std::string& GetShaderName() const;
		size_t GetRenderingHandle() const;
		const glm::vec4& GetColor() const;

		void SetRenderingHandle(size_t renderingHandle);
		void SetColor(const glm::vec4& color);
	};
}


