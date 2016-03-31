//
// Created by Jan on 31.03.2016.
//

#ifndef INC_3DCHESS_READER_H
#define INC_3DCHESS_READER_H

#include <string>
#include <fstream>
#include "Delarations.h"

using namespace std;

class Reader {
public:
    Reader(string name);
    ~Reader();

private:
    string event="";
    string site="";
    string date="";
    string result="";
    string white="";
    string black="";
    ifstream file;

    Reader();
};


#endif //INC_3DCHESS_READER_H
