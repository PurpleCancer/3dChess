//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_DELARATIONS_H
#define INC_3DCHESS_DELARATIONS_H

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8


enum Colour { White, Black };

enum PieceType { Pawn, Rook, Knight, Bishop, Queen, King, None };

struct Tile
{
    Colour colour;
    PieceType type;
};

#endif //INC_3DCHESS_DELARATIONS_H
