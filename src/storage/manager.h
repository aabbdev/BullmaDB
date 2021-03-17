#ifndef __Manager_H__
#define __Manager_H__

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <filesystem>
#include <msgpack.hpp>
#include <rocksdb/db.h>

#include "database.h"

namespace fs = std::filesystem;
namespace Bullma::Storage {
	class Manager
	{
	// public variables and functions
	public:
		// class constructor
		Manager(std::string);
		~Manager();
		std::vector<Database*> databases;
		rocksdb::Options options;
		rocksdb::WriteOptions MINIMAL_DURABILITY;
		rocksdb::WriteOptions SOFT_DURABILITY;
		rocksdb::WriteOptions HARD_DURABILITY;
		static Manager* getInstance();
	protected:
		static Manager* singleton;
	};	
}
#endif // __Manager_H__