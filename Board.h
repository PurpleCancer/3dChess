//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_BOARD_H
#define INC_3DCHESS_BOARD_H

#include <string>
#include <iostream>
#include <regex>
#include "Player.h"
#include "Declarations.h"

using namespace std;

class Board {
public:
    void UpdateSnapshot();
    void Print();
    Pole Move(const string s);
    Tile** getBoardSnapshot();

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
