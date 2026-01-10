#pragma once
#include <string>
#include <iostream>
#include <thread>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


struct launcherStatus {
    std::string romPath;
    std::string savePath;
    bool pressStart = false;
};


class Launcher {


    bool IsClickInRect(int x, int y, SDL_Rect& rect);

    std::string OpenFileDialog(const char* filter);

    void RenderText(const char* text, int x, int y, SDL_Color color, bool centered = false, bool isTitle = false, SDL_Rect* clipRect = nullptr);
    void DrawRoundedRect(SDL_Rect rect, SDL_Color color, int radius);
    std::string GetFilename(const std::string& path);

public:

    Launcher();
    ~Launcher();
    launcherStatus Run();



private:
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    TTF_Font* font = nullptr;
    TTF_Font* titleFont = nullptr;
    launcherStatus currentLauncherStatus;
    const int resScale = 1; // how much resolution is scaled by

};