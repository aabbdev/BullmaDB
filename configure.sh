# Install dependencies
sudo apt-get install libgflags-dev libsnappy-dev zlib1g-dev libbz2-dev liblz4-dev libzstd-dev
mkdir -p third_party
git submodule update --recursive

# Builf dependencies
## Msgpack
cd third_party/msgpack
cmake -DMSGPACK_CXX17=ON .
make
## Google Marl
cd ../marl
git submodule update --init
mkdir -p build
cd build
cmake .. -DMARL_BUILD_EXAMPLES=1 -DMARL_BUILD_TESTS=1
make
## XXHASH
cd ../../xxhash
make
## RocksDB
cd ../rocksdb
rm -r build
mkdir -p build
cd build
cmake -DFORCE_SSE42=1 -DWITH_JEMALLOC=1 -DWITH_LZ4=1 -DWITH_SNAPPY=1 -DWITH_ZLIB=1 -DWITH_ZSTD=1 ..
make -j8
cd ../../../
premake5 gmake