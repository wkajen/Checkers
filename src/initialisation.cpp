#include "game.h"
// #include "squares.h"
#include <SDL2/SDL.h>
#include <iostream>

void Game::initFun()
{
    // SDL beginning initialisation
    this->quit = false;
    SDL_Init(SDL_INIT_VIDEO);
    this->window = SDL_CreateWindow("Checkers", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, this->width, this->height, 0);  // 0 -> SDL_WINDOW_ALLOW_HIGHDPI);
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);

    if (NULL == this->window)
    {
        std::cout << "Cannot create window" << SDL_GetError() << std::endl;
        // return 1;
    }

    this->chessboardSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/chessboard.bmp", "rb"), 1);
    this->chessboardTexture = SDL_CreateTextureFromSurface(this->renderer, this->chessboardSurf);

    // // SDL beginning initialisation  ----- end

    // Squares squares;
    squares.initAllSquares();

    this->x = 37; //200;
    this->y_white = 616;
    this->y_black = 124;
    // this->oneMove = 82;

    // white pawns
    this->whitePawnSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/white_pawn.bmp", "rb"), 1);
    this->whitePawnTexture = SDL_CreateTextureFromSurface(this->renderer, this->whitePawnSurf);
    // black pawns
    this->blackPawnSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/black_pawn.bmp", "rb"), 1);
    this->blackPawnTexture = SDL_CreateTextureFromSurface(this->renderer, this->blackPawnSurf);

    int whiteCnt = 0;
    int blackCnt = 8;
    for (int i = 0; i < 32; i++)
    {

        if (squares.squaresAll[i/4][i%4].occupied == 1)
        {
            this->pawnPos[whiteCnt].x = squares.squaresAll[i/4][i%4].x;
            this->pawnPos[whiteCnt].y = squares.squaresAll[i/4][i%4].y;
            this->pawnPos[whiteCnt].w = this->w;  
            this->pawnPos[whiteCnt].h = this->h;
            squares.setPawnPos(whiteCnt, squares.squaresAll[i/4][i%4].x, squares.squaresAll[i/4][i%4].y, 1);
            whiteCnt++;
        }
        else if (squares.squaresAll[i/4][i%4].occupied == 2)
        {
            this->pawnPos[blackCnt].x = squares.squaresAll[i/4][i%4].x;
            this->pawnPos[blackCnt].y = squares.squaresAll[i/4][i%4].y;
            this->pawnPos[blackCnt].w = this->w-3;  
            this->pawnPos[blackCnt].h = this->h-3;
            squares.setPawnPos((blackCnt-8), squares.squaresAll[i/4][i%4].x, squares.squaresAll[i/4][i%4].y, 2);
            blackCnt++;
        }
        
    }

    // squares -> possible moves
    this->squareSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/square.bmp", "rb"), 1);
    this->squareTexture = SDL_CreateTextureFromSurface(this->renderer, this->squareSurf);

}
