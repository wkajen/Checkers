// #include <includes.h>
#include "game.h"
#include <SDL2/SDL.h>
#include <iostream>

Game::Game() {}

Game::~Game() 
{
    SDL_DestroyTexture(this->pawnTexture);
    SDL_FreeSurface(this->pawnSurf);
    SDL_DestroyTexture(this->squareTexture);
    SDL_FreeSurface(this->squareSurf);
    SDL_DestroyTexture(this->chessboardTexture);
    SDL_FreeSurface(this->chessboardSurf);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}

void Game::initFun()
{
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

    this->x = 37; //200;
    this->y = 616;
    // this->oneMove = 82;

    // this->pawnSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/black_pawn.bmp", "rb"), 1);
    this->pawnSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/white_pawn.bmp", "rb"), 1);
    this->pawnTexture = SDL_CreateTextureFromSurface(this->renderer, this->pawnSurf);
    for (int i = 0; i < 8; i++)
    {
        this->pawnPos[i].x = x + i*this->oneMove; 
        if (i%2 == 0) this->pawnPos[i].y = y; 
        else this->pawnPos[i].y = y - this->oneMove; 
        this->pawnPos[i].w = w;  
        this->pawnPos[i].h = h;
    }
    this->squareSurf = SDL_LoadBMP_RW(SDL_RWFromFile("img/square.bmp", "rb"), 1);
    this->squareTexture = SDL_CreateTextureFromSurface(this->renderer, this->squareSurf);
    this->squarePos[0].x = this->pawnPos[1].x - this->squareDist; 
    this->squarePos[0].y = this->pawnPos[1].y - (this->squareDist + 5);
    this->squarePos[0].w = 80;
    this->squarePos[0].h = 81;

    this->squarePos[1].x = this->pawnPos[1].x + (this->squareDist - 8); 
    this->squarePos[1].y = this->pawnPos[1].y - (this->squareDist + 5);
    this->squarePos[1].w = 80;
    this->squarePos[1].h = 81;

}

void Game::run()
{
    while (!this->quit)
    {
        while ((SDL_PollEvent(&this->WindowEvent)) != 0)
        {
            switch(this->WindowEvent.type)
            {
                case SDL_QUIT:
                    this->quit = true;
                    break;

                case SDL_MOUSEMOTION:  //save current mouse coordinates
                    this->mouseX = this->WindowEvent.motion.x;
                    this->mouseY = this->WindowEvent.motion.y;

                case SDL_MOUSEBUTTONDOWN:  //loop only when button is pressed

                    for (int i = 0; i < 8; i++)
                    {
                        if (isClicked(i)) 
                        {
                                // this->pawnClicked = i;
                            // square on the left
                            this->squarePos[0].x = this->pawnPos[i].x - 87; 
                            this->squarePos[0].y = this->pawnPos[i].y - 91;
                            if ( isSquareFree(i, this->pawnPos[i].x - this->oneMove, this->pawnPos[i].y - this->oneMove) )
                            {
                                this->squarePos[0].w = this->oneMove;
                                this->squarePos[0].h = this->oneMove;
                            }
                            else
                            {
                                this->squarePos[0].w = 0;
                                this->squarePos[0].h = 0;          
                            }
                            
                            // square on the right
                            this->squarePos[1].x = this->pawnPos[i].x + 77; 
                            this->squarePos[1].y = this->pawnPos[i].y - 91;
                            if ( isSquareFree(i, this->pawnPos[i].x + this->oneMove, this->pawnPos[i].y - this->oneMove) )
                            {
                                this->squarePos[1].w = this->oneMove;
                                this->squarePos[1].h = this->oneMove;
                            }
                            else
                            {
                                this->squarePos[1].w = 0;
                                this->squarePos[1].h = 0;          
                            }                            

                        }
                    }

                // if( this->WindowEvent.key.keysym.sym == SDLK_ESCAPE ) this->quit = true;
            }

        }

        SDL_RenderClear(this->renderer);
        SDL_RenderCopy(this->renderer, this->chessboardTexture, NULL, NULL);
        for (int i = 0; i < 8; i++) 
        {
            SDL_RenderCopy(this->renderer, this->pawnTexture, NULL, &this->pawnPos[i]);
        }
        if(isPawnClicked) 
        {
            SDL_RenderCopy(this->renderer, this->squareTexture, NULL, &this->squarePos[0]);
            SDL_RenderCopy(this->renderer, this->squareTexture, NULL, &this->squarePos[1]);
        }
        SDL_RenderPresent(this->renderer);
    }
}

bool Game::isSquareFree(int i, int xPos, int yPos)
{
    if ( xPos > 10 && xPos < (this->width - this->oneMove) )  // *2
    {
        for (int j = 0; j < 8; j++) 
        {
            if (xPos == this->pawnPos[j].x && yPos == this->pawnPos[j].y )
            {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Game::isClicked(int no)
{
    if( this->WindowEvent.button.button == SDL_BUTTON_LEFT && ( this->mouseX >= this->pawnPos[no].x && this->mouseX <= this->pawnPos[no].x + this->pawnPos[no].w ) &&
    ( this->mouseY >= this->pawnPos[no].y && this->mouseY <= this->pawnPos[no].y + this->pawnPos[no].h ) )
        if (this->isPawnClicked) 
        {
            this->isPawnClicked = false;
            return true;
        }
        else 
        {
            this->isPawnClicked = true;
            return true;
        }
        
    else 
        return false;
}

