//
// Created by Jan on 24.03.2016.
//

#ifndef INC_3DCHESS_GAME_H
#define INC_3DCHESS_GAME_H

#include <string>
#include "Board.h"
#include "Reader.h"
#include "Delarations.h"

using namespace std;

class Game {
public:
    void Print();
    void Move(const string s);

    Game(string name);
    ~Game();
private:
    string event="";
    string site="";
    string date="";
    string result="";
    string white="";
    string black="";
    Board* board;
    Reader* reader;
    Game();
};


#endif //INC_3DCHESS_GAME_H
