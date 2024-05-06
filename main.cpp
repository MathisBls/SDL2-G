#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "player.h"
#include "map.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
TTF_Font* gFont = nullptr;
SDL_Texture* dungeonFloorTexture = nullptr;

bool initSDL();
void closeSDL();

int main(int argc, char* args[]) {
    if (!initSDL()) {
        std::cout << "Failed to initialize SDL!\n";
        return -1;
    }

    Player player;
    Map map;

    std::vector<std::vector<int>> mapData = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

        

    };

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 1) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            player.handleEvent(e);
        }

        player.move();
        player.updateHealth(91);
        map.loadMap(mapData);

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // Render map
        map.render(gRenderer);

        // Check if player is dead
        if (player.getHealth() <= 0) {
            quit = true;
        }

        // Render player
        SDL_Rect healthBarBackground = {10, 10, 200, 20};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &healthBarBackground);

        int healthBarWidth = static_cast<int>(player.getHealth() * 2);
        SDL_Rect healthBar = {10, 10, healthBarWidth, 20};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &healthBar);

        player.render();

        // std::string DamageText = "Damage: " + std::to_string(player.getDamage());

        SDL_Color textColor = {0, 0, 0};
        // SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, DamageText.c_str(), textColor);
        // if (textSurface == nullptr) {
        //     std::cout << "Failed to create text surface! SDL_Error: " << SDL_GetError() << "\n";
        // } else {
        //     SDL_Texture* textTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
        //     if (textTexture == nullptr) {
        //         std::cout << "Failed to create text texture! SDL_Error: " << SDL_GetError() << "\n";
        //     } else {
        //         SDL_RenderCopy(gRenderer, textTexture, nullptr, nullptr);
        //         SDL_DestroyTexture(textTexture);
        //     }
        //     SDL_FreeSurface(textSurface);
        // }

        SDL_RenderPresent(gRenderer);
    }

    closeSDL();
    return 0;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (TTF_Init() == -1) {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    }

    gWindow = SDL_CreateWindow("Simple SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Surface* dungeonFloorSurface = IMG_Load("assets/Dungeon_Floor.png");
    if (dungeonFloorSurface == nullptr) {
        std::cout << "Failed to load image! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    dungeonFloorTexture = SDL_CreateTextureFromSurface(gRenderer, dungeonFloorSurface);
    if (dungeonFloorTexture == nullptr) {
        std::cout << "Failed to create texture! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    gFont = TTF_OpenFont("Roman SD.ttf", 30);
    if (gFont == nullptr) {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    }

    TTF_SetFontStyle(gFont, TTF_STYLE_NORMAL);
    TTF_SetFontOutline(gFont, 0);
    SDL_FreeSurface(dungeonFloorSurface);

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);

    gRenderer = nullptr;
    gWindow = nullptr;
    gFont = nullptr;

    SDL_Quit();
}
