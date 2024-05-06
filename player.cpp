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
    mLastAnimationFrameTime = SDL_GetTicks();
    

    SDL_Surface* idleSurface = IMG_Load("assets/sprites/mainchar_idle.png");
    SDL_Surface* walkSurface = IMG_Load("assets/sprites/mainchar_walk.png");

    mIdleTexture = SDL_CreateTextureFromSurface(gRenderer, idleSurface);
    mWalkTexture = SDL_CreateTextureFromSurface(gRenderer, walkSurface);

    SDL_FreeSurface(idleSurface);
    SDL_FreeSurface(walkSurface);

    // sachant que l'image total fait 384 x 768

    mFrameWidth = 192;
    mFrameHeight = 192;

}

void Player::handleEvent(SDL_Event &e)
{
    float speed = PLAYER_SPEED;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY = -speed;
            break;
        case SDLK_DOWN:
            mVelY = speed;
            break;
        case SDLK_LEFT:
            mVelX = -speed;
            break;
        case SDLK_RIGHT:
            mVelX = speed;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            mVelY = 0;
            break;
        case SDLK_DOWN:
            mVelY = 0;
            break;
        case SDLK_LEFT:
            mVelX = 0;
            break;
        case SDLK_RIGHT:
            mVelX = 0;
            break;
        case SDLK_LSHIFT:
            mIsShiftPressed = false;
            break;
        }
    }
}

void Player::move()
{

    mPosX += mVelX;
    mPosY += mVelY;

    if (mPosX < 0)
    {
        mPosX = 0;
    }
    else if (mPosX + PLAYER_SIZE > SCREEN_WIDTH)
    {
        mPosX = SCREEN_WIDTH - PLAYER_SIZE;
    }

    if (mPosY < 0)
    {
        mPosY = 0;
    }
    else if (mPosY + PLAYER_SIZE > SCREEN_HEIGHT)
    {
        mPosY = SCREEN_HEIGHT - PLAYER_SIZE;
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

    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks - mLastAnimationFrameTime >= 100)
    {
        if (mVelX == 0 && mVelY == 0)
        {
            mCurrentFrame = (mCurrentFrame + 1) % 2; // animation en boucle sur 2 frames
        }
        else
        {
            mCurrentFrame = (mCurrentFrame + 1) % 8; // animation pour le personnage en marche
        }
        mLastAnimationFrameTime = currentTicks;
    }

    int frameRow = 0;
    if (mVelX < 0)
    {
        frameRow = 1; // vers la gauche
    }
    else if (mVelX > 0)
    {
        frameRow = 3; // vers la droite
    }
    else if (mVelY < 0)
    {
        frameRow = 0; // dos
    }
    else if (mVelY > 0)
    {
        frameRow = 2; // vers le bas
    }

    SDL_Rect srcRect = {mCurrentFrame * mFrameWidth, frameRow * mFrameHeight, mFrameWidth, mFrameHeight};
    SDL_Rect destRect = {mPosX, mPosY, mFrameWidth, mFrameHeight};

    if (mVelX == 0 && mVelY == 0)
    {
        // Animation en idle
        SDL_RenderCopy(gRenderer, mIdleTexture, &srcRect, &destRect);
    }
    else
    {
        // Animation en marche
        SDL_RenderCopy(gRenderer, mWalkTexture, &srcRect, &destRect);
        
    }
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