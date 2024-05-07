#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>

class Enemy {
    public:
        Enemy(int x, int y, int size) : mPosX(x), mPosY(y), mSize(size) {}

        void renderer(SDL_Renderer* renderer);

    private:
        int mPosX, mPosY, mSize;
};

#endif