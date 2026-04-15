#include "objectFactory.h"
#include "../components/Hierarchy.h"
#include "../components/Transformer.h"

using namespace ve;

Object* ve::createSceneObject(const std::string& type_name, Scene* scene)
{
	if (scene == NULL)
		return NULL;
	auto unique = std::make_unique<Object>(type_name);
	return scene->addObject(std::move(unique));
}

Object* ve::createSceneTransformerObject(const std::string& type_name, const glm::vec3& pos, Scene* scene)
{
	auto obj = createSceneObject(type_name, scene);
	if (obj)
		obj->addComponent<Transformer>(pos);
	return obj;
}

Object* ve::createSceneTransformerHierarchyObject(const std::string& type_name, const glm::vec3& pos, Scene* scene)
{
	auto obj = createSceneObject(type_name, scene);
	if (obj)
	{
		obj->addComponent<Transformer>(pos);
		obj->addComponent<Hierarchy>();
	}	
	return obj;
}