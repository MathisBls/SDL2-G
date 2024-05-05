#include <iostream>
#include <SDL2/SDL.h>
#include "constants.h"
#include "player.h"

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

bool initSDL();
void closeSDL();

int main(int argc, char* args[]) {
    if (!initSDL()) {
        std::cout << "Failed to initialize SDL!\n";
        return -1;
    }

    Player player;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            player.handleEvent(e);
        }

        player.move();

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_Rect playerRect = {player.mPosX, player.mPosY, PLAYER_SIZE, PLAYER_SIZE};
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &playerRect);

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

    return true;
}

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = nullptr;
    gWindow = nullptr;

    SDL_Quit();
}