#include "coin.h"
#include <vector>

class Game {
    public:
        Game();
        void loadTextures();
        void generateCoins();
        const std::vector<Coin>& getCoins() const;

    private:
        std::vector<Coin> mCoins;
        SDL_Texture* mCoinTexture;
};