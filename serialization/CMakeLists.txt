cmake_minimum_required(VERSION 3.5)

project(serialization LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(benchmark REQUIRED)

add_executable(serialization main.cpp class.h class.cpp)
target_link_libraries(serialization ${Boost_LIBRARIES} benchmark::benchmark)
