#pragma once
#include "Core/scenes/Scene.h"
#include "Core/objects/Object.h"


/// <summary>
/// Test a scene that can actual be instantiated and craetes some objects.
/// </summary>
class TestScene : public ve::Scene
{
public:
	TestScene();

	int startup() override;


	ve::Object* obj1 = NULL;
	ve::Object* obj2 = NULL;
	ve::Object* obj3 = NULL;
};