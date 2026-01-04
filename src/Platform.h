//
// Created by Daniel Elbaz on 1/1/26.
//

#ifndef GAMEBOYEMULATOR_PLATFORM_H
#define GAMEBOYEMULATOR_PLATFORM_H
#include "CPU.h"

//the platform class holds the actual entire computer's logic, pulling from game boy, ppu, etc.
class Platform {
public:
    Platform(const char* filename);
    void Run();

private:
    Memory mem{};
    CPU cpu{mem};
    const unsigned int TcyclesPerFrame{70224};
    const std::chrono::microseconds microSecondsPerFrame = std::chrono::microseconds{16744};

};


#endif //GAMEBOYEMULATOR_PLATFORM_H