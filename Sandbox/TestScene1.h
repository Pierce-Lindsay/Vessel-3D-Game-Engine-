#pragma once
#include "Core/scenes/Scene.h"
#include "Core/objects/Object.h"
#include "TestCessnaScript.h"
#include "Core/managers/Engine.h"

class TestScene1 : public ve::Scene 
{
public:

	TestScene1()
	{

	}


	int startup() override
	{
		auto obj = std::make_unique<ve::Object>("plane boi");
		obj->addComponent<TestCessnaScript>();
		addObject(std::move(obj));
		renderer->SetClearColor(glm::vec4(0.5, 0.25, 0.1, 1.0));
		renderer->SetViewport(0, 0, 1920, 1080);
		auto cam = new ve::Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 45.0f, 1920 / 1080, 0.1f, 100.0f);
		VE_ENGINE->GetScenesManager()->SetActiveCamera(cam);
		return 1;
	}
};