#include "Object.h"

using namespace ve;

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

void Object::start()
{
	//start all components
	components.mapVoid([](Component* comp) {comp->start(); });
}

void Object::update()
{
	//update all components
	components.mapVoid([](Component* comp) { comp->update(); });
}