#pragma once
#include <string>
#include <unordered_map>
#include <typeindex>
#include "../components/Component.h"
#include "../managers/LogManager.h"
#include <memory>
#include "../VectorMap.h"

namespace ve {

	class Scene; //forward declaraction so object can have access to scene
	/// <summary>
	/// A game object, has a set of components that dictate its data and behavior.
	/// </summary>
	class Object
	{
	private:
		inline static size_t currentID = 0;
		size_t id = 0;
		std::string type = "object"; //maybe a catergory the object falls in
		std::string name = "undefined"; //name if provided, helps with debugging/indentification
		bool active = true; //should this object be updated and drawn?
		bool markedForDeletion = false; //flag for delayed/lazy deletion
		VectorMap<std::type_index, Component> components;
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
		/// Sets the name using the provided name.
		/// </summary>
		void setName(const std::string& name);

		/// <summary>
		/// Sets the name using the provided name.
		/// </summary>
		const std::string& getName() const;

		/// <summary>
		/// Get whether this object is marked to be 
		/// deleted(deleted when convenient, but acts like doesn't exist).
		/// </summary>
		bool getMarkedForDeletion() const;

		/// <summary>
		/// Set a bool for whether that the scene will delete this object soon and so
		/// it shouldn't be updated/drawn.
		/// </summary>
		void setMarkedForDeletion(bool b);

		/// <summary>
		/// Set whether this object should be updated/rendered/ect.
		/// </summary>
		void setActive(bool b);

		/// <summary>
		/// Get whether this object should be updated/rendered/ect.
		/// </summary>
		bool getActive() const;

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
		template <typename T, typename ...Args>
		T* addComponent(Args&& ... args)
		{
			auto component = std::make_unique<T>(this, std::forward<Args>(args)...);
			//type id only allows 1 of each component type
			T* compPointer = component.get();
			components.add(typeid(T), std::move(component));
			return compPointer;
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
