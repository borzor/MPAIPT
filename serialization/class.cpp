#include "class.hpp"
#include <exception>
#include <fcntl.h>
#include <cerrno>
#include <system_error>

test::test(std::string_view path, std::size_t block_size,int flags)
    : block_size(block_size),vec(block_size)
    {
        if((fd_ = open(std::string(path).c_str(), flags))==-1)
            throw std::system_error(errno,std::system_category(),"open failed");
}
int test::random(int min, int max) {
    std::mt19937 prng(std::random_device{}());
    return std::uniform_int_distribution<>(min, max)(prng);
}
void test::test_test()
    {
    std::size_t offset = random(0,488000);
    offset*=block_size;
    uint64_t ret = pread(fd_, &vec[0], block_size, offset);
    if(ret!=vec.size())
        throw std::system_error(errno,std::system_category(),"read failed");
}
test::~test()
{
    close(fd_);
}
