#include <cstdint>
#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <chrono>

#define RANDAVX_512
#define RANDAVX_256
#include <randavx/gen128.h>
#include <randavx/gen256.h>
#include <randavx/gen512.h>

auto bench_generator_mqhr(uint_fast64_t num_iterations = 1'000'000) -> void {
    randavx::MQHRandom512 r{};

    std::set<uint_fast64_t> map;

    for (uint_fast64_t i = 0; i < num_iterations; i++) {
        map.insert(r());
    }

    double unique_percentage = static_cast<double>(map.size()) / num_iterations * 100.0;

    std::cout << "=== Unique Number Test (randavx::MQHRandom512) ===\n";
    std::cout << "=== Unique Numbers: " << map.size() << " ===\n";
    std::cout << "=== Unique Percentage: " << unique_percentage << "% ===\n";
}

auto bench_generator_multir(uint_fast64_t num_iterations = 1'000'000) -> void {
    randavx::MultiRandom512 r{};

    std::set<uint_fast64_t> map;

    for (uint_fast64_t i = 0; i < num_iterations; i++) {
        map.insert(r());
    }

    double unique_percentage = static_cast<double>(map.size()) / num_iterations * 100.0;

    std::cout << "=== Unique Number Test (randavx::MultiRandom512) ===\n";
    std::cout << "=== Unique Numbers: " << map.size() << " ===\n";
    std::cout << "=== Unique Percentage: " << unique_percentage << "% ===\n";
}

auto bench_generator_multir256(uint_fast64_t num_iterations = 1'000'000) -> void {
    randavx::MultiRandom256 r{};

    std::set<uint_fast64_t> map;

    for (uint_fast64_t i = 0; i < num_iterations; i++) {
        map.insert(r());
    }

    double unique_percentage = static_cast<double>(map.size()) / num_iterations * 100.0;

    std::cout << "=== Unique Number Test (randavx::MultiRandom256) ===\n";
    std::cout << "=== Unique Numbers: " << map.size() << " ===\n";
    std::cout << "=== Unique Percentage: " << unique_percentage << "% ===\n";
}

auto bench_generator_multir128(uint_fast64_t num_iterations = 1'000'000) -> void {
    randavx::MultiRandom128 r{};

    std::set<uint_fast64_t> map;

    for (uint_fast64_t i = 0; i < num_iterations; i++) {
        map.insert(r());
    }

    double unique_percentage = static_cast<double>(map.size()) / num_iterations * 100.0;

    std::cout << "=== Unique Number Test (randavx::MultiRandom128) ===\n";
    std::cout << "=== Unique Numbers: " << map.size() << " ===\n";
    std::cout << "=== Unique Percentage: " << unique_percentage << "% ===\n";
}

auto bench_generator_std(uint_fast64_t num_iterations = 1'000'000) -> void {
    std::mt19937_64 r;

    std::set<uint_fast64_t> map;

    for (uint_fast64_t i = 0; i < num_iterations; i++) {
        map.insert(r());
    }

    double unique_percentage = static_cast<double>(map.size()) / num_iterations * 100.0;

    std::cout << "=== Unique Number Test (std::mt19937_64) ===\n";
    std::cout << "=== Unique Numbers: " << map.size() << " ===\n";
    std::cout << "=== Unique Percentage: " << unique_percentage << "% ===\n";
}

auto bench_generator_rdrand(uint_fast64_t num_iterations = 1'000'000) -> void {
    std::mt19937_64 r;

    std::set<uint_fast64_t> map;

    for (uint_fast64_t i = 0; i < num_iterations; i++) {
        uint_fast64_t r = randavx::rdrand();

        map.insert(r);
    }

    double unique_percentage = static_cast<double>(map.size()) / num_iterations * 100.0;

    std::cout << "=== Unique Number Test (RDRAND) ===\n";
    std::cout << "=== Unique Numbers: " << map.size() << " ===\n";
    std::cout << "=== Unique Percentage: " << unique_percentage << "% ===\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);

    bench_generator_mqhr(1'000'000);
    std::cout << "\n";
    bench_generator_multir(1'000'000);
    std::cout << "\n";
    bench_generator_multir256(1'000'000);
    std::cout << "\n";
    bench_generator_multir128(1'000'000);
    std::cout << "\n";
    bench_generator_std(1'000'000);
    std::cout << "\n";
    bench_generator_rdrand(1'000'000);
}