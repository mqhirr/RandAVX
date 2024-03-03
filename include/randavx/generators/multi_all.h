#ifndef RANDAVX_GENERATORS_MULTI_ALL_H
#define RANDAVX_GENERATORS_MULTI_ALL_H

#include <randavx/cpu.h>
#include <cstdint>
#include <immintrin.h>

#include <type_traits>
#include <limits>
#include <bit>

namespace randavx {
    #ifdef RANDAVX_512
    class MultiRandom512 {
    public:
        MultiRandom512() {
            m_counter = 0;
            seed();
        }

    public:
        auto seed() -> void {
            #pragma unroll(16)
            for (int i = 0; i < 16; ++i) {
                m_state[i] = randavx::rdrand();
            }
        }

        template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        [[nodiscard]] auto get() -> T {
            constexpr uint_fast64_t min = std::numeric_limits<T>::min();
            constexpr uint_fast64_t range = std::numeric_limits<T>::max() - std::numeric_limits<T>::min();

            __m512i rnd = _mm512_load_si512((const __m512i*)(m_state));
            __m512i multiplier = _mm512_set1_epi64(0x9e3779b97f4a7c15);
            rnd = _mm512_mul_epu32(rnd, multiplier);
            _mm512_store_si512((__m512i*)(m_state), rnd);

            uint_fast64_t sum = 0;

            #pragma unroll(16)
            for (int i = 0; i < 16; ++i) {
                sum += m_state[i];
            }

            return static_cast<T>((sum & (range - 1)) + min);
        }

        [[nodiscard]] auto getf() -> double {
            uint_fast64_t value = (*this)();
            __m512i x = _mm512_load_epi64(&value);

            __m512d scale = _mm512_set1_pd(1.0 / (static_cast<double>(std::numeric_limits<uint_fast64_t>::max()) + 1.0));
            __m512d result = _mm512_cvtepi64_pd(x);
            result = _mm512_mul_pd(result, scale);

            alignas(64) double res[16];
            _mm512_store_pd(res, result);

            return res[0];
        }

        [[nodiscard]] auto operator()() -> uint_fast64_t {
            if (m_counter >= 16) {
                __m512i rnd = _mm512_loadu_si512((const __m512i*)m_state);
                __m512i multiplier = _mm512_set1_epi64(0x9e3779b97f4a7c15);
                rnd = _mm512_mul_epu32(rnd, multiplier);
                _mm512_storeu_si512((__m512i*)m_state, rnd);

                m_counter = 0;
            }

            return m_state[m_counter++];
        }
        
        [[nodiscard]] auto operator()(uint_fast64_t min, uint_fast64_t max) -> uint_fast64_t {
            const uint_fast64_t range = max - min;

            uint_fast64_t value = (*this)();
            
            uint_fast64_t scaled = value % (range);
            uint_fast64_t result = scaled + min;

            // value %= range;
            // uint_fast64_t result = value + min;

            return result;
        }

    private:
        alignas(32) uint_fast64_t m_state[16];
        uint_fast8_t m_counter;
    };
    #endif // !RANDAVX_512

    #ifdef RANDAVX_256
    class MultiRandom256 {
    public:
        MultiRandom256() {
            m_counter = 0;
            seed();
        }

    public:
        auto seed() -> void {
            #pragma unroll(4)
            for (int i = 0; i < 4; ++i) {
                m_state[i] = randavx::rdrand();
            }
        }

        template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        [[nodiscard]] auto get() -> T {
            constexpr uint_fast64_t min = std::numeric_limits<T>::min();
            constexpr uint_fast64_t range = std::numeric_limits<T>::max() - std::numeric_limits<T>::min();

            __m256i rnd = _mm256_load_si256((const __m256i*)(m_state));
            __m256i multiplier = _mm256_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm256_mul_epu32(rnd, multiplier);
            _mm256_store_si256((__m256i*)(m_state), rnd);

            uint_fast64_t sum = 0;

            #pragma unroll(4)
            for (int i = 0; i < 4; ++i) {
                sum += m_state[i];
            }

            return static_cast<T>((sum & (range - 1)) + min);
        }

        [[nodiscard]] auto getf() -> double {
            uint_fast64_t value = (*this)();
            __m256i x = _mm256_load_epi64(&value);

            __m256d scale = _mm256_set1_pd(1.0 / (static_cast<double>(std::numeric_limits<uint_fast64_t>::max()) + 1.0));
            __m256d result = _mm256_cvtepi64_pd(x);
            result = _mm256_mul_pd(result, scale);

            alignas(32) double res[4];
            _mm256_store_pd(res, result);

            return res[0];
        }

        [[nodiscard]] auto operator()() -> uint_fast64_t {
            if (m_counter >= 4) {
                __m256i rnd = _mm256_load_si256((const __m256i*)m_state);
                __m256i multiplier = _mm256_set1_epi64x(0x9e3779b97f4a7c15);
                rnd = _mm256_mul_epu32(rnd, multiplier);
                _mm256_store_si256((__m256i*)m_state, rnd);

                m_counter = 0;
            }

            return m_state[m_counter++];
        }

        [[nodiscard]] auto operator()(uint_fast64_t min, uint_fast64_t max) -> uint_fast64_t {
            const uint_fast64_t range = max - min;

            uint_fast64_t value = (*this)();
            
            uint_fast64_t scaled = value % (range);
            uint_fast64_t result = scaled + min;

            // value %= range;
            // uint_fast64_t result = value + min;

            return result;
        }
        
    private:
        alignas(32) uint_fast64_t m_state[4];
        uint_fast8_t m_counter;
    };
    #endif // !RANDAVX_256

    class MultiRandom128 {
    public:
        MultiRandom128() {
            m_counter = 0;
            seed();
        }

    public:
        auto seed() -> void {
            m_state[0] = randavx::rdrand();
            m_state[1] = randavx::rdrand();
        }

        template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        [[nodiscard]] auto get() -> T {
            constexpr uint_fast64_t min = std::numeric_limits<T>::min();
            constexpr uint_fast64_t range = std::numeric_limits<T>::max() - std::numeric_limits<T>::min();

            __m128i rnd = _mm_load_si128((const __m128i*)(m_state));
            __m128i multiplier = _mm_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm_mul_epu32(rnd, multiplier);
            _mm_store_si128((__m128i*)(m_state), rnd);

            uint_fast64_t sum = 0;

            sum += m_state[0];
            sum += m_state[1];

            return static_cast<T>((sum & (range - 1)) + min);
        }

        [[nodiscard]] auto getf() -> double {
            uint_fast64_t value = (*this)();
            __m128i x = _mm_load_epi64(&value);

            __m128d scale = _mm_set1_pd(1.0 / (static_cast<double>(std::numeric_limits<uint_fast64_t>::max()) + 1.0));
            __m128d result = _mm_cvtepi64_pd(x);
            result = _mm_mul_pd(result, scale);

            alignas(16) double res[2];
            _mm_store_pd(res, result);

            return res[0];
        }

        [[nodiscard]] auto operator()() -> uint_fast64_t {
            if (m_counter >= 2) {
                __m128i rnd = _mm_load_si128((const __m128i*)m_state);
                __m128i multiplier = _mm_set1_epi64x(0x9e3779b97f4a7c15);
                rnd = _mm_mul_epu32(rnd, multiplier);
                _mm_store_si128((__m128i*)m_state, rnd);

                m_counter = 0;
            }

            return m_state[m_counter++];
        }

        [[nodiscard]] auto operator()(uint_fast64_t min, uint_fast64_t max) -> uint_fast64_t {
            const uint_fast64_t range = max - min;

            uint_fast64_t value = (*this)();
            
            uint_fast64_t scaled = value % (range);
            uint_fast64_t result = scaled + min;

            // value %= range;
            // uint_fast64_t result = value + min;

            return result;
        }
        
    private:
        alignas(16) uint_fast64_t m_state[2];
        uint_fast8_t m_counter;
    };
}

#endif // !RANDAVX_GENERATORS_MULTI_ALL_H
