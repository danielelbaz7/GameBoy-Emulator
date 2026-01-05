//
// Created by Daniel Elbaz on 1/1/26.
//

#ifndef GAMEBOYEMULATOR_PLATFORM_H
#define GAMEBOYEMULATOR_PLATFORM_H
#include "CPU.h"
#include <chrono>

#include <SDL2/SDL.h>

#include "PPU.h"

//the platform class holds the actual entire computer's logic, pulling from cpu, ppu, etc.
class Platform {
public:
    Platform(const char* filename);
    void Run();

    void DrawFramebuffer(uint32_t *frameBuffer, uint16_t colCount);

private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Texture* texture = nullptr;

    Memory mem{};
    CPU cpu{mem};
    PPU ppu{mem};
    const unsigned int TcyclesPerFrame{70224};
    const std::chrono::microseconds microSecondsPerFrame = std::chrono::microseconds{16744};

};


#endif //GAMEBOYEMULATOR_PLATFORM_H