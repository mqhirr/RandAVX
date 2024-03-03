#ifndef RANDAVX_GENERATORS_MQHR_ALL_H
#define RANDAVX_GENERATORS_MQHR_ALL_H

#include <randavx/cpu.h>
#include <cstdint>
#include <immintrin.h>

#include <type_traits>
#include <limits>
#include <bit>

namespace randavx {
    #ifdef RANDAVX_512
    class MQHRandom512 {
    public:
        MQHRandom512() {
            alignas(64) uint_fast64_t t[8];

            #pragma unroll(8)
            for (int i = 0; i < 8; ++i) {
                t[i] = rdrand();
            }
            _mm512_store_si512((__m512i*)m_state, _mm512_load_si512((__m512i*)t));
        }

    public:
        uint_fast64_t operator()(uint_fast64_t min, uint_fast64_t max) {
            uint_fast64_t range = max - min;

            __m512i rnd = _mm512_load_si512((__m512i*)m_state);
            __m512i multiplier = _mm512_set1_epi64(0x9e3779b97f4a7c15);
            rnd = _mm512_mul_epu32(rnd, multiplier);
            _mm512_store_si512((__m512i*)m_state, rnd);

            uint_fast64_t sum = 0;
            for (int i = 0; i < 8; ++i) {
                sum += m_state[i];
            }

            sum = (sum ^ (sum >> 17)) * 0x9e3779b97f4a7c15;
            sum = (sum ^ (sum >> 23)) * 0x9e3779b97f4a7c15;
            
            uint_fast64_t scaled = sum & (range - 1);
            uint_fast64_t result = scaled + min;

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return result;
        }

        template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        T get() {
            constexpr uint_fast64_t min = std::numeric_limits<T>::min();
            constexpr uint_fast64_t range = std::numeric_limits<T>::max() - std::numeric_limits<T>::min();

            __m512i rnd = _mm512_load_si512((const __m512i*)(m_state));
            __m512i multiplier = _mm512_set1_epi64(0x9e3779b97f4a7c15);
            rnd = _mm512_mul_epu32(rnd, multiplier);
            _mm512_store_si512((__m512i*)(m_state), rnd);

            uint_fast64_t sum = 0;

            #pragma unroll(8)
            for (int i = 0; i < 8; ++i) {
                sum += m_state[i];
            }

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return static_cast<T>((sum & (range - 1)) + min);
        }
        
        double getf() {
            __m512i rnd = _mm512_load_si512((const __m512i*)(m_state));
            __m512i multiplier = _mm512_set1_epi64(0x9e3779b97f4a7c15);
            rnd = _mm512_mul_epu32(rnd, multiplier);
            _mm512_store_si512((__m512i*)(m_state), rnd);

            __m512d scale = _mm512_set1_pd(1.0 / (static_cast<double>(std::numeric_limits<uint_fast64_t>::max()) + 1.0));
            __m512d result = _mm512_cvtepi64_pd(rnd);
            result = _mm512_mul_pd(result, scale);

            alignas(64) double res[8];
            _mm512_store_pd(res, result);

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return res[0];
        }
    
        uint_fast64_t operator()() {
            __m512i rnd = _mm512_load_si512((const __m512i*)(m_state));
            __m512i multiplier = _mm512_set1_epi64(0x9e3779b97f4a7c15);
            rnd = _mm512_mul_epu32(rnd, multiplier);
            _mm512_store_si512((__m512i*)(m_state), rnd);

            return m_state[0];
        }

    private:
        alignas(64) uint_fast64_t m_state[8];
    };
    #endif // !RANDAVX_512

    #ifdef RANDAVX_256
    class MQHRandom256 {
    public:
        MQHRandom256() {
            alignas(32) uint_fast64_t t[4];

            #pragma unroll(4)
            for (int i = 0; i < 4; ++i) {
                t[i] = rdrand();
            }
            _mm256_store_si256((__m256i*)m_state, _mm256_load_si256((__m256i*)t));
        }

    public:
        uint_fast64_t operator()(uint_fast64_t min, uint_fast64_t max) {
            uint_fast64_t range = max - min;

            __m256i rnd = _mm256_load_si256((__m256i*)m_state);
            __m256i multiplier = _mm256_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm256_mul_epu32(rnd, multiplier);
            _mm256_store_si256((__m256i*)m_state, rnd);

            uint_fast64_t sum = 0;
            #pragma unroll(4)
            for (int i = 0; i < 4; ++i) {
                sum += m_state[i];
            }

            sum = (sum ^ (sum >> 17)) * 0x9e3779b97f4a7c15;
            sum = (sum ^ (sum >> 23)) * 0x9e3779b97f4a7c15;
            
            uint_fast64_t scaled = sum & (range - 1);
            uint_fast64_t result = scaled + min;

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 4; ++i) {
                m_state[i] = t;
            }
            #endif

            return result;
        }

        template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        T get() {
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

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 4; ++i) {
                m_state[i] = t;
            }
            #endif

            return static_cast<T>((sum & (range - 1)) + min);
        }
        
        double getf() {
            __m256i rnd = _mm256_load_si256((const __m256i*)(m_state));
            __m256i multiplier = _mm256_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm256_mul_epu32(rnd, multiplier);
            _mm256_store_si256((__m256i*)(m_state), rnd);

            __m256d scale = _mm256_set1_pd(1.0 / (static_cast<double>(std::numeric_limits<uint_fast64_t>::max()) + 1.0));
            __m256d result = _mm256_cvtepi64_pd(rnd);
            result = _mm256_mul_pd(result, scale);

            alignas(32) double res[4];
            _mm256_store_pd(res, result);

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return res[0];
        }
    
        uint_fast64_t operator()() {
            __m256i rnd = _mm256_load_si256((const __m256i*)(m_state));
            __m256i multiplier = _mm256_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm256_mul_epu32(rnd, multiplier);
            _mm256_store_si256((__m256i*)(m_state), rnd);

            return m_state[0];
        }

    private:
        alignas(32) uint_fast64_t m_state[4];
    };
    #endif // !RANDAVX_256

    class MQHRandom128 {
    public:
        MQHRandom128() {
            alignas(16) uint_fast64_t t[2];

            t[0] = rdrand();
            t[1] = rdrand();

            _mm_store_si128((__m128i*)m_state, _mm_load_si128((__m128i*)t));
        }

    public:
        uint_fast64_t operator()(uint_fast64_t min, uint_fast64_t max) {
            uint_fast64_t range = max - min;

            __m128i rnd = _mm_load_si128((__m128i*)m_state);
            __m128i multiplier = _mm_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm_mul_epu32(rnd, multiplier);
            _mm_store_si128((__m128i*)m_state, rnd);

            uint_fast64_t sum = 0;
            for (int i = 0; i < 8; ++i) {
                sum += m_state[i];
            }

            sum = (sum ^ (sum >> 17)) * 0x9e3779b97f4a7c15;
            sum = (sum ^ (sum >> 23)) * 0x9e3779b97f4a7c15;
            
            uint_fast64_t scaled = sum & (range - 1);
            uint_fast64_t result = scaled + min;

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return result;
        }

        template <typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
        T get() {
            constexpr uint_fast64_t min = std::numeric_limits<T>::min();
            constexpr uint_fast64_t range = std::numeric_limits<T>::max() - std::numeric_limits<T>::min();

            __m128i rnd = _mm_load_si128((const __m128i*)(m_state));
            __m128i multiplier = _mm_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm_mul_epu32(rnd, multiplier);
            _mm_store_si128((__m128i*)(m_state), rnd);

            uint_fast64_t sum = 0;

            #pragma unroll(2)
            for (int i = 0; i < 2; ++i) {
                sum += m_state[i];
            }

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return static_cast<T>((sum & (range - 1)) + min);
        }
        
        double getf() {
            __m128i rnd = _mm_load_si128((const __m128i*)(m_state));
            __m128i multiplier = _mm_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm_mul_epu32(rnd, multiplier);
            _mm_store_si128((__m128i*)(m_state), rnd);

            __m128d scale = _mm_set1_pd(1.0 / (static_cast<double>(std::numeric_limits<uint_fast64_t>::max()) + 1.0));
            __m128d result = _mm_cvtepi64_pd(rnd);
            result = _mm_mul_pd(result, scale);

            alignas(16) double res[2];
            _mm_store_pd(res, result);

            #ifdef RANDAVX_RESEED
            uint_fast64_t t = rdrand();

            for (int i = 0; i < 8; ++i) {
                m_state[i] = t;
            }
            #endif

            return res[0];
        }
    
        uint_fast64_t operator()() {
            __m128i rnd = _mm_load_si128((const __m128i*)(m_state));
            __m128i multiplier = _mm_set1_epi64x(0x9e3779b97f4a7c15);
            rnd = _mm_mul_epu32(rnd, multiplier);
            _mm_store_si128((__m128i*)(m_state), rnd);

            return m_state[0];
        }

    private:
        alignas(16) uint_fast64_t m_state[2];
    };
}

#endif // !RANDAVX_GENERATORS_MQHR_ALL_H