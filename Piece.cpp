//
// Created by Jan on 24.03.2016.
//

#include "Piece.h"

int Piece::getColumn()
{
    return column;
}

int Piece::getRow()
{
    return row;
}

PieceType Piece::getType()
{
    return type;
}

Piece::Piece(PieceType type, int column , int row)
{
    this->type = type;
    this->column = column;
    this->row = row;
}