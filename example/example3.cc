#include <randavx/gen.h>
#include <iostream>

int main() {
    std::cout << "Your CPU Supports the following: " <<
        #ifdef RANDAVX_512
        "AVX512 " <<
        #endif
        #ifdef RANDAVX_256
        "AVX2 " <<
        #endif
        "SSE4.2" << "\n";
    return 0;
}