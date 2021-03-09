#ifndef CMANAGER_H_
#define CMANAGER_H_

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <filesystem>
#include <msgpack.hpp>
#include <rocksdb/db.h>

#include "database.h"

namespace fs = std::filesystem;

class CManager
{
// public variables and functions
public:
	// class constructor
	CManager(std::string);
	~CManager();
	std::vector<CDatabase*> databases;
	rocksdb::Options options;
	rocksdb::WriteOptions MINIMAL_DURABILITY;
	rocksdb::WriteOptions SOFT_DURABILITY;
	rocksdb::WriteOptions HARD_DURABILITY;
	static CManager* getInstance();
protected:
	static CManager* singleton;
};
#endif // CMANAGER_H_