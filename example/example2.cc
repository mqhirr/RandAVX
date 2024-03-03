#include <randavx/gen.h>

#include <iostream>

int main() {
    randavx::MultiRandom r{};
    
    std::ios_base::sync_with_stdio(false);
    for (int i = 0; i < 10; i++) {
        std::cout << r(0, 10) << "\n";
    }

    return 0;
}