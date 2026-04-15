#include "ModelRenderer.h"

namespace ve {

	ModelRenderer::ModelRenderer(Object* owner)
	{

	}

	ModelRenderer::ModelRenderer(Object* owner, Mesh* mesh)
	{
		this->mesh = mesh;
		this->owner = owner;
	}

	ModelRenderer::ModelRenderer(Object* owner, const std::filesystem::path modelPath)
	{

	}

	ModelRenderer::~ModelRenderer()
	{

	}

	void ModelRenderer::start()
	{

	}

	void ModelRenderer::shutdown()
	{

	}

	void ModelRenderer::update()
	{

	}

	bool ModelRenderer::ShouldDraw() const
	{
		return shouldDraw;
	}

	void ModelRenderer::SetShouldDraw(bool b)
	{
	}

	void ModelRenderer::SetMesh(const Mesh* mesh)
	{
	}

	Mesh* ModelRenderer::GetMesh() const
	{
		return mesh;
	}

}