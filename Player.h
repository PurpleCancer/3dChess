//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_PLAYER_H
#define INC_3DCHESS_PLAYER_H

#include <vector>
#include <iostream>
#include "Piece.h"
#include "Declarations.h"

using namespace std;

class Player {
public:
    void PleaseCompleteTheSnapshot(Tile** snap);
    void FindPieceToMove(PieceType type, int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot);
    void FindPieceToTake(int targetColumn, int targetRow);
    void KingsideCastling();
    void QueensideCastling();
    void MovePawnAndPromote(PieceType type, int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot, PieceType promotion);

    Player(Colour colour);
    ~Player();
private:
    Player();
    int AbsoluteInt(int x);
    bool CanMoveDiagonally(int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot);
    bool CanMoveHorizontally(int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot);
    bool CanMoveVertically(int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot);
    bool CanKnightMove(int startColumn, int startRow, int targetColumn, int targetRow);
    bool CanPawnMove(int startColumn, int startRow, int targetColumn, int targetRow, Tile** boardSnapshot);
    bool CanPawnTake(int startRow, int targetRow);
    Colour colour;
    vector <Piece> myPieces;
};


#endif //INC_3DCHESS_PLAYER_H
