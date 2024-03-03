# randavx
random number generator that leverages avx2/avx512/sse4.2 for maximum performance

# requirements
a cpu that supports either sse4.2, avx2 or avx512

# generators
currently there are two generators (both are custom-made)

## mqhrandom (my first implementation)
### features:
- faster than std::mt19937_64 (by like 2x or smth)
## multirandom (my second implementation)
### features:
- faster than mqhrandom by 2x (on all avx2/avx512/sse4.2 stuff)
- for some reason the avx2 one is faster on my cpu, idk why

# examples
check the examples directory