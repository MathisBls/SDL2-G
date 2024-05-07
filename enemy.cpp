#include "enemy.h"

void Enemy::renderer(SDL_Renderer* renderer) {
    SDL_Rect rect = {mPosX, mPosY, mSize, mSize};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}