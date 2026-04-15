#pragma once
#include "Manager.h"
#include "Rendering/Renderer.h"
#include "ScenesManager.h"
#include "Context/window.h"
#include <memory>
#include <string>
#include <mutex>


#define VE_ENGINE ve::Engine::GetInstance()

namespace ve
{
	class Engine : public Manager
	{

	private:
		//force these to be private 
		~Engine();
		Engine();

		static Engine* instance;
		//used for multi-thread safety
		static std::mutex mutex;


		std::shared_ptr<Renderer> renderer;
		std::shared_ptr<ScenesManager> scenesManager;
		std::shared_ptr<Window> window;

		//TEMPORARY -> config files later
		const std::string MARKER_FILE_NAME = "engine.root";
		const std::string SHADERS_RELATIVE_PATH = "assets/shaders";
		const std::string MODELS_RELATIVE_PATH = "assets/models";

		std::expected<void, Diagnostic> Update();
		std::expected<void, Diagnostic> Draw();



	public:

		// N0 cloning
		Engine(Engine& other) = delete;
		//no assigning
		void operator=(const Engine&) = delete;

		static Engine* GetInstance();

		/// <summary>
		/// Startup Engine
		/// Defaults renderer to opengl
		/// </summary>
		/// <returns>0 if successful, negative else.</returns>
		int startUp() override;

		/// <summary>
		/// Cleanup dependencies.
		/// </summary>
		void shutDown() override;

		/// <summary>
		/// Runs the engine
		/// </summary>
		void Run();

		std::shared_ptr<Renderer> GetRenderer() const;
		std::shared_ptr<ScenesManager> GetScenesManager() const;
		std::shared_ptr<Window> GetWindow() const;
	};
}