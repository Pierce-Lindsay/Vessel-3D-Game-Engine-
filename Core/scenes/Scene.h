#pragma once
#include "../objects/Object.h"
#include <vector>

namespace ve {
	/// <summary>
	/// A abstract class for collection of game objects that are updates every frame. Only one scene should be
	/// active at once and a scene handles all of its objects and resource dependencies.
	/// Subclasses should act as individual scenes where startup must be and other functions may be overriden.
	/// </summary>
	class Scene
	{
	private:
		static const size_t DELETION_MAX_PER_UPDATE = 100; //at max delete 100 objects in a frame
		inline static size_t currentID = 0;
		size_t id = 0;
		std::string name = "scene";
		VectorMap<size_t, Object> objects; //a vector map for handling object(contiguous iteration with 
		//o(1) deletion and random access by id)
		std::vector <Object*> objectsToDelete; //stack like vector that is a queue of objects to delete

	public:
		/// <summary>
		/// Create default empty scene with no objects.
		/// </summary>
		Scene();

		/// <summary>
		/// Cleanup scene dependencies.
		/// </summary>
		~Scene();

		/// <summary>
		/// Move the given object unique pointer into the scenes internal object storage.
		/// The object will be rendered and updated every frame. Return a raw pointer to the
		/// object.
		/// </summary>
		Object* addObject(std::unique_ptr<Object> object);

		/// <summary>
		/// Get a const reference to the vector of objects that 
		/// comprise the scene.
		/// </summary>
		/// <returns></returns>
		const std::vector<std::unique_ptr<Object>>* getObjects() const;

		/// <summary>
		/// Get a pointer to the object with the given id or return null
		/// if not found in the internal vector.
		/// </summary>
		Object* getObject(size_t id);

		/// <summary>
		/// Returns true if the given object pointed to is in this scene. False else.
		/// </summary>
		bool contains(Object* obj);

		/// <summary>
		/// Returns true if the given object with the id is in this scene. False else.
		/// </summary>
		bool contains(size_t objID);

		/// <summary>
		/// Uses lazy deletion to remove the specified object with the given id when
		/// convenient and efficient for the engine. Object will be deactivated until removed.
		/// Returns 0 on success, -1 on error.
		/// </summary>
		int lazyDeleteObject(size_t id);

		/// <summary>
		/// Uses lazy deletion to remove the specified object when
		/// convenient and efficient for the engine. Object will be deactivated until removed.
		/// Returns 0 on success, -1 on error.
		/// </summary>
		int lazyDeleteObject(Object* obj);

		/// <summary>
		/// Only use this function if you are sure it is what you want. This is inefficient,
		/// may cause undefined behavior, and not reccommended using under almost all circumstances.
		/// Removes specified object from the scene on call. Returns 0 on success, -1 on error.
		/// </summary>
		int instantDeleteObject(Object* obj);

		/// <summary>
		/// Only use this function if you are sure it is what you want.
		/// May cause undefined behavior if done in the middle of updating, and not reccommended using unless necessary.
		/// Removes specified object from the scene on call and returns the unqiue pounter to it.Returns null on failure.
		/// </summary>
		std::unique_ptr<Object> swapOutObject(Object* obj);

		/// <summary>
		/// Get the name of the scene. Every scene should have a unique name for identification.
		/// </summary>
		const std::string& getName() const;

		/// <summary>
		/// Set the name of the scene. If this name already exists for a different scene, no 
		/// change in the current name will occur.
		/// </summary>
		/// <returns>0 if the given name is unique, -1 on failure.</returns>
		int setName(const std::string& name);

		/// <summary>
		/// Get the unqiue ID of the scene.
		/// </summary>
		size_t getID() const;

		/// <summary>
		/// Initilize all resources and initial game objects of the scene. Should return -1 on error
		/// 0 else.
		/// </summary>
		virtual int startup() = 0;

		/// <summary>
		/// Update all game objects.
		/// </summary>
		virtual void update();

		/// <summary>
		/// Shutdown scene and clearup all dependencies/unload resources.
		/// </summary>
		void shutdown();
	};
}