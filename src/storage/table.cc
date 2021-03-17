#include "table.h"
using namespace Bullma;
using namespace Bullma::Storage;

Table::Table(rocksdb::DB* _db, rocksdb::ColumnFamilyHandle* _cf){
    assert(_db != nullptr);
    assert(_cf != nullptr);

    db = _db;
    handle = _cf;
    name = _cf->GetName();
}
Table::~Table(){
    
}

rocksdb::ColumnFamilyHandle* Table::getHandle(){
    return handle;
}