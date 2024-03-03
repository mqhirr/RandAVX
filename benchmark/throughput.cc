#include <cstdint>
#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

#define RANDAVX_512
#define RANDAVX_256
#include <randavx/gen128.h>
#include <randavx/gen256.h>
#include <randavx/gen512.h>

#include <benchmark/benchmark.h>

void warmUp(std::mt19937_64& gen, int num_iterations) {
    for (int i = 0; i < num_iterations; ++i) {
        uint_fast64_t t1 = gen();

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

auto bench_generator_mqhr(int num_iterations = 1'000'000, int num_repeats = 5) -> void {
    randavx::MQHRandom512 r{};

    size_t data_size_per_op = sizeof(uint_fast64_t);
    size_t total_data_generated = data_size_per_op * num_iterations; 

    std::ios_base::sync_with_stdio(false);
    warmUp(r, num_iterations);

    double total_throughput = 0.0;
    for (int k = 0; k < num_repeats; ++k) {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; i++) {
            uint_fast64_t t = r();
            benchmark::DoNotOptimize(t);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        double throughput = static_cast<double>(num_iterations * sizeof(uint_fast64_t)) / (duration * 1.0e-9) / (1024 * 1024 * 1024);

        total_throughput += throughput;
    }

    double average_throughput = total_throughput / num_repeats;

    std::cout << "=== MQHRandom Generator Throughput ===\n";
    std::cout << "Iterations: " << num_iterations << "\n";
    std::cout << "Total Data Generated: " << total_data_generated << " bytes\n";
    std::cout << "Average Throughput (GB/s): " << average_throughput << "\n";
}

auto bench_generator_multir(int num_iterations = 1'000'000, int num_repeats = 5) -> void {
    randavx::MultiRandom512 r{};

    size_t data_size_per_op = sizeof(uint_fast64_t);
    size_t total_data_generated = data_size_per_op * num_iterations; 

    std::ios_base::sync_with_stdio(false);

    std::mt19937_64 gen64;
    warmUp(r, num_iterations);

    double total_throughput = 0.0;
    for (int k = 0; k < num_repeats; ++k) {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; i++) {
            uint_fast64_t t = r();
            benchmark::DoNotOptimize(t);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        double throughput = static_cast<double>(num_iterations * sizeof(uint_fast64_t)) / (duration * 1.0e-9) / (1024 * 1024 * 1024);

        total_throughput += throughput;
    }

    double average_throughput = total_throughput / num_repeats;

    std::cout << "=== MultiRandom Generator Throughput ===\n";
    std::cout << "Iterations: " << num_iterations << "\n";
    std::cout << "Total Data Generated: " << total_data_generated << " bytes\n";
    std::cout << "Average Throughput (GB/s): " << average_throughput << "\n";
}

auto bench_generator_multir256(int num_iterations = 1'000'000, int num_repeats = 5) -> void {
    randavx::MultiRandom256 r{};

    size_t data_size_per_op = sizeof(uint_fast64_t);
    size_t total_data_generated = data_size_per_op * num_iterations; 

    std::ios_base::sync_with_stdio(false);

    std::mt19937_64 gen64;
    warmUp(r, num_iterations);

    double total_throughput = 0.0;
    for (int k = 0; k < num_repeats; ++k) {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; i++) {
            uint_fast64_t t = r();
            benchmark::DoNotOptimize(t);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        double throughput = static_cast<double>(num_iterations * sizeof(uint_fast64_t)) / (duration * 1.0e-9) / (1024 * 1024 * 1024);

        total_throughput += throughput;
    }

    double average_throughput = total_throughput / num_repeats;

    std::cout << "=== MultiRandom256 Generator Throughput ===\n";
    std::cout << "Iterations: " << num_iterations << "\n";
    std::cout << "Total Data Generated: " << total_data_generated << " bytes\n";
    std::cout << "Average Throughput (GB/s): " << average_throughput << "\n";
}

auto bench_generator_multir128(int num_iterations = 1'000'000, int num_repeats = 5) -> void {
    randavx::MultiRandom128 r{};

    size_t data_size_per_op = sizeof(uint_fast64_t);
    size_t total_data_generated = data_size_per_op * num_iterations; 

    std::ios_base::sync_with_stdio(false);

    std::mt19937_64 gen64;
    warmUp(r, num_iterations);

    double total_throughput = 0.0;
    for (int k = 0; k < num_repeats; ++k) {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; i++) {
            uint_fast64_t t = r();
            benchmark::DoNotOptimize(t);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        double throughput = static_cast<double>(num_iterations * sizeof(uint_fast64_t)) / (duration * 1.0e-9) / (1024 * 1024 * 1024);

        total_throughput += throughput;
    }

    double average_throughput = total_throughput / num_repeats;

    std::cout << "=== MultiRandom128 Generator Throughput ===\n";
    std::cout << "Iterations: " << num_iterations << "\n";
    std::cout << "Total Data Generated: " << total_data_generated << " bytes\n";
    std::cout << "Average Throughput (GB/s): " << average_throughput << "\n";
}

auto bench_generator_std(int num_iterations = 1'000'000, int num_repeats = 5) -> void {
    std::mt19937_64 gen64;

    size_t data_size_per_op = sizeof(uint_fast64_t);
    size_t total_data_generated = data_size_per_op * num_iterations; 
    warmUp(gen64, num_iterations);

    double total_throughput = 0.0;
    for (int k = 0; k < num_repeats; ++k) {
        auto start_time = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < num_iterations; i++) {
            uint_fast64_t t = gen64();
            benchmark::DoNotOptimize(t);
        }
        auto end_time = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
        double throughput = static_cast<double>(num_iterations * sizeof(uint_fast64_t)) / (duration * 1.0e-9) / (1024 * 1024 * 1024);

        total_throughput += throughput;
    }

    double average_throughput = total_throughput / num_repeats;

    std::cout << "=== C++ Standard Generator Throughput ===\n";
    std::cout << "Iterations: " << num_iterations << "\n";
    std::cout << "Total Data Generated: " << total_data_generated << " bytes\n";
    std::cout << "Average Throughput (GB/s): " << average_throughput << "\n";
}

int main() {
    const int num_iterations = 25'000'000;
    const int num_repeats = 5;

    bench_generator_mqhr(num_iterations, num_repeats);
    bench_generator_multir(num_iterations, num_repeats);
    bench_generator_multir256(num_iterations, num_repeats);
    bench_generator_multir128(num_iterations, num_repeats);
    bench_generator_std(num_iterations, num_repeats);

    return 0;
}