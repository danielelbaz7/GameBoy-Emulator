#include <iostream>

#include "Gameboy.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Gameboy g;
    uint16_t value = 8;
    uint16_t returnAddress = value++;
    std::cout << returnAddress;
    return 0;
}
