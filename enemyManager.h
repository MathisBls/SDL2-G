#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "enemy.h"
#include <vector>

class EnemyManager {
    public:
        EnemyManager() {}

        void generateRandomEnemies(int numEnemies, int minX, int minY, int maxX, int maxY);

        void renderer(SDL_Renderer* renderer);

    private:
        std::vector<Enemy> mEnemies;
};

#endif