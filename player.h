#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include <SDL2/SDL.h>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum class AttackState {
    NONE,
    SLASH
};

enum class AfterAttackState {
    IDLE,
    WALK
};

enum class DefenseState {
    NONE,
    THRUST
};

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
    SDL_Texture* mSlashTexture;
    SDL_Texture* mThrustTexture;
    SDL_Texture* mCoinTexture;
    int mCurrentFrame;
    int mFrameWidth;
    int mFrameHeight;
    int mMoney;
    Uint32 mLastAnimationFrameTime;
    bool mIsShiftPressed;
    Direction mLastDirection; // Nouvelle variable pour stocker la dernière direction
    AttackState mAttackState;
    DefenseState mDefenseState;
    AfterAttackState mAfterAttackState;
};

#endif
