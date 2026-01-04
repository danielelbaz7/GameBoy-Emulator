#ifndef GAMEBOYEMULATOR_PPU_H
#define GAMEBOYEMULATOR_PPU_H
#include "Gameboy.h"

class PPU {
public:
    PPU(Gameboy& gb) : gb(gb) {};
    void UpdatePPU(uint8_t TcyclesSinceLastUpdate);

private:
    Gameboy& gb;
    unsigned int TcyclesSinceLastScanline{};
    uint8_t currentScanline{}; //goes from 0-153, last 10 are vblank
    uint8_t currentMode{2};
    bool modesCompleted[4]{}; //mode 2 is OAM, then mode 3 is drawing pixels,
    //then mode 0 is horizontal blank, and mode 1 is vertical blank

    //resets all values to that of a new frame
    void BeginNewFrame();

};


#endif