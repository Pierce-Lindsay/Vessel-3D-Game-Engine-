#include "Renderer.h"

namespace ve
{
	void Renderer::SetShaderDirectory(const std::filesystem::path& path)
	{
		this->shaderDirectory = path;
	}
	std::filesystem::path Renderer::GetShaderDirectory() const
	{
		return shaderDirectory;
	}

	void Renderer::Draw(const Mesh* mesh, const glm::mat4& model, const Camera* camera)
	{
		Draw(mesh, model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}
}