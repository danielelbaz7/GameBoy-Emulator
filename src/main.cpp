#include <iostream>

#include "Platform.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "You have the wrong number of arguments!";
        return 1;
    }
    const char* ROMFilename = argv[1];
    Platform platform(ROMFilename);
    platform.Run();

    return 0;
}
