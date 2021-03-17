// Your First C++ Program

#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>
#include <cxxopts.hpp>

#include "shared/emoji.h"
#include "storage/manager.h"
#include "banner.h"

using namespace Bullma;

int main( int argc, const char* argv[] ) {
    cxxopts::Options options("BullmaDB", banner);
    options.allow_unrecognised_options();
    options.add_options()
        ("i,cli", "Open shell") // a bool parameter
        ("h,host", "Listen hostname", cxxopts::value<std::string>()->default_value("127.0.0.1"))
        ("p,port", "Listen port", cxxopts::value<int>()->default_value("4810"))
        ("c,cpu", "Number of cpu cores to be used", cxxopts::value<int>()->default_value("-1"))
        ("d,data", "Data directory", cxxopts::value<std::string>()->default_value("bullmadb_data"))
        ("help", "Print usage");
        // ("v,verbose", "Verbose output", cxxopts::value<bool>()->default_value("false"))
    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        return 1;
    }else if(result.unmatched().size() > 0){
        std::cout << options.help() << std::endl;
        return 1;
    }else{
        std::cout << banner << std::endl;
    }
    Storage::Manager* manager = new Storage::Manager(result["data"].as<std::string>());
    return 0;
}
