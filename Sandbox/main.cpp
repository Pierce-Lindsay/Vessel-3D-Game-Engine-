#include <iostream>
#include "Instrumentation/logging/LogManager.h"
#include "Context/window.h"

void test()
{
    LM.startUp();
    std::string root = "engine.root";
    LM.setOutputPathByRoot(root);
    LM.setConsolePrint();
    LM.setFlush(true);
    using namespace ve;
    VE_LOG(std::format("Hello {} world!", 10));
    VE_WARN("This is a warning!");
    VE_ERROR("This is an error!");
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
