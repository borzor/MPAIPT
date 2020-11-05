#include <iostream>
#include <benchmark/benchmark.h>
#include <fcntl.h>
#include "class.h"

static void func(benchmark::State& state, std::string path, int flag){
    test check(path,state.range(0),flag);
    try {
        for (auto _ : state)
            check.test_test();
    }
    catch(const std::exception& e){
        std::cerr << e.what() << '\n';
    }
}


BENCHMARK_CAPTURE(func, state, "/home/boris/test8gb.txt", O_RDONLY)->Arg(16384);
BENCHMARK_CAPTURE(func, state, "/home/boris/test8gb.txt", O_RDONLY|O_DIRECT)->Arg(16384);
BENCHMARK_CAPTURE(func, state, "/media/boris/_borzor/test8gb.txt", O_RDONLY)->Arg(16384);
BENCHMARK_CAPTURE(func, state, "/media/boris/_borzor/test8gb.txt", O_RDONLY|O_DIRECT)->Arg(16384);
BENCHMARK_CAPTURE(func, state, "/media/boris/533f2c93-7470-451f-991a-5757fc7ad28e/backup1/test8gb.txt", O_RDONLY)->Arg(16384);
BENCHMARK_CAPTURE(func, state, "/media/boris/533f2c93-7470-451f-991a-5757fc7ad28e/backup1/test8gb.txt", O_RDONLY|O_DIRECT)->Arg(16384);
BENCHMARK_MAIN();
