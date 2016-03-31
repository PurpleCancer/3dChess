//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_BOARD_H
#define INC_3DCHESS_BOARD_H

#include <string>
#include <iostream>
#include <regex>
#include "Player.h"
#include "Delarations.h"

using namespace std;

class Board {
public:
    void Print();
    void Move(const string s);

    Board();
    ~Board();
private:
    Player* whitePlayer;
    Player* blackPlayer;
    Colour turn;
    Tile** boardSnapshot;
    regex* pattern;
};


#endif //INC_3DCHESS_BOARD_H
