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
    void FindPieceToMove(PieceType type, int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot);
    void FindPieceToTake(int targetColumn, int targetRow);

    Player(Colour colour);
    ~Player();
private:
    Player();
    int AbsoluteInt(int x);
    Colour colour;
    vector <Piece> myPieces;
};


#endif //INC_3DCHESS_PLAYER_H
