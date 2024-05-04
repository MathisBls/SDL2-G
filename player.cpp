#include "player.h"

Player::Player(SDL_Rect rect) : rect(rect) {}

void Player::move(SDL_Event& event){
    const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
    if(keystates[SDL_SCANCODE_LEFT]){ // if the left arrow key is pressed
        rect.x -= 5;
    }
    if(keystates[SDL_SCANCODE_RIGHT]){ // if the right arrow key is pressed
        rect.x += 5;
    }
    if(keystates[SDL_SCANCODE_UP]){ // if the up arrow key is pressed
        rect.y -= 5;
    }
    if(keystates[SDL_SCANCODE_DOWN]){ // if the down arrow key is pressed
        rect.y += 5;
    }
}

    SDL_Rect& Player::getRect(){
        return rect;
    }