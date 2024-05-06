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
    void render();
    void updateHealth(int health);
    int getHealth() const;

    int mPosX, mPosY;

private:
    int mVelX, mVelY;
    int mHealth;
    SDL_Texture* mIdleTexture;
    SDL_Texture* mWalkTexture;
    int mCurrentFrame;
    int mFrameWidth;
    int mFrameHeight;
    Uint32 mLastAnimationFrameTime;
    bool mIsShiftPressed;
};

#endif