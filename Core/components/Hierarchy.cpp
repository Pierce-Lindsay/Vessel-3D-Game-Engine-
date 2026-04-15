#include "Hierarchy.h"

using namespace ve;
Hierarchy::Hierarchy(Object* owner, Object* parent) : Component(owner), parent{parent}
{
	setType("hierarchy");
}

Hierarchy::Hierarchy(Object* owner, const std::vector<Object*>& children, Object* parent)
	: Component(owner), parent{ parent }, children{children}
{
	setType("hierarchy");
}

void Hierarchy::shutdown()
{
	//clean up parent
	if (parent)
	{
		auto hierarchy = parent->getComponent<Hierarchy>();
		if (hierarchy)
			hierarchy->removeChild(owner->getID());
	}

	for (int i = 0; i < children.size(); i++)
	{
		auto child = children[i];
		if (child)
		{
			auto hierarchy = child->getComponent<Hierarchy>();
			if (hierarchy)
				hierarchy->parent = NULL;
		}
	}
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

void Hierarchy::addParentChildRelationship(Object* parent, Object* child)
{
	auto parentH = parent->getComponent<Hierarchy>();
	if (!parentH)
		parent->addComponent<Hierarchy>();
	parentH->addChild(child);

	auto childH = child->getComponent<Hierarchy>();
	if (!childH)
		child->addComponent<Hierarchy>(parent);
	else
		childH->setParent(parent);
}

/// <summary>
	/// Gets whether this component's object's model matrix should be influenced by the transforms
	/// of its parent/ancestors.
	/// </summary>
bool Hierarchy::GetExperiencesHierarchicalTransformations() const
{
	return hierarchicalTransformations;
}

/// <summary>
/// Set whether this component's object's model matrix should be influenced by the transforms
/// of its parent/ancestors.
/// </summary>
void Hierarchy::SetExperiencesHierarchicalTransformations(bool b)
{
	hierarchicalTransformations = b;
}

/// <summary>
/// Compute this component's object's model matrix by the transforms
/// of its parent/ancestors. If this object doesn't have a transformer
/// return identity matrix. If it isn't supposed to have herarchical transformation
/// just returns this objects transformer.
/// </summary>
glm::mat4 Hierarchy::ComputeHierarchicalTransform() const
{
	auto trans = owner->getComponent<Transformer>();
	glm::mat4 model = glm::mat4(1.0f);
	if (!trans)
		return model;
	model = trans->getModelMat();
	if (!hierarchicalTransformations || !parent)
		return model;

	if (auto parentHierarchy = parent->getComponent<Hierarchy>())
		return parentHierarchy->ComputeHierarchicalTransform() * model;

	if (auto parentTrans = parent->getComponent<Transformer>())
		return parentTrans->getModelMat() * model;

	return model;
}