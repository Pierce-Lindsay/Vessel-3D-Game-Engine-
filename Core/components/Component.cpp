#include "Component.h"

using namespace ve;

Component::Component(Object* owner) : owner{owner}
{}


Component::~Component()
{
	shutdown();
}

const std::string& Component::getType() const
{
	return type;
}

void Component::setType(const std::string& type)
{
	this->type = type;
}

void Component::start(){}

void Component::shutdown() {}

void Component::update() {}