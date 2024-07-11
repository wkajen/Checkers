all:
	g++ -I src/include -L src/lib -o game main.cpp src/game.cpp -lmingw32 -lSDL2main -lSDL2