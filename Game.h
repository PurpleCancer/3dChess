//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_GAME_H
#define INC_3DCHESS_GAME_H

#include <string>
#include "Board.h"
#include "Delarations.h"

using namespace std;

class Game {
public:
    void Print();

    Game();

private:
    string event="";
    string date="";
    string result="";
    string white="";
    string black="";
    Board* board;
};


#endif //INC_3DCHESS_GAME_H
