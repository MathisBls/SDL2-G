#include "map.h"
#include "textures.h"
#include "constants.h"
#include <SDL2/SDL_image.h>

// Utilisez extern pour accéder à dungeonFloorTexture défini dans main.cpp
extern SDL_Texture* dungeonFloorTexture;
extern SDL_Texture* dungeonWallTexture; // collision

Map::Map() {
    mapData = {
       
    };
}

void Map::loadMap(const std::vector<std::vector<int>>& data) {
    mapData = data;

    // Effacez les rectangles de murs précédents
    wallRects.clear();

    // Parcourez les données de la carte pour trouver les murs et ajoutez leurs rectangles au vecteur wallRects
    for (size_t y = 0; y < mapData.size(); ++y) {
        for (size_t x = 0; x < mapData[y].size(); ++x) {
            if (mapData[y][x] == 12 || mapData[y][x] == 13 || mapData[y][x] == 17 || mapData[y][x] == 18 || mapData[y][x] == 19 || mapData[y][x] == 20) {
                SDL_Rect wallRect = {static_cast<int>(x * TILE_SIZE), static_cast<int>(y * TILE_SIZE), TILE_SIZE, TILE_SIZE};
                wallRects.push_back(wallRect);
            }
        }
    }
}

const std::vector<SDL_Rect>& Map::getWallRects() const {
    return wallRects;
}

void Map::render(SDL_Renderer* renderer) {
    // Utilisez le renderer passé en paramètre plutôt que gRenderer
    for (size_t y = 0; y < mapData.size(); ++y) {
        for (size_t x = 0; x < mapData[y].size(); ++x) {
            SDL_Rect destRect = {static_cast<int>(x * TILE_SIZE), static_cast<int>(y * TILE_SIZE), TILE_SIZE, TILE_SIZE};       
            switch (mapData[y][x]) {
                case 0:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TEXTURE_RECT_1, &destRect);
                    break;
                case 1:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TEXTURE_RECT_2, &destRect);
                    break;
                case 2:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TEXTURE_RECT_3, &destRect);
                    break;
                case 3:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_1, &destRect);
                    break;
                case 4:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_2, &destRect);
                    break;
                case 5:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_3, &destRect);
                    break;
                case 6:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_4, &destRect);
                    break;
                case 7:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_5, &destRect);
                    break;
                case 8:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_6, &destRect);
                    break;
                case 9:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_7, &destRect);
                    break;
                case 10:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_8, &destRect);
                    break;
                case 11:
                    SDL_RenderCopy(renderer, dungeonFloorTexture, &TRAP_9, &destRect);
                    break;
                case 12:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &WALL_1, &destRect);
                    break;
                case 13:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &NONE, &destRect);
                    break;
                case 14:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &COIN, &destRect);
                    break;
                case 15:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &COIN_2, &destRect);
                    break;
                case 16:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &COIN_3, &destRect);
                    break;
                case 17:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &WALL_2, &destRect);
                    break;
                case 18:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &WALL_3, &destRect);
                    break;
                case 19:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &WALL_4, &destRect);
                    break;
                case 20:
                    SDL_RenderCopy(renderer, dungeonWallTexture, &WALL_5, &destRect);
                    break;



                default:
                    // Cas par défaut
                    break;
            }
        }
    }
}

