#ifndef RANDAVX_GEN_AVX_H
#define RANDAVX_GEN_AVX_H

#if defined(__GNUC__) || defined(__clang__)
    #if defined(__AVX512F__) || defined(__AVX512CD__) || defined(__AVX512ER__) || defined(__AVX512PF__) || defined(__AVX512BW__) || defined(__AVX512DQ__) || defined(__AVX512VL__) || defined(__AVX512IFMA__) || defined(__AVX512VBMI__) || defined(__AVX512VBMI2__) || defined(__AVX512VNNI__) || defined(__AVX512BITALG__) || defined(__AVX512VPOPCNTDQ__) || defined(__AVX5124FMAPS__) || defined(__AVX5124VNNIW__) || defined(__AVX512VPOPCNTDQ__) || defined(__AVX5124VNNIW__) || defined(__AVX5124FMAPS__)
        #define RANDAVX_512
        #include <randavx/gen512.h>

        #ifndef RANDAVX_BEST_SET
            #define RANDAVX_BEST_SET
            namespace randavx {
                using MQHRandom = randavx::MQHRandom512;
                using MultiRandom = randavx::MultiRandom512;
            }
        #endif // RANDAVX_BEST_SET
    #endif
    #if defined(__AVX2__)
        #define RANDAVX_256
        #include <randavx/gen256.h>

        #ifndef RANDAVX_BEST_SET
            #define RANDAVX_BEST_SET
            namespace randavx {
                using MQHRandom = randavx::MQHRandom256;
                using MultiRandom = randavx::MultiRandom256;
            }
        #endif // RANDAVX_BEST_SET
    #endif
    #if defined(__SSE4_2__)
        #include <randavx/gen128.h>

        #ifndef RANDAVX_BEST_SET
            #define RANDAVX_BEST_SET
            namespace randavx {
                using MQHRandom = randavx::MQHRandom128;
                using MultiRandom = randavx::MultiRandom128;
            }
        #endif // RANDAVX_BEST_SET
    #else
        #error "Unsupported, please make sure to check if your CPU supports SSE/AVX2/AVX512 or check if your compiler is compiling for SSE/AVX2/AVX512"
    #endif
#elif defined(_MSC_VER)
    #if defined(__AVX512F__) || defined(__AVX512CD__) || defined(__AVX512ER__) || defined(__AVX512PF__) || defined(__AVX512BW__) || defined(__AVX512DQ__) || defined(__AVX512VL__) || defined(__AVX512IFMA__) || defined(__AVX512VBMI__) || defined(__AVX512VBMI2__) || defined(__AVX512VNNI__) || defined(__AVX512BITALG__) || defined(__AVX512VPOPCNTDQ__) || defined(__AVX5124FMAPS__) || defined(__AVX5124VNNIW__) || defined(__AVX512VPOPCNTDQ__) || defined(__AVX5124VNNIW__) || defined(__AVX5124FMAPS__)
        #define RANDAVX_512
        #include <randavx/gen512.h>

        #ifndef RANDAVX_BEST_SET
            #define RANDAVX_BEST_SET
            namespace randavx {
                using MQHRandom = randavx::MQHRandom512;
                using MultiRandom = randavx::MultiRandom512;
            }
        #endif // RANDAVX_BEST_SET
    #endif
    #if defined(__AVX2__)
        #define RANDAVX_256
        #include <randavx/gen256.h>

        #ifndef RANDAVX_BEST_SET
            #define RANDAVX_BEST_SET
            namespace randavx {
                using MQHRandom = randavx::MQHRandom256;
                using MultiRandom = randavx::MultiRandom256;
            }
        #endif // RANDAVX_BEST_SET
    #endif
    #if defined(__SSE4_2__)
        #include <randavx/gen128.h>

        #ifndef RANDAVX_BEST_SET
            #define RANDAVX_BEST_SET
            namespace randavx {
                using MQHRandom = randavx::MQHRandom128;
                using MultiRandom = randavx::MultiRandom128;
            }
        #endif // RANDAVX_BEST_SET
    #else
        #error "Unsupported, please make sure to check if your CPU supports SSE/AVX2/AVX512 or check if your compiler is compiling for SSE/AVX2/AVX512"
    #endif
#else
    #error "Unknown Compiler"
#endif

#endif // !RANDAVX_GEN_AVX_H