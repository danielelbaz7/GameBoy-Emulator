cmake_minimum_required(VERSION 3.10)
project(GameBoyEmulator)

set(CMAKE_CXX_STANDARD 20)

# Platform-specific SDL2 configuration
if(WIN32)
    # Windows with MinGW
    set(SDL2_DIR "C:/sdl2/SDL2-2.30.10/x86_64-w64-mingw32")
    set(SDL2_INCLUDE_DIR "${SDL2_DIR}/include/SDL2")
    set(SDL2_LIB_DIR "${SDL2_DIR}/lib")
elseif(APPLE)
    # macOS with Homebrew
    set(SDL2_INCLUDE_DIR "/opt/homebrew/include")
    set(SDL2_LIB_DIR "/opt/homebrew/lib")
else()
    # Linux - use pkg-config
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
endif()

add_executable(GameBoyEmulator
        src/main.cpp
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
        src/Memory.h
)

target_include_directories(GameBoyEmulator PRIVATE ${SDL2_INCLUDE_DIR})
target_link_directories(GameBoyEmulator PRIVATE ${SDL2_LIB_DIR})

if(WIN32)
    target_link_libraries(GameBoyEmulator PRIVATE mingw32 SDL2main SDL2)
    # Copy SDL2.dll to output directory on Windows
    add_custom_command(TARGET GameBoyEmulator POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SDL2_DIR}/bin/SDL2.dll"
            $<TARGET_FILE_DIR:GameBoyEmulator>
    )
elseif(APPLE)
    target_link_libraries(GameBoyEmulator PRIVATE SDL2)
else()
    target_link_libraries(GameBoyEmulator PRIVATE ${SDL2_LIBRARIES})
endif()
