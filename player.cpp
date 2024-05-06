#include "player.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

extern SDL_Renderer* gRenderer;

Player::Player()
{
    mPosX = SCREEN_WIDTH / 2 - PLAYER_SIZE / 2;
    mPosY = SCREEN_HEIGHT / 2 - PLAYER_SIZE / 2;
    mVelX = 0;
    mVelY = 0;
    mHealth = 100;
    mCurrentFrame = 0;
    

    SDL_Surface* idleSurface = IMG_Load("assets/mainchar_idle.png");
    SDL_Surface* walkSurface = IMG_Load("assets/mainchar_walk.png");

    mIdleTexture = SDL_CreateTextureFromSurface(gRenderer, idleSurface);
    mWalkTexture = SDL_CreateTextureFromSurface(gRenderer, walkSurface);

    SDL_FreeSurface(idleSurface);
    SDL_FreeSurface(walkSurface);

    // sachant que l'image total fait 384 x 768

    mFrameWidth = 384;
    mFrameHeight = 768;

}

void Player::handleEvent(SDL_Event &e)
{

    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY -= 1;
            break;
        case SDLK_DOWN:
            mVelY += 1;
            break;
        case SDLK_LEFT:
            mVelX -= 1;
            break;
        case SDLK_RIGHT:
            mVelX += 1;
            break;
        case SDLK_LSHIFT:
            mIsShiftPressed = true;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY += 1;
            break;
        case SDLK_DOWN:
            mVelY -= 1;
            break;
        case SDLK_LEFT:
            mVelX += 1;
            break;
        case SDLK_RIGHT:
            mVelX -= 1;
            break;
        case SDLK_LSHIFT:
            mIsShiftPressed = false;
            break;
        }
    }
}

void Player::move()
{
    int speed = mIsShiftPressed ? PLAYER_FAST_SPEED : PLAYER_SPEED;

    mPosX += mVelX;
    mPosY += mVelY;

    if (mPosX < 0 || mPosX + PLAYER_SIZE > SCREEN_WIDTH)
    {
        mPosX -= mVelX * speed;
    }
    if (mPosY < 0 || mPosY + PLAYER_SIZE > SCREEN_HEIGHT)
    {
        mPosY -= mVelY * speed;
    }
}

void Player::renderHealthBar()
{

    SDL_Rect healthBar = {10, 10, mHealth, 10}; //
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &healthBar);
}

void Player::render()
{
    SDL_Rect srcRect = {0, mCurrentFrame * mFrameHeight, mFrameWidth, mFrameHeight};
    SDL_Rect destRect = {mPosX, mPosY, mFrameWidth, mFrameHeight};

    if(mVelX == 0 && mVelY == 0)
    {
        SDL_RenderCopy(gRenderer, mIdleTexture, &srcRect, &destRect);
    } else {
        SDL_RenderCopy(gRenderer, mWalkTexture, &srcRect, &destRect);
    }

    mCurrentFrame = (mCurrentFrame + 1) % 8;

}

void Player::updateHealth(int newHealth)
{
    mHealth = newHealth;
}

int Player::getHealth() const
{
    return mHealth;
}

// int Player::getDamage() const
// {
//     return mDamage;
// }

// int Player::getSpeed() const
// {
//     return mSpeed;
// }