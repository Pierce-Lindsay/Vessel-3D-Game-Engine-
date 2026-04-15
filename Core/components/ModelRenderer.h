#pragma once
#include "Component.h"
#include "Rendering/Mesh.h"
#include <filesystem>

namespace ve
{
	class ModelRenderer : public Component
	{
	protected:
		Mesh* mesh = NULL;
		bool shouldDraw = true;

	public:
		ModelRenderer(Object* owner);

		ModelRenderer(Object* owner, Mesh* mesh);

		ModelRenderer(Object* owner, const std::filesystem::path modelPath);

		~ModelRenderer();

		void start() override;

		void shutdown() override;

		void update() override;

		bool ShouldDraw() const;

		void SetShouldDraw(bool b);

		void SetMesh(const Mesh* mesh);

		/// <summary>
		/// Can't be const as it might need to be registered.
		/// </summary>
		Mesh* GetMesh() const;
	};
}