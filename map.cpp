// map.cpp

#include "map.h"
#include "textures.h" 
#include "constants.h"

Map::Map() {
    mapData = {
       
    };
}

void Map::loadMap(const std::vector<std::vector<int>>& data) {
    mapData = data;
}

void Map::render(SDL_Renderer* renderer) {
    for (size_t y = 0; y < mapData.size(); ++y) {
        for (size_t x = 0; x < mapData[y].size(); ++x) {
            SDL_Color color;
            switch (mapData[y][x]) {
                case 0:
                    color = COLOR_GREEN;
                    break;
                case 1:
                    color = COLOR_RED;
                    break;
                default:
                    color = COLOR_BLUE;
                    break;
            }

            int screenX = static_cast<int>(x * TILE_SIZE);
            int screenY = static_cast<int>(y * TILE_SIZE);
            SDL_Rect rect = {screenX, screenY, TILE_SIZE, TILE_SIZE};
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
            SDL_RenderFillRect(renderer, &rect);
        }
    }
}