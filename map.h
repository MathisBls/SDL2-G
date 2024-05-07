#ifndef MAP_H
#define MAP_H

#include <vector>
#include <SDL2/SDL.h>

class Map {
public:
    Map();
    void loadMap(const std::vector<std::vector<int>>& data);
    void render(SDL_Renderer* renderer);
    const std::vector<SDL_Rect>& getWallRects() const;

private:
    std::vector<std::vector<int>> mapData;
    std::vector<SDL_Rect> wallRects; // Vecteur pour stocker les rectangles de murs
};

#endif
