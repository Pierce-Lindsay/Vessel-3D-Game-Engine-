#include "pch.h"
#include "TestScene.h"
#include "../Engine/components/Transformer.h"
#include "../Engine/components/Hierarchy.h"
#include "../Engine/objects/ObjectFactory.h"


using namespace ve;
TestScene::TestScene()
{
	setName("testScene");
}

int TestScene::startup()
{ 
	//create some objects and add them to the scene
	obj1 = createSceneObject("hello", this);
	obj1->addComponent<Transformer>(glm::vec3(1, 1, 1));

	obj2 = createSceneObject("hello2", this);
	obj2->addComponent<Transformer>(glm::vec3(3, 1, 1));
	obj2->addComponent<Hierarchy>(obj1);
	obj3 = createSceneObject("hello3", this);
	std::vector<Object*> children = { obj1 };
	obj3->addComponent<Hierarchy>(children, nullptr);
	return 1;
}