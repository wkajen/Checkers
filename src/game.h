// #ifndef GAME_H_INCLUDED
// #define GAME_H_INCLUDED

#include <SDL2/SDL.h>
#include "squares.h"

class Game
{
private:
    bool quit;
    const int width = 720, height = 720;
    SDL_Window *window = NULL;
    SDL_Renderer * renderer = NULL;
    SDL_Surface * chessboardSurf = NULL;
    SDL_Surface * whitePawnSurf = NULL;
    SDL_Surface * blackPawnSurf = NULL;
    SDL_Surface * squareSurf = NULL;
    // SDL_Surface * squareBad = NULL;
    SDL_Texture * chessboardTexture = NULL;
    SDL_Texture * whitePawnTexture = NULL;
    SDL_Texture * blackPawnTexture = NULL;
    SDL_Texture * squareTexture = NULL;
    // SDL_Texture * squareBadTexture = NULL;
    SDL_Event WindowEvent;
    SDL_Rect pawnPos[16];
    SDL_Rect squarePos[4];  // 2

    unsigned int x, y_white, y_black, w = 70, h = 70;
    unsigned int oneMove = 82;
    unsigned int squareDist = 86;
    bool isPawnClicked = false;
    bool isUpdateReady = false;
    int pawnClickedNo = -1;
    bool isWhiteTurn = true;
    bool isCapture = false;
    int pawnCapturedNo = -1; 

    int newPosX = 0;
    int newPosY = 0;

    // const Uint8 * keystate = SDL_GetKeyboardState(NULL);
    int mouseX, mouseY;

    // void initAllSquares();
    // PosXY squaresAll[32];
    // PosXY whitePawns[8];
    // PosXY blackPawns[8];
    bool pawnClicked(int pawnNo);
    void pawnUpdate_2(int pawnNo);
    void pawnUpdate(int pawnNo);
    void squareDisp(int pawnNo);
    void squareDisp_new(int pawnNo);
    int isSquareFree(int pawnNo, bool dir);
    // int isSquareFree_new(int i, bool isRight, bool backward);

    Squares squares;

public:
    Game();
    ~Game();
    void initFun();
    void run();

};

// #endif