#pragma once
#include <string>
#include <unordered_map>
#include <typeindex>
#include "components/Component.h"
#include "managers/LogManager.h"
#include <memory>
#include "ComponentMap.h"

namespace ve {

	/// <summary>
	/// A game object, has a set of components that dictate its data and behavior.
	/// </summary>
	class Object
	{
	private:
		inline static size_t currentID = 0;
		size_t id = 0;
		std::string type = "object";
		ComponentMap components;

		/// <summary>
		/// Adds a component to the collection and returns a raw pointer to it.
		/// </summary>
		/// <typeparam name="T">The type of the component.</typeparam>
		/// <param name="uniquePointer">A unique pointer to the component to be added.</param>
		/// <returns>A raw pointer to the added component.</returns>
		template <typename T>
		T* addComponentPointer(std::unique_ptr<T> uniquePointer)
		{
			T* compPointer = uniquePointer.get(); //get pointer to return before moving
			components.add(typeid(T), std::move(uniquePointer)); //type id only allows 1 of each component type
			return compPointer;
		}

	public:

		/// <summary>
		/// Default constructor for the Object class.
		/// </summary>
		Object(const std::string& type_name);

		/// <summary>
		/// Sets the type using the provided type name.
		/// </summary>
		void setType(const std::string& type_name);

		/// <summary>
		/// Get objects internal id.
		/// </summary>
		size_t getID() const;

		/// <summary>
		/// Get the name of the object.
		/// </summary>
		std::string getType() const;

		/// <summary>
		/// Add a new component type to the object. There can only be one
		/// component of each type. The input is <typename>(constructor arguments).
		/// </summary>
		/// <returns>Raw pointer to the newly created component.</returns>
		template <typename T, typename ...arguments>
		T* addComponent(arguments&& ... args)
		{
			auto component = std::make_unique<T>(std::forward<arguments>(args)...);
			return addComponentPointer(std::move(component));
		}
		
		/// <summary>
		/// Add a new component type to the object that is a copy of the component passed in.
		/// There can only be one of each type.
		/// The input is <typename>(constructor arguments).
		/// </summary>
		/// <returns>Raw pointer to the newly created component.</returns>
		template <typename T>
		T* addComponent(T* component)
		{
			//copy component
			std::unique_ptr<T> typedUnique = dynamic_cast<std::unique_ptr<T>>(component->copy());
			return addComponentPointer(std::move(typedUnique)); //pass ownership
		}

		/// <summary>
		/// Retrieves a pointer to the component of the specified type, if it exists.
		/// </summary>
		/// <typeparam name="T">The type of the component to retrieve.</typeparam>
		/// <returns>A pointer to the component of type T if found; otherwise, NULL.</returns>
		template <typename T>
		T* getComponent()
		{
			//search for type( can only have 1 component of each type0
			auto value = components.get(typeid(T));
			if (value == NULL)
				return NULL;
			return static_cast<T*>(value); //dangerous!!! but we should be very sure its valid
		}

		/// <summary>
		/// Remove the component of the given type.
		/// </summary>
		/// <returns>-1 on removal faliure, 0 else.</returns>
		template <typename T>
		int removeComponent()
		{
			//search for type( can only have 1 component of each type0
			int result = components.remove(typeid(T));//automatically deallocate(unique pointer)
			if (result == -1)
			{
				LOG(std::format("Failure to remove component {} from object {} with type {}.", typeid(T).name(), id, type));
				return -1;
			}
			return 0;
		}

		/// <summary>
		/// Performs strat operation on all components before teh first update frame.
		/// </summary>
		void start();

		/// <summary>
		/// Performs an update operation on every frame on object and all it components.
		/// </summary>
		void update();
	};

}
