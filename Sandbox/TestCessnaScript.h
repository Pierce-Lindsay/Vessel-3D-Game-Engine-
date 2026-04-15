#pragma once
#include "Core/components/Component.h"
#include "Core/components/Transformer.h"
#include "Core/components/ModelRenderer.h"
#include "Core/objects/Object.h"
#include "Rendering/Mesh.h"
#include "Rendering/Material.h"
#include "Instrumentation/files/FileUtils.h"
#include "Loaders/OBJLoader.h"



class TestCessnaScript : public ve::Component
{
protected:
	ve::Material* mat;
	ve::Mesh* mesh;

public:

	TestCessnaScript(ve::Object* owner)
	{
		this->owner = owner;
	}

	void start()
	{
		mesh = new ve::Mesh();
		auto dir = ve::FileUtils::GetPathToMarker("engine.root") / "assets";
		if (auto e = ve::OBJLoader::LoadOBJ((dir / "models" / "cessna.obj").string(), mesh); !e)
		{
			VE_WARN(e.error());
		}
		mat = new ve::Material("basicShader.shader", glm::vec4(0.0f, 1.0f, 0.01f, 1.0f));
		mesh->SetSubMeshes({ ve::SubMesh{"cessna", 0, mesh->GetIndices().size(), mat} });
		auto trans = owner->addComponent<ve::Transformer>();
		trans->setRotation(0.0, glm::vec3(0, 1, 0));
		trans->setScaleUniform(0.1);
		trans->move(glm::vec3(0, 0, -20));

		owner->addComponent<ve::ModelRenderer>(mesh);
	}

	void shutdown()
	{

	}

	void update()
	{
		owner->getComponent<ve::Transformer>()->rotate(0.1f);
	}
};