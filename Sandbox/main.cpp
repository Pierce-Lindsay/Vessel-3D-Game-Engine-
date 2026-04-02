#include <iostream>
#include "../Instrumentation/logging/LogManager.h"

int main(int argc, char* argv[])
{
    LM.startUp();
    LM.setConsolePrint();
    using namespace ve;
    LOG(std::format("Hello {} world!", 10));
}
