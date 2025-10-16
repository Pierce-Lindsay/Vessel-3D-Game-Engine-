#pragma once
#include "Component.h"
#include "../Object.h"
#include <vector>

namespace ve {

	/// <summary>
	/// Represents a hierarchical relationship between objects, 
	/// allowing for parent-child associations and management of child objects.
	/// This componnet assumes the relationship isn't one way, for example, if
	/// the componnet marks an object as a parent, it is expect that parnet has a 
	/// hierarchy that has this object has a child.
	/// </summary>
	class Hierarchy : public Component
	{
	private:
		Object* parent = NULL;
		std::vector<Object*> children;

		/// <summary>
		/// Get the vector iterator from looking for the child with the given id.
		/// </summary>
		std::vector<Object*>::iterator getChildIterator(size_t id);

	public:

		/// <summary>
		/// Default with NULL parent and no children. 
		/// Optionally pass in pointer to parrent.
		/// </summary>
		Hierarchy(Object* owner, Object* parent = nullptr);

		/// <summary>
		/// Establishes a parent-child hierarchy among objects.
		/// </summary>
		/// <param name="children">A vector containing pointers to child objects to be assigned to the parent.</param>
		/// <param name="parent">A pointer to the parent object. If NULL, no parent is assigned. Defaults to NULL.</param>
		Hierarchy(Object* owner, const std::vector<Object*>& children, Object* parent = nullptr);

		/// <summary>
		/// Cleans up other object's relationships with this component when this is
		/// destructed. Sets this object to NULL or removes it.
		/// </summary>
		void shutdown() override;

		/// <summary>
		/// Add a child to the vector of children
		/// </summary>
		void addChild(Object* child);

		/// <summary>
		/// Remove a child from the vector of children with the given id.
		/// Does not maintain order of vector.
		/// </summary>
		/// <returns>-1 if removal fail, 0 else.</returns>
		int removeChild(size_t id);

		/// <summary>
		/// Get the child with the specified id or return null
		/// if not found.
		/// </summary>
		Object* getChild(size_t id);

		/// <summary>
		/// Returns a constant reference to the list of child objects.
		/// </summary>
		/// <returns>A constant reference to a std::vector containing pointers to child Object instances.</returns>
		const std::vector<Object*>& getChildren() const;

		/// <summary>
		/// Sets the parent object for the current object.
		/// </summary>
		/// <param name="parent">Pointer to the parent object to be assigned.</param>
		void setParent(Object* parent);

		/// <summary>
		/// Returns a pointer to the parent object.
		/// </summary>
		/// <returns>A constant pointer to the parent Object, or nullptr if there is no parent.</returns>
		Object* const getParent() const;

		/// <summary>
		/// Create a parent child relation ship where the right object is the child of the
		/// left object and the left object is the parent of the right object. Checks if 
		/// objects have a hierarchy component and if they don't add one, else mutates 
		/// already existing hierarchy components.
		/// </summary>
		static void addParentChildRelationship(Object* parent, Object* child);
	};
}