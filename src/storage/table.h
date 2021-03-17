#ifndef __Table_H__
#define __Table_H__

#include <iostream>
#include <string.h>
#include <assert.h>
#include <map>
#include <sstream>
#include <vector>

#include <msgpack.hpp>
#include <rocksdb/db.h>

namespace Bullma::Storage{
    class Table
    {
    public:
        std::string name;
        std::map<std::string, rocksdb::ColumnFamilyHandle*> indexes;
        Table(rocksdb::DB*, rocksdb::ColumnFamilyHandle*);
        ~Table();
        rocksdb::ColumnFamilyHandle* getHandle();
    private:
        rocksdb::ColumnFamilyHandle* handle;
        rocksdb::DB* db;
    };
}
#endif // __Table_H__