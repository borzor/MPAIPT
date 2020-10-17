#include <iostream>
#include <fstream>
#include <benchmark/benchmark.h>
#include <fcntl.h>
#include <unistd.h>
#include <random>

static void create(){
    std::ofstream test("/home/boris/test4gb.txt");
        for(int i = 0; i<429496729;i++){
          test<<"1234567890";
     }
    test.close();
}
int random(int min, int max) {
    static std::mt19937 prng(std::random_device{}());
    return std::uniform_int_distribution<>(min, max)(prng);
}
static void with_cache(benchmark::State& state, std::string path){//
    int fd;
    void *buf=malloc(state.range(0));
    if((fd = open(path.c_str(), O_RDONLY))==-1)
        std::cerr<<"no file\n";
    for (auto _ : state) {
        if(pread(fd, buf, state.range(0), random(0,1048000)*state.range(0))<state.range(0))
            std::cerr<<" error on read\n";
    }
    free(buf);
    close(fd);
}

static void without_cache(benchmark::State& state, std::string path){
    int fd;
    void *buf;
    if((fd = open(path.c_str(), O_RDONLY|O_DIRECT))==-1)
        std::cerr<<"no file";
    posix_memalign(&buf, 512, state.range(0));
    for (auto _ : state) {
        if(pread(fd, buf, state.range(0), random(0,1048000)*state.range(0))<state.range())
            std::cerr<<"error on read\n";
    }
    free(buf);
    close(fd);
}
BENCHMARK_CAPTURE(with_cache, state, "/home/boris/test8gb.txt")->Arg(4096)->Arg(8192);
BENCHMARK_CAPTURE(without_cache, state, "/home/boris/test8gb.txt")->Arg(4096)->Arg(8192);
BENCHMARK_CAPTURE(with_cache, state, "/media/boris/533f2c93-7470-451f-991a-5757fc7ad28e/backup1/test8gb.txt")->Arg(4096)->Arg(8192);
BENCHMARK_CAPTURE(without_cache, state, "/media/boris/533f2c93-7470-451f-991a-5757fc7ad28e/backup1/test8gb.txt")->Arg(4096)->Arg(8192);
BENCHMARK_MAIN();

//media/boris/533f2c93-7470-451f-991a-5757fc7ad28e/backup1/test8gb.txt
//media/boris/533f2c93-7470-451f-991a-5757fc7ad28e/backup1/test4gb.txt
