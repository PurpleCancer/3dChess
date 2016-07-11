//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_PIECE_H
#define INC_3DCHESS_PIECE_H

#include "Declarations.h"

class Piece {
public:
    int getColumn();
    int getRow();
    PieceType getType();

    void setColumn(int column);
    void setRow(int row);
    void setType(PieceType type);

    Piece(PieceType type, int column, int row);
    ~Piece();
private:
    PieceType type;
    int column;
    int row;
    Piece();
};


#endif //INC_3DCHESS_PIECE_H
