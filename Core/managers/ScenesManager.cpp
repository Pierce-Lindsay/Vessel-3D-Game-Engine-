#include "ScenesManager.h"
#include "logging/LogManager.h"

using namespace ve;

ScenesManager::ScenesManager()
{
	setType("ScenesManager");
}

ScenesManager::~ScenesManager() //clean thing sup to be safe
{
	for (const auto& [key, value] : sceneMap)
		value.get()->shutdown();
	sceneMap.clear();
	activeScene = nullptr;
	globalScene = nullptr;
}

ScenesManager& ScenesManager::GetInstance()
{
	static ScenesManager sm;
	return sm;
}

int ScenesManager::startUp()
{
	VE_LOG("Scenes Manager successfully started!");
	return Manager::startUp();
}

void ScenesManager::shutDown()
{
	VE_LOG("ScenesManager successfully shutdown!");
	Manager::shutDown();
}

void ScenesManager::update()
{
	if (globalScene)
		globalScene->update();
	if (activeScene)
		activeScene->update();
}


int ScenesManager::setActiveScene(Scene* scene)
{
	if (!scene)
	{
		VE_LOG("Failed to set active scene, provided scene was null.");
		return -1;
	}
	else if (!sceneMap.contains(scene->getID()))
	{
		VE_LOG("Failed to set active scene, scene was not found in the internal scene map.");
		return -1;
	}

	activeScene = scene;
	return 0;
}


int ScenesManager::setActiveScene(size_t sceneID)
{
	if (!sceneMap.contains(sceneID))
	{
		VE_LOG("Failed to set active scene, scene was not found in the internal scene map.");
		return -1;
	}
	activeScene = sceneMap[sceneID].get();
	return 0;
}

Scene* ScenesManager::addScene(std::unique_ptr<Scene> scene)
{
	if (!scene)
		return nullptr;

	auto scenePointer = scene.get();
	sceneMap[scenePointer->getID()] = std::move(scene); //assuming we don't need to check if id already here because should be unique
	return scenePointer;
}


Scene* ScenesManager::getActiveScene(size_t sceneID)
{
	if (!sceneMap.contains(sceneID))
		return nullptr;
	return sceneMap[sceneID].get();
}

int ScenesManager::swapObjectsScene(Object* obj, Scene* sceneA, Scene* sceneB)
{
	if (!obj)
	{
		VE_LOG("Failed to swap object scene, provided object was null.");
		return -1;
	}		

	return swapObjectsScene(obj->getID(), sceneA, sceneB);
}


int ScenesManager::swapObjectsScene(size_t objID, Scene* sceneA, Scene* sceneB)
{
	if (!sceneA || !sceneB || !sceneA->contains(objID)) //requirements to swap
	{
		VE_LOG("Failed to swap object scene, provided object was not in scene 'a' or one of the provided scenes was null.");
		return -1;
	}
	auto obj = sceneA->getObject(objID);
	auto unique = sceneA->swapOutObject(obj);
	sceneB->addObject(std::move(unique));
	if (sceneB->addObject(std::move(unique)))
		return 0;
	return -1;
}

int ScenesManager::removeScene(size_t sceneID)
{
	if (!sceneMap.contains(sceneID))
	{
		VE_LOG("Failed to remove scene, provided id was not in the scene map.");
		return -1;
	}
	else if (activeScene->getID() == sceneID || globalScene->getID() == sceneID)
	{
		VE_LOG("Failed to remove scene, provided scene was either the active or global scene which is not allowed to remove.");
		return -1;
	}
	sceneMap[sceneID].get()->shutdown(); //cleanup first
	sceneMap.erase(sceneID);
	return 0;
}