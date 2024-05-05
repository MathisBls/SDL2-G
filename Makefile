all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp player.cpp map.cpp -Lmingw32 -LSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image