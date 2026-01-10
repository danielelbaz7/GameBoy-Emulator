#include <iostream>
#include "Platform.h"
#include "Launcher.h"



int main(int argc, char* argv[]) {
    // change to just accept the executable name or just run executable
    // uses sdl 'start' window to prompt for rom file and optional save file
    // on button press, builds platform with given data

    // less than 2 args means executable and that's all
    if (argc < 2) {
        // std::cerr << "You have the wrong number of arguments!";
        // // change to call launcher
        launcherStatus runInfo;
        {
            Launcher launcher;
            runInfo = launcher.Run();
        } // launcher closes
        if (runInfo.romPath == "") {
            std::cerr << "No ROM file selected\n";
            return -1;
        }
        if (runInfo.pressStart) {
            //pass a nullptr if we didnt choose a savefile
            Platform platform(runInfo.romPath.c_str(), runInfo.savePath == "" ? nullptr : runInfo.savePath.c_str());
            platform.Run();
        }
        return 0;

    }
    return 0;
}
