#include <boost/align.hpp>
#include <vector>
#include <random>
class test
{
private:
    int fd_;
    std::size_t block_size;
    std::vector<char,boost::alignment::aligned_allocator<char, 512>>vec;
public:
    test(std::string_view path, std::size_t block_size, int flags);
    test(const test& ass)=delete;
    ~test();
    void test_test();
    static int random(int min, int max);
};

