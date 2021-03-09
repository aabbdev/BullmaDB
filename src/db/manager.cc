#include "manager.h"
CManager *CManager::singleton = 0;
CManager::CManager(std::string path)
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
				databases.push_back(new CDatabase(file_path));
			}
		}
	}else{
		fs::create_directory(path);
	}
}
CManager::~CManager()
{
	std::for_each(databases.begin(), databases.end(), [](CDatabase* db){
		delete db;
	});
	databases.clear();
	databases.shrink_to_fit();
	singleton = nullptr;
}

CManager *CManager::getInstance()
{
	return singleton;
}
