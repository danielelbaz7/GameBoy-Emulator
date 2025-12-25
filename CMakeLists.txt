cmake_minimum_required(VERSION 4.0)
project(GameBoyEmulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(GameBoyEmulator src/main.cpp
        src/Gameboy.cpp
        src/Gameboy.h)
