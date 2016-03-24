//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_PLAYER_H
#define INC_3DCHESS_PLAYER_H

#include "Piece.h"
#include <vector>

using namespace std;

enum Colour {White, Black};

struct Tile
{
    Colour colour;
    PieceType type;
};

class Player {
public:
    void PleaseCompleteTheSnapshot(Tile** snap);
    Player(Colour colour);
private:
    Player();
    Colour colour;
    vector <Piece> myPieces;
};


#endif //INC_3DCHESS_PLAYER_H
