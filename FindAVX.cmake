# credits: https://gist.github.com/UnaNancyOwen/263c243ae1e05a2f9d0e

macro(CHECK_FOR_AVX)
    set(AVX_FLAGS)
    include(CheckCXXSourceRuns)
    set(CMAKE_REQUIRED_FLAGS)

    if (MSVC)
        # Check AVX
        if(NOT MSVC_VERSION LESS 1600)
        set(CMAKE_REQUIRED_FLAGS "/arch:AVX")
        endif()

        check_cxx_source_runs("
        #include <immintrin.h>
        int main()
        {
          __m128i a, b, c;
          const float src[8] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };
          float dst[8];
          a = _mm_loadu_ps( src );
          b = _mm_loadu_ps( src );
          c = _mm_add_ps( a, b );
          _mm_storeu_ps( dst, c );
          for( int i = 0; i < 8; i++ ){
            if( ( src[i] + src[i] ) != dst[i] ){
              return -1;
            }
          }
          return 0;
        }"
        HAVE_AVX_EXTENSIONS)

        # Check AVX2
        if(NOT MSVC_VERSION LESS 1800)
        set(CMAKE_REQUIRED_FLAGS "/arch:AVX2")
        endif()

        check_cxx_source_runs("
        #include <immintrin.h>
        int main()
        {
          __m256i a, b, c;
          const int src[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
          int dst[8];
          a =  _mm256_loadu_si256( (__m256i*)src );
          b =  _mm256_loadu_si256( (__m256i*)src );
          c = _mm256_add_epi32( a, b );
          _mm256_storeu_si256( (__m256i*)dst, c );
          for( int i = 0; i < 8; i++ ){
            if( ( src[i] + src[i] ) != dst[i] ){
              return -1;
            }
          }
          return 0;
        }"
        HAVE_AVX2_EXTENSIONS)

        # Check AVX512
        if(NOT MSVC_VERSION LESS 1800)
        set(CMAKE_REQUIRED_FLAGS "/arch:AVX512")
        endif()

        check_cxx_source_runs("
        #include <immintrin.h>
        int main()
        {
          __m512i a, b, c;
          const int src[8] = { 1, 2, 3, 4, 5, 6, 7, 8 };
          int dst[8];
          a =  _mm512_loadu_si512( (__m512i*)src );
          b =  _mm512_loadu_si512( (__m512i*)src );
          c = _mm512_add_epi32( a, b );
          _mm512_storeu_si512( (__m512i*)dst, c );
          for( int i = 0; i < 8; i++ ){
            if( ( src[i] + src[i] ) != dst[i] ){
              return -1;
            }
          }
          return 0;
        }"
        HAVE_AVX512_EXTENSIONS)

        if (HAVE_AVX512_EXTENSIONS AND NOT MSVC_VERSION LESS 1800)
            set(AVX_FLAGS "${AVX_FLAGS} /arch:AVX512")
        elseif(HAVE_AVX2_EXTENSIONS AND NOT MSVC_VERSION LESS 1800)
            set(AVX_FLAGS "${AVX_FLAGS} /arch:AVX2")
        elseif(HAVE_AVX_EXTENSIONS  AND NOT MSVC_VERSION LESS 1600)
            set(AVX_FLAGS "${AVX_FLAGS} /arch:AVX")
        endif()
    endif()
endmacro(CHECK_FOR_AVX)