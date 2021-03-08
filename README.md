<img style="width:70%;" src="/assets/bullmadb.png">

[BullmaDB](#)
======================================
What is Bullma?
------------------
* **Open source** database for building realtime web applications
* **NoSQL** database that stores your JSON documents with or without a predefined schema
* **Distributed** database that is easy to scale
* **High availability** database with automatic failover and robust fault tolerance
* **Server-less** deploy your application as close as possible to your data with lambda functions.
* **S3 Compatible** manage your storage with an S3 api compatible.

###### BullmaDB is a new way of writing these applications.
How to Build?
------------------
```
$ git clone https://github.com/aabbdev/bullmadb.git
$ cd bullmadb
$ ./configure.sh
$ cd build
$ make -j4
```
Contributing
------------------
TODO

Credits
------------------
* **RethinkDB** For inspiration and especially [rethinkdb-lite](https://github.com/lbguilherme/rethinkdb-lite)
* **Google** For the wonderful hybrid thread management library [Marl](https://github.com/google/marl)
* **Facebook** For the super storage engine [RocksDB](https://github.com/facebook/rocksdb)
* **Twitter** For the super cool identifier generator [Snowflake ID](https://en.wikipedia.org/wiki/Snowflake_ID)
* **MessagePack** For serialization of JSON documents in binary format [MessagePack](https://github.com/msgpack/msgpack-c/tree/cpp_master)
* **Cyan4973** For the extremely fast hash algorithm [XXHASH](https://github.com/Cyan4973/xxHash)
* **Cameron314** For the most incredible lock-free queue [concurrentqueue](https://github.com/cameron314/concurrentqueue)

License
------------------
[Apache License v2.0](/LICENSE)
