#ifndef COIN_H
#define COIN_H

#include <SDL2/SDL.h>

class Coin {
public:
    Coin(int x, int y, SDL_Texture *texture);
    void render(SDL_Renderer *renderer) const;
    SDL_Rect getRect() const;
    void move(int newX, int newY) const;
private:
    int mX, mY;
    SDL_Texture *mTexture;     
};

#endif
