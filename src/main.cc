// Your First C++ Program

#include <iostream>
#include <atomic>
#include <thread>
#include <assert.h>

#include "db/manager.h"

#include <marl/defer.h>
#include <marl/scheduler.h>
#include <marl/waitgroup.h>
#include <cxxopts.hpp>
#include "shared/emoji.h"

/*
auto MINIMAL_DURABILITY = rocksdb::WriteOptions();
MINIMAL_DURABILITY.disableWAL = true;
MINIMAL_DURABILITY.sync = false;

auto SOFT_DURABILITY = rocksdb::WriteOptions();
SOFT_DURABILITY.disableWAL = false;
SOFT_DURABILITY.sync = false;

auto HARD_DURABILITY = rocksdb::WriteOptions();
HARD_DURABILITY.disableWAL = false;
HARD_DURABILITY.sync = true;
*/
std::string banner = "\x1b[38;5;199m \x1b["
   "0m\x1b[38;5;199m_"
   "\x1b[0m\x1b[38;5;199"
   "m_\x1b[0m\x1b[38;5;1"
   "63m_\x1b[0m\x1b[38;5"
   ";164m \x1b[0m\x1b[38"
   ";5;164m \x1b[0m\x1b["
   "38;5;164m \x1b[0m"
   "\x1b[38;5;164m \x1b["
   "0m\x1b[38;5;164m "
   "\x1b[0m\x1b[38;5;164"
   "m \x1b[0m\x1b[38;5;1"
   "64m_\x1b[0m\x1b[38;5"
   ";164m \x1b[0m\x1b[38"
   ";5;164m_\x1b[0m\x1b["
   "38;5;164m \x1b[0m"
   "\x1b[38;5;164m \x1b["
   "0m\x1b[38;5;128m "
   "\x1b[0m\x1b[38;5;129"
   "m \x1b[0m\x1b[38;5;1"
   "29m \x1b[0m\x1b[38;5"
   ";129m \x1b[0m\x1b[38"
   ";5;129m \x1b[0m\x1b["
   "38;5;129m \x1b[0m"
   "\x1b[38;5;129m \x1b["
   "0m\x1b[38;5;129m "
   "\x1b[0m\x1b[38;5;129"
   "m \x1b[0m\x1b[38;5;1"
   "29m \x1b[0m\x1b[38;5"
   ";93m_\x1b[0m\x1b[38;"
   "5;93m_\x1b[0m\x1b[38"
   ";5;93m_\x1b[0m\x1b[3"
   "8;5;93m \x1b[0m\x1b["
   "38;5;93m \x1b[0m\x1b"
   "[38;5;93m_\x1b[0m"
   "\x1b[38;5;93m_\x1b[0"
   "m\x1b[38;5;93m_\x1b["
   "0m\x1b[38;5;93m \x1b"
   "[0m\r\n"
   "\x1b[38;5;163m|\x1b["
   "0m\x1b[38;5;164m "
   "\x1b[0m\x1b[38;5;164"
   "m_\x1b[0m\x1b[38;5;1"
   "64m \x1b[0m\x1b[38;5"
   ";164m)\x1b[0m\x1b[38"
   ";5;164m_\x1b[0m\x1b["
   "38;5;164m \x1b[0m"
   "\x1b[38;5;164m \x1b["
   "0m\x1b[38;5;164m_"
   "\x1b[0m\x1b[38;5;164"
   "m|\x1b[0m\x1b[38;5;1"
   "64m \x1b[0m\x1b[38;5"
   ";164m|\x1b[0m\x1b[38"
   ";5;128m \x1b[0m\x1b["
   "38;5;129m|\x1b[0m"
   "\x1b[38;5;129m_\x1b["
   "0m\x1b[38;5;129m "
   "\x1b[0m\x1b[38;5;129"
   "m_\x1b[0m\x1b[38;5;1"
   "29m_\x1b[0m\x1b[38;5"
   ";129m \x1b[0m\x1b[38"
   ";5;129m \x1b[0m\x1b["
   "38;5;129m_\x1b[0m"
   "\x1b[38;5;129m_\x1b["
   "0m\x1b[38;5;93m \x1b"
   "[0m\x1b[38;5;93m_"
   "\x1b[0m\x1b[38;5;93m"
   "|\x1b[0m\x1b[38;5;93"
   "m \x1b[0m\x1b[38;5;9"
   "3m \x1b[0m\x1b[38;5;"
   "93m \x1b[0m\x1b[38;5"
   ";93m\\\x1b[0m\x1b[38"
   ";5;93m|\x1b[0m\x1b[3"
   "8;5;93m \x1b[0m\x1b["
   "38;5;93m_\x1b[0m\x1b"
   "[38;5;63m \x1b[0m"
   "\x1b[38;5;63m)\x1b[0"
   "m\r\n"
   "\x1b[38;5;164m|\x1b["
   "0m\x1b[38;5;164m "
   "\x1b[0m\x1b[38;5;164"
   "m_\x1b[0m\x1b[38;5;1"
   "64m \x1b[0m\x1b[38;5"
   ";164m\\\x1b[0m\x1b[3"
   "8;5;164m \x1b[0m\x1b"
   "[38;5;164m|\x1b[0m"
   "\x1b[38;5;164m|\x1b["
   "0m\x1b[38;5;164m "
   "\x1b[0m\x1b[38;5;128"
   "m|\x1b[0m\x1b[38;5;1"
   "29m \x1b[0m\x1b[38;5"
   ";129m|\x1b[0m\x1b[38"
   ";5;129m \x1b[0m\x1b["
   "38;5;129m|\x1b[0m"
   "\x1b[38;5;129m \x1b["
   "0m\x1b[38;5;129m\'"
   "\x1b[0m\x1b[38;5;129"
   "m \x1b[0m\x1b[38;5;1"
   "29m \x1b[0m\x1b[38;5"
   ";129m\\\x1b[0m\x1b[3"
   "8;5;93m/\x1b[0m\x1b["
   "38;5;93m \x1b[0m\x1b"
   "[38;5;93m_\x1b[0m"
   "\x1b[38;5;93m`\x1b[0"
   "m\x1b[38;5;93m \x1b["
   "0m\x1b[38;5;93m|\x1b"
   "[0m\x1b[38;5;93m "
   "\x1b[0m\x1b[38;5;93m"
   "|\x1b[0m\x1b[38;5;93"
   "m)\x1b[0m\x1b[38;5;9"
   "3m \x1b[0m\x1b[38;5;"
   "63m|\x1b[0m\x1b[38;5"
   ";63m \x1b[0m\x1b[38;"
   "5;63m_\x1b[0m\x1b[38"
   ";5;63m \x1b[0m\x1b[3"
   "8;5;63m\\\x1b[0m\r\n"
   "\x1b[38;5;164m|\x1b["
   "0m\x1b[38;5;164m_"
   "\x1b[0m\x1b[38;5;164"
   "m_\x1b[0m\x1b[38;5;1"
   "64m_\x1b[0m\x1b[38;5"
   ";164m/\x1b[0m\x1b[38"
   ";5;164m\\\x1b[0m\x1b"
   "[38;5;128m_\x1b[0m"
   "\x1b[38;5;129m,\x1b["
   "0m\x1b[38;5;129m_"
   "\x1b[0m\x1b[38;5;129"
   "m|\x1b[0m\x1b[38;5;1"
   "29m_\x1b[0m\x1b[38;5"
   ";129m|\x1b[0m\x1b[38"
   ";5;129m_\x1b[0m\x1b["
   "38;5;129m|\x1b[0m"
   "\x1b[38;5;129m_\x1b["
   "0m\x1b[38;5;129m|"
   "\x1b[0m\x1b[38;5;93m"
   "_\x1b[0m\x1b[38;5;93"
   "m|\x1b[0m\x1b[38;5;9"
   "3m_\x1b[0m\x1b[38;5;"
   "93m\\\x1b[0m\x1b[38;"
   "5;93m_\x1b[0m\x1b[38"
   ";5;93m_\x1b[0m\x1b[3"
   "8;5;93m,\x1b[0m\x1b["
   "38;5;93m_\x1b[0m\x1b"
   "[38;5;93m|\x1b[0m"
   "\x1b[38;5;93m_\x1b[0"
   "m\x1b[38;5;63m_\x1b["
   "0m\x1b[38;5;63m_\x1b"
   "[0m\x1b[38;5;63m/"
   "\x1b[0m\x1b[38;5;63m"
   "|\x1b[0m\x1b[38;5;63"
   "m_\x1b[0m\x1b[38;5;6"
   "3m_\x1b[0m\x1b[38;5;"
   "63m_\x1b[0m\x1b[38;5"
   ";63m/\x1b[0m\r\n"
   "\x1b[38;5;164m \x1b["
   "0m\x1b[38;5;164m "
   "\x1b[0m\x1b[38;5;164"
   "m \x1b[0m\x1b[38;5;1"
   "28m \x1b[0m\x1b[38;5"
   ";129m \x1b[0m\x1b[38"
   ";5;129m \x1b[0m\x1b["
   "38;5;129m \x1b[0m"
   "\x1b[38;5;129m \x1b["
   "0m\x1b[38;5;129m "
   "\x1b[0m\x1b[38;5;129"
   "m \x1b[0m\x1b[38;5;1"
   "29m \x1b[0m\x1b[38;5"
   ";129m \x1b[0m\x1b[38"
   ";5;129m \x1b[0m\x1b["
   "38;5;93m \x1b[0m\x1b"
   "[38;5;93m \x1b[0m"
   "\x1b[38;5;93m \x1b[0"
   "m\x1b[38;5;93m \x1b["
   "0m\x1b[38;5;93m \x1b"
   "[0m\x1b[38;5;93m "
   "\x1b[0m\x1b[38;5;93m"
   " \x1b[0m\x1b[38;5;93"
   "m \x1b[0m\x1b[38;5;9"
   "3m \x1b[0m\x1b[38;5;"
   "93m \x1b[0m\x1b[38;5"
   ";63m \x1b[0m\x1b[38;"
   "5;63m \x1b[0m\x1b[38"
   ";5;63m \x1b[0m\x1b[3"
   "8;5;63m \x1b[0m\x1b["
   "38;5;63m \x1b[0m\x1b"
   "[38;5;63m \x1b[0m"
   "\x1b[38;5;63m \x1b[0"
   "m\x1b[38;5;63m \x1b["
   "0m\x1b[38;5;63m \x1b"
   "[0m\x1b[38;5;63m "
   "\x1b[0m\x1b[38;5;63m"
   " \x1b[0m";
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
        exit(0);
    }else if(result.unmatched().size() > 0){
        std::cout << options.help() << std::endl;
        exit(0);
    }
    CManager* manager = new CManager(result["data"].as<std::string>());

    delete manager;
    return 0;
}
