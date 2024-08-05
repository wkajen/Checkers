#include "game.h"
// #include "squares.h"
#include <SDL2/SDL.h>

Game::Game() {}

Game::~Game() 
{
    SDL_DestroyTexture(this->whitePawnTexture);
    SDL_DestroyTexture(this->blackPawnTexture);
    SDL_FreeSurface(this->whitePawnSurf);
    SDL_FreeSurface(this->blackPawnSurf);
    SDL_DestroyTexture(this->squareTexture);
    SDL_FreeSurface(this->squareSurf);
    SDL_DestroyTexture(this->chessboardTexture);
    SDL_FreeSurface(this->chessboardSurf);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
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
                    if( this->WindowEvent.button.button == SDL_BUTTON_LEFT)
                    {
                        if (this->isWhiteTurn)
                        {
                            for (int i = 0; i < 8; i++)
                            {
                                if (pawnClicked(i)) 
                                {
                                    squareDisp(i);
                                }
                            }
                        }
                        else
                        {
                            for (int i = 8; i < 16; i++)
                            {
                                if (pawnClicked(i)) 
                                {
                                    squareDisp(i);
                                }
                            }
                        }

                        pawnUpdate(this->pawnClickedNo);
                    }
                    
                // if( this->WindowEvent.key.keysym.sym == SDLK_ESCAPE ) this->quit = true;
            }
        }

        SDL_RenderClear(this->renderer);
        SDL_RenderCopy(this->renderer, this->chessboardTexture, NULL, NULL);
        for (int i = 0; i < 8; i++) 
        {
            SDL_RenderCopy(this->renderer, this->whitePawnTexture, NULL, &this->pawnPos[i]);
            SDL_RenderCopy(this->renderer, this->blackPawnTexture, NULL, &this->pawnPos[i+8]);
        }
        if(isPawnClicked) 
        {
            this->isUpdateReady = true;
            SDL_RenderCopy(this->renderer, this->squareTexture, NULL, &this->squarePos[0]);
            SDL_RenderCopy(this->renderer, this->squareTexture, NULL, &this->squarePos[1]);
        }
        SDL_RenderPresent(this->renderer);
    }
}

/*
int Game::isSquareFree_new(int pawnNo, bool isRight, bool backward)
{
    int xPos;
    int yPos; 
    if (!isRight)  // on the left
        xPos = this->pawnPos[pawnNo].x - this->oneMove;
    else    // on the right
        xPos = this->pawnPos[pawnNo].x + this->oneMove;
    if ( (this->isWhiteTurn && !backward) || (!this->isWhiteTurn && backward) )
        yPos = this->pawnPos[pawnNo].y - this->oneMove;
    else
        yPos = this->pawnPos[pawnNo].y + this->oneMove;

    if ( xPos > 10 && yPos > 10 && xPos < (this->width - this->oneMove) ) 
    {
        for (int sqrPos = 0; sqrPos < 32; sqrPos++) 
        {
            if (squares.squaresAll[sqrPos/4][sqrPos%4].x == xPos && squares.squaresAll[sqrPos/4][sqrPos%4].y == yPos)
            {
                if( (squares.squaresAll[sqrPos/4][sqrPos%4].occupied == 1 && this->isWhiteTurn) || (squares.squaresAll[sqrPos/4][sqrPos%4].occupied == 2 && !this->isWhiteTurn) )
                    return 0;
                else if ( (squares.squaresAll[sqrPos/4][sqrPos%4].occupied == 1 && !this->isWhiteTurn) || (squares.squaresAll[sqrPos/4][sqrPos%4].occupied == 2 && this->isWhiteTurn) )
                {
                    if (squares.squaresAll[sqrPos/4][sqrPos%4].occupied )// --------------------------
                    {
                        
                        return -1;
                    }
                    else
                        // this->isCapture = false;
                        return 0;
                    // return -1;
                }
                    
                else
                    return 1;
            }
        }
        return 1;
    }
    return 0;
}
*/


int Game::isSquareFree(int pawnNo, bool isRight)
{
    int xPos;
    int yPos; 
    if (!isRight)  // on the left
        xPos = this->pawnPos[pawnNo].x - this->oneMove;
    else    // on the right
        xPos = this->pawnPos[pawnNo].x + this->oneMove;
    if (this->isWhiteTurn)
        yPos = this->pawnPos[pawnNo].y - this->oneMove;
    else
        yPos = this->pawnPos[pawnNo].y + this->oneMove;

    if ( xPos > 10 && yPos > 10 && xPos < (this->width - this->oneMove) )  // *2
    {
        for (int j = 0; j < 8; j++) 
        {
            if (xPos == this->pawnPos[j].x && yPos == this->pawnPos[j].y)
            {
                if (this->isWhiteTurn)
                    return 0;
                else
                {
                    if (isSquareFree(j, isRight))
                    {
                        this->isCapture = true;
                        if (!isRight)
                            {this->newPosX = pawnPos[j].x - this->oneMove;}
                        else
                            {this->newPosX = pawnPos[j].x + this->oneMove;}
                        this->newPosY = pawnPos[j].y + this->oneMove;
                        return -1;
                    }
                    else
                        // this->isCapture = false;
                        return 0;
                }
            }
        }
        for (int j = 8; j < 16; j++) 
        {
            if (xPos == this->pawnPos[j].x && yPos == this->pawnPos[j].y)
            {
                if (this->isWhiteTurn)
                {
                    if (isSquareFree(j, isRight))
                    {
                        this->isCapture = true;
                        if (!isRight)
                            {this->newPosX = pawnPos[j].x - this->oneMove;}
                        else
                            {this->newPosX = pawnPos[j].x + this->oneMove;}
                        this->newPosY = pawnPos[j].y - this->oneMove;
                        return -1;
                    }
                    else
                        return 0;
                }
                else
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}


bool Game::pawnClicked(int no)
{
    if( ( this->mouseX >= this->pawnPos[no].x && this->mouseX <= this->pawnPos[no].x + this->pawnPos[no].w ) &&
    ( this->mouseY >= this->pawnPos[no].y && this->mouseY <= this->pawnPos[no].y + this->pawnPos[no].h ) )
    {
        if (this->isPawnClicked == true) 
        {
            this->isPawnClicked = false;
            pawnClickedNo = -1;
            this->isUpdateReady = false;
        }
        else 
        {
            this->isPawnClicked = true;
            pawnClickedNo = no;
            
        }
        // std::cout << pawnClickedNo << std::endl;  //just for debugging
        return true;
    }    
    return false;
}


void Game::squareDisp_new(int pawnNo)
{
    int row;
    int col;
    for (int i = 0; i < 32; i++)
    {
        if (pawnPos[pawnNo].x == squares.squaresAll[i/4][i%4].x && pawnPos[pawnNo].y == squares.squaresAll[i/4][i%4].y)
        {
            row = i/4;
            col = i%4;
        }
    }

    int sqrNo = 0;

    if (this->isWhiteTurn)
    {
        int currOccupant = 1;
        // square on the left
        if (col > 0)
            currOccupant = squares.squaresAll[row+1][col-1].occupied;
        else if (row % 2 == 1)
            {currOccupant = (squares.squaresAll[row+1][col].occupied);}

        switch (currOccupant)
        {
            case 0: // square free
            {
                this->squarePos[sqrNo].w = this->oneMove;
                this->squarePos[sqrNo].h = this->oneMove;
                this->squarePos[sqrNo].x = squares.squaresAll[row][col].x - 5;
                this->squarePos[sqrNo].y = squares.squaresAll[row][col].y - 10;
                break;
            }
            case 2: // enemy
            {
                
                break;
            }
            default: // no work
            {
                break;
            }
        }
    }
    
  
}
// ======================================



void Game::squareDisp(int pawnNo)
{
    this->squarePos[0].w = this->oneMove;
    this->squarePos[0].h = this->oneMove;
    this->squarePos[1].w = this->oneMove;
    this->squarePos[1].h = this->oneMove;

    // square on the left    (int pawnNo, bool isRight, bool backward)
    switch ( isSquareFree(pawnNo, false) )
    {
    case 1:     // left square is free
        this->squarePos[0].x = this->pawnPos[pawnNo].x - 87; 
        if (pawnNo < 8)
            this->squarePos[0].y = this->pawnPos[pawnNo].y - 92;
        else
            this->squarePos[0].y = this->pawnPos[pawnNo].y + 71;
        break;

    case -1:    // there is an oppponent on the left square
        this->squarePos[0].x = this->pawnPos[pawnNo].x - (this->oneMove + 87); 
        if (pawnNo < 8)
            this->squarePos[0].y = this->pawnPos[pawnNo].y - (this->oneMove + 92);
        else
            this->squarePos[0].y = this->pawnPos[pawnNo].y + (this->oneMove + 71);
        break;
    
    default:    // left square is already occupied
        this->squarePos[0].w = 0;
        this->squarePos[0].h = 0;  
        break;
    }

    // square on the right
    switch ( isSquareFree(pawnNo, true) )
    {
    case 1:     // right square is free
        this->squarePos[1].x = this->pawnPos[pawnNo].x + 77; 
        if (pawnNo < 8)
            this->squarePos[1].y = this->pawnPos[pawnNo].y - 92;
        else
            this->squarePos[1].y = this->pawnPos[pawnNo].y + 71;
        break;

    case -1:    // there is an oppponent on the right square
        this->squarePos[1].x = this->pawnPos[pawnNo].x + (this->oneMove + 77); 
        if (pawnNo < 8)
            this->squarePos[1].y = this->pawnPos[pawnNo].y - (this->oneMove + 92);
        else
            this->squarePos[1].y = this->pawnPos[pawnNo].y + (this->oneMove + 71);
        break;
    
    default:    // right square is already occupied
        this->squarePos[1].w = 0;
        this->squarePos[1].h = 0;  
        break;
    }

}

void Game::pawnUpdate_2(int pawnNo)
{
    if (this->isUpdateReady && this->isPawnClicked && pawnNo >= 0)
    {
        for (int no = 0; no < 2; no++)
        {
            if( ( this->mouseX >= this->squarePos[no].x && this->mouseX <= this->squarePos[no].x + this->squarePos[no].w ) &&
            ( this->mouseY >= this->squarePos[no].y && this->mouseY <= this->squarePos[no].y + this->squarePos[no].h ) )
            {
                this->pawnPos[pawnNo].x = this->squarePos[no].x + 5;   // <------------------------------------------------  here TODO
                this->pawnPos[pawnNo].y = this->squarePos[no].y + 10;

                if (this->isWhiteTurn)
                    {this->isWhiteTurn = false;}
                else
                    {this->isWhiteTurn = true;}
                this->isPawnClicked = false;
                this->pawnClickedNo = -1;
                
            }
        }
        
    }
}

void Game::pawnUpdate(int pawnNo)
{
    if (this->isUpdateReady && this->isPawnClicked && pawnNo >= 0)
    {
        for (int no = 0; no < 2; no++)
        {
            if( ( this->mouseX >= this->squarePos[no].x && this->mouseX <= this->squarePos[no].x + this->squarePos[no].w ) &&
            ( this->mouseY >= this->squarePos[no].y && this->mouseY <= this->squarePos[no].y + this->squarePos[no].h ) )
            {
                if (this->isWhiteTurn)
                {
                    if (this->mouseX < this->pawnPos[pawnNo].x)
                    {
                        this->pawnPos[pawnNo].x -= this->oneMove;
                        this->pawnPos[pawnNo].y -= this->oneMove;

                    }
                    else if (this->mouseX > this->pawnPos[pawnNo].x)
                    {
                        this->pawnPos[pawnNo].x += this->oneMove;
                        this->pawnPos[pawnNo].y -= this->oneMove;

                    }
                    this->isWhiteTurn = false;
                }
                else
                {
                    if (this->mouseX < this->pawnPos[pawnNo].x)
                    {
                        this->pawnPos[pawnNo].x -= this->oneMove;
                        this->pawnPos[pawnNo].y += this->oneMove;
                        // this->isPawnClicked = false;
                        // this->pawnClickedNo = -1;
                    }
                    else if (this->mouseX > this->pawnPos[pawnNo].x)
                    {
                        this->pawnPos[pawnNo].x += this->oneMove;
                        this->pawnPos[pawnNo].y += this->oneMove;
                        // this->isPawnClicked = false;
                        // this->pawnClickedNo = -1;
                    }
                    this->isWhiteTurn = true;
                }

                this->isPawnClicked = false;
                this->pawnClickedNo = -1;
                
            }
        }
        
    }
}
