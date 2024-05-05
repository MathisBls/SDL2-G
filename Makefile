all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp player.cpp -Lmingw32 -LSDL2main -lSDL2