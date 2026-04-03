#include <iostream>
#include "Instrumentation/logging/LogManager.h"
#include "Rendering/window.h"

int main(int argc, char* argv[])
{
    LM.startUp();
    LM.setConsolePrint();
    using namespace ve;
    LOG(std::format("Hello {} world!", 10));
    Window w;
	w.init();

    while(w.isOpen())
    {
        w.update();
	}   
}
