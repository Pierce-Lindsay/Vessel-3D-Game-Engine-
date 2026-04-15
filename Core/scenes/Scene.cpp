#include "Scene.h"
#include "logging/LogManager.h"
#include <algorithm>
#include <unordered_set>
#include "../components/ModelRenderer.h"
#include "../components/Transformer.h"
#include "../components/Hierarchy.h"
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
	object->SetScene(this);
	if (started && renderer) //we're started so we need to register rendering dependencies immidetly
	{
		if (auto mod = object->getComponent <ModelRenderer>())
		{
			if (auto e = renderer->Register(mod->GetMesh()); !e)
			{
				VE_LOG_DIAGNOSTIC(e.error());
			}			
		}		
	}
	return objects.add(id, std::move(object));
}

const std::vector<std::unique_ptr<Object>>& Scene::getObjects() const
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
		VE_LOG("Faliure, object was null.");
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
		VE_LOG("Faliure, object was null.");
		return -1;
	}
	return objects.remove(obj->getID());
}

std::unique_ptr<Object> Scene::swapOutObject(Object* obj)
{
	if (obj == NULL)
	{
		VE_LOG("Faliure, object was null.");
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
		VE_LOG("Scene name " + name + " already taken, not changing name.");
		return -1;
	}
	sceneNameAvailability.erase(this->name);
	this->name = name;
	sceneNameAvailability.insert(name);
	return 0;
}

void Scene::update()
{
	if (!started) //first update startUp
	{
		startup(); //allow for addition of objects in startup first
		started = true;
		//register all objects that require drawing already in the scene
		if (renderer)
		{
			//assume renderer is init
			for (auto& obj : objects.getValues())
			{
				if (auto rend = obj->getComponent<ModelRenderer>())
				{
					if (auto e = renderer->Register(rend->GetMesh()); !e)
					{
						VE_LOG_DIAGNOSTIC(e.error());
					}

				}
			}
		}
	}


	//update objects
	//note objects itself takes care whether it actually updates or not
	objects.mapVoid([](Object* obj) 
		{obj->update();});
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

void Scene::QueueDraws()
{
	for (const auto& obj : objects.getValues())
	{
		if (auto ptr = obj->getComponent<ModelRenderer>())
		{
			if (!ptr->ShouldDraw())
				continue;

			if (auto m = ptr->GetMesh())
			{
				if (!m->IsRegisteredWithRenderer())
					renderer->Register(m);
			}

			auto modelMat = glm::mat4(1.0f);

			if (auto trans = obj->getComponent<Transformer>())
				modelMat = trans->getModelMat();

			if (auto hierarchy = obj->getComponent<Hierarchy>()) //apply hierarchical transformations if applicable
				modelMat = hierarchy->ComputeHierarchicalTransform();

			renderer->QueueADraw(ptr->GetMesh(), modelMat);
		}
	}
}

void Scene::shutdown()
{
	objects.clear(); //unique pointers clean up themselves
	//resources still loaded?
}

void Scene::SetRenderer(std::shared_ptr<Renderer> renderer)
{
	this->renderer = renderer;
}

std::shared_ptr<Renderer> Scene::GetRenderer() const
{
	return renderer;
}