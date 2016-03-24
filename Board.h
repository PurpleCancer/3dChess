//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_BOARD_H
#define INC_3DCHESS_BOARD_H

#include "Player.h"

class Board {
public:
    void Print();

    Board();
private:
    Player* whitePlayer;
    Player* blackPlayer;
    Colour turn;
    Tile** boardSnapshot;
};


#endif //INC_3DCHESS_BOARD_H
