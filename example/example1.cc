#include <bit>
#include <randavx/gen.h>

#include <iostream>
#include <sstream>

#include <bitset>

int main() {
    randavx::MultiRandom r;

    std::cout << "Random with random????\n";
    std::stringstream ss; 
    for (int i = 0; i < 64; i++) {
        int_fast16_t v = r(0, 2);
        ss << v;
    }

    std::cout << "Bits: " << ss.str() << "\n";
    std::cout << "Converted number: " << std::bitset<64>(ss.str()).to_ullong() << "\n";
}