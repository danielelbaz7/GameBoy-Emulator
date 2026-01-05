//
// Created by Daniel Elbaz on 1/1/26.
//

#include "Platform.h"

#include <thread>

Platform::Platform(const char* filename)
    : window(SDL_CreateWindow("Gameboy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        160 * 3, 144 * 3, SDL_WINDOW_SHOWN)),
    renderer(SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED )),
    texture(SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 160, 144)) {
    //initializes the draw color, and this whole constructor places the rom into memory and creates an SDL window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    mem.LoadRom(filename);
}

//overall run, manages input, interrupts, etc.
void Platform::Run() {
    unsigned int cyclesUsed = 0;
    //using steady clock so we don't rely on the user's computer system time
    auto frameStartTime =
    std::chrono::time_point_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now()
    );

    bool quit = false;

    while (!quit) {

        if (cpu.stopped) {
            break;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                quit = true;
        }


        //only handles fetch, decode, execute, won't do anything if the gameboy is halted
        uint8_t TcyclesUsedThisInstr = cpu.Step();
        cyclesUsed += TcyclesUsedThisInstr;

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


void Platform::DrawFramebuffer(uint32_t *frameBuffer, uint16_t rowCount) {
    SDL_RenderClear(renderer);

}
