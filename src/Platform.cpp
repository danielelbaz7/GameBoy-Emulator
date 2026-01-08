//
// Created by Daniel Elbaz on 1/1/26.
//

#include "Platform.h"

#include <iostream>
#include <thread>

Platform::Platform(const char* filename)
    : window(SDL_CreateWindow("Gameboy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        160 * 3, 144 * 3, SDL_WINDOW_SHOWN)),
    renderer(SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED )),
    texture(SDL_CreateTexture( renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 160, 144)) {
    //initializes the draw color, and this whole constructor places the rom into memory and creates an SDL window
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    mem.InitializeMemory();
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


        //only handles fetch, decode, execute, won't do anything if the gameboy is halted
        //call PPU with the same amount of instructions we used in the CPU
        uint8_t TcyclesUsedThisInstr = cpu.Step();
        ppu.UpdatePPU(TcyclesUsedThisInstr);
        mem.UpdateCounter(TcyclesUsedThisInstr);
        cyclesUsed += TcyclesUsedThisInstr;

        if (cyclesUsed < TcyclesPerFrame) {
            continue;
        }

        cyclesUsed -= TcyclesPerFrame;

        //keyboard mappings: WASD -> D-pad (Direction buttons)
        // A button -> Z, B button -> X, Start -> C, Select -> V
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            switch (e.type) {
                //quit the program if the user quits the application
                case SDL_QUIT: {
                    quit = true;
                } break;

                case SDL_KEYDOWN: {
                    switch (e.key.keysym.sym) {
                        //direction buttons
                        case SDLK_w: { SetButtonStatusInMemory("W", KeyStatus::Pressed); break; }
                        case SDLK_a: { SetButtonStatusInMemory("A", KeyStatus::Pressed); break; }
                        case SDLK_s: { SetButtonStatusInMemory("S", KeyStatus::Pressed); break; }
                        case SDLK_d: { SetButtonStatusInMemory("D", KeyStatus::Pressed); break; }

                        case SDLK_z: { SetButtonStatusInMemory("Z", KeyStatus::Pressed); break; }
                        case SDLK_x: { SetButtonStatusInMemory("X", KeyStatus::Pressed); break; }
                        case SDLK_c: { SetButtonStatusInMemory("C", KeyStatus::Pressed); break; }
                        case SDLK_v: { SetButtonStatusInMemory("V", KeyStatus::Pressed); break; }

                    }
                }

                case SDL_KEYUP: {
                    switch (e.key.keysym.sym) {
                        //direction buttons
                        case SDLK_w: { SetButtonStatusInMemory("W", KeyStatus::Released); break; }
                        case SDLK_a: { SetButtonStatusInMemory("A", KeyStatus::Released); break; }
                        case SDLK_s: { SetButtonStatusInMemory("S", KeyStatus::Released); break; }
                        case SDLK_d: { SetButtonStatusInMemory("D", KeyStatus::Released); break; }

                        case SDLK_z: { SetButtonStatusInMemory("Z", KeyStatus::Released); break; }
                        case SDLK_x: { SetButtonStatusInMemory("X", KeyStatus::Released); break; }
                        case SDLK_c: { SetButtonStatusInMemory("C", KeyStatus::Released); break; }
                        case SDLK_v: { SetButtonStatusInMemory("V", KeyStatus::Released); break; }

                    }
                }
            }

        }

        //render last so we account for the time it takes to render in our frametime waiter
        DrawFramebuffer(ppu.getFrameBuffer(), ppu.getColCount() * 4);

        // both framestarttime and now() are time_points, so cast their difference's duration to microseconds
        auto timeSinceLastFrame = std::chrono::duration_cast<std::chrono::microseconds>
        (std::chrono::steady_clock::now() - frameStartTime);

        std::cout << timeSinceLastFrame << std::endl;

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


void Platform::DrawFramebuffer(uint32_t *frameBuffer, uint16_t colCount) {
    //pass in the texture, nullptr means we want to update the entire screen, the framebuffer to place on the texture
    //and then the number of bytes in a row
    SDL_UpdateTexture(texture, nullptr, frameBuffer, colCount);

    SDL_RenderClear(renderer);
    //first nullptr means we use the entire source texture, second one means fill the entire renderer
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Platform::SetButtonStatusInMemory(std::string key, KeyStatus status) {
    KeyStatus oldStatus = buttonStatus[keysToButtons[key]];
    //set the new status
    buttonStatus[keysToButtons[key]] = status;

    if(status == KeyStatus::Pressed && oldStatus == KeyStatus::Released) {
        mem.SetInputInterrupt();
    }
}