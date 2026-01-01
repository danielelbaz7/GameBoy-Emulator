//
// Created by Daniel Elbaz on 1/1/26.
//

#include "Platform.h"

#include <iostream>

Platform::Platform(const char* filename) {
    gb.LoadRom(filename);
}

//overall run, manages input, interrupts, etc.
void Platform::Run( ) {
    while (true) {

        if (gb.stopped) {
            continue;
        }

        //only handles fetch, decode, execute
        gb.Step();
    }
}
