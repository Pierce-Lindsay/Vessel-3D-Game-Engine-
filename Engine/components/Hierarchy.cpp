#include "Hierarchy.h"

using namespace ve;
Hierarchy::Hierarchy(Object* parent)
{
	this->parent = parent;
	setType("hierarchy");
}

Hierarchy::Hierarchy(const std::vector<Object*>& children, Object* parent)
{
	this->children = children;
	this->parent = parent;
	setType("hierarchy");
}


void Hierarchy::addChild(Object* child)
{
	children.push_back(child);
}

std::vector<Object*>::iterator Hierarchy::getChildIterator(size_t id)
{
	return std::find_if(children.begin(), children.end(),
		[id](Object* p) {return p->getID() == id; });
}

Object* Hierarchy::getChild(size_t id)
{
	auto iterator = getChildIterator(id);
	if (iterator == children.end())
		return NULL;
	return children[iterator - children.begin()];
}


int Hierarchy::removeChild(size_t id)
{
	//order of children does not matter
	auto iterator = getChildIterator(id);
	if (iterator == children.end())
		return -1;

	//swap with last element
	if (children.size() != 1)
		children[iterator - children.begin()] = children[children.size() - 1];

	children.pop_back();
	return 0;
}


const std::vector<Object*>& Hierarchy::getChildren() const
{
	return children;
}

void Hierarchy::setParent(Object* parent)
{
	this->parent = parent;
}

Object* const Hierarchy::getParent() const
{
	return parent;
}