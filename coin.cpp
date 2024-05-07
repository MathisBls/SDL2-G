#include "coin.h"

Coin::Coin(int x, int y, SDL_Texture *texture) : mX(x), mY(y), mTexture(texture) {}


void Coin::render(SDL_Renderer *renderer) const {
    SDL_Rect coinRect = {mX, mY, 32, 32};
    SDL_RenderCopy(renderer, mTexture, nullptr, &coinRect);
}

SDL_Rect Coin::getRect() const {
    return {mX, mY, 32, 32};
}

void Coin::move(int newX, int newY) const {
    const_cast<int&>(mX) = newX;
    const_cast<int&>(mY) = newY;
}