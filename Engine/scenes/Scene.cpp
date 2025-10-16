#include "Scene.h"
#include <algorithm>
using namespace ve;

Scene::Scene()
{
	id = currentID;
	currentID++;
}

/// <summary>
/// Cleanup scene dependencies.
/// </summary>
Scene::~Scene()
{
	//resources still loaded?
}

/// <summary>
/// Move the given object unique pointer into the scenes internal object storage.
/// The object will be rendered and updated every frame.
/// </summary>
Object* Scene::addObject(std::unique_ptr<Object> object)
{
	auto id = object.get()->getID();
	return objects.add(id, std::move(object));
}

/// <summary>
/// Get a const reference to the vector of objects that 
/// comprise the scene.
/// </summary>
/// <returns></returns>
const std::vector<std::unique_ptr<Object>>* Scene::getObjects() const
{
	return objects.getValues();
}

/// <summary>
/// Get a pointer to the object with the given id or return null
/// if not found in the internal vector.
/// </summary>
Object* Scene::getObject(size_t id)
{
	return objects.get(id);
}

/// <summary>
/// Uses lazy deletion to remove the specified object with the given id when
/// convenient and efficient for the engine. Object will be deactivated until removed.
/// Returns 0 on success, -1 on error.
/// </summary>
int Scene::lazyDeleteObject(size_t id)
{
	Object* obj = objects.get(id);
	return lazyDeleteObject(obj);
}

/// <summary>
/// Uses lazy deletion to remove the specified object when
/// convenient and efficient for the engine. Object will be deactivated until removed.
/// Returns 0 on success, -1 on error.
/// </summary>
int Scene::lazyDeleteObject(Object* obj)
{
	if (obj == NULL)
		return -1;

	obj->setMarkedForDeletion(true);
	objectsToDelete.push_back(obj);
	return 0;
}

/// <summary>
/// Only use this function if you are sure it is what you want. This is inefficient,
/// may cause undefined behavior, and not reccommended using under almost all circumstances.
/// Removes specified object from the scene on call. Returns 0 on success, -1 on error.
/// </summary>
int Scene::instantDeleteObject(Object* obj)
{
	if (obj == NULL)
		return -1;
	return objects.remove(obj->getID());
}

/// <summary>
/// Get the unqiue ID of the scene.
/// </summary>
size_t Scene::getID() const
{
	return id;
}

const std::string& Scene::getName() const
{
	return name;
}

void Scene::setName(const std::string& name)
{
	this->name = name;
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