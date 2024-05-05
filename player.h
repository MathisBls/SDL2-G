#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include <SDL2/SDL.h>

class Player {
public:
    Player();
    void handleEvent(SDL_Event& e);
    void move();
    void renderHealthBar();
    void updateHealth(int health);
    int getHealth() const;
    int getDamage() const;
    int getSpeed() const;

    int mPosX, mPosY;

private:
    int mVelX, mVelY;
    int mHealth;
    int mDamage;
    int mSpeed;
    bool mIsShiftPressed;
};

#endif