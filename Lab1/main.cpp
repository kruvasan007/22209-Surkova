#include "BitArray.h"
#include <iostream>

int main() {
    size_t numBits = 2;
    unsigned long N = 17;

    BitArray bitArray = BitArray(numBits, N);
    bitArray.resize(1);

    std::cout << bitArray.toString() << std::endl;

    return 0;
}
