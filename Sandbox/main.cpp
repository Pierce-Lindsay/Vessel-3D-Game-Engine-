#include <iostream>
#include "Instrumentation/logging/LogManager.h"
#include "Instrumentation/timing/LifetimeTimer.h"
#include "Instrumentation/timing/FunctionTimer.h"
#include "Context/window.h"

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

    while(w.isOpen())
    {
        w.update();
	}   
}
