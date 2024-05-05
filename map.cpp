#include "map.h"
#include "textures.h"
#include "constants.h"
#include <SDL2/SDL_image.h>

// Utilisez extern pour accéder à dungeonFloorTexture défini dans main.cpp
extern SDL_Texture* dungeonFloorTexture;

Map::Map() {
    mapData = {
       
    };
}

void Map::loadMap(const std::vector<std::vector<int>>& data) {
    mapData = data;
}

void Map::render(SDL_Renderer* renderer) {
    // Utilisez le renderer passé en paramètre plutôt que gRenderer
    for (size_t y = 0; y < mapData.size(); ++y) {
        for (size_t x = 0; x < mapData[y].size(); ++x) {
            SDL_Rect destRect = {static_cast<int>(x * TILE_SIZE), static_cast<int>(y * TILE_SIZE), TILE_SIZE, TILE_SIZE};            switch (mapData[y][x]) {
                case 0:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TEXTURE_RECT_1, &destRect);
                    break;
                case 1:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TEXTURE_RECT_2, &destRect);
                    break;
                case 2:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TEXTURE_RECT_3, &destRect);
                    break;
                default:
                    // Cas par défaut
                    break;
            }

            int screenX = static_cast<int>(x * TILE_SIZE);
            int screenY = static_cast<int>(y * TILE_SIZE);
            SDL_Rect rect = {screenX, screenY, TILE_SIZE, TILE_SIZE};
            // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderDrawRect(renderer, &rect);
        }
    }
}
