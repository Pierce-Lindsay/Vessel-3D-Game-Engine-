#include "renderingAPI/OpenGLImpl/GLRenderer.h"
#include <iostream>
#include "Instrumentation/logging/LogManager.h"
#include "Instrumentation/timing/LifetimeTimer.h"
#include "Instrumentation/timing/FunctionTimer.h"
#include "Instrumentation/files/FileUtils.h"
#include "Context/window.h"
#include "Rendering/Mesh.h"
#include "Rendering/Camera.h"
#include "Loaders/OBJLoader.h"
#include <glm/gtx/norm.hpp>



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

	//testOBJLoader();

    ve::Renderer* renderer = new ve::GLRenderer();
	renderer->Init();
	renderer->SetShaderDirectory(ve::FileUtils::GetPathToMarker("engine.root") / "assets" / "shaders");
	renderer->SetClearColor(glm::vec4(0.2, 0.3, 0.3, 1.0));
	renderer->SetViewport(0, 0, 1920, 1080);

    //auto cam = new ve::Camera();
	auto cam = new ve::Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 45.0f, w.getAspectRatio(), 0.1f, 100.0f);


	auto material = new ve::Material("basicShader.shader", glm::vec4(1.0, 0, 0, 1.0));
	auto mesh = new ve::Mesh(
        { },
        { }, material);

    auto path = ve::FileUtils::GetPathToMarker("engine.root") / "assets" / "models";
   auto er = ve::OBJLoader::LoadOBJ((path / "cessna.obj").string(), mesh);  

   if (!er)
       VE_WARN(er.error());

	renderer->Register(mesh);

    float f = 0;
  

    while(w.isOpen())
    {
        auto mat = glm::scale(glm::mat4(1.0f), glm::vec3(0.1, 0.1, 0.1));
        mat = glm::rotate(mat, glm::radians(f), glm::vec3(0, 1, 0));
        mat = glm::translate(mat, glm::vec3(0, 0, -30));
        
        renderer->Clear();
		renderer->Draw(mesh, mat, cam);
        w.update();
        f += 0.01;
        
	}
	delete mesh;
	delete material;
	delete renderer;
	return 0;
}
