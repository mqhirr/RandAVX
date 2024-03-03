#include "randavx/cpu.h"
#include <benchmark/benchmark.h>

#define RANDAVX_512
#define RANDAVX_256
#include <randavx/gen128.h>
#include <randavx/gen256.h>
#include <randavx/gen512.h>

#include <cstdint>
#include <iostream>
#include <map>
#include <random>
#include <chrono>
#include <iomanip>

void warmUp(std::mt19937_64& gen, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = gen();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(std::mt19937& gen, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = gen();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = randavx::rdrand();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(randavx::MQHRandom512& r, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = r();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(randavx::MQHRandom256& r, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = r();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(randavx::MQHRandom128& r, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = r();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(randavx::MultiRandom512& r, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = r();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(randavx::MultiRandom256& r, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = r();

        benchmark::DoNotOptimize(t1);
    }
}

void warmUp(randavx::MultiRandom128& r, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = r();

        benchmark::DoNotOptimize(t1);
    }
}

void BenchMultiRandom512(benchmark::State& state) {
    randavx::MultiRandom512 r;
    warmUp(r, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = r();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMultiRandom256(benchmark::State& state) {
    randavx::MultiRandom256 r;
    warmUp(r, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = r();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMultiRandom128(benchmark::State& state) {
    randavx::MultiRandom128 r;
    warmUp(r, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = r();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMQHRandom512(benchmark::State& state) {
    randavx::MQHRandom512 r;
    warmUp(r, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = r();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMQHRandom256(benchmark::State& state) {
    randavx::MQHRandom256 r;
    warmUp(r, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = r();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMQHRandom128(benchmark::State& state) {
    randavx::MQHRandom128 r;
    warmUp(r, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = r();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMT19937Random_64(benchmark::State& state) {
    std::mt19937_64 gen64;
    warmUp(gen64, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = gen64();
        benchmark::DoNotOptimize(t);
    }
}

void BenchMT19937Random(benchmark::State& state) {
    std::mt19937 gen32;
    warmUp(gen32, 1000000);

    for (auto _ : state) {
        uint_fast64_t t = gen32();
        benchmark::DoNotOptimize(t);
    }
}

void BenchRDRand(benchmark::State& state) {
    warmUp(1000000);

    for (auto _ : state) {
        uint_fast64_t t = randavx::rdrand();
        benchmark::DoNotOptimize(t);
    }
}

BENCHMARK(BenchRDRand);
BENCHMARK(BenchMT19937Random);
BENCHMARK(BenchMT19937Random_64);

BENCHMARK(BenchMultiRandom512);
BENCHMARK(BenchMultiRandom256);
BENCHMARK(BenchMultiRandom128);

BENCHMARK(BenchMQHRandom512);
BENCHMARK(BenchMQHRandom256); // stack smashing detected??
BENCHMARK(BenchMQHRandom128);

BENCHMARK_MAIN();
