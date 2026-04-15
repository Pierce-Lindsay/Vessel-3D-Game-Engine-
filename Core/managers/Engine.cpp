#include "renderingAPI/OpenGLImpl/GLRenderer.h"
#include "Engine.h"
#include "Instrumentation/logging/LogManager.h"
#include "Instrumentation/files/FileUtils.h"

namespace ve
{

	Engine* Engine::instance{ nullptr };
	std::mutex Engine::mutex;

	/**
	 * The first time we call GetInstance we will lock the storage location
	 *      and then we make sure again that the variable is null and then we
	 *      set the value.
	 */
	Engine* Engine::GetInstance()
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (instance == nullptr)
		{
			instance = new Engine();
		}
		return instance;
	}

	Engine::Engine()
	{

	}

	Engine::~Engine()
	{
		//cleanup
	}

	int Engine::startUp()
	{
		window = std::make_shared<Window>();
		window->init();

		renderer = std::make_shared<GLRenderer>();
		
		if (auto e = renderer->Init(); !e)
		{
			VE_LOG_DIAGNOSTIC(e.error());
		}
		if (auto e = renderer->SetShaderDirectory(FileUtils::GetPathToMarker(MARKER_FILE_NAME) / SHADERS_RELATIVE_PATH); !e)
		{
			VE_LOG_DIAGNOSTIC(e.error());
		}

		scenesManager = std::make_shared<ScenesManager>();
		scenesManager->SetRenderer(renderer);
		scenesManager->startUp();
		
		return 0;
	}

	void Engine::shutDown()
	{
		//shared ptr automatically takes care of itself
	}

	void Engine::Run()
	{
		while (window->isOpen())
		{
			renderer->Clear();
			Update();
			Draw();	
			window->update();
		}
	}

	std::expected<void, Diagnostic> Engine::Update()
	{
		scenesManager->update();
		return {};
	}

	std::expected<void, Diagnostic> Engine::Draw()
	{
		scenesManager->Draw();
		return {};
	}

	std::shared_ptr<Renderer> Engine::GetRenderer() const
	{
		return renderer;
	}
	std::shared_ptr<ScenesManager> Engine::GetScenesManager() const
	{
		return scenesManager;
	}
	std::shared_ptr<Window> Engine::GetWindow() const
	{
		return window;
	}
}