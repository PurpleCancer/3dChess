//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_PLAYER_H
#define INC_3DCHESS_PLAYER_H

#include <vector>
#include <iostream>
#include "Piece.h"
#include "Delarations.h"

using namespace std;

class Player {
public:
    void PleaseCompleteTheSnapshot(Tile** snap);

    Player(Colour colour);
    ~Player();
private:
    Player();
    Colour colour;
    vector <Piece> myPieces;
};


#endif //INC_3DCHESS_PLAYER_H
