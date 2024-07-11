// #ifndef GAME_H_INCLUDED
// #define GAME_H_INCLUDED

// #include "includes.h"
#include <SDL2/SDL.h>

class Game
{
private:
    bool quit;
    const int width = 720, height = 720;
    SDL_Window *window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Surface * chessboardSurf = NULL;
    SDL_Surface * pawnSurf = NULL;
    SDL_Surface * squareSurf = NULL;
    // SDL_Surface * squareBad = NULL;
    SDL_Texture * chessboardTexture = NULL;
    SDL_Texture * pawnTexture = NULL;
    SDL_Texture * squareTexture = NULL;
    // SDL_Texture * squareBadTexture = NULL;
    SDL_Event WindowEvent;
    SDL_Rect pawnPos[8];
    SDL_Rect squarePos[2];

    unsigned int x, y, w = 70, h = 70;
    unsigned int oneMove = 82;
    unsigned int squareDist = 86;
    bool isPawnClicked = false;
    int pawnClicked = 0;

    // const Uint8 * keystate = SDL_GetKeyboardState(NULL);
    int mouseX, mouseY;

    bool isClicked(int pawnNo);
    bool isSquareFree(int i, int xPos, int yPos);

public:
    Game();
    ~Game();
    void initFun();
    void run();
};

// #endif