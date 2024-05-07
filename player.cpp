#include "player.h"
#include "constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <iostream>

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
    
    //sprites du joueur
    SDL_Surface* idleSurface = IMG_Load("assets/sprites/mainchar_idle.png");
    SDL_Surface* walkSurface = IMG_Load("assets/sprites/mainchar_walk.png");
    SDL_Surface* slashSurface = IMG_Load("assets/sprites/mainchar_slash.png");
    SDL_Surface* thrustSurface = IMG_Load("assets/sprites/mainchar_thrust.png");

    //items
    SDL_Surface* coinSurface = IMG_Load("assets/coin.png");

    mIdleTexture = SDL_CreateTextureFromSurface(gRenderer, idleSurface);
    mWalkTexture = SDL_CreateTextureFromSurface(gRenderer, walkSurface);
    mSlashTexture = SDL_CreateTextureFromSurface(gRenderer, slashSurface);
    mThrustTexture = SDL_CreateTextureFromSurface(gRenderer, thrustSurface);
    mCoinTexture = SDL_CreateTextureFromSurface(gRenderer, coinSurface);

    SDL_FreeSurface(idleSurface);
    SDL_FreeSurface(walkSurface);
    SDL_FreeSurface(slashSurface);
    SDL_FreeSurface(thrustSurface);
    SDL_FreeSurface(coinSurface);

    // sachant que l'image total fait 384 x 768

    mFrameWidth = 192;
    mFrameHeight = 192;

}

void Player::handleEvent(SDL_Event& e) {
    float speed = PLAYER_SPEED;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
                mVelY = -speed;
                mLastDirection = Direction::UP;
                break;
            case SDLK_DOWN:
                mVelY = speed;
                mLastDirection = Direction::DOWN;
                break;
            case SDLK_LEFT:
                mVelX = -speed;
                mLastDirection = Direction::LEFT;
                break;
            case SDLK_RIGHT:
                mVelX = speed;
                mLastDirection = Direction::RIGHT;
                break;
            case SDLK_j:
                // Attaque
                mAttackState = AttackState::SLASH;
                mAfterAttackState = AfterAttackState::IDLE;
                break;
            case SDLK_k:
                // Défense
                mDefenseState = DefenseState::THRUST;
                break;
        }
    } else if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP:
            case SDLK_DOWN:
                mVelY = 0;
                break;
            case SDLK_LEFT:
            case SDLK_RIGHT:
                mVelX = 0;
                break;
            case SDLK_j:
                mAttackState = AttackState::NONE;
                break;
            case SDLK_k:
                mDefenseState = DefenseState::NONE;
                break;
        }
    }
}


void Player::render() {
    Uint32 currentTicks = SDL_GetTicks();
    if (currentTicks - mLastAnimationFrameTime >= 100) {
        if (mVelX == 0 && mVelY == 0) {
            mCurrentFrame = (mCurrentFrame + 1) % 2; // animation en boucle sur 2 frames
        } else {
            mCurrentFrame = (mCurrentFrame + 1) % 8; // animation pour le personnage en marche
        }
        mLastAnimationFrameTime = currentTicks;
    }

    int frameRow = 0;
    if (mVelX < 0) {
        frameRow = 1; // vers la gauche
    } else if (mVelX > 0) {
        frameRow = 3; // vers la droite
    } else if (mVelY < 0) {
        frameRow = 0; // dos
    } else if (mVelY > 0) {
        frameRow = 2; // vers le bas
    }

    SDL_Rect srcRect = {mCurrentFrame * mFrameWidth, frameRow * mFrameHeight, mFrameWidth, mFrameHeight};
    SDL_Rect destRect = {mPosX, mPosY, mFrameWidth, mFrameHeight};

    if (mVelX == 0 && mVelY == 0) {
        // Animation en idle
        switch (mLastDirection) {
            case Direction::UP:
                srcRect.y = 0; // Utiliser la partie de la texture idle correspondant à la direction vers le haut
                break;
            case Direction::DOWN:
                srcRect.y = mFrameHeight * 2; // Utiliser la partie de la texture idle correspondant à la direction vers le bas
                break;
            case Direction::LEFT:
                srcRect.y = mFrameHeight; // Utiliser la partie de la texture idle correspondant à la direction vers la gauche
                break;
            case Direction::RIGHT:
                srcRect.y = mFrameHeight * 3; // Utiliser la partie de la texture idle correspondant à la direction vers la droite
                break;
        }
        SDL_RenderCopy(gRenderer, mIdleTexture, &srcRect, &destRect);
    } else {
        // Animation en marche
        SDL_RenderCopy(gRenderer, mWalkTexture, &srcRect, &destRect);
    }

    if(mAttackState != AttackState::NONE) {
        // Animation d'attaque
        switch (mAttackState) {
            case AttackState::SLASH:
                SDL_RenderCopy(gRenderer, mSlashTexture, &srcRect, &destRect);
                
                if(currentTicks - mLastAnimationFrameTime >= 100) {
                   //5frames par attaque
                   if(mCurrentFrame == 4)
                   {
                        mAttackState = AttackState::NONE;
                        switch(mAfterAttackState)
                        {
                            case AfterAttackState::IDLE:
                                mVelX = 0;
                                mVelY = 0;
                                break;
                            case AfterAttackState::WALK:
                                mVelX = PLAYER_SPEED;
                                mVelY = 0;
                                break;
                        }
                   }
                   mLastAnimationFrameTime = currentTicks; // Reset the animation frame time
                }
                break;
        }
    }

}

void Player::move()
{

    int coinPosX = 32;
    int coinPosY = 192;
    int distance = sqrt(pow(mPosX - coinPosX, 2) + pow(mPosY - coinPosY, 2));

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


    if (distance < 10)
    {
        mMoney += 5;
        std::cout << "Money: " << mMoney << std::endl;
    }
}

void Player::renderHealthBar()
{

    SDL_Rect healthBar = {10, 10, mHealth, 10}; //
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &healthBar);
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