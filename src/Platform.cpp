//
// Created by Daniel Elbaz on 1/1/26.
//

#include "Platform.h"

#include <iostream>
#include <thread>

Platform::Platform(const char* filename) {
    mem.LoadRom(filename);
}

//overall run, manages input, interrupts, etc.
void Platform::Run() {
    unsigned int cyclesUsed = 0;
    //using steady clock so we don't realize on the user's computer system time
    auto frameStartTime =
    std::chrono::time_point_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now()
    );
    while (true) {

        if (cpu.stopped) {
            break;
        }

        //only handles fetch, decode, execute, won't do anything if the gameboy is halted
        cyclesUsed += cpu.Step();

        if (cyclesUsed < TcyclesPerFrame) {
            continue;
        }

        cyclesUsed -= TcyclesPerFrame;
        //std::cout << cyclesUsed << std::endl;

        // both framestarttime and now() are time_points, so cast their difference's duration to microseconds
        auto timeSinceLastFrame = std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::steady_clock::now() - frameStartTime);

        //if its been less than 16,744 microseconds (16.744 milliseconds, approx 59.73 fps), wait until it's been that long. else wait no time
        std::chrono::microseconds timeToWait{microSecondsPerFrame - timeSinceLastFrame};

        if (timeToWait > std::chrono::microseconds{0}) {
            std::this_thread::sleep_for(timeToWait);
        }

        frameStartTime = std::chrono::time_point_cast<std::chrono::microseconds>(
                std::chrono::steady_clock::now()
            );

    }
}
