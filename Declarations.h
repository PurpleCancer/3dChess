//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_DELARATIONS_H
#define INC_3DCHESS_DELARATIONS_H

#define BOARD_HEIGHT 8
#define BOARD_WIDTH 8


enum Colour { White, Black };

enum PieceType { None, Pawn, Rook, Knight, Bishop, Queen, King };

struct Tile
{
    Colour colour;
    PieceType type;
};


struct Model3D{
    float vertices[];
    float normals[];
    float vertexNormals[];
    float texCoords[];
    float colors[];
};

#endif //INC_3DCHESS_DELARATIONS_H
