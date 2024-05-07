#include "enemyManager.h"
#include "enemy.h"
#include <cstdlib>

void EnemyManager::generateRandomEnemies(int numEnemies, int minX, int minY, int maxX, int maxY) {
    mEnemies.clear();
    for(int i = 0; i <numEnemies; i++)
    {
        int x = rand() % (maxX - minX) + minX;
        int y = rand() % (maxY - minY) + minY;
        int size = rand() % 20 + 10;
        mEnemies.push_back(Enemy(x, y, 20));
    
    }
}

void EnemyManager::renderer(SDL_Renderer* renderer) {
    for (auto& enemy : mEnemies) {
        enemy.renderer(renderer);
    }
}