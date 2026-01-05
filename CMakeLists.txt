cmake_minimum_required(VERSION 4.0)
project(GameBoyEmulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameBoyEmulator src/main.cpp
        src/CPU.cpp
        src/CPU.h
        src/OpcodeHelpers.cpp
        src/OpcodeHelpers.h
        src/Platform.cpp
        src/Platform.h
        src/Opcodes.cpp
        src/PPU.cpp
        src/PPU.h
        src/Memory.cpp
        src/Memory.h)

target_include_directories(GameBoyEmulator PRIVATE
        /opt/homebrew/include
)

target_link_directories(GameBoyEmulator PRIVATE
        /opt/homebrew/lib
)

target_link_libraries(GameBoyEmulator PRIVATE
        SDL2
)

target_link_libraries(GameBoyEmulator PRIVATE
        /opt/homebrew/opt/sdl2/lib/libSDL2.dylib)

