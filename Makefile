all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp player.cpp map.cpp coin.cpp game.cpp enemy.cpp enemyManager.cpp -Lmingw32 -LSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image