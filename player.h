// Dans player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include <SDL2/SDL.h>
#include <vector> // Ajout de l'inclusion de la bibliothèque vector

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
    void setWallRects(const std::vector<SDL_Rect>& rects); // Correction de la signature de la fonction
    bool checkCollision() const;

    int mPosX, mPosY;

private:
    int mVelX, mVelY;
    int mHealth;
    std::vector<SDL_Rect> wallRects;
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
    Direction mLastDirection;
    AttackState mAttackState;
    DefenseState mDefenseState;
    AfterAttackState mAfterAttackState;
};

#endif
