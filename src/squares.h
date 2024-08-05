#include <unordered_map>
#include <tuple>

struct PosXY
{
    int x;
    int y;
    int occupied;
};


class Squares
{
    // void initAllPawns();

    PosXY whitePawns[8];
    PosXY blackPawns[8];

public:
    void initAllSquares();
    void setPawnPos(int pawnNo, int pawnX, int pawnY, int color);
    void getPawnNo(int pawnX, int pawnY);
    // int getPawnPosX(int pawnNo);
    // int getPawnPosY(int pawnNo);
    PosXY squaresAll[8][4];

};