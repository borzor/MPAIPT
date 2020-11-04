#include "class.h"
#include <boost/align.hpp>
#include <random>
#include <stdexcept>
#include <fcntl.h>
#include <sys/eventfd.h>

test::test(std::string path, std::size_t block_size,int flags)
        : block_size(block_size),vec(block_size)
    {
        if((fd_ = open(path.c_str(), flags))==-1)
            throw std::runtime_error("class:open failed");
}
    int test::random(int min, int max) {
        static std::mt19937 prng(std::random_device{}());
        return std::uniform_int_distribution<>(min, max)(prng);
    }
    void test::test_test()
    {
        std::size_t offset = random(0,488000);
        offset*=block_size;
        uint64_t ret = pread(fd_, &vec[0], block_size, offset);
        if(ret!=vec.size())
            throw std::runtime_error("pread: failed");
    }
test::~test()
{
    close(fd_);
}
