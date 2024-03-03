cmake_minimum_required(VERSION 3.25)

include("FindAVX.cmake")

project(
    randavx 
    LANGUAGES CXX 
    DESCRIPTION "random number generator that aims to be fast (uses avx512)"
    VERSION 1.0
)

if (MSVC)
    CHECK_FOR_AVX()
endif ()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(RANDAVX_BENCHMARK "enables building of benchmarks" ON)
option(RANDAVX_BUILD_EXAMPLES "enables building of examples" ON)

if (LINUX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native")
elseif (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${AVX_FLAGS}")
else ()
message("i dont know about your platform :p")
endif () 

add_library(mqh_randavx INTERFACE)
target_include_directories(mqh_randavx INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
add_library(mqh::randavx ALIAS mqh_randavx)

if (RANDAVX_BENCHMARK)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_ENABLE_TESTING OFF)
add_subdirectory(vendor/benchmark)

add_executable(benchmark_throughput benchmark/throughput.cc)
target_link_libraries(benchmark_throughput mqh::randavx benchmark)

add_executable(benchmark_unique benchmark/unique.cc)
target_link_libraries(benchmark_unique mqh::randavx)

add_executable(benchmark_randavx benchmark/bench.cc)
target_link_libraries(benchmark_randavx mqh::randavx benchmark)
endif ()

if (RANDAVX_BUILD_EXAMPLES)
add_executable(example1 example/example1.cc)
target_link_libraries(example1 mqh::randavx)

add_executable(example2 example/example2.cc)
target_link_libraries(example2 mqh::randavx)

add_executable(example3 example/example3.cc)
target_link_libraries(example3 mqh::randavx)
endif ()