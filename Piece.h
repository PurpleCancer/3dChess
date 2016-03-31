//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_PIECE_H
#define INC_3DCHESS_PIECE_H

#include "Delarations.h"

class Piece {
public:
    int getColumn();
    int getRow();
    PieceType getType();

    Piece(PieceType type, int column, int row);
    ~Piece();
private:
    PieceType type;
    int column;
    int row;
    Piece();
};


#endif //INC_3DCHESS_PIECE_H
