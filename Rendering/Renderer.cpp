#include "Renderer.h"

namespace ve
{
	std::expected<void, Diagnostic> Renderer::SetShaderDirectory(const std::filesystem::path& path)
	{
		if (std::filesystem::exists(path))
		{
			this->shaderDirectory = path;
			return {};
		}
		return std::unexpected(VE_ERROR_DIAGNOSTIC("Passed file path does not exist"));
	}
	std::filesystem::path Renderer::GetShaderDirectory() const
	{
		return shaderDirectory;
	}

	std::expected<void, Diagnostic> Renderer::Draw(Mesh* mesh, const glm::mat4& model, const Camera* camera)
	{
		return Draw(mesh, model, camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}

	void Renderer::QueueADraw(Mesh* mesh, const glm::mat4& model)
	{
		drawQueue.emplace_back(mesh, model);
	}

	std::expected<void, Diagnostic> Renderer::DrawQueue(const Camera* camera)
	{
		if (!camera)
			return std::unexpected(VE_ERROR_DIAGNOSTIC("Cameria is null!"));
		return DrawQueue(camera->GetViewMatrix(), camera->GetProjectionMatrix());
	}

	std::expected<void, Diagnostic> Renderer::DrawQueue(const glm::mat4& view, const glm::mat4& projection)
	{
		//simplilest varient -> add batching and instancing later
		auto diag = VE_INFO_DIAGNOSTIC("Grouping diagnostic:");
		for (auto& element : drawQueue)
		{
			if (auto e = Draw(element.mesh, element.model, view, projection); !e)
				diag.AddAdditionalDiagnostic(e.error());
		}
		drawQueue.clear();

		if (diag.GetSubDiagnostics().size())
			return std::unexpected(diag);
		return {};
	}
}