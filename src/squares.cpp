#include "squares.h"

// Squares::Squares() {}
// Squares::~Squares() {}

void Squares::initAllSquares()
{
    int x = 37;
    int y = 616;
    for (int i = 0; i < 8; i++)
    {
        if (i % 2 == 0)
            { x = 37; }
        else
            { x = 119; }

        for (int j = 0; j < 4; j++)
        {
            if (i < 2)
                { squaresAll[i][j].occupied = 1; }
            else if (i > 5)
                { squaresAll[i][j].occupied = 2; }
            else
                { squaresAll[i][j].occupied = 0; }
            
            squaresAll[i][j].x = x + j*82*2;
            squaresAll[i][j].y = y;
        }
        y -= 82;
    }
}

void Squares::setPawnPos(int pawnNo, int pawnX, int pawnY, int color)
{
    if (color == 1)  //white
    {
        whitePawns[pawnNo].x = pawnX;
        whitePawns[pawnNo].y = pawnY;
    }
    else
    {
        blackPawns[pawnNo].x = pawnX;
        blackPawns[pawnNo].y = pawnY;
    }
}

void Squares::getPawnNo(int pawnX, int pawnY)
{
    
}
