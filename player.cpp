#include "player.h"
#include <SDL2/SDL.h>

Player::Player() {
    mPosX = SCREEN_WIDTH / 2 - PLAYER_SIZE / 2;
    mPosY = SCREEN_HEIGHT / 2 - PLAYER_SIZE / 2;
    mVelX = 0;
    mVelY = 0;
}

void Player::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVelY -= PLAYER_SPEED;
                break;
            case SDLK_DOWN:
                mVelY += PLAYER_SPEED;
                break;
            case SDLK_LEFT:
                mVelX -= PLAYER_SPEED;
                break;
            case SDLK_RIGHT:
                mVelX += PLAYER_SPEED;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                mIsShiftPressed = true;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVelY += PLAYER_SPEED;
                break;
            case SDLK_DOWN:
                mVelY -= PLAYER_SPEED;
                break;
            case SDLK_LEFT:
                mVelX += PLAYER_SPEED;
                break;
            case SDLK_RIGHT:
                mVelX -= PLAYER_SPEED;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                mIsShiftPressed = false;
                break;
        }
    }
}

void Player::move() {
    int speed = mIsShiftPressed ? PLAYER_FAST_SPEED : PLAYER_SPEED;

    mPosX += mVelX;
    mPosY += mVelY;

    if (mPosX < 0 || mPosX + PLAYER_SIZE > SCREEN_WIDTH) {
        mPosX -= mVelX * speed;
    }
    if (mPosY < 0 || mPosY + PLAYER_SIZE > SCREEN_HEIGHT) {
        mPosY -= mVelY * speed;
    }
}