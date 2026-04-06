#include "renderingAPI/OpenGLImpl/GLRenderer.h"
#include <iostream>
#include "Instrumentation/logging/LogManager.h"
#include "Instrumentation/timing/LifetimeTimer.h"
#include "Instrumentation/timing/FunctionTimer.h"
#include "Instrumentation/files/FileUtils.h"
#include "Context/window.h"
#include "Rendering/Mesh.h"
#include "Rendering/Camera.h"



void foo()
{
    for (int i = 0; i < 1000000; ++i)
    {
		auto x = i * i;
    }

}

int foo2(int x, double y)
{
    for (int i = 0; i < 1000000; ++i)
    {
        auto z = x * y;
    }
    return 0;
}

void test()
{
	ve::LifetimeTimer timer("test_timer");
    LM.startUp();
    std::string root = "engine.root";
    LM.setOutputPathByRoot(root);
    LM.setConsolePrint();
    LM.setFlush(true);
    using namespace ve;
    VE_LOG(std::format("Hello {} world!", 10));
    VE_WARN("This is a warning!");
    VE_ERROR("This is an error!");

	auto time = ve::measureFunctionTime(foo);
	VE_LOG(std::format("Time taken by foo: {} ms", std::chrono::duration_cast<std::chrono::milliseconds>(time).count()));
    //ve::measureFunctionTimeRigorous(100, foo);
	VE_TIME_MEASURE(100, foo);
	VE_TIME_MEASURE(100, foo2, 10, 3.14);
}

int main(int argc, char* argv[])
{
    test();
    ve::Window w;
	w.init();

    ve::Renderer* renderer = new ve::GLRenderer();
	renderer->Init();
	renderer->SetShaderDirectory(ve::FileUtils::GetPathToMarker("engine.root") / "assets" / "shaders");
	renderer->SetClearColor(glm::vec4(0.2, 0.3, 0.3, 1.0));
	renderer->SetViewport(0, 0, 1920, 1080);

    //auto cam = new ve::Camera();
	auto cam = new ve::Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 45.0f, w.getAspectRatio(), 0.1f, 100.0f);


	auto material = new ve::Material("basicShader.shader", glm::vec4(1.0, 0, 0, 1.0));
	auto mesh = new ve::Mesh(
        { -1, -1, 0, 1, 1, -1, 0, 1, 0, 1, 0, 1 }, 
        {0, 0, 0, 0, 0, 0}, 
        { 0, 0, 0, 0, 0, 0, 0, 0 ,0 }, 
        { 0, 1, 2 }, material);

	renderer->Register(mesh);

    while(w.isOpen())
    {
        renderer->Clear();
		renderer->Draw(mesh, glm::mat4(1.0f), cam);
        w.update();
        
	}
	delete mesh;
	delete material;
	delete renderer;
	return 0;
}
