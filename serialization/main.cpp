#include <iostream>
#include <benchmark/benchmark.h>
#include <fcntl.h>
#include "class.hpp"
#include <optional>

std::optional<class test> test_;

static void func(benchmark::State& state){
    for (auto _ : state)
        test_->test_test();
}

int main(int argc, char* argv[]){
    try {
        if(argc<3)
        {
            throw std::runtime_error("error xd\n");
        }
        std::string f1=argv[1];
        std::size_t f_size=std::stoul(argv[2]);
        int mode = std::stoul(argv[3]); //040000
        if(mode == 1){
            mode = O_DIRECT|O_RDONLY;
        }
        test_.emplace(f1, f_size, mode);
            BENCHMARK(func);
            ::benchmark::RunSpecifiedBenchmarks();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
    return 0;
}



