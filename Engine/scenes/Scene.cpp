#include "Scene.h"
#include "logging/LogManager.h"
#include <algorithm>
#include <unordered_set>
using namespace ve;

//map for enforcing unique scene names
std::unordered_set<std::string> sceneNameAvailability;

Scene::Scene()
{
	id = currentID;
	currentID++;
	setName("scene" + std::to_string(id));
}

Scene::~Scene()
{
	//resources still loaded?
}

Object* Scene::addObject(std::unique_ptr<Object> object)
{
	auto id = object.get()->getID();
	return objects.add(id, std::move(object));
}

const std::vector<std::unique_ptr<Object>>* Scene::getObjects() const
{
	return objects.getValues();
}

Object* Scene::getObject(size_t id)
{
	return objects.get(id);
}

bool Scene::contains(Object* obj)
{
	if (!obj)
		return false;

	return objects.contains(obj->getID());
}

bool Scene::contains(size_t objID)
{
	return objects.contains(objID);
}

int Scene::lazyDeleteObject(size_t id)
{
	Object* obj = objects.get(id);
	return lazyDeleteObject(obj);
}

int Scene::lazyDeleteObject(Object* obj)
{
	if (obj == NULL)
	{
		LOG("Faliure, object was null.");
		return -1;
	}

	obj->setMarkedForDeletion(true);
	objectsToDelete.push_back(obj);
	return 0;
}

int Scene::instantDeleteObject(Object* obj)
{
	if (obj == NULL)
	{
		LOG("Faliure, object was null.");
		return -1;
	}
	return objects.remove(obj->getID());
}

std::unique_ptr<Object> Scene::swapOutObject(Object* obj)
{
	if (obj == NULL)
	{
		LOG("Faliure, object was null.");
		return NULL;
	}
	return objects.swapOut(obj->getID());
}

size_t Scene::getID() const
{
	return id;
}

const std::string& Scene::getName() const
{
	return name;
}

int Scene::setName(const std::string& name)
{
	if(sceneNameAvailability.contains(name))
	{
		LOG("Scene name " + name + " already taken, not changing name.");
		return -1;
	}
	sceneNameAvailability.erase(this->name);
	this->name = name;
	sceneNameAvailability.insert(name);
	return 0;
}

void Scene::update()
{
	//update objects
	//note objects itself takes care whether it actually updates or not
	objects.mapVoid([](Object* obj) {obj->update(); });
	//deletions
	// 
	//delete a certain amount according to max count and queue size
	size_t delCount = std::min(DELETION_MAX_PER_UPDATE, objectsToDelete.size());
	for (int i = 0; i < delCount; i++) //just keep popping from deletion list
	{
		objects.remove(objectsToDelete.back()->getID());
		objectsToDelete.pop_back();
	}
}

void Scene::shutdown()
{
	objects.clear(); //unique pointers clean up themselves
	//resources still loaded?
}