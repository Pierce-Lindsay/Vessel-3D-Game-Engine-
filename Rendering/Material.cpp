#include "Material.h"

namespace ve
{
	Material::Material(const std::string& shaderName, const glm::vec4& color) 
		: shaderName{ shaderName }, color{ color }
	{
	}
	Material::~Material()
	{
	}
	const std::string& Material::GetShaderName() const { return shaderName; }
	const glm::vec4& Material::GetColor() const { return color; }
	void Material::SetColor(const glm::vec4& color) { this->color = color; }
}