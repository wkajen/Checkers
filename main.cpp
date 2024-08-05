// #include <SDL2/SDL.h>
#include "src/game.h"
// #include "src/squares.h"

int main(int argc, char *argv[])
{
    Game checkers;
    checkers.initFun();
    checkers.run();
    // checkers.~Game();
    return 0; //EXIT_SUCCESS;
}