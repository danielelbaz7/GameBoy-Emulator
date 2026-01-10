//
// Created by Jackson Johannessen on 1/9/26.
//

#include "Launcher.h"

#include <fstream>

#include "portable-file-dialogs.h"

Launcher::Launcher() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //create window & renderer (same as platform mostly)
    window = SDL_CreateWindow("Game Boy Emulator - Launcher",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        160 * 3, 144 * 3, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load fonts
#ifdef _WIN32
    font = TTF_OpenFont("C:\\Windows\\Fonts\\arial.ttf", 16);
    titleFont = TTF_OpenFont("C:\\Windows\\Fonts\\arialbd.ttf", 32);
#elif __APPLE__
    font = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 16);
    titleFont = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 32);
#endif

    if (!font) {
        std::cerr << "Warning: Could not load font\n";
    }
    if (!titleFont) {
        std::cerr << "Warning: Could not load title font\n";
        titleFont = font; // fallback
    }
}

Launcher::~Launcher() {
    if (titleFont != nullptr && titleFont != font) {
        TTF_CloseFont(titleFont);
    }
    if (font != nullptr) {
        TTF_CloseFont(font);
    }
    if (renderer != nullptr) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != nullptr) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
}

bool Launcher::IsClickInRect(int x, int y, SDL_Rect& rect) {
    return (x >= rect.x && x <= rect.x + rect.w &&
            y >= rect.y && y <= rect.y + rect.h);
}

void Launcher::RenderText(const char* text, int x, int y, SDL_Color color, bool centered, bool isTitle, SDL_Rect* clipRect) {
    TTF_Font* useFont = isTitle ? titleFont : font;
    if (!useFont || !text) return;

    SDL_Surface* surface = TTF_RenderText_Blended(useFont, text, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture) {
        if (clipRect) {
            SDL_RenderSetClipRect(renderer, clipRect);
        }

        int finalX = x;
        if (centered) {
            finalX = x - (surface->w / 2);
        }
        SDL_Rect destRect = {finalX, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &destRect);

        if (clipRect) {
            SDL_RenderSetClipRect(renderer, NULL);
        }

        SDL_DestroyTexture(texture);
    }
    SDL_FreeSurface(surface);
}

void Launcher::DrawRoundedRect(SDL_Rect rect, SDL_Color color, int radius) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Draw main rectangles
    SDL_Rect topRect = {rect.x + radius, rect.y, rect.w - 2 * radius, radius};
    SDL_Rect middleRect = {rect.x, rect.y + radius, rect.w, rect.h - 2 * radius};
    SDL_Rect bottomRect = {rect.x + radius, rect.y + rect.h - radius, rect.w - 2 * radius, radius};

    SDL_RenderFillRect(renderer, &topRect);
    SDL_RenderFillRect(renderer, &middleRect);
    SDL_RenderFillRect(renderer, &bottomRect);

    // Draw corners (approximated with filled rectangles)
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, rect.x + w, rect.y + h);
                SDL_RenderDrawPoint(renderer, rect.x + rect.w - w - 1, rect.y + h);
                SDL_RenderDrawPoint(renderer, rect.x + w, rect.y + rect.h - h - 1);
                SDL_RenderDrawPoint(renderer, rect.x + rect.w - w - 1, rect.y + rect.h - h - 1);
            }
        }
    }
} // claude function

//this just takes the relative name of the file out of the full path so it can be displayed
std::string Launcher::GetFilename(const std::string& path) {
    if (path.empty()) return "";
    size_t lastSlash = path.find_last_of("\\/");
    if (lastSlash != std::string::npos) {
        return path.substr(lastSlash + 1);
    }
    return path;
} // claude function

std::string Launcher::OpenFileDialog(const char* filter) {
    // Determine what we're selecting based on the filter
    if (strcmp(filter, "Game Boy ROMs") == 0) {
        // ROM selection
        auto selection = pfd::open_file(
            "Select Game Boy ROM", // title of selection window
            ".",
            { "Game Boy ROMs", "*.gb",
            }, //only allow .gb files
            pfd::opt::none
        ).result();

        return selection.empty() ? "" : selection[0];
    }
    else if (strcmp(filter, "Save Files") == 0) {
        // Save file selection
        auto selection = pfd::open_file(
            "Select Save File",  // Specific title
            ".",
            { "Save Files", "*.sav"
            },  // Only relevant filters
            pfd::opt::none
        ).result();

        return selection.empty() ? "" : selection[0];
    }

    // Fallback (shouldn't happen)
    auto selection = pfd::open_file(
        "Select a file",
        ".",
        { "All Files", "*" }
    ).result();

    return selection.empty() ? "" : selection[0];
}
launcherStatus Launcher::Run() {
    bool quit = false;
    SDL_Event e;
    int mouseX = 0;
    int mouseY = 0;
    bool romButtonHovered = false;
    bool saveButtonHovered = false;
    bool startButtonHovered = false;

    // button positions (x | y | width | height)
    SDL_Rect romButton = {65, 140, 350, 45};
    SDL_Rect saveButton = {65, 230, 350, 45};
    SDL_Rect startButton = {125, 330, 230, 55};

    std::vector<std::string> recentROMs;

    std::ifstream recentROMsFile("recent_roms.txt");
    std::string line;
    while (std::getline(recentROMsFile, line)) {
        recentROMs.push_back(line);
    }

    std::vector<std::string> recentSaves;

    std::ifstream recentSavesFile("recent_savs.txt");
    while (std::getline(recentSavesFile, line)) {
        recentSaves.push_back(line);
    }

    while(!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_MOUSEMOTION) {
                mouseX = e.motion.x;
                mouseY = e.motion.y;
                romButtonHovered = IsClickInRect(mouseX, mouseY, romButton);
                saveButtonHovered = IsClickInRect(mouseX, mouseY, saveButton);
                startButtonHovered = IsClickInRect(mouseX, mouseY, startButton);
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    if (IsClickInRect(mouseX, mouseY, romButton)) {
                        // prompt user to choose rom | update struct
                        std::string path = OpenFileDialog("Game Boy ROMs");
                        currentLauncherStatus.romPath = path;
                    }
                    else if (IsClickInRect(mouseX, mouseY, saveButton)) {
                        // prompt user to choose sav | update struct
                        std::string path = OpenFileDialog("Save Files");
                        currentLauncherStatus.savePath = path;
                    }
                    else if (IsClickInRect(mouseX, mouseY, startButton)) {
                        // exit loop
                        currentLauncherStatus.pressStart= true;
                        quit = true;
                    }
                }
            }
        }

        // Render - gradient background
        for (int y = 0; y < 144 * 3; y++) {
            int r = 15 + (y * 10 / (144 * 3));
            int g = 20 + (y * 15 / (144 * 3));
            int b = 40 + (y * 30 / (144 * 3));
            SDL_SetRenderDrawColor(renderer, r, g, b, 255);
            SDL_RenderClear(renderer); // fixed visual artifacting bug, clears the window's backbuffer before rerender
            SDL_RenderDrawLine(renderer, 0, y, 160 * 3, y);
        }

        SDL_Color whiteColor = {255, 255, 255, 255};
        SDL_Color titleColor = {230, 240, 255, 255};
        SDL_Color darkTextColor = {20, 25, 35, 255};
        SDL_Color subtleWhite = {220, 230, 245, 255};
        SDL_Color buttonColor = {70, 150, 230, 255};
        SDL_Color buttonHoverColor = {90, 170, 250, 255};
        SDL_Color startColor = {80, 200, 120, 255};
        SDL_Color startHoverColor = {100, 220, 140, 255};

        // Title
        RenderText("Game Boy Launcher", 240, 30, titleColor, true, true);

        // ROM section
        RenderText("Choose ROM", 75, 115, subtleWhite);
        DrawRoundedRect(romButton, romButtonHovered ? buttonHoverColor : buttonColor, 8);
        if (!currentLauncherStatus.romPath.empty()) {
            std::string filename = GetFilename(currentLauncherStatus.romPath);
            RenderText(filename.c_str(), 240, 152, whiteColor, true, false, &romButton);
        } else {
            RenderText("Click to select ROM", 240, 152, whiteColor, true);
        }

        // Save section
        RenderText("Choose SAV (Optional)", 75, 205, subtleWhite);
        DrawRoundedRect(saveButton, saveButtonHovered ? buttonHoverColor : buttonColor, 8);
        if (!currentLauncherStatus.savePath.empty()) {
            std::string filename = GetFilename(currentLauncherStatus.savePath);
            RenderText(filename.c_str(), 240, 242, whiteColor, true, false, &saveButton);
        } else {
            RenderText("Click to select SAV", 240, 242, whiteColor, true);
        }

        // Start button
        DrawRoundedRect(startButton, startButtonHovered ? startHoverColor : startColor, 8);
        RenderText("START", 240, 345, darkTextColor, true);

        SDL_RenderPresent(renderer);
    }

    return currentLauncherStatus;
}

