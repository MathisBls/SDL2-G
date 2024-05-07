#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constants.h"
#include "player.h"
#include "map.h"
#include "coin.h"
#include "game.h"

SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
TTF_Font *gFont = nullptr;
SDL_Texture *dungeonFloorTexture = nullptr;
SDL_Texture *mCoinTexture = nullptr;

bool initSDL();
void closeSDL();

int main(int argc, char *args[])
{
    if (!initSDL())
    {
        std::cout << "Failed to initialize SDL!\n";
        return -1;
    }

    Player player;
    Map map;
    Game game;

    std::vector<std::vector<int>> mapData = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 3, 4, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 6, 7, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 9, 10, 11, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    bool quit = false;
    SDL_Event e;
    int FPS = 60;
    int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;

    while (!quit)
    {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
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
        if (player.getHealth() <= 0)
        {
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

        SDL_RenderPresent(gRenderer);

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
        {
            SDL_Delay(frameDelay - frameTime);
        }

        game.loadTextures(); 

        for(auto &coin : game.getCoins()) {
            int newX = rand() % SCREEN_WIDTH;
            int newY = rand() % SCREEN_HEIGHT;
            coin.move(newX, newY);
            coin.render(gRenderer);
}

    }


    closeSDL();
    return 0;
}

bool initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    }

    gWindow = SDL_CreateWindow("Simple SDL Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Surface *dungeonFloorSurface = IMG_Load("assets/Dungeon_Floor.png");
    if (dungeonFloorSurface == nullptr)
    {
        std::cout << "Failed to load image! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    dungeonFloorTexture = SDL_CreateTextureFromSurface(gRenderer, dungeonFloorSurface);
    if (dungeonFloorTexture == nullptr)
    {
        std::cout << "Failed to create texture! SDL_Error: " << SDL_GetError() << "\n";
        return false;
    }

    SDL_Texture *coinTexture = IMG_LoadTexture(gRenderer, "assets/coin.png");
    if (coinTexture == nullptr)
    {
        std::cout << "Failed to load image! SDL_image Error: " << IMG_GetError() << "\n";
        return false;
    }

    gFont = TTF_OpenFont("Roman SD.ttf", 30);
    if (gFont == nullptr)
    {
        std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << "\n";
        return false;
    }

    TTF_SetFontStyle(gFont, TTF_STYLE_NORMAL);
    TTF_SetFontOutline(gFont, 0);
    SDL_FreeSurface(dungeonFloorSurface);

    return true;
}

void closeSDL()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyTexture(dungeonFloorTexture);
    SDL_DestroyTexture(mCoinTexture);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(gFont);

    gRenderer = nullptr;
    gWindow = nullptr;
    gFont = nullptr;

    SDL_Quit();
}
