#include "game.h"
#include "constants.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL_image.h>

extern SDL_Renderer* gRenderer;

Game::Game() {
    loadTextures();
    generateCoins();
    
}

void Game::loadTextures() {
    mCoinTexture = IMG_LoadTexture(gRenderer, "assets/coin.png");
    if (mCoinTexture == nullptr) {
        std::cout << "Failed to load coin texture! SDL_Error: " << SDL_GetError() << "\n";
    }
}

void Game::generateCoins() {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;

    Coin coin(x, y, mCoinTexture);
    mCoins.push_back(coin);
}

const std::vector<Coin>& Game::getCoins() const {
    return mCoins;
}
