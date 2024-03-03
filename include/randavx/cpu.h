#ifndef RANDAVX_CPU_H
#define RANDAVX_CPU_H

#include <cstdint>
#include <utility>

#ifdef _WIN32
#include <intrin.h>
#else
#include <immintrin.h>
#endif

namespace randavx {
    [[nodiscard]] inline __attribute__((always_inline)) auto rdrand() -> uint_fast64_t {
        unsigned long long r{};
        _rdrand64_step(&r);

        return r; 
    }
}

#endif // !RANDAVX_CPU_H