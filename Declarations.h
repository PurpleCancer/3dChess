//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_DELARATIONS_H
#define INC_3DCHESS_DELARATIONS_H

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8

#include <glm/detail/type_vec.hpp>
#include "Constants.h"


enum Colour {
    White=0,
    Black=1,
};

enum PieceType {
    Pawn=0,
    Rook=1,
    Knight=2,
    Bishop=3,
    Queen=4,
    King=5,
    None,
};

struct Tile
{
    Colour colour;
    PieceType type;
};

struct OBJModel{
    float *vertices;
    float *normals;
    float *texcoords;
    int vertexCount;
};

enum textureEnum {
    white=0,
    black=1,
    board=2,
    boardSides=3,
    boardBottom=4,

};







#endif //INC_3DCHESS_DELARATIONS_H
