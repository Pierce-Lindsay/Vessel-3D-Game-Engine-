#pragma once
#include "Manager.h"
#include <unordered_map>
#include "../scenes/Scene.h"
#include "../utils/VectorMap.h"
#include "Instrumentation/logging/Diagnostic.h"
#include "Rendering/Camera.h"
#include <expected>

namespace ve {

	class ScenesManager : public Manager
	{
	private:

		std::unordered_map<size_t, std::unique_ptr<Scene>> sceneMap; //map of all scenes used in the game
		Scene* activeScene = NULL; //currently active scene

		std::unique_ptr<Scene> globalScene; // a scene that is always active while the game runs
		//seperate from the activeScene. Handles objects that have lifetimes greater than a single scene.
		std::shared_ptr<Renderer> renderer;
		Camera* activeCamera = NULL;
		Camera DEFAULT_CAMERA;


	public:

		ScenesManager();

		~ScenesManager();

		/// <summary>
		/// Startup scenes manager.
		/// </summary>
		/// <returns>0 if successful, negative else.</returns>
		int startUp() override;

		/// <summary>
		/// Cleanup dependencies.
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Updates the current active scene and the global scene.
		/// </summary>
		void update();

		/// <summary>
		/// Draw the current scene aswell as the global scene.
		/// </summary>
		/// <returns></returns>
		std::expected<void, Diagnostic> Draw();

		/// <summary>
		/// Set the active scene by a pointer to a scene that is currently in the scene map.
		/// </summary>
		/// <returns>0 if setting the scene succeeded, -1 if setting the scene failed.</returns>
		int setActiveScene(Scene* scene);

		/// <summary>
		/// Set the active scene from among scenes within teh scene map by the string name corresponding to a scene.
		/// </summary>
		/// <returns>0 if setting the scene succeeded, -1 if setting the scene failed.</returns>
		int setActiveScene(size_t sceneID);

		/// <summary>
		/// Get a pointer to the active scene.
		/// </summary>
		Scene* getActiveScene(size_t sceneID);

		/// <summary>
		/// Swap the scene that holds the obect from sceneA to sceneB.
		/// Should be avoided calling in the middle of scene updates as this rips the objects out of a scene, possibly
		/// messeing up its logic.
		/// </summary>
		/// <returns>-1 if swap faliure, 0 else.</returns>
		static int swapObjectsScene(Object* obj, Scene* sceneA, Scene* sceneB);

		/// <summary>
		/// Swap the scene that holds the obect with the given ID from sceneA to sceneB.
		/// Should be avoided calling in the middle of scene updates as this rips the objects out of a scene, possibly
		/// messeing up its logic.
		/// </summary>
		/// <returns>-1 if swap faliure, 0 else.</returns>
		static int swapObjectsScene(size_t objID, Scene* sceneA, Scene* sceneB);

		/// <summary>
		/// Add and "move" the given scene unqiue pointer to the internal scane map.
		/// </summary>
		/// <param name="scene"></param>
		/// <returns>null if faliure to add, else raw pointer to the moved scene.</returns>
		Scene* addScene(std::unique_ptr<Scene> scene);

		/// <summary>
		/// Create a new instance of the scene of the given type and "move" the given scene unqiue pointer to the internal scane map.
		/// </summary>
		/// <param name="scene"></param>
		/// <returns>null if faliure to add, else raw pointer to the moved scene.</returns>
		template <typename T, typename ...Args>
		Scene* addScene(Args&& ... args)
		{
			auto scene = std::make_unique<T>(std::forward<Args>(args)...);
			return addScene(std::move(scene));
		}

		/// <summary>
		/// Attempt to remove the given scene from teh scenemap. Operation will fail if the specified scene is the active or global scene or
		/// if the scene cannot be found.
		/// </summary>
		/// <param name="sceneID"></param>
		/// <returns>0 on success, -1 on faliure to remove.</returns>
		int removeScene(size_t sceneID);

		void SetRenderer(std::shared_ptr<Renderer> renderer);

		std::shared_ptr<Renderer> GetRenderer() const;

		void SetActiveCamera(Camera* camera);

		Camera* GetActiveCamera() const;
	};
}