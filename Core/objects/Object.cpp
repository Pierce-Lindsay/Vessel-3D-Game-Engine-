#include "Object.h"
#include "../scenes/Scene.h"
#include "logging/LogManager.h"

using namespace ve;

void Object::log(const std::string& message)
{
	VE_LOG(message);
}

Object::Object(const std::string& type_name)
{
	this->type = type_name;
	id = currentID;
	currentID++; //increment id
}

size_t Object::getID() const
{
	return id;
}

void Object::setType(const std::string& type_name)
{
	this->type = type_name;
}

std::string Object::getType() const
{
	return type;
}


void Object::setName(const std::string& name)
{
	this->name = name;
}

const std::string& Object::getName() const
{
	return name;
}

bool Object::getMarkedForDeletion() const
{
	return markedForDeletion;
}

void Object::setMarkedForDeletion(bool b)
{
	markedForDeletion = b;
}

/// <summary>
/// Set whether this object should be updated/rendered/ect.
/// </summary>
void Object::setActive(bool b)
{
	active = b;
}

/// <summary>
/// Get whether this object should be updated/rendered/ect.
/// </summary>
bool Object::getActive() const
{
	return active;
}

void Object::start()
{
	//start all components
	components.mapVoid([](Component* comp) {comp->start(); });
}

void Object::update()
{
	//update all components if allowed
	if(active && !markedForDeletion)
		components.mapVoid([](Component* comp) { comp->update(); });
}