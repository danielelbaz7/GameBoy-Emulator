//
// Created by Jackson Johannessen on 1/9/26.
//

#include "Launcher.h"
#include <algorithm>
#include <fstream>

#include "portable-file-dialogs.h"

void Launcher::CreateVectors()  {
    //open an if stream of the file that stores the recent roms
    std::ifstream recentROMsFile("recent_roms.txt");
    std::string line;
    //write every line (each rom) to the vector
    while (std::getline(recentROMsFile, line)) {
        // dont read blank lines or whitespace-only lines
        if (!line.empty() && line.find_first_not_of(" \t\r\n") != std::string::npos) {
            recentROMs.push_back(line);
        }
    }
    //if there is a most recent rom, set the launcher's current rom path

    std::ifstream recentSavesFile("recent_saves.txt");
    while (std::getline(recentSavesFile, line)) {
        // dont read blank lines or whitespace-only lines
        if (!line.empty() && line.find_first_not_of(" \t\r\n") != std::string::npos) {
            recentSaves.push_back(line);
        }
    }
}

Launcher::Launcher() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    //create window & renderer (same as platform mostly)
    window = SDL_CreateWindow("Game Boy Emulator - Launcher",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        160 * 3*resScale, 144 * 3*resScale, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Read in recent Saves and Roms
    CreateVectors();

    // create drop down rects
    romDropdownRect = {371*resScale, 140*resScale, 44*resScale, 45*resScale};
    saveDropdownRect = {65*resScale, 275*resScale, 350*resScale, 200*resScale};

    


    // Load fonts | use pixelated font for 'authentic' look (and bc font sharpness sucks)
#ifdef _WIN32
    font = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 12*resScale);
    if (!font) {
        font = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 14*resScale);
    }
    smallFont = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 9*resScale);
    if (!smallFont) {
        smallFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 11*resScale);
    }
    titleFont = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 20*resScale);
    if (!titleFont) {
        titleFont = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 24*resScale);
    }
#elif __APPLE__
    font = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 12*resScale);
    if (!font) {
        font = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 14*resScale);
    }
    smallFont = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 9*resScale);
    if (!smallFont) {
        smallFont = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 11*resScale);
    }
    titleFont = TTF_OpenFont("fonts/PressStart2P-Regular.ttf", 20*resScale);
    if (!titleFont) {
        titleFont = TTF_OpenFont("/System/Library/Fonts/Helvetica.ttc", 24*resScale);
    }
#endif

    // higher res text
    if (font) {
        TTF_SetFontHinting(font, TTF_HINTING_NONE);
    }
    if (smallFont) {
        TTF_SetFontHinting(smallFont, TTF_HINTING_NONE);
    }
    if (titleFont) {
        TTF_SetFontHinting(titleFont, TTF_HINTING_NONE);
    }

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
    if (smallFont != nullptr && smallFont != font) {
        TTF_CloseFont(smallFont);
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

void Launcher::RenderText(const char* text, int x, int y, SDL_Color color, bool centered, bool isTitle, SDL_Rect* clipRect, bool isSmall) {
    TTF_Font* useFont = isTitle ? titleFont : (isSmall ? smallFont : font);
    if (!useFont || !text) return;

    SDL_Surface* surface = TTF_RenderText_Blended(useFont, text, color);
    if (!surface) return;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture) {
        // texture filtering
        SDL_SetTextureScaleMode(texture, SDL_ScaleModeLinear);
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

// draws NON-ROUND rect w 8-bit border
void Launcher::DrawRoundedRect(SDL_Rect rect, SDL_Color color, int radius, bool useGreyBorder) {
    // Fill button
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);

    if (useGreyBorder) {
        // Grey-themed borders for grey buttons
        // Dark border (bottom + right) - 2 pixels
        SDL_SetRenderDrawColor(renderer, 64, 64, 64, 255); // dark grey
        for (int i = 0; i < 2; i++) {
            SDL_RenderDrawLine(renderer, rect.x + i, rect.y + rect.h - 1 - i, 
                              rect.x + rect.w - 1 - i, rect.y + rect.h - 1 - i); // bottom
            SDL_RenderDrawLine(renderer, rect.x + rect.w - 1 - i, rect.y + i, 
                              rect.x + rect.w - 1 - i, rect.y + rect.h - 1 - i); // right
        }
        
        // Light highlight (top + left) - 2 pixels
        SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255); // light grey
        for (int i = 0; i < 2; i++) {
            SDL_RenderDrawLine(renderer, rect.x + i, rect.y + i, 
                              rect.x + rect.w - 1 - i, rect.y + i); // top
            SDL_RenderDrawLine(renderer, rect.x + i, rect.y + i, 
                              rect.x + i, rect.y + rect.h - 1 - i); // left
        }
    } else {
        // Green-themed borders for green buttons
        // Dark border (bottom + right) - 2 pixels
        SDL_SetRenderDrawColor(renderer, 15, 56, 15, 255); // color_0 (darkest)
        for (int i = 0; i < 2; i++) {
            SDL_RenderDrawLine(renderer, rect.x + i, rect.y + rect.h - 1 - i, 
                              rect.x + rect.w - 1 - i, rect.y + rect.h - 1 - i); // bottom
            SDL_RenderDrawLine(renderer, rect.x + rect.w - 1 - i, rect.y + i, 
                              rect.x + rect.w - 1 - i, rect.y + rect.h - 1 - i); // right
        }
        
        // Light highlight (top + left) - 2 pixels
        SDL_SetRenderDrawColor(renderer, 155, 188, 15, 255); // color_2 (brightest)
        for (int i = 0; i < 2; i++) {
            SDL_RenderDrawLine(renderer, rect.x + i, rect.y + i, 
                              rect.x + rect.w - 1 - i, rect.y + i); // top
            SDL_RenderDrawLine(renderer, rect.x + i, rect.y + i, 
                              rect.x + i, rect.y + rect.h - 1 - i); // left
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
    bool romDropdownHovered = false;

    // button positions (x | y | width | height)
    SDL_Rect romButton = {65*resScale, 140*resScale, 306*resScale, 45*resScale};
    SDL_Rect saveButton = {65*resScale, 230*resScale, 350*resScale, 45*resScale};
    SDL_Rect startButton = {125*resScale, 360*resScale, 230*resScale, 45*resScale};
    SDL_Rect romMenu = {60*resScale, 70*resScale, 360*resScale, 280*resScale};
    SDL_Rect closeButtonRectROM = {
    romMenu.x + romMenu.w - 10*resScale - 10*resScale*2,  // x position with some extra padding
    romMenu.y + 6*resScale,                       // y position
    10*resScale*2,                                       // width (make it a bit bigger than the X for easier clicking)
    10*resScale*2                                        // height
};

    // std::vector<std::string> recentROMs;
    currentLauncherStatus.romPath = !recentROMs.empty() ? recentROMs.back() : "";
    //std::vector<std::string> recentSaves;
    currentLauncherStatus.savePath = !recentSaves.empty() ? recentSaves.back() : "";


    

    while(!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_MOUSEMOTION) {
                mouseX = e.motion.x;
                mouseY = e.motion.y;
            }

            if (e.type == SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    int mouseX = e.button.x;
                    int mouseY = e.button.y;

                    //if the recent roms is full (10 roms, don't do GEQ bc if it went over 10 user modified, let them
                    //modify) then erase the beginning one, and push either way the newest selected one
                    // if recent rom contains select rom, push selected rom to top, remove 'lower' duplicate
                    if (!romDropOpen && IsClickInRect(mouseX, mouseY, romButton)) {
                        std::string path = OpenFileDialog("Game Boy ROMs");
                        // check for existing duplicate
                        auto dupe = std::find(recentROMs.begin(), recentROMs.end(), path);
                        if (dupe != recentROMs.end()) {
                            recentROMs.erase(dupe); // kill old saved rom
                        }
                        else if (recentROMs.size() == 10) {
                            recentROMs.erase(recentROMs.begin());
                        }
                        recentROMs.push_back(path);
                        currentLauncherStatus.romPath = path;
                        //trunc mode explicitly clears the file
                    }
                    else if (!romDropOpen && IsClickInRect(mouseX, mouseY, saveButton)) {
                        // prompt user to choose sav | update struct
                        std::string path = OpenFileDialog("Save Files");
                        //same as above but for saves, not roms
                        // check for existing duplicate
                        auto dupe = std::find(recentSaves.begin(), recentSaves.end(), path);
                        if (dupe != recentSaves.end()) {
                            recentSaves.erase(dupe); // kill old saved sav
                        }
                        else if (recentSaves.size() == 10) {
                            recentSaves.erase(recentSaves.begin());
                        }
                        recentSaves.push_back(path);
                        currentLauncherStatus.savePath = path;
                    }
                    else if (!romDropOpen && IsClickInRect(mouseX, mouseY, startButton)) {
                        //push the roms list to the roms file after wiping the file
                        std::ofstream outROMs("recent_roms.txt", std::ios::trunc);
                        for (std::string save : recentROMs) {
                            outROMs << save << "\n";
                        }
                        outROMs.close();

                        //do the same with saves
                        std::ofstream outSaves("recent_saves.txt", std::ios::trunc);
                        for (std::string save : recentSaves) {
                            outSaves << save << "\n";
                        }
                        outSaves.close();

                        // exit loop
                        currentLauncherStatus.pressStart= true;
                        quit = true;
                    }
                    else if (IsClickInRect(mouseX, mouseY, romDropdownRect)) {
                        //open the rom menu
                        romDropOpen = true;
                    }
                    else if (romDropOpen && IsClickInRect(mouseX, mouseY, closeButtonRectROM)) {
                        romDropOpen = false;
                    }
                    // handle recent rom clikc
                    else if (romDropOpen) {
                        int itemHeight = 25*resScale;
                        int startY = romMenu.y + 45*resScale;

                        for (int i =recentROMs.size() -1; i >= 0; i--) {
                            int itemY = startY + ((recentROMs.size()-1-i) * itemHeight);
                            SDL_Rect itemRect = {romMenu.x + 4, itemY, romMenu.w - 8, itemHeight - 1};
                            if (IsClickInRect(mouseX, mouseY, itemRect)) {
                                // handle dupe
                                std::string selectedPath = recentROMs[i];
                                recentROMs.erase(recentROMs.begin() + i);
                                recentROMs.push_back(selectedPath);
                                currentLauncherStatus.romPath = selectedPath;

                                romDropOpen = false;
                            }

                        }
                    }
                }
            }
        }

        romButtonHovered = IsClickInRect(mouseX, mouseY, romButton);
        saveButtonHovered = IsClickInRect(mouseX, mouseY, saveButton);
        startButtonHovered = IsClickInRect(mouseX, mouseY, startButton);
        romDropdownHovered = IsClickInRect(mouseX, mouseY, romDropdownRect);

        // COLOR SCHEME
        SDL_Color whiteColor = {255, 255, 255, 255};
        SDL_Color titleColor = {188, 201, 116, 255}; // bright lime for title
        SDL_Color darkTextColor = {15, 56, 15, 255}; // dark green for START button text
        SDL_Color subtleWhite = {188, 201, 116, 255}; // LIGHTER lime-yellow for labels (better contrast)
        SDL_Color buttonColor = {48, 98, 48, 255}; // medium green
        SDL_Color buttonHoverColor = {67, 117, 67, 255}; // lighter green hover
        SDL_Color startColor = {155, 188, 15, 255}; // bright lime
        SDL_Color startHoverColor = {175, 203, 30, 255}; // brighter lime hover
        SDL_Color plusButtonColor = {128, 128, 128, 255}; // medium grey
        SDL_Color plusButtonHoverColor = {160, 160, 160, 255}; // lighter grey hover
        SDL_Color menuBgColor = {64, 64, 64, 255}; // dark grey for menu background
        SDL_Color menuItemHoverColor = {96, 96, 96, 255}; // lighter grey for hover
        SDL_Color bgColor = {0, 0, 0, 255}; // DARK green background
        
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderClear(renderer);
        // Title
        RenderText("Game Boy Launcher", 240*resScale, 30*resScale, titleColor, true, true);

        // ROM section
        RenderText("Choose ROM", 75*resScale, 120*resScale, subtleWhite);
        DrawRoundedRect(romButton, romButtonHovered ? buttonHoverColor : buttonColor, 8*resScale);
        // adjusted width to account for borders
        SDL_Rect romClip = {romButton.x + 2, romButton.y, romButton.w - 4, romButton.h};
        if (!currentLauncherStatus.romPath.empty()) {
            std::string filename = GetFilename(currentLauncherStatus.romPath);
            RenderText(filename.c_str(), romButton.x + 8*resScale, 158*resScale, whiteColor, false, false, &romClip, false); // align left, big font
        } else {
            RenderText("Click to select ROM", 240*resScale, 158*resScale, whiteColor, true, false, &romClip, false);
        }

        // Menu button for ROMs
        DrawRoundedRect(romDropdownRect, romDropdownHovered ? plusButtonHoverColor : plusButtonColor, 0, true);
        // Draw white downward arrow/triangle (pixelated/retro style)
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
        int centerX = romDropdownRect.x + romDropdownRect.w / 2;
        int centerY = romDropdownRect.y + romDropdownRect.h / 2;
        int pixelSize = 3*resScale; // size of each pixel block (increased for slightly bigger triangle)
        // Draw pixelated downward triangle (widest at top, point at bottom)
        // Top row: 7 pixels (widest)
        for (int i = -3; i <= 3; i++) {
            SDL_Rect pixel = {centerX + i*pixelSize - pixelSize/2, centerY - 2*pixelSize, pixelSize, pixelSize};
            SDL_RenderFillRect(renderer, &pixel);
        }
        // Second row: 5 pixels
        for (int i = -2; i <= 2; i++) {
            SDL_Rect pixel = {centerX + i*pixelSize - pixelSize/2, centerY - pixelSize, pixelSize, pixelSize};
            SDL_RenderFillRect(renderer, &pixel);
        }
        // Third row: 3 pixels
        for (int i = -1; i <= 1; i++) {
            SDL_Rect pixel = {centerX + i*pixelSize - pixelSize/2, centerY, pixelSize, pixelSize};
            SDL_RenderFillRect(renderer, &pixel);
        }
        // Bottom tip: 1 pixel
        SDL_Rect tipPixel = {centerX - pixelSize/2, centerY + pixelSize, pixelSize, pixelSize};
        SDL_RenderFillRect(renderer, &tipPixel);
        
        // Save section
        RenderText("Choose SAV (Optional)", 75*resScale, 210*resScale, subtleWhite);
        DrawRoundedRect(saveButton, saveButtonHovered ? buttonHoverColor : buttonColor, 8*resScale);
        // adjusted width to account for borders
        SDL_Rect saveClip = {saveButton.x + 2, saveButton.y, saveButton.w - 4, saveButton.h};
        if (!currentLauncherStatus.savePath.empty()) {
            std::string filename = GetFilename(currentLauncherStatus.savePath);
            RenderText(filename.c_str(), saveButton.x + 8*resScale, 248*resScale, whiteColor, false, false, &saveClip); //align left
        } else {
            RenderText("Click to select SAV", 240*resScale, 248*resScale, whiteColor, true, false, &saveClip);
        }

        //DROPDOWNS
        if (romDropOpen) {
            DrawRoundedRect(romMenu, menuBgColor, 8*resScale, true);
            
            // Title at top center
            int menuCenterX = romMenu.x + romMenu.w / 2;
            RenderText("Recent ROMs", menuCenterX, romMenu.y + 15*resScale, whiteColor, true, false, nullptr, false);
            
            // Close button (X) in top right
            int xSize = 10*resScale;
            int xPadding = 10*resScale;
            int xCenterX = romMenu.x + romMenu.w - xPadding - xSize/2;
            int xCenterY = romMenu.y + 10*resScale + 6*resScale; // align with text baseline
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
            // Draw X with diagonal lines
            for (int i = 0; i < 2; i++) {
                // Top-left to bottom-right
                SDL_RenderDrawLine(renderer, xCenterX - xSize/2 + i, xCenterY - xSize/2, xCenterX + xSize/2 + i, xCenterY + xSize/2);
                // Top-right to bottom-left
                SDL_RenderDrawLine(renderer, xCenterX + xSize/2 - i, xCenterY - xSize/2, xCenterX - xSize/2 - i, xCenterY + xSize/2);
            }
            
            // Display recent ROMs
            int itemHeight = 25*resScale;
            int startY = romMenu.y + 45*resScale; // Adjusted to start below title
            SDL_Rect menuClip = {romMenu.x + 4, romMenu.y + 4, romMenu.w - 8, romMenu.h - 8};
            
            for (int i = recentROMs.size() - 1; i >= 0; i--) {
                int itemY = startY + ((recentROMs.size() - 1 - i) * itemHeight);
                SDL_Rect itemRect = {romMenu.x + 4, itemY, romMenu.w - 8, itemHeight - 1};  // -1 to prevent overlap
                
                // Check if this item is hovered
                bool itemHovered = IsClickInRect(mouseX, mouseY, itemRect);
                if (itemHovered) {
                    SDL_SetRenderDrawColor(renderer, menuItemHoverColor.r, menuItemHoverColor.g, menuItemHoverColor.b, menuItemHoverColor.a);
                    SDL_RenderFillRect(renderer, &itemRect);
                }
                
                std::string filename = GetFilename(recentROMs[i]);
                // Center text vertically within the item rectangle
                int textY = itemY + (itemHeight / 2) - 6*resScale; // Roughly center the 12pt font
                RenderText(filename.c_str(), romMenu.x + 10*resScale, textY, whiteColor, false, false, &menuClip, false);
            }
        }

        // Start button
        DrawRoundedRect(startButton, startButtonHovered ? startHoverColor : startColor, 8*resScale);
        RenderText("START", 240*resScale, 377*resScale, darkTextColor, true);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    return currentLauncherStatus;
}
