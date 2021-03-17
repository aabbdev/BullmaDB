#include "console.h"
using namespace Bullma;
using namespace Bullma::CLI;

Console *Console::singleton = 0;
Console::Console(){
    singleton = this;
}
Console::~Console(){
    singleton = nullptr;
}
Console *Console::getInstance()
{
	return singleton;
}
void Console::run(std::atomic<bool>& run){
    std::string buffer;

    while (run.load())
    {
        std::cin >> buffer;
        if (buffer == "Quit")
        {
            run.store(false);
        }
    }
}