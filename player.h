#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include <SDL2/SDL.h>

class Player {
public:
    Player();
    void handleEvent(SDL_Event& e);
    void move();

    int mPosX, mPosY;

private:
    int mVelX, mVelY;
    bool mIsShiftPressed;
};

#endif