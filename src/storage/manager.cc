#include "manager.h"
using namespace Bullma;
using namespace Bullma::Storage;

Manager *Manager::singleton = 0;
Manager::Manager(std::string path)
{
	singleton = this;
	MINIMAL_DURABILITY = rocksdb::WriteOptions();
	MINIMAL_DURABILITY.disableWAL = true;
	MINIMAL_DURABILITY.sync = false;

	SOFT_DURABILITY = rocksdb::WriteOptions();
	SOFT_DURABILITY.disableWAL = false;
	SOFT_DURABILITY.sync = false;

	HARD_DURABILITY = rocksdb::WriteOptions();
	HARD_DURABILITY.disableWAL = false;
	HARD_DURABILITY.sync = true;

	options.create_if_missing = true;
	options.paranoid_checks = false;
	options.allow_ingest_behind = true;
	options.enable_pipelined_write = true;
	options.max_background_jobs = 4;
	options.IncreaseParallelism(8);
	options.OptimizeLevelStyleCompaction();

	if(fs::exists(path)){
		for (const auto & entry : fs::directory_iterator(path)){
			auto file_path = entry.path();
			if(fs::is_directory(file_path)){
				// Verify if its an Rocks Directory
				databases.push_back(new Database(file_path));
			}
		}
	}else{
		fs::create_directory(path);
	}
}
Manager::~Manager()
{
	std::for_each(databases.begin(), databases.end(), [](Database* db){
		delete db;
	});
	databases.clear();
	databases.shrink_to_fit();
	singleton = nullptr;
}

Manager *Manager::getInstance()
{
	return singleton;
}
