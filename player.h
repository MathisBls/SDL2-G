#ifndef PLAYER_H // include guard
#define PLAYER_H

#include <SDL2/SDL.h>

class Player {
    public:
        Player(SDL_Rect rect);
        void move(SDL_Event& event);
        SDL_Rect& getRect();

    private:
        SDL_Rect rect;
};

#endif // PLAYER_H