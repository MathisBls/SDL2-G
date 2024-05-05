#pragma once // include guard to prevent multiple inclusions of header file

#include <vector>
#include <SDL2/SDL.h>

class Map {
    public:
        Map();
        void loadMap(const std::vector<std::vector<int>>& data);
        void render(SDL_Renderer* renderer);

    private:
        std::vector<std::vector<int>> mapData;
};