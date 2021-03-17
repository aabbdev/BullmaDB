#ifndef __Database_H__
#define __Database_H__

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <sstream>
#include <vector>
#include <filesystem>

#include <msgpack.hpp>
#include <rocksdb/db.h>

#include "table.h"

namespace fs = std::filesystem;
namespace Bullma::Storage {
    class Database
    {
    public:
        //std::map<std::string, rocksdb::ColumnFamilyHandle> tables;
        std::string name;
        rocksdb::DB* db;
        std::map<std::string, Table*> tables;
        Table* table_get(std::string);
        Table* table_create(std::string);
        bool table_drop(std::string);
        Database(fs::path);
        ~Database();
    };
}
#endif // __Database_H__