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
    SDL_Surface* coinSurface = IMG_Load("assets/coin.png");
    if (coinSurface == nullptr) {
        std::cout << "Failed to load coin surface! SDL_Error: " << SDL_GetError() << "\n";
    } else {
        mCoinTexture = SDL_CreateTextureFromSurface(gRenderer, coinSurface);
        if (mCoinTexture == nullptr) {
            std::cout << "Failed to create coin texture from surface! SDL_Error: " << SDL_GetError() << "\n";
        }
        SDL_FreeSurface(coinSurface);
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
