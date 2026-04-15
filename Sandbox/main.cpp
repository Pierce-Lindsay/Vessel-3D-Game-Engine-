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
#include "Rendering/SubMesh.h"
#include "TestScene1.h"
#include "Core/managers/Engine.h"




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
    VE_LM.StartUp();

    std::string root = "engine.root";
    if (auto e = VE_LM.SetOutputPathByRoot(root); !e)
    {
        VE_LOG_DIAGNOSTIC(e.error());
    }
    VE_LM.SetConsolePrint();
    VE_LM.SetFlush(true);
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
    std::string root = "engine.root";

    VE_LM.StartUp();
    VE_TRY_LOG(VE_LM.SetOutputPathByRoot(root));

    //init engine
    VE_ENGINE->startUp();

    //add scenes in use
    auto scene = VE_ENGINE->GetScenesManager()->addScene<TestScene1>();
    VE_ENGINE->GetScenesManager()->setActiveScene(scene->getID());

    //run engine
    VE_ENGINE->Run();
	return 0;
}
