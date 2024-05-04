all:
	g++ -Isrc/Include -Lsrc/lib -o main main.cpp -Lmingw32 -LSDL2main -lSDL2